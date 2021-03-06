//---------------------------------------------------------------------------//
//!
//! \file   tstSimulationProperties.cpp
//! \author Alex Robinson
//! \brief  Simulation properties unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Test the simulation properties defaults
TEUCHOS_UNIT_TEST( SimulationProperties, defaults )
{
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
                       MonteCarlo::NEUTRON_MODE );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationProperties::getNumberOfHistories(),
                      0 );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationProperties::getSurfaceFluxEstimatorAngleCosineCutoff(),
		      0.001 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getFreeGasThreshold(),
                       400.0 );
  TEST_EQUALITY_CONST( 
               MonteCarlo::SimulationProperties::getAbsoluteMinNeutronEnergy(),
               1e-11 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMinNeutronEnergy(),
                       1e-11 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMaxNeutronEnergy(),
                       20.0 );
  TEST_EQUALITY_CONST( 
               MonteCarlo::SimulationProperties::getAbsoluteMaxNeutronEnergy(),
               20.0 );
  TEST_EQUALITY_CONST(
               MonteCarlo::SimulationProperties::getAbsoluteMinPhotonEnergy(),
               1e-3 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMinPhotonEnergy(),
		       1e-3 );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMaxPhotonEnergy(),
                       20.0 );
  TEST_EQUALITY_CONST( 
                MonteCarlo::SimulationProperties::getAbsoluteMaxPhotonEnergy(),
                20.0 );    
  TEST_EQUALITY_CONST(
               MonteCarlo::SimulationProperties::getAbsoluteMinElectronEnergy(),
               1.5e-5 );
  TEST_EQUALITY_CONST(
               MonteCarlo::SimulationProperties::getMinElectronEnergy(),
               1.5e-5 );
  TEST_EQUALITY_CONST(
               MonteCarlo::SimulationProperties::getMaxElectronEnergy(),
               20.0 );
  TEST_EQUALITY_CONST(
	      MonteCarlo::SimulationProperties::getAbsoluteMaxElectronEnergy(),
	      20.0 );
  TEST_EQUALITY_CONST(
	       MonteCarlo::SimulationProperties::getKahnSamplingCutoffEnergy(),
	       3.0 );
  TEST_EQUALITY_CONST(
	     MonteCarlo::SimulationProperties::getNumberOfPhotonHashGridBins(),
	     1000 );
  TEST_ASSERT( MonteCarlo::SimulationProperties::displayWarnings() );
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isImplicitCaptureModeOn() );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getIncoherentModelType(),
		       MonteCarlo::COUPLED_FULL_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  TEST_ASSERT( MonteCarlo::SimulationProperties::isAtomicRelaxationModeOn() );
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isDetailedPairProductionModeOn() );
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isPhotonuclearInteractionModeOn() );
  TEST_EQUALITY_CONST( 
    MonteCarlo::SimulationProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::TWOBS_DISTRIBUTION );
  TEST_EQUALITY_CONST( 
        MonteCarlo::SimulationProperties::getElasticCutoffAngle(),
	    1.0e-6 );
}

//---------------------------------------------------------------------------//
// Test that the particle mode can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setParticleMode )
{
  MonteCarlo::ParticleModeType default_mode = 
    MonteCarlo::SimulationProperties::getParticleMode();

  MonteCarlo::SimulationProperties::setParticleMode( MonteCarlo::NEUTRON_MODE);

  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_MODE );

  MonteCarlo::SimulationProperties::setParticleMode( MonteCarlo::PHOTON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
		       MonteCarlo::PHOTON_MODE );

  MonteCarlo::SimulationProperties::setParticleMode( 
						   MonteCarlo::ELECTRON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
		       MonteCarlo::ELECTRON_MODE );

  MonteCarlo::SimulationProperties::setParticleMode( 
					     MonteCarlo::NEUTRON_PHOTON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_PHOTON_MODE );

  MonteCarlo::SimulationProperties::setParticleMode( 
					    MonteCarlo::PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
		       MonteCarlo::PHOTON_ELECTRON_MODE );
  
  MonteCarlo::SimulationProperties::setParticleMode( 
				    MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getParticleMode(),
		       MonteCarlo::NEUTRON_PHOTON_ELECTRON_MODE );

  MonteCarlo::SimulationProperties::setParticleMode( default_mode );
}

//---------------------------------------------------------------------------//
// Test that the number of histories to run can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setNumberOfHistories )
{
  unsigned long long default_value = 
    MonteCarlo::SimulationProperties::getNumberOfHistories();

  MonteCarlo::SimulationProperties::setNumberOfHistories( 1000000000 );
  
  TEST_ASSERT( MonteCarlo::SimulationProperties::getNumberOfHistories() !=
	       default_value );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationProperties::getNumberOfHistories(),
		      1000000000 );
}

