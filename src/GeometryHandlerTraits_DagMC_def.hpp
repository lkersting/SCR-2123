//---------------------------------------------------------------------------//
//!
//! \file   GeometryHandlerTraits_DagMC_def.hpp
//! \author Alex Robinson
//! \brief  DagMC specialization of the GeometryHandlerTraits class (def.)
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_HANDLER_TRAITS_DAGMC_DEF_HPP
#define GEOMETRY_HANDLER_TRAITS_DAGMC_DEF_HPP

// Std Lib Includes
#include <limits>

// FACEMC Includes
#include "MOABException.hpp"
#include "ExceptionTestMacros.hpp"
#include "ContractException.hpp"

namespace FACEMC{

namespace Traits{

// Get an instance of DagMC (singleton pattern)
inline GeometryHandlerTraits<moab::DagMC>::GeometryHandlerPtr 
GeometryHandlerTraits<moab::DagMC>::getHandler()
{ 
  return moab::DagMC::instance(); 
}

// Fire a ray through the geometry
/*! \details If for any reason the ray fire fails, a FACEMC::MOABException 
 * will be thrown. This exception should be caught and a lost particle should
 * be indicated.
 */
inline void GeometryHandlerTraits<moab::DagMC>::fireRay( 
				     const ParticleState<CellHandle>& particle,
				     SurfaceHandle& surface_hit,
				     double& distance_to_surface_hit )
{
  moab::ErrorCode return_value = 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->ray_fire( 
			    particle.getCell(),
			    particle.getPosition(),
			    particle.getDirection(),
			    surface_hit,
			    distance_to_surface_hit,
			    &GeometryHandlerTraits<moab::DagMC>::ray_history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );
}

// Indicate that a new ray will be started (after a collision)
/*! \details DagMC has an internal RayHistory class that it uses to help with
 * ray tracing. This class simply stores the entity handles of surface facets
 * that have been crossed so that those facets will not be intersected again by
 * the current ray. This class is very specific to DagMC and thus should be 
 * hidden from the rest of FACEMC so that genericity in the particle tracking 
 * algorithms is maintained. This specialized class has a RayHistory instance 
 * stored as a private static member. Everytime a particle changes direction 
 * and ray tracing recommences, this function must be called to reset the 
 * RayHistory instance. In other specializations this function may be 
 * optimized out.
 */
inline void GeometryHandlerTraits<moab::DagMC>::newRay()
{
  GeometryHandlerTraits<moab::DagMC>::ray_history.reset();
}

// Update the cell that contains a given particle (start of history)
/*! \details This function should be called after a particle is generated. It
 * is used to find the starting cell of a particle, which must be done before
 * ray tracing may begin. The cell containing the particle will be updated
 * in the particle class. If no cell can be found, a FACEMC::MOABException will
 * be thrown. This exception should be caught and a lost particle should be
 * indicated.
 */
inline void GeometryHandlerTraits<moab::DagMC>::updateCellContainingParticle( 
					  ParticleState<CellHandle>& particle )
{
  // Reset the RayHistory
  GeometryHandlerTraits<moab::DagMC>::newRay();
  
  if( GeometryHandlerTraits<moab::DagMC>::all_cells.empty() )    
    GeometryHandlerTraits<moab::DagMC>::getAllCells();
  
  CellHandle cell_containing_point = 
    GeometryHandlerTraits<moab::DagMC>::invalidCellHandle;
  
  // Try using the cells found to contain previously tested particles first.
  GeometryHandlerTraits<moab::DagMC>::testCellsContainingTestPoints( 
							 cell_containing_point,
							 particle );
  
  // Try all remaining cells
  if( cell_containing_point == 
      GeometryHandlerTraits<moab::DagMC>::invalidCellHandle )
  {
    GeometryHandlerTraits<moab::DagMC>::testAllRemainingCells(
							 cell_containing_point,
							 particle );
  }
  
  // Test if the particle is lost
  TEST_FOR_EXCEPTION( cell_containing_point == 
		      GeometryHandlerTraits<moab::DagMC>::invalidCellHandle,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[4] );
  
  // Update the particle state
  particle.setCell( cell_containing_point );
}
						  
// Update the cell that contains a given particle (surface crossing)
/*! \details This function should be called after a particle has intersected a
 * surface. It is used to find the cell on the other side of the surface (at
 * the point of intersection. The cell containing the particle will be updated
 * in the particle class. If no cell can be found, a FACEMC::MOABException will
 * be thrown. This exception should be caught and a lost particle should be
 * indicated.
 */
inline void GeometryHandlerTraits<moab::DagMC>::updateCellContainingParticle( 
					  const SurfaceHandle& surface,
				          ParticleState<CellHandle>& particle )
  {
    CellHandle next_cell;
    
    moab::ErrorCode return_value = 
      GeometryHandlerTraits<moab::DagMC>::dagmc_instance->next_vol( 
							    surface, 
							    particle.getCell(),
							    next_cell );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			FACEMC::MOABException,
			moab::ErrorCodeStr[return_value] );

