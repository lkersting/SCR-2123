//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class BremsstrahlungElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the bremsstrahlung distribution
  typedef Teuchos::Array<Utility::Pair<double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  BremsstrahlungDistribution;

  //! Constructor with simple dipole photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution );

  //! Constructor with detailed tabular photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution,
    const Teuchos::RCP<Utility::OneDDistribution>& angular_distribution,
    const double lower_cutoff_energy,
    const double upper_cutoff_energy );

  //! Constructor with detailed 2BS photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution,
    const int atomic_number );

  //! Destructor 
  virtual ~BremsstrahlungElectronScatteringDistribution()
  { /* ... */ }

  //! Return the min incoming energy
  double getMinEnergy() const;

  //! Return the Max incoming energy
  double getMaxEnergy() const;

  //! Return the max incoming electron energy for a given photon energy
  double getMaxIncomingEnergyAtOutgoingEnergy( const double energy ) const;

  //! Evaluate the PDF value for a given incoming and photon energy
  double evaluatePDF( const double incoming_energy, 
                      const double photon_energy ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& photon_energy,
               double& photon_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& photon_energy,
                              double& photon_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
                        ParticleBank& bank,
                        SubshellType& shell_of_interaction ) const;

private:

  // atomic number (Z)
  double d_atomic_number;

  // upper cutoff energy for the condensed-history method
  double d_upper_cutoff_energy;

  // lower cutoff energy for the condensed-history method
  double d_lower_cutoff_energy;

  // bremsstrahlung scattering distribution
  BremsstrahlungDistribution d_bremsstrahlung_scattering_distribution;

  // bremsstrahlung angular distribution of generated photons
  Teuchos::RCP<Utility::OneDDistribution> d_angular_distribution;

  // Sample the outgoing photon angle from a tabular distribution 
  double SampleTabularAngle(  const double incoming_electron_energy, 
                              const double photon_energy ) const ;

  // Sample the outgoing photon angle from a dipole distribution
  double SampleDipoleAngle(  const double incoming_electron_energy, 
                             const double photon_energy ) const ;

  // Sample the outgoing photon angle using the 2BS sampling routine of Kock and Motz
  double Sample2BSAngle(  const double incoming_electron_energy, 
                          const double photon_energy ) const ;

  // Calculate the rejection function for the 2BS sampling routine
  double Calculate2BSRejection( const double outgoing_electron_energy,
                                const double two_ratio,
                                const double parameter1,
                                const double x ) const;

  // The doppler broadening function pointer
  boost::function<double ( const double, const double )> 
                                        d_angular_distribution_func; 

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
