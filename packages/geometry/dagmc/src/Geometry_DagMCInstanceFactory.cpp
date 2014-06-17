//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCInstanceFactory.hpp
//! \author Alex Robinson
//! \brief  Dagmc instance factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <map>

// FRENSIE Includes
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize DagMC
void DagMCInstanceFactory::initializeDagMC( 
				       const Teuchos::ParameterList& geom_rep )
{
  // Validate the geometry representation
  DagMCInstanceFactory::validateGeometryRep( geom_rep );

  // Get the CAD file name
  std::string cad_file_name = geom_rep.get<std::string>( "CAD File" );

  // Get the face tolerance
  double facet_tol = 1e-3; // default value

  if( geom_rep.isParameter( "Facet Tolerance" ) )
    facet_tol = geom_rep.get<double>( "Facet Tolerance" );

  // Get the property synonyms
  std::vector<std::string> properties( 9 );

  if( geom_rep.isParameter( "Termination Cell Synonym" ) )
  {
    properties[0] = geom_rep.get<std::string>( "Termination Cell Synonym" ); 
    
    DagMCProperties::setTerminationCellPropertyName( properties[0] );
  }
  else
    properties[0] = DagMCProperties::getTerminationCellPropertyName();

  if( geom_rep.isParameter( "Material Synonym" ) )
  {
    properties[1] = geom_rep.get<std::string>( "Material Synonym" );

    DagMCProperties::setMaterialPropertyName( properties[1] );
  }
  else
    properties[1] = DagMCProperties::getMaterialPropertyName();

  if( geom_rep.isParameter( "Density Synonym" ) )
  {
    properties[2] = geom_rep.get<std::string>( "Density Synonym" );

    DagMCProperties::setDensityPropertyName( properties[2] );
  }
  else
    properties[2] = DagMCProperties::getDensityPropertyName();

  if( geom_rep.isParameter( "Estimator Synonym" ) )
  {
    properties[3] = geom_rep.get<std::string>( "Estimator Synonym" );

    DagMCProperties::setEstimatorPropertyName( properties[3] );
  }
  else
    properties[3] = DagMCProperties::getEstimatorPropertyName();

  if( geom_rep.isParameter( "Cell Track Length Flux Estimator Synonym" ) )
  {
    properties[4] = geom_rep.get<std::string>( "Cell Track Length Flux Estimator Synonym" );
    
    DagMCProperties::setCellTrackLengthFluxPropertyName( properties[4] );
  }
  else
    properties[4] = DagMCProperties::getCellTrackLengthFluxPropertyName();
  
  if( geom_rep.isParameter( "Cell Collision Flux Estimator Synonym" ) )
  {
    properties[5] = geom_rep.get<std::string>( "Cell Collision Flux Estimator Synonym" );
    
    DagMCProperties::setCellCollisionFluxPropertyName( properties[5] );
  }
  else
    properties[5] = DagMCProperties::getCellCollisionFluxPropertyName();

  if( geom_rep.isParameter( "Cell Pulse Height Estimator Synonym" ) )
  {
    properties[6] = geom_rep.get<std::string>( "Cell Pulse Height Estimator Synonym" );
    
    DagMCProperties::setCellPulseHeightPropertyName( properties[6] );
  }
  else
    properties[6] = DagMCProperties::getCellPulseHeightPropertyName();

  if( geom_rep.isParameter( "Surface Flux Estimator Synonym" ) )
  {
    properties[7] = geom_rep.get<std::string>( "Surface Flux Estimator Synonym" );

    DagMCProperties::setSurfaceFluxPropertyName( properties[7] );
  }
  else
    properties[7] = DagMCProperties::getSurfaceFluxPropertyName();

  if( geom_rep.isParameter( "Surface Current Estimator Synonym" ) )
  {
    properties[8] = geom_rep.get<std::string>( "Surface Current Estimator Synonym" );

    DagMCProperties::setSurfaceCurrentPropertyName( properties[8] );
  }
  else
    properties[8] = DagMCProperties::getSurfaceCurrentPropertyName();

  // Initialize DagMC
  Geometry::initializeDagMC( cad_file_name, properties, facet_tol );

  // Print the unused parameters
  geom_rep.unused( std::cout );
}

// Validate a geometry representation
void DagMCInstanceFactory::validateGeometryRep( 
				       const Teuchos::ParameterList& geom_rep )
{
  testPrecondition( geom_rep.get<std::string>( "Handler" ) == "DagMC" );
  
  TEST_FOR_EXCEPTION( !geom_rep.isParameter( "CAD File" ),
		      InvalidGeometryRepresentation,
		      "Error: The CAD file needs to be specified!" );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCInstanceFactory.cpp
//---------------------------------------------------------------------------//
