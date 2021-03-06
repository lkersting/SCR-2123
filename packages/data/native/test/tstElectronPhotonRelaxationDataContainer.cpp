//---------------------------------------------------------------------------//
//!
//! \file   tstElectronPhotonRelaxationDataContainer.cpp
//! \author Alex Robinson
//! \brief  Electron-photon-relaxation data container class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::ElectronPhotonRelaxationVolatileDataContainer epr_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setAtomicNumber )
{
  epr_data_container.setAtomicNumber( 1u );
  
  TEST_EQUALITY_CONST( epr_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the subshells can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setSubshells )
{
  std::set<unsigned> subshells;
  subshells.insert( 1 );

  epr_data_container.setSubshells( subshells );
  
  TEST_ASSERT( epr_data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container.getSubshells().count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancies can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
		   setSubshellOccupancy )
{
  epr_data_container.setSubshellOccupancy( 1, 1.0 );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellOccupancy( 1 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energies can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
		   setSubshellBindingEnergy )
{
  epr_data_container.setSubshellBindingEnergy( 1, 1.361e-5 );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of subshell relaxation transitions can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationTransitions )
{
  TEST_ASSERT( !epr_data_container.hasRelaxationData() );

  epr_data_container.setSubshellRelaxationTransitions( 1, 1 );
  
  TEST_EQUALITY_CONST( epr_data_container.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container.hasRelaxationData() );
  TEST_ASSERT( epr_data_container.hasSubshellRelaxationData( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the relaxation vacancies for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationVacancies )
{
  std::vector<std::pair<unsigned,unsigned> > vacancies( 1 );
  vacancies[0].first = 1u;
  vacancies[1].second = 0u;

  epr_data_container.setSubshellRelaxationVacancies( 1, vacancies );

  UTILITY_TEST_COMPARE_ARRAYS( 
			epr_data_container.getSubshellRelaxationVacancies( 1 ),
			vacancies );
  
}

//---------------------------------------------------------------------------//
// Check that the relaxation particle energies for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationEnergies )
{
  std::vector<double> energies( 1 );
  energies[0] = 1e-6;
  
  epr_data_container.setSubshellRelaxationParticleEnergies( 1, energies );

  TEST_COMPARE_ARRAYS( 
		 epr_data_container.getSubshellRelaxationParticleEnergies( 1 ),
		 energies );
}

//---------------------------------------------------------------------------//
// Check that the relaxation probabilities for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationProbabilities )
{
  std::vector<double> probabilities( 1 );
  probabilities[0] = 1.0;

  epr_data_container.setSubshellRelaxationProbabilities( 1, probabilities );

  TEST_COMPARE_ARRAYS( 
		    epr_data_container.getSubshellRelaxationProbabilities( 1 ),
		    probabilities );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setComptonProfileMomentumGrid )
{
  std::vector<double> compton_profile_momentum_grid( 3 );
  compton_profile_momentum_grid[0] = -1.0;
  compton_profile_momentum_grid[1] = 0.0;
  compton_profile_momentum_grid[2] = 1.0;

  epr_data_container.setComptonProfileMomentumGrid( 
					    1, compton_profile_momentum_grid );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getComptonProfileMomentumGrid( 1 ),
		       compton_profile_momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setComptonProfile )
{
  std::vector<double> compton_profile( 3 );
  compton_profile[0] = 1e-12;
  compton_profile[1] = 10.0;
  compton_profile[2] = 1e-12;

  epr_data_container.setComptonProfile( 1, compton_profile );

  TEST_COMPARE_ARRAYS( epr_data_container.getComptonProfile( 1 ), 
		       compton_profile );
} 

//---------------------------------------------------------------------------//
// Check that the occupation number momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setOccupationNumberMomentumGrid )
{
  std::vector<double> momentum_grid( 3 );
  momentum_grid[0] = -1.0;
  momentum_grid[1] = 0.0;
  momentum_grid[2] = 1.0;

  epr_data_container.setOccupationNumberMomentumGrid( 1, momentum_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getOccupationNumberMomentumGrid( 1 ),
		       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the occupation number for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setOccupationNumber )
{
  std::vector<double> occupation_number( 3 );
  occupation_number[0] = 0.0;
  occupation_number[1] = 0.5;
  occupation_number[2] = 1.0;

  epr_data_container.setOccupationNumber( 1, occupation_number );

  TEST_COMPARE_ARRAYS( epr_data_container.getOccupationNumber( 1 ),
		       occupation_number );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeScatteringFunctionMomentumGrid )
{
  std::vector<double> momentum_grid( 4 );
  momentum_grid[0] = 1e-30;
  momentum_grid[1] = 1.0;
  momentum_grid[2] = 10.0;
  momentum_grid[3] = 1e8;

  epr_data_container.setWallerHartreeScatteringFunctionMomentumGrid(
							       momentum_grid );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeScatteringFunctionMomentumGrid(),
		       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeScatteringFunction )
{
  std::vector<double> scattering_function( 4 );
  scattering_function[0] = 1e-30;
  scattering_function[1] = 1e-3;
  scattering_function[2] = 0.1;
  scattering_function[3] = 1.0;

  epr_data_container.setWallerHartreeScatteringFunction( scattering_function );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeScatteringFunction(),
		       scattering_function );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeAtomicFormFactorMomentumGrid )
{
  std::vector<double> momentum_grid( 4 );
  momentum_grid[0] = 1e-30;
  momentum_grid[1] = 1.0;
  momentum_grid[2] = 10.0;
  momentum_grid[3] = 1e8;

  epr_data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
							       momentum_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeAtomicFormFactorMomentumGrid(),
		       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeAtomicFormFactor )
{
  std::vector<double> form_factor( 4 );
  form_factor[0] = 1.0;
  form_factor[1] = 1.0;
  form_factor[2] = 0.3;
  form_factor[3] = 1e-30;

  epr_data_container.setWallerHartreeAtomicFormFactor( form_factor );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeAtomicFormFactor(),
		       form_factor );
}

//---------------------------------------------------------------------------//
// Check that the photon energy grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPhotonEnergyGrid )
{
  std::vector<double> photon_energy_grid( 3 );
  photon_energy_grid[0] = 1e-3;
  photon_energy_grid[1] = 1.0;
  photon_energy_grid[2] = 20.0;

  epr_data_container.setPhotonEnergyGrid( photon_energy_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getPhotonEnergyGrid(),
		       photon_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the average heating numbers can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setAveragePhotonHeatingNumbers )
{
  std::vector<double> heating_numbers( 3 );
  heating_numbers[0] = 1e-6;
  heating_numbers[1] = 1e-3;
  heating_numbers[2] = 1.0;

  epr_data_container.setAveragePhotonHeatingNumbers( heating_numbers );

  TEST_COMPARE_ARRAYS( epr_data_container.getAveragePhotonHeatingNumbers(),
		       heating_numbers );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree incoherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeIncoherentCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeIncoherentCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree incoherent cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. incoherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxIncoherentCrossSection( cross_section );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getImpulseApproxIncoherentCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. incoherent cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. subshell incoherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxSubshellIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxSubshellIncoherentCrossSection( 1, cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getImpulseApproxSubshellIncoherentCrossSection( 1 ),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. subshell incoh. cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1, 0 );

  TEST_EQUALITY_CONST( epr_data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree coherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeCoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeCoherentCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeCoherentCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree coherent cs threshold energy index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeCoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setWallerHartreeCoherentCrossSectionThresholdEnergyIndex( 0 );
  
  TEST_EQUALITY_CONST( epr_data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPairProductionCrossSection )
{
  std::vector<double> cross_section( 2 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1.0;
  
  epr_data_container.setPairProductionCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getPairProductionCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPairProductionCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setPairProductionCrossSectionThresholdEnergyIndex( 1 );

  TEST_EQUALITY_CONST( epr_data_container.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPhotoelectricCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setPhotoelectricCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getPhotoelectricCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect cs threshold energy index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPhotoelectricCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setPhotoelectricCrossSectionThresholdEnergyIndex( 0u );

  TEST_EQUALITY_CONST( epr_data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric effect cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellPhotoelectricCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setSubshellPhotoelectricCrossSection( 1, cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getSubshellPhotoelectricCrossSection( 1 ),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric effect cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellPhotoelectricCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1, 0u );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree total cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeTotalCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeTotalCrossSection( cross_section );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeTotalCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. total cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxTotalCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxTotalCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getImpulseApproxTotalCrossSection(),
		       cross_section );
}

// Electron Tests

//---------------------------------------------------------------------------//
// Check that the Cutoff Angle can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setCutoffAngle )
{
  epr_data_container.setCutoffAngle( 0.10 );
  
  TEST_EQUALITY_CONST( epr_data_container.getCutoffAngle(), 
                       0.10 );
}

//---------------------------------------------------------------------------//
// Check that the angular energy grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  epr_data_container.setElasticAngularEnergyGrid( 
                                    angular_energy_grid );
  
  grid = epr_data_container.getElasticAngularEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], angular_energy_grid[0] );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setAnalogElasticAnglesAtEnergy )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  epr_data_container.setAnalogElasticAnglesAtEnergy( 1.0, angles );

  TEST_COMPARE_ARRAYS( epr_data_container.getAnalogElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setAnalogElasticPDFAtEnergy )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  epr_data_container.setAnalogElasticPDFAtEnergy( 1.0, pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getAnalogElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setAnalogElasticAngles )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  double energy = 1.0;
  std::map<double, std::vector<double> > angles_map;

  angles_map[energy] = angles;

  epr_data_container.setAnalogElasticAngles( angles_map );

  TEST_COMPARE_ARRAYS( epr_data_container.getAnalogElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setAnalogElasticPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;
  
  double energy = 1.0;
  std::map<double, std::vector<double> > pdf_map;

  pdf_map[energy] = pdf;

  epr_data_container.setAnalogElasticPDF( pdf_map );

  TEST_COMPARE_ARRAYS( epr_data_container.getAnalogElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford elastic normalization constant can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setScreenedRutherfordNormalizationConstant )
{
  std::vector<double> norm( 3 );
  norm[0] = 100;
  norm[1] = 200;
  norm[2] = 700;

  epr_data_container.setScreenedRutherfordNormalizationConstant( norm );

  TEST_COMPARE_ARRAYS( epr_data_container.getScreenedRutherfordNormalizationConstant(),
                       norm );
}

//---------------------------------------------------------------------------//
// Check that Moliere's screening constant can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setMoliereScreeningConstant )
{
  std::vector<double> eta( 3 );
  eta[0] = 100;
  eta[1] = 0.0;
  eta[2] = 0.90;

  epr_data_container.setMoliereScreeningConstant( eta );

  TEST_COMPARE_ARRAYS( epr_data_container.getMoliereScreeningConstant(),
                       eta );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving elastic discrete angles can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setMomentPreservingElasticDiscreteAngles )
{
  std::vector<double> discrete_angles( 3 );
  discrete_angles[0] = 0.90;
  discrete_angles[1] = 0.95;
  discrete_angles[2] = 0.99;

  epr_data_container.setMomentPreservingElasticDiscreteAngles( 1.0, 
                                                            discrete_angles );

  TEST_COMPARE_ARRAYS( epr_data_container.getMomentPreservingElasticDiscreteAngles(1.0),
                       discrete_angles );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving elastic weights can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setMomentPreservingElasticWeights )
{
  std::vector<double> weights( 3 );
  weights[0] = 0.1;
  weights[1] = 0.2;
  weights[2] = 0.7;

  epr_data_container.setMomentPreservingElasticWeights( 1.0, weights );

  TEST_COMPARE_ARRAYS( epr_data_container.getMomentPreservingElasticWeights(1.0),
                       weights );
}

//---------------------------------------------------------------------------//
// Check that the electroionization energy grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setElectroionizationEnergyGrid )
{
  std::vector<double> energy_grid(1), grid(1);
  energy_grid[0] = 1.0;

  unsigned subshell = 1;

  epr_data_container.setElectroionizationEnergyGrid( 
                                subshell,
                                energy_grid );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getElectroionizationEnergyGrid( subshell ), 
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setElectroionizationRecoilEnergyAtIncomingEnergy )
{
  std::vector<double> recoil_energy( 3 );
  recoil_energy[0] = 0.01;
  recoil_energy[1] = 0.001;
  recoil_energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setElectroionizationRecoilEnergyAtIncomingEnergy( 
                                subshell,
                                energy, 
                                recoil_energy );

  TEST_COMPARE_ARRAYS( epr_data_container.getElectroionizationRecoilEnergy(subshell, energy),
                       recoil_energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setElectroionizationRecoilPDFAtIncomingEnergy )
{
  std::vector<double> recoil_pdf( 3 );
  recoil_pdf[0] = 1.0;
  recoil_pdf[1] = 2.0;
  recoil_pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setElectroionizationRecoilPDFAtIncomingEnergy(
                                subshell,
                                energy, 
                                recoil_pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getElectroionizationRecoilPDF( subshell, energy ),
                       recoil_pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setElectroionizationRecoilEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > recoil_energy;

  recoil_energy[energy_bin] = energy;

  epr_data_container.setElectroionizationRecoilEnergy( 
                                subshell,
                                recoil_energy );

  TEST_COMPARE_ARRAYS( 
    epr_data_container.getElectroionizationRecoilEnergy(subshell, energy_bin),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setElectroionizationRecoilPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > recoil_pdf;

  recoil_pdf[energy_bin] = pdf;

  epr_data_container.setElectroionizationRecoilPDF(
                                subshell,
                                recoil_pdf );

  TEST_COMPARE_ARRAYS( 
    epr_data_container.getElectroionizationRecoilPDF( subshell, energy_bin ),
    pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setBremsstrahlungEnergyGrid )
{
  std::vector<double> energy_grid(1), grid(1);
  energy_grid[0] = 1.0;

  epr_data_container.setBremsstrahlungEnergyGrid( energy_grid );
  
  grid = epr_data_container.getBremsstrahlungEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], energy_grid[0] );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setBremsstrahlungPhotonEnergyAtIncomingEnergy )
{
  std::vector<double> photon_energy( 3 );
  photon_energy[0] = 0.01;
  photon_energy[1] = 0.001;
  photon_energy[2] = 0.0001;

  epr_data_container.setBremsstrahlungPhotonEnergyAtIncomingEnergy( 1.0, 
                                                                   photon_energy );

  TEST_COMPARE_ARRAYS( epr_data_container.getBremsstrahlungPhotonEnergy(1.0),
                       photon_energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setBremsstrahlungPhotonPDFAtIncomingEnergy )
{
  std::vector<double> photon_pdf( 3 );
  photon_pdf[0] = 1.0;
  photon_pdf[1] = 2.0;
  photon_pdf[2] = 5.0;

  epr_data_container.setBremsstrahlungPhotonPDFAtIncomingEnergy( 1.0, 
                                                                photon_pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getBremsstrahlungPhotonPDF(1.0),
                       photon_pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setBremsstrahlungPhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_energy;

  photon_energy[energy_bin] = energy;

  epr_data_container.setBremsstrahlungPhotonEnergy( photon_energy );

  TEST_COMPARE_ARRAYS( epr_data_container.getBremsstrahlungPhotonEnergy(energy_bin),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setBremsstrahlungPhotonPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_pdf;

  photon_pdf[energy_bin] = pdf;

  epr_data_container.setBremsstrahlungPhotonPDF( photon_pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getBremsstrahlungPhotonPDF(energy_bin),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setAtomicExcitationEnergyGrid )
{
  std::vector<double> energy_grid(3);
  energy_grid[0] = 1.0;
  energy_grid[1] = 5.0;
  energy_grid[2] = 10.0;

  epr_data_container.setAtomicExcitationEnergyGrid( 
                                    energy_grid );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getAtomicExcitationEnergyGrid(), 
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy loss can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
                   setAtomicExcitationEnergyLoss )
{
  std::vector<double> energy_loss(3);
  energy_loss[0] = 1.0;
  energy_loss[1] = 5.0;
  energy_loss[2] = 10.0;

  epr_data_container.setAtomicExcitationEnergyLoss( 
                                    energy_loss );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getAtomicExcitationEnergyLoss(), 
                       energy_loss );
}

//---------------------------------------------------------------------------//
// Check that the electron energy grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  epr_data_container.setElectronEnergyGrid( electron_energy_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getElectronEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic electron cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  epr_data_container.setCutoffElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            epr_data_container.getCutoffElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		           setCutoffElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setCutoffElasticCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the screened rutherford elastic electron cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setScreenedRutherfordElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.6e-6;
  cross_section[1] = 0.6e-1;
  cross_section[2] = 0.6;

  epr_data_container.setScreenedRutherfordElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            epr_data_container.getScreenedRutherfordElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		           setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( 
    epr_data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
    0 );
}

//---------------------------------------------------------------------------//
// Check that the total elastic electron cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setTotalElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setTotalElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            epr_data_container.getTotalElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		           setTotalElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setTotalElasticCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getTotalElasticCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving (MP) elastic electron cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setMomentPreservingCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setMomentPreservingCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            epr_data_container.getMomentPreservingCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		        setMomentPreservingCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setMomentPreservingCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getMomentPreservingCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization electron cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  unsigned subshell = 1;

  epr_data_container.setElectroionizationCrossSection( 
                        subshell,
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            epr_data_container.getElectroionizationCrossSection( subshell ),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the electroionization cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		        setElectroionizationCrossSectionThresholdEnergyIndex )
{
  unsigned subshell = 1;

  epr_data_container.setElectroionizationCrossSectionThresholdEnergyIndex( subshell, 0 );

  TEST_EQUALITY_CONST( 
    epr_data_container.getElectroionizationCrossSectionThresholdEnergyIndex( subshell ),
    0 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung electron cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setBremsstrahlungCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            epr_data_container.getBremsstrahlungCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		        setBremsstrahlungCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setBremsstrahlungCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation electron cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setAtomicExcitationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setAtomicExcitationCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            epr_data_container.getAtomicExcitationCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		        setAtomicExcitationCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAtomicExcitationCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   export_importData_ascii )
{
  const std::string test_ascii_file_name( "test_epr_data_container.txt" );

  epr_data_container.exportData( test_ascii_file_name,
				 Utility::ArchivableObject::ASCII_ARCHIVE );

  const Data::ElectronPhotonRelaxationDataContainer 
    epr_data_container_copy( test_ascii_file_name, 
			     Utility::ArchivableObject::ASCII_ARCHIVE );

  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffAngle(), 0.10 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticPDF(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMoliereScreeningConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticWeights(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSection(1u).size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSectionThresholdEnergyIndex(1u),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   export_importData_binary )
{
  const std::string test_binary_file_name( "test_epr_data_container.bin" );

  epr_data_container.exportData( test_binary_file_name,
				 Utility::ArchivableObject::BINARY_ARCHIVE );

  const Data::ElectronPhotonRelaxationDataContainer 
    epr_data_container_copy( test_binary_file_name, 
			     Utility::ArchivableObject::BINARY_ARCHIVE );

  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffAngle(), 0.10 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticPDF(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMoliereScreeningConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticWeights(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSection(1u).size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSectionThresholdEnergyIndex(1u),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   export_importData_xml )
{
  const std::string test_xml_file_name( "test_epr_data_container.xml" );

  epr_data_container.exportData( test_xml_file_name,
				 Utility::ArchivableObject::XML_ARCHIVE );

  const Data::ElectronPhotonRelaxationDataContainer 
    epr_data_container_copy( test_xml_file_name, 
			     Utility::ArchivableObject::XML_ARCHIVE );

  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffAngle(), 0.10 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticPDF(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMoliereScreeningConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticWeights(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSection(1u).size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSectionThresholdEnergyIndex(1u),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be packed into a string and unpacked from a string
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   pack_unpackDataFromString )
{
  std::string packed_data = epr_data_container.packDataInString();

  Data::ElectronPhotonRelaxationVolatileDataContainer epr_data_container_copy;
  
  epr_data_container_copy.unpackDataFromString( packed_data );
  
  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupationNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffAngle(), 0.10 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAnalogElasticPDF(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMoliereScreeningConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingElasticWeights(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getCutoffElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getTotalElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSection(1u).size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getElectroionizationCrossSectionThresholdEnergyIndex(1u),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    epr_data_container_copy.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// end tstElectronPhotonRelaxationDataContainer.cpp
//---------------------------------------------------------------------------//
