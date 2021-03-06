//---------------------------------------------------------------------------//
// \file   tstConcavePolyhedralCell.cpp
// \author Alex Robinson
// \brief  Cell class unit test
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "Cell.hpp"
#include "Surface.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
#include "TestCell.hpp"

//---------------------------------------------------------------------------//
// Testing Info.
//---------------------------------------------------------------------------//
#define CELL_DEFINITION_1 "-1 n 2 n 3 n (-4 u -5) n -6 n 7"
#define SIMPLIFIED_CELL_DEFINITION_1 "-1   2   3    -4   -5    -6   7"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell can test if an intersection point is real
TEUCHOS_UNIT_TEST( Cell, testIntersectionPoint )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense>
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      1, 0, 0,
				      2 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 1, 0,
				      1 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      -1, 1, 0,
				      0 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      1, 1, 0,
				      0 ) );
  
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 1,
				      -4 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 7,
				      0, 0, 1,
				      0 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  FACEMC::Quad<double,double,unsigned,unsigned>
    intersection_point( -2.0, -1.0, 2, 3 );

  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point,
					   7 ) );

  intersection_point( -1.0, -1.0, 3, 4 );

  TEST_ASSERT( !cell.testIntersectionPoint( copy_cell_surfaces,
					    intersection_point,
					    7 ) );

  intersection_point( -1.0, -1.0, 4, 3 );

  TEST_ASSERT( !cell.testIntersectionPoint( copy_cell_surfaces,
					    intersection_point,
					    7 ) );

  intersection_point( 1.0, -1.0, 3, 5 );

  TEST_ASSERT( !cell.testIntersectionPoint( copy_cell_surfaces,
					    intersection_point,
					    7 ) );

  intersection_point( 1.0, -1.0, 5, 3 );

  TEST_ASSERT( !cell.testIntersectionPoint( copy_cell_surfaces,
					    intersection_point,
					    7 ) );

  intersection_point( 2.0, -1.0, 1, 3 );

  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point,
					   7 ) );

  intersection_point( 2.0, 2.0, 1, 4 );

  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point, 
					   7 ) );

  intersection_point( 0.0, 0.0, 4, 5 );

  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point,
					   7 ) );

  intersection_point( -2.0, 2.0, 2, 5 );

  TEST_ASSERT( cell.testIntersectionPoint( copy_cell_surfaces,
					   intersection_point,
					   7 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the intersection points with the z-axis
TEUCHOS_UNIT_TEST( Cell, calculatePolygonIntersectionPoints )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense>
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      1, 0, 0,
				      2 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 1, 0,
				      1 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      -1, 1, 0,
				      0 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      1, 1, 0,
				      0 ) );
  
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 1,
				      -4 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 7,
				      0, 0, 1,
				      0 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > intersection_points;

  cell.calculatePolygonIntersectionPoints( 7,
					   copy_cell_surfaces,
					   intersection_points );

  TEST_EQUALITY_CONST( intersection_points.size(), 5 );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    point = intersection_points.begin();

  FACEMC::Quad<double,double,unsigned,unsigned>
    ref_intersection_point( 2.0, -1.0, 1, 3 );

  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );

  ++point;
  ref_intersection_point( 2.0, 2.0, 1, 4 );

  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );

  ++point;
  ref_intersection_point( -2.0, -1.0, 2, 3 );

  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );

  ++point;
  ref_intersection_point( -2.0, 2.0, 2, 5 );
  
  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );

  ++point;
  ref_intersection_point( 0.0, 0.0, 4, 5 );
  
  FACEMC_TEST_EQUALITY( *point, ref_intersection_point );
}

//---------------------------------------------------------------------------//
// Check that the cell can initialize a polygon from a list of intersection 
// points
TEUCHOS_UNIT_TEST( Cell, initializePolygon )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense>
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      1, 0, 0,
				      2 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 1, 0,
				      1 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      -1, 1, 0,
				      0 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      1, 1, 0,
				      0 ) );
  
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 1,
				      -4 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 7,
				      0, 0, 1,
				      0 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > 
    intersection_points, polygon;

  cell.calculatePolygonIntersectionPoints( 7,
					   copy_cell_surfaces,
					   intersection_points );

  unsigned current_surface_id;
  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    start_point = cell.initializePolygon( polygon,
					  intersection_points,
					  copy_cell_surfaces,
					  current_surface_id );

  TEST_EQUALITY_CONST( polygon.size(), 3 );
  TEST_EQUALITY_CONST( intersection_points.size(), 2 );
  TEST_EQUALITY_CONST( current_surface_id, 5 );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    point = polygon.begin();

  FACEMC::Quad<double,double,unsigned,unsigned> 
    ref_corner_point( 2.0, -1.0, 1, 3 );

  FACEMC_TEST_EQUALITY( *start_point, ref_corner_point );
  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ++point;
  ref_corner_point( 2.0, 2.0, 1, 4 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );
  
  ++point;
  ref_corner_point( 0.0, 0.0, 4, 5 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );
}

