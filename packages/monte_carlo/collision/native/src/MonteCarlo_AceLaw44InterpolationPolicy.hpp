//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw44InterpolationPolicy.hpp
//! \author Alex Bennett, Alex Robinson
//! \brief  The law 44 interpolation policy class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ACE_LAW_44_INTERPOLATION_POLICY 
#define FACEMC_ACE_LAW_44_INTERPOLATION_POLICY 

namespace MonteCarlo {

struct AceLaw44HistogramInterpolationPolicy
{
  //! Return interpolated A or R
  inline static double interpolate( const double& indep_var_prime,
                                    const double& indep_var_0,
                                    const double& indep_var_1,
                                    const double& dep_var_0,
                                    const double& dep_var_1 )
  { 
    return dep_var_0;
  }
};

struct AceLaw44LinLinInterpolationPolicy
{
  //! Return interpolated A or R
  inline static double interpolate( const double& indep_var_prime,
                                    const double& indep_var_0,
                                    const double& indep_var_1,
                                    const double& dep_var_0,
                                    const double& dep_var_1 )
  {
    return dep_var_0 + (dep_var_1 - dep_var_0)*(indep_var_prime - indep_var_0)/(indep_var_1 - indep_var_0);
  }
}; 

} // end MonteCarlo namespace

#endif //FACEMC_ACE_LAW_44_INTERPOLATION_POLICY

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw44InterpolationPolicy.hpp
//---------------------------------------------------------------------------//