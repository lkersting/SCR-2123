//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy distribution declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The Doppler broadened photon energy distribution class
class DopplerBroadenedPhotonEnergyDistribution
{

public:
  
  //! The electron momentum distribution array (Compton Profiles)
  typedef Teuchos::Array<std::shared_ptr<const ComptonProfile> >
  ElectronMomentumDistArray;
  
  //! Constructor
  DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  virtual bool isComplete() const = 0;

  //! Evaluate the distribution with electron momentum projection
  virtual double evaluateWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine ) const;

  //! Evaluate the exact distribution
  virtual double evaluateExact(
                              const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF with electron momentum projection
  virtual double evaluatePDFWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine ) const;

  //! Evaluate the exact PDF
  virtual double evaluateExactPDF(
                              const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateIntegratedCrossSection(
                                          const double incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const = 0;
  
  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateExactIntegratedCrossSection( 
			             const double incoming_energy,
                                     const double scattering_angle_cosine,
                                     const double precision ) const = 0;

  //! Sample an outgoing energy from the distribution
  virtual void sample( const double incoming_energy,
		       const double scattering_angle_cosine,
		       double& outgoing_energy,
		       Data::SubshellType& shell_of_interaction ) const = 0;

  //! Sample an outgoing energy and record the number of trials
  virtual void sampleAndRecordTrials( 
				const double incoming_energy,
				const double scattering_angle_cosine,
				double& outgoing_energy,
				Data::SubshellType& shell_of_interaction,
				unsigned& trials ) const = 0;

  //! Sample an electron momentum projection and record the number of trials
  virtual void sampleMomentumAndRecordTrials(
                                          const double incoming_energy,
                                          const double scattering_angle_cosine,
                                          double& electron_momentum_projection,
                                          Data::SubshellType& shell_of_interaction,
                                          unsigned& trials ) const = 0;

protected:

  //! Evaluate the cross section multiplier
  double evaluateMultiplier( const double incoming_energy,
			     const double scattering_angle_cosine ) const;
};

// Evaluate the distribution
/*! \details The approximate double differential cross section
 * (d^2 sigma)/(dmu dE) will be evaluated by evaluating the 
 * approximate double differential cross section dependent on the
 * electron momentum projection (pz) and doing a change of variable to
 * energy.
 */  
double evaluate( const double incoming_energy,
                 const double outgoing_energy,
                 const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the electron momentum projection
  const ComptonProfile::MomentumQuantity electron_momentum_projection = 
    calculateElectronMomentumProjection( incoming_energy,
                                         outgoing_energy,
                                         scattering_angle_cosine );

  // Evaluate the double differential cross section dependent on the
  // electron momentum projection
  const double cross_section = this->evaluateWithElectronMomentumProjection(
                                                  incoming_energy,
                                                  electron_momentum_projection,
                                                  scattering_angle_cosine );

  // Calculate the Jacobian for the change of variables
  const double jacobian = 
}

// Evaluate the cross section multiplier
/*! \details It is assumed that the Compton profiles have been divided by
 * the average electron momentum in the ground state of hydrogen (atomic 
 * units). This multiplier term therefore has units of b/(m_e*c).
 */
inline double DopplerBroadenedPhotonEnergyDistribution::evaluateMultiplier(
                                   const double incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double term_1 = 
    Utility::PhysicalConstants::pi*1e24*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;
  
  const double compton_line_energy = 
    calculateComptonLineEnergy( incoming_energy, scattering_angle_cosine );

  const double term_2 = (compton_line_energy/incoming_energy)*
    (compton_line_energy/incoming_energy)*
    (incoming_energy/compton_line_energy +
     compton_line_energy/incoming_energy +
     scattering_angle_cosine*
     scattering_angle_cosine - 1.0);
  
  return term_1*term_2;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
