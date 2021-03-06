//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The absorption electroatomic reaction class decl.
//!
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor without doppler broadening
template<typename InterpPolicy, bool processed_cross_section>
AbsorptionElectroatomicReaction<InterpPolicy,processed_cross_section>::AbsorptionElectroatomicReaction(
	   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	   const Teuchos::ArrayRCP<const double>& cross_section,
	   const unsigned threshold_energy_index,
	   const ElectroatomicReactionType reaction )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
						      incoming_energy_grid,
						      cross_section,
						      threshold_energy_index ),
    d_reaction( reaction )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
  testPrecondition( cross_section.size() == 
		    incoming_energy_grid.size() - threshold_energy_index );    
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AbsorptionElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType AbsorptionElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return d_reaction;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AbsorptionElectroatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     ElectronState& electron, 
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  electron.setAsGone();
  
  shell_of_interaction = UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