    particle.setCell( next_cell );
  }

// Check if the cell is a termination cell
inline bool GeometryHandlerTraits<moab::DagMC>::isTerminationCell( 
						       const CellHandle& cell )
{
  return GeometryHandlerTraits<moab::DagMC>::dagmc_instance->has_prop( cell, GeometryHandlerTraits<moab::DagMC>::termination_cell_property_name );
}

// Get the particle location w.r.t. a given cell
/*! \details This function is used to determine if a particle is in, on, or
 * outside a given cell. If a particles position relative to a cell cannot
 * be determined, a FACEMC::MOABException will be thrown. This exception 
 * should be caught and a lost particle should be indicated.
 */
inline PointLocation GeometryHandlerTraits<moab::DagMC>::getParticleLocation(
				    const CellHandle& cell,
				    const ParticleState<CellHandle>& particle )
					     
{
  int test_result;
  moab::ErrorCode return_value = 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->point_in_volume( 
			    cell,
			    particle.getPosition(),
			    test_result,
			    particle.getDirection(),
			    &GeometryHandlerTraits<moab::DagMC>::ray_history );
    
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  switch( test_result )
  {
  case -1: 
    return POINT_ON_CELL;
  case 0:
    return POINT_OUTSIDE_CELL;
  case 1:
    return POINT_INSIDE_CELL;
  }
}

// Get the surface normal at a point on the surface
/* \details This function will throw a FACEMC::MOABException if the desired
 * surface does not exist or if the particle is not actually on the surface.
 */
inline void GeometryHandlerTraits<moab::DagMC>::getSurfaceNormal( 
				     const SurfaceHandle& surface,
				     const ParticleState<CellHandle>& particle,
				     double normal[3] )
{
  moab::ErrorCode return_value =
      GeometryHandlerTraits<moab::DagMC>::dagmc_instance->get_angle( 
			    surface, 
			    particle.getPosition(), 
			    normal, 
			    &GeometryHandlerTraits<moab::DagMC>::ray_history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );
}

// Get the volume of a cell
/*! \details This function will throw a FACEMC::MOABException if the desired
 * cell does not exist.
 */
inline double GeometryHandlerTraits<moab::DagMC>::getCellVolume( 
						       const CellHandle& cell )
{
  double volume = 0.0;
  
  moab::ErrorCode return_value = 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->measure_volume( 
								      cell, 
								      volume );
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );

  // Make sure that the calculated volume is valid
  testPostcondition( !ST::isnaninf( volume ) );
  testPostcondition( volume > 0.0 );
  
  return volume;
}

// Get the surface area of a surface bounding a cell
/*! \details This function will throw a FACEMC::MOABException if the 
 * desired surface does not exist.
 */ 
