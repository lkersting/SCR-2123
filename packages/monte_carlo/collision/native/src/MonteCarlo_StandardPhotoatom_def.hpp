//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The standard photoatom class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOM_DEF_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOM_DEF_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
StandardPhotoatom<InterpPolicy,processed_cross_section>::StandardPhotoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Photoatom::ReactionMap& standard_scattering_reactions,
	  const Photoatom::ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model )
  : Photoatom( name,
	       atomic_number,
	       standard_scattering_reactions,
	       standard_absorption_reactions,
	       atomic_relaxation_model ),
    d_energy_grid( energy_grid ),
    d_total_cross_section(),
    d_absorption_cross_section(),
    d_total_threshold_energy_index( 0u ),
    d_absorption_threshold_energy_index( 0u )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Calculate the total absorption cross section
  calculateTotalAbsorptionCrossSection();

  // Calculate the total cross section
  calculateTotalCrossSection();  
}

// Constructor
template<typename InterpPolicy>
StandardPhotoatom<InterpPolicy,false>::StandardPhotoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Photoatom::ReactionMap& standard_scattering_reactions,
	  const Photoatom::ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model )
  : Photoatom( name,
	       atomic_number,
	       standard_scattering_reactions,
	       standard_absorption_reactions,
	       atomic_relaxation_model ),
    d_energy_grid( energy_grid ),
    d_total_cross_section( energy_grid.size() ),
    d_absorption_cross_section( energy_grid.size() )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Calculate the total absorption cross section
  calculateTotalAbsorptionCrossSection();

  // Calculate the total cross section
  calculateTotalCrossSection();  
}

// Return the total cross section at the desired energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardPhotoatom<InterpPolicy,processed_cross_section>::getTotalCrossSection( const double energy ) const
{
  return getCrossSection( energy, 
			  d_total_cross_section,
			  d_total_threshold_energy_index );
}

// Return the total cross section at the desired energy
template<typename InterpPolicy>
double StandardPhotoatom<InterpPolicy,false>::getTotalCrossSection( const double energy ) const
{
  return getCrossSection( energy, d_total_cross_section );
}

// Return the total absorption cross section at the desired energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardPhotoatom<InterpPolicy,processed_cross_section>::getAbsorptionCrossSection( const double energy ) const
{
  return getCrossSection( energy, 
			  d_absorption_cross_section,
			  d_absorption_threshold_energy_index );
}

// Return the total absorption cross section at the desired energy
template<typename InterpPolicy>
double StandardPhotoatom<InterpPolicy,false>::getAbsorptionCrossSection( const double energy ) const
{
  return getCrossSection( energy, d_absorption_cross_section );
}

// Return the cross section at the desired energy
template<typename InterpPolicy, bool processed_cross_section>
inline double StandardPhotoatom<InterpPolicy,processed_cross_section>::getCrossSection( 
			    const double energy,
			    const Teuchos::Array<double>& cross_section,
			    const unsigned threshold_index ) const
{
  double cross_section_value;
  
  double processed_energy = InterpPolicy::processIndepVar( energy );

  if( processed_energy >= d_energy_grid[threshold_index] &&
      processed_energy < d_energy_grid[d_energy_grid.size()-1] )
  {
    unsigned energy_index = 
      Utility::Search::binaryLowerBoundIndex( d_energy_grid.begin(),
					      d_energy_grid.end(),
					      processed_energy );

    unsigned cs_index = energy_index - threshold_index;

    double processed_slope = 
      (cross_section[cs_index+1]-cross_section[cs_index])/
      (d_energy_grid[energy_index+1]-d_energy_grid[energy_index]);

    cross_section_value = 
      InterpPolicy::interpolate( d_energy_grid[energy_index],
				 processed_energy,
				 cross_section[cs_index],
				 processed_slope );
  }
  else if( processed_energy < d_energy_grid[threshold_index] )
    cross_section_value = 0.0;
  else if( processed_energy == d_energy_grid[d_energy_grid.size()-1] )
  {
    cross_section_value = 
      InterpPolicy::recoverProcessedDepVar( cross_section.back() );
  }
  else // energy > max grid energy
    cross_section_value = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section_value >= 0.0 );

  return cross_section_value;
}

// Return the cross section at the desired energy
template<typename InterpPolicy>
inline double StandardPhotoatom<InterpPolicy,false>::getCrossSection( 
			    const double energy,
			    const Teuchos::Array<double>& cross_section ) const
{
  double cross_section_value;
  
  if( energy >= d_energy_grid[0] &&
      energy < d_energy_grid[d_energy_grid.size()-1] )
  {
    unsigned index = 
      Utility::Search::binaryLowerBoundIndex( d_energy_grid.begin(),
					      d_energy_grid.end(),
					      energy );

    cross_section_value =
      InterpPolicy::interpolate( d_energy_grid[index],
				 d_energy_grid[index+1],
				 energy,
				 cross_section[index],
				 cross_section[index+1] );
  }
  else if( energy < d_energy_grid[0] )
    cross_section_value = 0.0;
  else if( energy == d_energy_grid[d_energy_grid.size()-1] )
    cross_section_value = cross_section.back();
  else // energy > max grid energy
    cross_section_value = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section_value >= 0.0 );

  return cross_section_value;
}

