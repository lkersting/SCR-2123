//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistribuiton.hpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The incoherent adjoint photon scattering distribution class
class IncoherentAdjointPhotonScatteringDistribution : public AdjointPhotonScatteringDistribution
{

protected:

  //! Typedef for ArrayRCP const iterator
  typedef Teuchos::ArrayRCP<const double>::const_iterator LineEnergyIterator;

public:

  //! Constructor
  IncoherentAdjointPhotonScatteringDistribution( const double max_energy );

  //! Destructor
  virtual ~IncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Set the critical line energies
  void setCriticalLineEnergies( 
	       const Teuchos::ArrayRCP<const double>& critical_line_energies );

  //! Set the max energy
  void setMaxEnergy( const double max_energy );

  //! Return the max energy
  double getMaxEnergy() const;

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double max_energy,
			   const double scattering_angle_cosine ) const = 0;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the pdf
  virtual double evaluatePDF( const double incoming_energy,
			      const double max_energy,
			      const double scattering_angle_cosine ) const;

  //! Evaluate the pdf
  double evaluatePDF( const double incoming_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  virtual double evaluateIntegratedCrossSection( const double incoming_energy,
						 const double max_energy,
						 const double precision ) const = 0;

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const;
  
protected:

  //! Evaluate the adjoint Klein-Nishina distribution
  double evaluateAdjointKleinNishinaDist( 
				  const double incoming_energy,
				  const double max_energy,
				  const double scattering_angle_cosine ) const;

  //! Basic sampling implementation
  void sampleAndRecordTrialsAdjointKleinNishina( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    unsigned& trials ) const;

  //! Check if an energy is below the scattering window
  virtual bool isEnergyBelowScatteringWindow( 
					   const double energy_of_interest,
					   const double initial_energy ) const;

  //! Check if an energy is above the scattering window
  virtual bool isEnergyAboveScatteringWindow( 
					   const double energy_of_interest,
					   const double initial_energy ) const;

  //! Check if an energy is in the scattering window
  bool isEnergyInScatteringWindow( const double energy_of_interest,
				   const double initial_energy ) const;

  // Return only the critical line energies that can be scattered into
  void getCriticalLineEnergiesInScatteringWindow( 
					const double energy,
				        LineEnergyIterator& start_energy,
					LineEnergyIterator& end_energy ) const;

  //! Create a probe particle
  virtual void createProbeParticle( const double energy_of_interest, 
				    const AdjointPhotonState& adjoint_photon,
				    ParticleBank& bank ) const;

  //! Create the probe particles
  void createProbeParticles( const AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank ) const;
  
private:

  // The maximum energy
  double d_max_energy;

  // The critical line energies
  Teuchos::ArrayRCP<const double> d_critical_line_energies;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
