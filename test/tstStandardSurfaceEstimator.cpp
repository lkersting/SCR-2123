//---------------------------------------------------------------------------//
//!
//! \file   tstStandardSurfaceEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard surface estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "StandardSurfaceEstimator.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardSurfaceEstimator : public FACEMC::StandardSurfaceEstimator
{
public:
  TestStandardSurfaceEstimator( 
	 const unsigned long long id,
	 const double multiplier,
         const Teuchos::Array<FACEMC::StandardSurfaceEstimator::surfaceIdType>&
	 entity_ids,
	 const Teuchos::Array<double>& entity_norm_constants )
    : FACEMC::StandardSurfaceEstimator( id, 
					multiplier,
					entity_ids,
					entity_norm_constants )
  { /* ... */ }

  ~TestStandardSurfaceEstimator()
  { /* ... */ }

  void addPartialHistoryContribution( 
	const FACEMC::ParticleState& particle,
        const FACEMC::StandardSurfaceEstimator::surfaceIdType surface_crossed,
	const double angle_cosine )
  { /* ... */ }

  void print( std::ostream& os ) const
  { printImplementation( os, "Surface" ); }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle types can be assigned
TEUCHOS_UNIT_TEST( StandardSurfaceEstimator, setParticleType )
{
  Teuchos::Array<FACEMC::StandardSurfaceEstimator::surfaceIdType> 
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  Teuchos::Array<double> surface_norm_consts( 2 );
  surface_norm_consts[0] = 1.0;
  surface_norm_consts[1] = 2.0;
  
  Teuchos::RCP<TestStandardSurfaceEstimator> estimator(
	  new TestStandardSurfaceEstimator( 0ull,
					    2.0,
					    surface_ids,
					    surface_norm_consts ) );

  Teuchos::Array<FACEMC::ParticleType> particle_types( 4 );
  particle_types[0] = FACEMC::PHOTON;
  particle_types[1] = FACEMC::NEUTRON;
  particle_types[2] = FACEMC::ADJOINT_PHOTON;
  particle_types[3] = FACEMC::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );
  
  TEST_ASSERT( estimator->isParticleTypeAssigned( FACEMC::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_NEUTRON ) );

  particle_types[0] = FACEMC::NEUTRON;
  particle_types[1] = FACEMC::PHOTON;

  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::PHOTON ) );
  TEST_ASSERT( estimator->isParticleTypeAssigned( FACEMC::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_NEUTRON ) );

}

//---------------------------------------------------------------------------//
// end tstStandardSurfaceEstimator.cpp
//---------------------------------------------------------------------------//