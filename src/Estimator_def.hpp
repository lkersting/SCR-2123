//---------------------------------------------------------------------------//
//!
//! \file   Estimator_def.hpp
//! \author Alex Robinson
//! \brief  Estimator base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_DEF_HPP
#define ESTIMATOR_DEF_HPP

// FACEMC Includes
#include "GeneralEstimatorDimensionDiscretization.hpp"

namespace FACEMC{

// Set the bin boundaries for a dimension of the sphase space
template<EstimatorPhaseSpaceDimension dimension, typename DimensionType>
void Estimator::setBinBoundaries( 
			  const Teuchos::Array<DimensionType>& bin_boundaries )
{
  // Make sure the DimensionType matches the type associated with the dimension
  testStaticPrecondition((boost::is_same<typename Traits::EstimatorPhaseSpaceDimensionTraits<dimension>::dimensionType,DimensionType>::value));
  
  Teuchos::RCP<EstimatorDimensionDiscretization> dimension_bin_boundaries(
    new GeneralEstimatorDimensionDiscretization<dimension>( bin_boundaries ) );
  
  assignBinBoundaries( dimension_bin_boundaries );
}

} // end FACEMC namespace

#endif // end ESTIMATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Estimator_def.hpp
//---------------------------------------------------------------------------//
