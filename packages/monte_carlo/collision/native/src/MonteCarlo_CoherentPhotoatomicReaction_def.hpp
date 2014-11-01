//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The coherent photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::CoherentPhotoatomicReaction( 
                   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index,
		   const Teuchos::RCP<Utility::OneDDistribution>& form_factor )
  : StandardPhotoatomicReaction<InterPolicy,processed_cross_section>(
                                                      incoming_energy_grid,
						      cross_section,
                                                      threshold_energy_index ),
    d_scattering_distribution( form_factor )
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
  // Make sure the form factor is valid
  testPrecondition( !form_factor->is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 1u;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void CoherentPhotoatomicReaction<InterpPolicy,processed_cross_section>::react( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterPhoton( photon, bank );

  // No subshell vacancies are created by this reaction
  shell_of_interaction = UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