//---------------------------------------------------------------------------//
// Test that the surface flux angle cosine cutoff can be set
TEUCHOS_UNIT_TEST( SimulationProperties, 
		   setSurfaceFluxEstimatorAngleCosineCutoff )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getSurfaceFluxEstimatorAngleCosineCutoff();

  MonteCarlo::SimulationProperties::setSurfaceFluxEstimatorAngleCosineCutoff( 0.1 );

  TEST_ASSERT( MonteCarlo::SimulationProperties::getSurfaceFluxEstimatorAngleCosineCutoff() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getSurfaceFluxEstimatorAngleCosineCutoff(),
		       0.1 );

  // Reset to the default
  MonteCarlo::SimulationProperties::setSurfaceFluxEstimatorAngleCosineCutoff( default_value );
}

//---------------------------------------------------------------------------//
// Test that the free gas thermal treatment temp threshold can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setFreeGasThreshold )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getFreeGasThreshold();

  MonteCarlo::SimulationProperties::setFreeGasThreshold( 1000.0 );

  TEST_ASSERT( MonteCarlo::SimulationProperties::getFreeGasThreshold() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getFreeGasThreshold(),
		       1000.0 );

  // Reset to the default
  MonteCarlo::SimulationProperties::setFreeGasThreshold( default_value );
}

//---------------------------------------------------------------------------//
// Test that the min neutron energy can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setMinNeutronEnergy )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getMinNeutronEnergy();

  MonteCarlo::SimulationProperties::setMinNeutronEnergy( 1e-8 );
  
  TEST_ASSERT( MonteCarlo::SimulationProperties::getMinNeutronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMinNeutronEnergy(),
		       1e-8 );

  // Reset the default
  MonteCarlo::SimulationProperties::setMinNeutronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the max neutron energy can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setMaxNeutronEnergy )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getMaxNeutronEnergy();

  MonteCarlo::SimulationProperties::setMaxNeutronEnergy( 15.0 );
  
  TEST_ASSERT( MonteCarlo::SimulationProperties::getMaxNeutronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMaxNeutronEnergy(),
		       15.0 );

  // Reset the default
  MonteCarlo::SimulationProperties::setMaxNeutronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the min photon energy can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setMinPhotonEnergy )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getMinPhotonEnergy();

  MonteCarlo::SimulationProperties::setMinPhotonEnergy( 1e-2 );

  TEST_ASSERT( MonteCarlo::SimulationProperties::getMinPhotonEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMinPhotonEnergy(),
		       1e-2 );

  // Reset the default value
  MonteCarlo::SimulationProperties::setMinPhotonEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the max photon energy can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setMaxPhotonEnergy )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getMaxPhotonEnergy();

  MonteCarlo::SimulationProperties::setMaxPhotonEnergy( 15.0 );

  TEST_ASSERT( MonteCarlo::SimulationProperties::getMaxPhotonEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST( MonteCarlo::SimulationProperties::getMaxPhotonEnergy(),
		       15.0 );

  // Reset the default value
  MonteCarlo::SimulationProperties::setMaxPhotonEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the Kahn sampling cutoff energy can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setKahnSamplingCutoffEnergy )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getKahnSamplingCutoffEnergy();

  MonteCarlo::SimulationProperties::setKahnSamplingCutoffEnergy( 2.5 );

  TEST_ASSERT( 
	    MonteCarlo::SimulationProperties::getKahnSamplingCutoffEnergy() !=
	    default_value );
  TEST_EQUALITY_CONST(
	      MonteCarlo::SimulationProperties::getKahnSamplingCutoffEnergy(),
	      2.5 );
  
  // Reset the default value
  MonteCarlo::SimulationProperties::setKahnSamplingCutoffEnergy( 
							       default_value );
}

//---------------------------------------------------------------------------//
// Test that the number of photon hash grid bins can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setNumberOfPhotonHashGridBins )
{
  unsigned default_value = 
    MonteCarlo::SimulationProperties::getNumberOfPhotonHashGridBins();

  MonteCarlo::SimulationProperties::setNumberOfPhotonHashGridBins( 500 );

  TEST_ASSERT( 
	  MonteCarlo::SimulationProperties::getNumberOfPhotonHashGridBins() !=
	  default_value );
  TEST_EQUALITY_CONST( 
	     MonteCarlo::SimulationProperties::getNumberOfPhotonHashGridBins(),
	     500 );
  
  // Reset the default value
  MonteCarlo::SimulationProperties::setNumberOfPhotonHashGridBins( default_value );
}