//---------------------------------------------------------------------------//
// Check that the cell can create a polygon from a list of intersection points
TEUCHOS_UNIT_TEST( Cell, createPolygon )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense>
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      1, 0, 0,
				      2 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 1, 0,
				      1 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      -1, 1, 0,
				      0 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      1, 1, 0,
				      0 ) );
  
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 1,
				      -4 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 7,
				      0, 0, 1,
				      0 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > 
    intersection_points, polygon;

  cell.calculatePolygonIntersectionPoints( 7,
					   copy_cell_surfaces,
					   intersection_points );

  cell.createPolygon( intersection_points,
		      copy_cell_surfaces );

  TEST_EQUALITY_CONST( intersection_points.size(), 6 );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> >::const_iterator
    point = intersection_points.begin();
  
  FACEMC::Quad<double,double,unsigned,unsigned> 
    ref_corner_point( 2.0, -1.0, 1, 3 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ++point;
  ref_corner_point( 2.0, 2.0, 1, 4 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ++point;
  ref_corner_point( 0.0, 0.0, 4, 5 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ++point;
  ref_corner_point( -2.0, 2.0, 2, 5 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ++point;
  ref_corner_point( -2.0, -1.0, 2, 3 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );

  ++point;
  ref_corner_point( 2.0, -1.0, 1, 3 );

  FACEMC_TEST_EQUALITY( *point, ref_corner_point );
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the area of the polygon created from the
// intersection points
TEUCHOS_UNIT_TEST( Cell, calculatePolygonArea )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense>
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      1, 0, 0,
				      2 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 1, 0,
				      1 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      -1, 1, 0,
				      0 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      1, 1, 0,
				      0 ) );
  
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 1,
				      -4 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 7,
				      0, 0, 1,
				      0 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > 
    intersection_points, polygon;

  cell.calculatePolygonIntersectionPoints( 7,
					   copy_cell_surfaces,
					   intersection_points );

  cell.createPolygon( intersection_points,
		      copy_cell_surfaces );

  std::list<double> polygon_areas;

  cell.calculatePolygonArea( 7,
			     intersection_points,
			     polygon_areas );

  TEST_EQUALITY_CONST( polygon_areas.front(), 8.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the volume contribution of the polygon 
// created from intersection points
TEUCHOS_UNIT_TEST( Cell, calculatePolygonVolumeContribution )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  TestCell cell( cell_definition );

  Teuchos::Array<FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense> >
    copy_cell_surfaces;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  FACEMC::Pair<FACEMC::Surface,FACEMC::Surface::Sense>
    copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 2,
				      1, 0, 0,
				      2 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 3,
				      0, 1, 0,
				      1 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 4,
				      -1, 1, 0,
				      0 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 5,
				      1, 1, 0,
				      0 ) );
  
  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 1,
				      -4 ) );

  copy_surface( *surface, -1 );
  copy_cell_surfaces.push_back( copy_surface );

  surface.reset( new FACEMC::Surface( 7,
				      0, 0, 1,
				      0 ) );

  copy_surface( *surface, 1 );
  copy_cell_surfaces.push_back( copy_surface );

  std::list<FACEMC::Quad<double,double,unsigned,unsigned> > 
    intersection_points, polygon;

  cell.calculatePolygonIntersectionPoints( 7,
					   copy_cell_surfaces,
					   intersection_points );

  cell.createPolygon( intersection_points,
		      copy_cell_surfaces );

  std::list<double> polygon_areas;

  cell.calculatePolygonArea( 7,
			     intersection_points,
			     polygon_areas );

  FACEMC::Surface reference_surface( 0, 
				     0, 0, 1, 
				     -4 );
  
  cell.calculatePolygonVolumeContribution( reference_surface,
					   intersection_points,
					   polygon_areas,
					   -1,
					   1 );

  TEST_EQUALITY_CONST( cell.getVolume(), 32.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell can calculate the surface area of all surfaces bounding
// the cell and the cell volume assuming a polyhedral cell
TEUCHOS_UNIT_TEST( Cell, constructor )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  std::map<unsigned,Teuchos::RCP<FACEMC::Surface> > global_surface_map;

  Teuchos::RCP<FACEMC::Surface> surface( new FACEMC::Surface( 1,
							      1, 0, 0,
							      -2 ) );

  global_surface_map[1] = surface;

  surface.reset( new FACEMC::Surface( 2,
				      1, 0, 0,
				      2 ) );

  global_surface_map[2] = surface;
  
  surface.reset( new FACEMC::Surface( 3,
				      0, 1, 0,
				      1 ) );

  global_surface_map[3] = surface;
  
  surface.reset( new FACEMC::Surface( 4,
				      -1, 1, 0,
				      0 ) );

  global_surface_map[4] = surface;
  
  surface.reset( new FACEMC::Surface( 5,
				      1, 1, 0,
				      0 ) );
  
  global_surface_map[5] = surface;
  
  surface.reset( new FACEMC::Surface( 6,
				      0, 0, 1,
				      -4 ) );

  global_surface_map[6] = surface;
  
  surface.reset( new FACEMC::Surface( 7,
				      0, 0, 1,
				      0 ) );
  global_surface_map[7] = surface;

  Teuchos::RCP<FACEMC::Cell> cell( new FACEMC::Cell( 1,
						     cell_definition,
						     global_surface_map,
						     true ) );
  
  TEST_FLOATING_EQUALITY( cell->getVolume(), 32.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cell->getSurfaceArea( 1 ), 12.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cell->getSurfaceArea( 2 ), 12.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cell->getSurfaceArea( 3 ), 16.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cell->getSurfaceArea( 4 ), 8*sqrt(2), 1e-12 );
  TEST_FLOATING_EQUALITY( cell->getSurfaceArea( 5 ), 8*sqrt(2), 1e-12 );
  TEST_FLOATING_EQUALITY( cell->getSurfaceArea( 6 ), 8.0, 1e-12 );
  TEST_FLOATING_EQUALITY( cell->getSurfaceArea( 7 ), 8.0, 1e-12 );
}
//---------------------------------------------------------------------------//
// end tstConcavePolyhedralCell.cpp
//---------------------------------------------------------------------------//

