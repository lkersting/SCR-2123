//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The single scattering elastic electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MOMENT_PRESERVING_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_MOMENT_PRESERVING_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
MomentPreservingElectroatomicReaction<InterpPolicy,processed_cross_section>::MomentPreservingElectroatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const MomentPreservingElectronScatteringDistribution>&
         scattering_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                       incoming_energy_grid,
                                                       cross_section,
                                                       threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
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
  // Make sure scattering distribution is valid
  testPrecondition( !scattering_distribution.is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned MomentPreservingElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned MomentPreservingElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType MomentPreservingElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return MOMENT_PRESERVING_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void MomentPreservingElectroatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     ElectronState& electron, 
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterElectron( electron, 
                                              bank, 
                                              shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MOMENT_PRESERVING_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_MomentPreservingElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//