// Calculate the total absorption cross section
template<typename InterpPolicy, bool processed_cross_section>
void StandardPhotoatom<InterpPolicy,processed_cross_section>::calculateTotalAbsorptionCrossSection()
{
  // Make sure the energy grid is valid
  testPrecondition( d_energy_grid.size() > 1 );
  // Make sure the absorption cross section is sized correctly
  testPrecondition( d_absorption_cross_section.size() == 0 );
  // Make sure the threshold index has been initialized
  testPrecondition( d_absorption_threshold_energy_index == 0u );

  Photoatom::ReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < d_energy_grid.size(); ++i )
  {
    absorption_reaction = getAbsorptionReactions().begin();

    double raw_cross_section = 0.0;
    
    const double raw_energy = 
      InterpPolicy::recoverProcessedIndepVar( d_energy_grid[i] );

    while( absorption_reaction != getAbsorptionReactions().end() )
    {
      raw_cross_section += 
	absorption_reaction->second->getCrossSection( raw_energy );

      ++absorption_reaction;
    }
    
    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      d_absorption_cross_section.push_back( 
			    InterpPolicy::processDepVar( raw_cross_section ) );
    }
    else
    {
      // Ignore this data point
      ++d_absorption_threshold_energy_index;
    }
  }
  
  // Make sure the absorption cross section is valid
  remember( Teuchos::Array<double>::const_iterator zero_element = 
	    std::find( d_absorption_cross_section.begin(),
		       d_absorption_cross_section.end(),
		       0.0 ) );
  testPostcondition( zero_element == d_absorption_cross_section.end() );
  remember( Teuchos::Array<double>::const_iterator inf_element = 
	    std::find( d_absorption_cross_section.begin(),
		       d_absorption_cross_section.end(),
		       std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == d_absorption_cross_section.end() );
}

// Calculate the total absorption cross section
template<typename InterpPolicy>
void StandardPhotoatom<InterpPolicy,false>::calculateTotalAbsorptionCrossSection()
{
  // Make sure the absorption cross section is sized correctly
  testPrecondition( d_absorption_cross_section.size() == 
		    d_energy_grid.size() );

  Photoatom::ReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < d_absorption_cross_section.size(); ++i )
  {
    absorption_reaction = getAbsorptionReactions().begin();

    d_absorption_cross_section[i] = 0.0;
    
    while( absorption_reaction != getAbsorptionReactions().end() )
    {
      d_absorption_cross_section[i] +=
	absorption_reaction->second->getCrossSection( d_energy_grid[i] );

      ++absorption_reaction;
    }
  }
}

// Calculate the total cross section
template<typename InterpPolicy, bool processed_cross_section>
void StandardPhotoatom<InterpPolicy,processed_cross_section>::calculateTotalCrossSection()
{
  // Make sure the energy grid is valid
  testPrecondition( d_energy_grid.size() > 1 );
  // Make sure the total cross section is sized correctly
  testPrecondition( d_total_cross_section.size() == 0 );
  // Make sure the threshold index has been initialized
  testPrecondition( d_total_threshold_energy_index == 0u );

  Photoatom::ReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < d_energy_grid.size(); ++i )
  {
    scattering_reaction = getScatteringReactions().begin(); 
    
    const double raw_energy = 
      InterpPolicy::recoverProcessedIndepVar( d_energy_grid[i] );

    double raw_cross_section;

    if( i < d_absorption_threshold_energy_index )
      raw_cross_section = 0.0;
    else
    {
      raw_cross_section = 
	InterpPolicy::recoverProcessedDepVar(
	   d_absorption_cross_section[i-d_absorption_threshold_energy_index] );
    }

    while( scattering_reaction != getScatteringReactions().end() )
    {
      raw_cross_section += 
	scattering_reaction->second->getCrossSection( raw_energy );

      ++scattering_reaction;
    }
    
    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      d_total_cross_section.push_back( 
			    InterpPolicy::processDepVar( raw_cross_section ) );
    }
    else
    {
      // Ignore this data point
      ++d_total_threshold_energy_index;
    }
  }
  
  // Make sure the absorption cross section is valid
  remember( Teuchos::Array<double>::const_iterator zero_element = 
	    std::find( d_total_cross_section.begin(),
		       d_total_cross_section.end(),
		       0.0 ) );
  testPostcondition( zero_element == d_total_cross_section.end() );
  remember( Teuchos::Array<double>::const_iterator inf_element = 
	    std::find( d_total_cross_section.begin(),
		       d_total_cross_section.end(),
		       std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == d_total_cross_section.end() );
}

// Calculate the total cross section
template<typename InterpPolicy>
void StandardPhotoatom<InterpPolicy,false>::calculateTotalCrossSection()
{
  // Make sure the total cross section is sized correctly
  testPrecondition( d_total_cross_section.size() == d_energy_grid.size() );

  Photoatom::ReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < d_total_cross_section.size(); ++i )
  {
    scattering_reaction = getScatteringReactions().begin();

    d_total_cross_section[i] = d_absorption_cross_section[i];
        
    while( scattering_reaction != getScatteringReactions().end() )
    {
      d_total_cross_section[i] +=
	scattering_reaction->second->getCrossSection( d_energy_grid[i] );

      ++scattering_reaction;
    }
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PHOTOATOM_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatom_def.hpp
//---------------------------------------------------------------------------//