//---------------------------------------------------------------------------//
// Test that the min electron energy can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setMinElectronEnergy )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getMinElectronEnergy();

  MonteCarlo::SimulationProperties::setMinElectronEnergy( 1e-2 );

  TEST_ASSERT( MonteCarlo::SimulationProperties::getMinElectronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationProperties::getMinElectronEnergy(),
		      1e-2 );

  // Reset the default value
  MonteCarlo::SimulationProperties::setMinElectronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the max electron energy can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setMaxElectronEnergy )
{
  double default_value = 
    MonteCarlo::SimulationProperties::getMaxElectronEnergy();

  MonteCarlo::SimulationProperties::setMaxElectronEnergy( 15.0 );

  TEST_ASSERT( MonteCarlo::SimulationProperties::getMaxElectronEnergy() !=
	       default_value );
  TEST_EQUALITY_CONST(MonteCarlo::SimulationProperties::getMaxElectronEnergy(),
		      15.0 );

  // Reset the default value
  MonteCarlo::SimulationProperties::setMaxElectronEnergy( default_value );
}

//---------------------------------------------------------------------------//
// Test that the min particle energy can be returned
TEUCHOS_UNIT_TEST( SimulationProperties, getMinParticleEnergy )
{
  double default_value_neutron = 
    MonteCarlo::SimulationProperties::getMinNeutronEnergy();

  MonteCarlo::SimulationProperties::setMinNeutronEnergy( 1e-8 );
  
  double default_value_photon = 
    MonteCarlo::SimulationProperties::getMinPhotonEnergy();

  MonteCarlo::SimulationProperties::setMinPhotonEnergy( 1e-2 );
  
  double default_value_electron = 
    MonteCarlo::SimulationProperties::getMinElectronEnergy();

  MonteCarlo::SimulationProperties::setMinElectronEnergy( 1e-2 );

  TEST_EQUALITY( MonteCarlo::SimulationProperties::getMinParticleEnergy<MonteCarlo::NeutronState>(),
		 1e-8 );
  TEST_EQUALITY( MonteCarlo::SimulationProperties::getMinParticleEnergy<MonteCarlo::PhotonState>(),
		 1e-2 );
  TEST_EQUALITY( MonteCarlo::SimulationProperties::getMinParticleEnergy<MonteCarlo::ElectronState>(),
		 1e-2 );

  // Reset the default values
  MonteCarlo::SimulationProperties::setMinNeutronEnergy( default_value_neutron );
  MonteCarlo::SimulationProperties::setMinPhotonEnergy( default_value_photon );
  MonteCarlo::SimulationProperties::setMinElectronEnergy( default_value_electron );
}

//---------------------------------------------------------------------------//
// Test that the max particle energy can be returned
TEUCHOS_UNIT_TEST( SimulationProperties, getMaxParticleEnergy )
{
  double default_value_neutron = 
    MonteCarlo::SimulationProperties::getMaxNeutronEnergy();

  MonteCarlo::SimulationProperties::setMaxNeutronEnergy( 15.0 );
  
  double default_value_photon = 
    MonteCarlo::SimulationProperties::getMaxPhotonEnergy();

  MonteCarlo::SimulationProperties::setMaxPhotonEnergy( 15.0 );
  
  double default_value_electron = 
    MonteCarlo::SimulationProperties::getMaxElectronEnergy();

  MonteCarlo::SimulationProperties::setMaxElectronEnergy( 15.0 );

  TEST_EQUALITY( MonteCarlo::SimulationProperties::getMaxParticleEnergy<MonteCarlo::NeutronState>(),
		 15.0 );
  TEST_EQUALITY( MonteCarlo::SimulationProperties::getMaxParticleEnergy<MonteCarlo::PhotonState>(),
		 15.0 );
  TEST_EQUALITY( MonteCarlo::SimulationProperties::getMaxParticleEnergy<MonteCarlo::ElectronState>(),
		 15.0 );

  // Reset the default values
  MonteCarlo::SimulationProperties::setMaxNeutronEnergy( default_value_neutron );
  MonteCarlo::SimulationProperties::setMaxPhotonEnergy( default_value_photon );
  MonteCarlo::SimulationProperties::setMaxElectronEnergy( default_value_electron );
}

//---------------------------------------------------------------------------//
// Test that warnings can be disabled
TEUCHOS_UNIT_TEST( SimulationProperties, setWarningsOff )
{
  TEST_ASSERT( MonteCarlo::SimulationProperties::displayWarnings() );

  MonteCarlo::SimulationProperties::setWarningsOff();

  TEST_ASSERT( !MonteCarlo::SimulationProperties::displayWarnings() );
}

