//---------------------------------------------------------------------------//
//!
//! \file   tstDagFacemcH1-2500K-mpi.cpp
//! \author Alex Robinson
//! \brief  facemc executable mpi verification test for H-1 at 2500K
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "tstFacemcH1-2500K.hpp"

int main( int argc, char** argv )
{
  return conductParallelTest( argc, argv, "DagFacemcH1-2500K-mpi.h5", true );
}

//---------------------------------------------------------------------------//
// end tstDagFacemcH1-2500K-mpi.cpp
//---------------------------------------------------------------------------//