inline double GeometryHandlerTraits<moab::DagMC>::getCellSurfaceArea( 
						  const SurfaceHandle& surface,
						  const CellHandle& cell )
{
  double area = 0.0;
  
  moab::ErrorCode return_value = 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->measure_area( surface, 
								      area );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );
  
  // Make sure that the calculated area is valid
  testPostcondition( !ST::isnaninf( area ) );
  testPostcondition( area > 0.0 );
  
  return area;
}  

// Get the cell id corresponding to the cell handle
inline GeometryHandlerTraits<moab::DagMC>::CellId 
GeometryHandlerTraits<moab::DagMC>::getCellId( const CellHandle& cell )
{
  return 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->get_entity_id( cell );
}

// Get the surface id corresponding to the surface handle
inline GeometryHandlerTraits<moab::DagMC>::SurfaceId 
GeometryHandlerTraits<moab::DagMC>::getSurfaceId( const SurfaceHandle& surface)
{
  return 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->get_entity_id(surface);
}

// Get all the cells contained in the geometry
void GeometryHandlerTraits<moab::DagMC>::getAllCells()
{
  moab::Interface* moab_instance = 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->moab_instance();
  
  const int three = 3;
  const void* const three_val[] = {&three};
  
  moab::Tag geom_tag = 
    GeometryHandlerTraits<moab::DagMC>::dagmc_instance->geom_tag();
  
  moab::ErrorCode return_value = 
    moab_instance->get_entities_by_type_and_tag( 
			       0, 
			       moab::MBENTITYSET,
			       &geom_tag,
			       three_val,
			       1,
			       GeometryHandlerTraits<moab::DagMC>::all_cells );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      FACEMC::MOABException,
		      moab::ErrorCodeStr[return_value] );
}

// Test the cells found to contain test points for point containment
inline void GeometryHandlerTraits<moab::DagMC>::testCellsContainingTestPoints( 
				    CellHandle& cell,
				    const ParticleState<CellHandle>& particle )
{
  std::set<CellHandle>::const_iterator cell_handle = 
    GeometryHandlerTraits<moab::DagMC>::cells_containing_test_points.begin();
    
  std::set<CellHandle>::const_iterator end_cell_handle = 
    GeometryHandlerTraits<moab::DagMC>::cells_containing_test_points.end();
    
  while( cell_handle != end_cell_handle )
  {
    PointLocation test_point_location = 
      GeometryHandlerTraits<moab::DagMC>::getParticleLocation( *cell_handle,
							       particle );
    
    if( test_point_location == POINT_INSIDE_CELL )
    {
      cell = *cell_handle;
      
      break;
    }
    else
      ++cell_handle;
  }
}

// Test all remaining cells for point containment
void GeometryHandlerTraits<moab::DagMC>::testAllRemainingCells(
				   CellHandle& cell,
				   const ParticleState<CellHandle>& particle )
{
  moab::Range::const_iterator cell_handle = 
    GeometryHandlerTraits<moab::DagMC>::all_cells.begin();
  
  moab::Range::const_iterator end_cell_handle = 
    GeometryHandlerTraits<moab::DagMC>::all_cells.end();
  
  while( cell_handle != end_cell_handle )
  {
    PointLocation test_point_location = 
      GeometryHandlerTraits<moab::DagMC>::getParticleLocation( *cell_handle,
							       particle );
    
    if( test_point_location == POINT_INSIDE_CELL )
    {
      cell = *cell_handle;
      
      // Add the cell to the set of cells found to contain test points
      GeometryHandlerTraits<moab::DagMC>::cells_containing_test_points.insert( 
								*cell_handle );
      
      // Remove the entity handle from the remaining cells container so 
      // that it is not checked twice in the future.
      GeometryHandlerTraits<moab::DagMC>::all_cells.erase( cell );
	
      break;
    }
    else
      ++cell_handle;
  }
}

} // end Traits namespace

} // end FACEMC namespace

#endif // end GEOMETRY_HANDLER_TRAITS_DAGMC_DEF_HPP

//---------------------------------------------------------------------------//
// end GeometryHandlerTraits_DagMC_def.hpp
//---------------------------------------------------------------------------//
