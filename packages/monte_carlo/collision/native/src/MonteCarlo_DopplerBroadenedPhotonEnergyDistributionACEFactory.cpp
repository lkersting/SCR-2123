//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy distribution ACE factory def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_CoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution>&
		  doppler_broadened_dist,
		  const bool use_full_profile )
{
  // Create the subshell order array
  Teuchos::Array<SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  // Create the Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> converter;
  
  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );
  
  // Create the compton profile distributions
  Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
    compton_profiles;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDistArray(
							    raw_photoatom_data,
							    use_full_profile,
							    compton_profiles );

  doppler_broadened_dist.reset( 
		  new CoupledCompleteDopplerBroadenedPhotonEnergyDistribution( 
			   raw_photoatom_data.extractSubshellBindingEnergies(),
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   converter,
			   compton_profiles ) );
}

// Create a coupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution(
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
	  doppler_broadened_dist,
	  const bool use_full_profile )
{
  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createCoupledCompleteDistribution( 
							    raw_photoatom_data,
							    dist,
							    use_full_profile );

  doppler_broadened_dist = 
    Teuchos::rcp_dynamic_cast<const CompleteDopplerBroadenedPhotonEnergyDistribution>( dist );
}

// Create a decoupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution>&
		  doppler_broadened_dist,
		  const bool use_full_profile )
{
  // Create the subshell order array
  Teuchos::Array<SubshellType> subshell_order;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
							    raw_photoatom_data,
							    subshell_order );

  // Create the compton profile distributions
  Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
    compton_profiles;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDistArray(
							    raw_photoatom_data,
							    use_full_profile,
							    compton_profiles );
  
  doppler_broadened_dist.reset( 
		new DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution( 
			   raw_photoatom_data.extractSubshellOccupancies(),
			   subshell_order,
			   raw_photoatom_data.extractLBEPSBlock(),
			   raw_photoatom_data.extractLNEPSBlock(),
			   compton_profiles ) );
}

// Create a decoupled complete Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution(
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  Teuchos::RCP<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
	  doppler_broadened_dist,
	  const bool use_full_profile )
{
  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createDecoupledCompleteDistribution( 
							    raw_photoatom_data,
							    dist,
							    use_full_profile );

  doppler_broadened_dist = 
    Teuchos::rcp_dynamic_cast<const CompleteDopplerBroadenedPhotonEnergyDistribution>( dist );
}

// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution(
		  const Data::XSSEPRDataExtractor& raw_photoatom_data,
		  const unsigned endf_subshell,
		  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution>&
		  doppler_broadened_dist,
		  const bool use_full_profile )
{
  // Convert the endf subshell to a subshell type
  SubshellType subshell = convertENDFDesignatorToSubshellEnum( endf_subshell );
  
  TEST_FOR_EXCEPTION( subshell == INVALID_SUBSHELL,
		      std::logic_error,
		      "Error: the requested endf subshell " << 
		      endf_subshell << " is invalid! " );

  // Create the Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> converter;
  
  ComptonProfileSubshellConverterFactory::createConverter(
				    converter,
				    raw_photoatom_data.extractAtomicNumber() );

  // Get the Compton profile index corresponding to the ENDF subshell
  unsigned compton_index;
  
  try{
    compton_index = converter->convertSubshellToIndex( subshell );
  }
  EXCEPTION_CATCH_RETHROW( std::logic_error,
			   "Error: the requested endf subshell " 
			   << endf_subshell << " is invalid!" );

  // Extract the Compton profile
  Teuchos::ArrayView<const double> lswd_block = 
    raw_photoatom_data.extractLSWDBlock();
  
  Teuchos::ArrayView<const double> swd_block = 
    raw_photoatom_data.extractSWDBlock(); 

  unsigned subshell_index = lswd_block[compton_index]; 
    
  unsigned num_momentum_points = swd_block[subshell_index];
    
  Teuchos::Array<double> half_momentum_grid( 
			swd_block( subshell_index + 1, num_momentum_points ) );

  Teuchos::Array<double> half_profile(
                           swd_block( subshell_index + 1 + num_momentum_points,
				      num_momentum_points ) );

  Teuchos::RCP<const Utility::TabularOneDDistribution> compton_profile;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDist(
							    half_momentum_grid,
							    half_profile,
							    use_full_profile,
							    compton_profile );

  doppler_broadened_dist.reset(
		      new SubshellDopplerBroadenedPhotonEnergyDistribution(
			 subshell,
			 raw_photoatom_data.extractLNEPSBlock()[compton_index],
		         raw_photoatom_data.extractLBEPSBlock()[compton_index],
			 compton_profile ) );
			 
}

