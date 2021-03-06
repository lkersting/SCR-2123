//---------------------------------------------------------------------------//
//! 
//! \file   tstModuleInterface.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Geometry module interface unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_Root.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#include "Geometry_Ray.hpp"

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geom_root_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that cells can be checked for existence
TEUCHOS_UNIT_TEST( ModuleInterface_Root, canBeCheckedForExist )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;
  
  // Test that cell 1 exists
  TEST_ASSERT( GMI::doesCellExist( 1 ) );
  
  // Test that cell 2 exists
  TEST_ASSERT( GMI::doesCellExist( 2 ) );
  
  // Test that cell 3 does exist
  TEST_ASSERT( GMI::doesCellExist( 3 ) );
  
  // Test that cell 4 does not exist
  TEST_ASSERT( !GMI::doesCellExist( 4 ) );
}

//---------------------------------------------------------------------------//
// Check that a cell containing a point can be determined (birth)
TEUCHOS_UNIT_TEST( ModuleInterface_Root, cellContainingPointBirth )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;

  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
  
  // Find cell containing ray
  GMI::InternalCellHandle cell = GMI::findCellContainingPoint( ray );
  
  TEST_EQUALITY_CONST( cell, 2 );
}

//---------------------------------------------------------------------------//
// Check that the distance to surface is calculated correctly
TEUCHOS_UNIT_TEST( ModuleInterface_Root, distanceToCrossing )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;

  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
  
  // Find the cell that contains the point
  GMI::InternalCellHandle cell = GMI::findCellContainingPoint( ray );
 
  // Fire a ray through the geometry
  GMI::InternalSurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GMI::fireRay( ray, cell, surface_hit, distance_to_surface_hit );
  
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 2.5, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the correct cell is found after a surface crossing
TEUCHOS_UNIT_TEST( ModuleInterface_Root, cellContainingPointSurfaceCrossing )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;

  // Initialize the ray
  Geometry::Ray ray( 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 );
  
  // Find the cell that contains the point
  GMI::InternalCellHandle cell = GMI::findCellContainingPoint( ray );
 
  // Fire a ray through the geometry
  GMI::InternalSurfaceHandle surface_hit;
  double distance_to_surface_hit;

  GMI::fireRay( ray, cell, surface_hit, distance_to_surface_hit );
  
  int cell_internal = GMI::findCellContainingPoint( ray, cell, surface_hit );
  
  TEST_EQUALITY_CONST( cell_internal, 1 );
}

//---------------------------------------------------------------------------//
// Check if cell is a termination cell
TEUCHOS_UNIT_TEST( ModuleInterface_Root, cellIsTerminationCell )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;

  // Test that the cube is full of termination material
  TEST_ASSERT( !GMI::isTerminationCell( 1 ) );
  
  // Test that the sphere is not full of termination material
  TEST_ASSERT( !GMI::isTerminationCell( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that a cell volume can be calculated
TEUCHOS_UNIT_TEST( ModuleInterface_Root, cellVolumeCanBeFound )
{
  typedef Geometry::ModuleInterface<Geometry::Root> GMI;

  double vol_sphere_calcluated = 65.4498469497874;
  double vol_cube_calculated   = 934.550153050213;
  double vol_term_cube_calculated = 1744.0;
  
  Double_t vol_sphere = GMI::getCellVolume( 2 );
  Double_t vol_cube   = GMI::getCellVolume( 1 );
  Double_t vol_term   = GMI::getCellVolume( 3 );
  
  TEST_FLOATING_EQUALITY( vol_sphere_calcluated, vol_sphere, 1e-9 );
  TEST_FLOATING_EQUALITY( vol_cube_calculated, vol_cube, 1e-9 );
  TEST_FLOATING_EQUALITY( vol_term_cube_calculated, vol_term, 1e-9 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  int threads = 1;

  clp.setOption( "test_root_file",
		 &test_geom_root_file_name,
		 "Test root geometry file name" );

  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );
  
  // Initialize Root
  Geometry::Root::initialize( test_geom_root_file_name );

  // Initialize the Module Interface
  Geometry::ModuleInterface<Geometry::Root>::initialize();
  
  mpiSession.barrier();
  
  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//