//---------------------------------------------------------------------------//
// Test that implicit capture mode can be turned on
TEUCHOS_UNIT_TEST( SimulationProperties, setImplicitCaptureModeOn )
{
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isImplicitCaptureModeOn() );

  MonteCarlo::SimulationProperties::setImplicitCaptureModeOn();

  TEST_ASSERT( MonteCarlo::SimulationProperties::isImplicitCaptureModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the incoherent model type can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setIncoherentModelType )
{
  MonteCarlo::IncoherentModelType default_model = 
    MonteCarlo::SimulationProperties::getIncoherentModelType();

  MonteCarlo::SimulationProperties::setIncoherentModelType(
					     MonteCarlo::KN_INCOHERENT_MODEL );

  TEST_ASSERT( MonteCarlo::SimulationProperties::getIncoherentModelType() !=
	       default_model );
  TEST_EQUALITY_CONST(
		    MonteCarlo::SimulationProperties::getIncoherentModelType(),
		    MonteCarlo::KN_INCOHERENT_MODEL );
  
  // Reset the default model
  MonteCarlo::SimulationProperties::setIncoherentModelType( default_model );
}

//---------------------------------------------------------------------------//
// Test that atomic relaxation mode can be turned off
TEUCHOS_UNIT_TEST( SimulationProperties, setAtomicRelaxationModeOff )
{
  TEST_ASSERT( MonteCarlo::SimulationProperties::isAtomicRelaxationModeOn() );
  
  MonteCarlo::SimulationProperties::setAtomicRelaxationModeOff();

  TEST_ASSERT( !MonteCarlo::SimulationProperties::isAtomicRelaxationModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the detailed pair production mode can be turned on
TEUCHOS_UNIT_TEST( SimulationProperties, setDetailedPairProductionModeOn )
{
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isDetailedPairProductionModeOn() );
  
  MonteCarlo::SimulationProperties::setDetailedPairProductionModeOn();

  TEST_ASSERT( MonteCarlo::SimulationProperties::isDetailedPairProductionModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the photonuclear interaction mode can be turned on
TEUCHOS_UNIT_TEST( SimulationProperties, setPhotonuclearInteractionModeOn )
{
  TEST_ASSERT( !MonteCarlo::SimulationProperties::isPhotonuclearInteractionModeOn() );
  
  MonteCarlo::SimulationProperties::setPhotonuclearInteractionModeOn();

  TEST_ASSERT( MonteCarlo::SimulationProperties::isPhotonuclearInteractionModeOn() );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Dipole
TEUCHOS_UNIT_TEST( SimulationProperties, setBremsstrahlungAngularDistributionFunction_Dipole )
{
  TEST_EQUALITY_CONST( 
    MonteCarlo::SimulationProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::TWOBS_DISTRIBUTION );
  
  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::SimulationProperties::setBremsstrahlungAngularDistributionFunction( 
                          function );

  TEST_EQUALITY_CONST( 
    MonteCarlo::SimulationProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::DIPOLE_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the bremsstrahlung angular distribution function can be turned to Tabular
TEUCHOS_UNIT_TEST( SimulationProperties, setBremsstrahlungAngularDistributionFunction_Tabular )
{
  TEST_EQUALITY_CONST( 
    MonteCarlo::SimulationProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::DIPOLE_DISTRIBUTION );
  
  MonteCarlo::BremsstrahlungAngularDistributionType function;
  function = MonteCarlo::TABULAR_DISTRIBUTION;

  MonteCarlo::SimulationProperties::setBremsstrahlungAngularDistributionFunction( 
                          function );

  TEST_EQUALITY_CONST( 
    MonteCarlo::SimulationProperties::getBremsstrahlungAngularDistributionFunction(),
	MonteCarlo::TABULAR_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Test that the elastic cutoff angle cosine can be set
TEUCHOS_UNIT_TEST( SimulationProperties, setElasticCutoffAngle )
{
  TEST_EQUALITY( 
    MonteCarlo::SimulationProperties::getElasticCutoffAngle(),
	1.0e-6 );
  
  MonteCarlo::SimulationProperties::setElasticCutoffAngle( 0.1 );

  TEST_EQUALITY( 
    MonteCarlo::SimulationProperties::getElasticCutoffAngle(),
	0.1 );
}

//---------------------------------------------------------------------------//
// end tstSimulationProperties.cpp
//---------------------------------------------------------------------------//