// Create a subshell Doppler broadened photon energy dist
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution(
	  const Data::XSSEPRDataExtractor& raw_photoatom_data,
	  const unsigned endf_subshell,
	  Teuchos::RCP<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
	  doppler_broadened_dist,
	  const bool use_full_profile )
{
  Teuchos::RCP<const DopplerBroadenedPhotonEnergyDistribution> dist;

  DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellDistribution( 
							    raw_photoatom_data,
							    endf_subshell,
							    dist,
							    use_full_profile );

  doppler_broadened_dist = 
    Teuchos::rcp_dynamic_cast<const SubshellDopplerBroadenedPhotonEnergyDistribution>( dist );
}

// Create the subshell order array
void 
DopplerBroadenedPhotonEnergyDistributionACEFactory::createSubshellOrderArray(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   Teuchos::Array<SubshellType>& subshell_order )
{
  Teuchos::ArrayView<const double> subshell_endf_designators = 
    raw_photoatom_data.extractSubshellENDFDesignators();
  
  subshell_order.resize( subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
  }
}

// Create the Compton profile distribution
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDistArray(
	 const Data::XSSEPRDataExtractor& raw_photoatom_data,
	 const bool use_full_profile,
	 Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >&
	 compton_profiles )
{
  Teuchos::ArrayView<const double> lswd_block = 
    raw_photoatom_data.extractLSWDBlock();
  
  Teuchos::ArrayView<const double> swd_block = 
    raw_photoatom_data.extractSWDBlock(); 

  compton_profiles.resize( lswd_block.size() );
  
  for( unsigned subshell = 0; subshell < lswd_block.size(); ++subshell )
  {
    unsigned subshell_index = lswd_block[subshell]; 
    
    unsigned num_momentum_points = swd_block[subshell_index];
    
    Teuchos::Array<double> half_momentum_grid( 
			swd_block( subshell_index + 1, num_momentum_points ) );

    Teuchos::Array<double> half_profile(
                           swd_block( subshell_index + 1 + num_momentum_points,
				      num_momentum_points ) );

    DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDist(
						  half_momentum_grid,
						  half_profile,
						  use_full_profile,
						  compton_profiles[subshell] );
  }
}

// Create the Compton profile distribution
void DopplerBroadenedPhotonEnergyDistributionACEFactory::createComptonProfileDist(
			  Teuchos::Array<double>& raw_half_momentum_grid,
			  Teuchos::Array<double>& raw_half_profile,
			  const bool use_full_profile,
                          Teuchos::RCP<const Utility::TabularOneDDistribution>&
			  compton_profile_dist )
{
  // Make sure the half grid and profile are valid
  testPrecondition( raw_half_momentum_grid.size() > 1 );
  testPrecondition( raw_half_profile.size() ==
		    raw_half_momentum_grid.size() );
  
  if( use_full_profile )
  {
    Teuchos::Array<double> full_momentum_grid, full_profile;
    
    MonteCarlo::createFullProfileFromHalfProfile( raw_half_momentum_grid.begin(),
						  raw_half_momentum_grid.end(),
						  raw_half_profile.begin(),
						  raw_half_profile.end(),
						  full_momentum_grid,
						  full_profile );
    
    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );
    
    MonteCarlo::convertProfileToInverseMeCUnits( full_profile.begin(),
						 full_profile.end() );
    
    // Ignore interp parameter (always assume lin-lin inerpolation)
    compton_profile_dist.reset(
	 new Utility::TabularDistribution<Utility::LinLin>( full_momentum_grid,
							    full_profile ) );
  }
  else
  {
    MonteCarlo::convertMomentumGridToMeCUnits( raw_half_momentum_grid.begin(),
					       raw_half_momentum_grid.end() );
    
    MonteCarlo::convertProfileToInverseMeCUnits( raw_half_profile.begin(),
						 raw_half_profile.end() );
    
    // Ignore interp parameter (always assume lin-lin interpolation)
    compton_profile_dist.reset(
		          new Utility::TabularDistribution<Utility::LinLin>( 
						        raw_half_momentum_grid,
							raw_half_profile ) );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
