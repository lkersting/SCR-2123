//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCInstanceFactory.cpp
//! \author Alex Robinson
//! \brief  DagMC instance factory class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Include
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_DagMCProperties.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_geom_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that DagMC can be properly initialized
TEUCHOS_UNIT_TEST( DagMCInstanceFactory, initializeDagMC )
{
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
  
  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getTerminationCellPropertyName(),
		       "graveyard" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getMaterialPropertyName(),
		       "mat" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getDensityPropertyName(),
		       "rho" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getEstimatorPropertyName(),
		       "tally" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getSurfaceCurrentName(),
		       "surf.cur" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getSurfaceFluxName(),
		       "surf.flux" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getCellPulseHeightName(),
		       "c.pulse" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getCellTrackLengthFluxName(),
		       "c.tl.f" );
  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getCellCollisionFluxName(),
		       "c.c.f" );

  boost::unordered_map<std::string,
		      std::vector<Geometry::ModuleTraits::InternalCellHandle> >
    prop_value_cell_id_map;

  Geometry::getCellIdsWithPropertyValue(
			  Geometry::DagMCProperties::getMaterialPropertyName(),
			  prop_value_cell_id_map );

  TEST_EQUALITY_CONST( prop_value_cell_id_map["9"].size(), 36 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["1"].size(), 2 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["2"].size(), 1 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["3"].size(), 7 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].size(), 2 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["10"].size(), 1 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["8"].size(), 1 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["4"].size(), 2 );
  TEST_EQUALITY_CONST( prop_value_cell_id_map["7"].size(), 4 );

  boost::unordered_map<std::string,
		   std::vector<Geometry::ModuleTraits::InternalSurfaceHandle> >
    prop_value_surface_id_map;

  Geometry::getSurfaceIdsWithPropertyValue(
			 Geometry::DagMCProperties::getEstimatorPropertyName(),
			 prop_value_surface_id_map);
  
  TEST_EQUALITY_CONST(prop_value_surface_id_map["5.surf.flux.n"].size(), 7);
  TEST_EQUALITY_CONST(prop_value_surface_id_map["6.surf.flux.p"].size(), 7);
  TEST_EQUALITY_CONST( prop_value_surface_id_map["7.surf.cur.n"].size(),
		       7);
  TEST_EQUALITY_CONST( prop_value_surface_id_map["8.surf.cur.p"].size(),
		       7);
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_xml_file",
		 &test_geom_xml_file_name,
		 "Test xml geometry file name" );
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}

//---------------------------------------------------------------------------//
// end tstDagMCInstanceFactory.cpp
//---------------------------------------------------------------------------//
