//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionEntryConverterDB.cpp
//! \author Alex Robinson
//! \brief  1D distribution parameter entry converter database definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize the static member data
OneDDistributionEntryConverterDB::ConverterMap 
OneDDistributionEntryConverterDB::master_map;

const bool OneDDistributionEntryConverterDB::initialized = 
  OneDDistributionEntryConverterDB::initialize();

// Add a converter to the database
void OneDDistributionEntryConverterDB::addConverter(
	 const Teuchos::RCP<OneDDistributionEntryConverter>& converter_to_add )
{
  OneDDistributionEntryConverterDB::master_map[converter_to_add->getTypeName()]
    = converter_to_add;
}

// Get the appropriate converter for the given parameter entry
Teuchos::RCP<OneDDistributionEntryConverter>
OneDDistributionEntryConverterDB::getConverter(
		     const Teuchos::RCP<const Teuchos::ParameterEntry>& entry )
{
  ConverterMap::const_iterator it =
    OneDDistributionEntryConverterDB::master_map.find( 
						  entry->getAny().typeName() );
 
  TEST_FOR_EXCEPTION( it == OneDDistributionEntryConverterDB::master_map.end(),
  		      InvalidDistributionStringName,
  		      "Error: The 1D distribution "
  		      << entry->getAny().typeName()
  		      << " is not currently supported!" );

  return it->second;
} 

// Get the OneDDistribution from the given parameter entry
Teuchos::RCP<OneDDistribution> OneDDistributionEntryConverterDB::convertEntry(
                     const Teuchos::RCP<const Teuchos::ParameterEntry>& entry )
{
  Teuchos::RCP<OneDDistributionEntryConverter> converter = 
    OneDDistributionEntryConverterDB::getConverter( entry );

  return converter->getDistribution( entry );
}

// Initialize the class
bool OneDDistributionEntryConverterDB::initialize()
{
  UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DB_SETUP();

  return true;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionEntryConverterDB.cpp
//---------------------------------------------------------------------------//
