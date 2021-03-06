//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The absorption photoatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_ABSORPTION_PHOTOATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardPhotoatomicReaction.hpp"

namespace MonteCarlo{

/*! The absorption photoatomic reaction
 * \details This reaction should be used to represent miscellaneous
 * absorption reactions (e.g. heating).
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class AbsorptionPhotoatomicReaction : public StandardPhotoatomicReaction<InterpPolicy,processed_cross_section>
{
  
public:

  //! Basic constructor
  AbsorptionPhotoatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cross_section,
	  const unsigned threshold_energy_index,
	  const PhotoatomicReactionType reaction );

  //! Constructor
  AbsorptionPhotoatomicReaction(
       const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
       const Teuchos::ArrayRCP<const double>& cross_section,
       const unsigned threshold_energy_index,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const PhotoatomicReactionType reaction );

  //! Destructor
  ~AbsorptionPhotoatomicReaction()
  { /* ... */ }

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  PhotoatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( PhotonState& photon, 
	      ParticleBank& bank,
	      SubshellType& shell_of_interaction ) const;

private:

  // The reaction type
  PhotoatomicReactionType d_reaction;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AbsorptionPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ABSORPTION_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
