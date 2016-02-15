//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegrator.hpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integrator
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GAUSS_KRONROD_INTEGRATOR_HPP
#define UTILITY_GAUSS_KRONROD_INTEGRATOR_HPP

// std Includes
#include <queue>

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Utility{

struct BinTraits
{
  double lower_limit;
  double upper_limit;
  double result;
  double error;

  bool operator <( const BinTraits& bins ) const
  {
    return error < bins.error;
  }
};

typedef std::priority_queue<BinTraits> BinQueue;

//! The Gauss-Kronrod integrator
class GaussKronrodIntegrator
{

public:

  //! Constructor
  GaussKronrodIntegrator( const double relative_error_tol,
                          const double absolute_error_tol = 0.0,
                          const size_t subinterval_limit = 1000 );

  //! Destructor
  ~GaussKronrodIntegrator();
/*
  //! Integrate the function
  template<typename Functor>
  void integrate( Functor& integrand, 
		  double lower_limit, 
		  double upper_limit,
		  double& result,
		  double& absolute_error,
		  size_t& number_of_function_evals ) const;
*/
  //! Integrate the function adaptively
  template<int Points, typename Functor>
  void integrateAdaptivelyWithoutQueue( Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error ) const;

  //! Integrate the function adaptively with BinQueue
  template<int Points, typename Functor>
  void integrateAdaptively( Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error ) const;

  //! Integrate the function with point rule
  template<int Points, typename Functor>
  void integrateWithPointRule( 
                Functor& integrand,
			    double lower_limit,
			    double upper_limit,
			    double& result,
			    double& absolute_error,
                double& result_abs, 
                double& result_asc ) const;
/*
  //! Integrate the function over a semi-infinite interval (+infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalUpper( Functor& integrand,
					   double lower_limit,
					   double& result,
					   double& absolute_error ) const;

  //! Integrate the function over a semi-infinite interval (-infinity)
  template<typename Functor>
  void integrateSemiInfiniteIntervalLower( Functor& integrand,
					   double upper_limit,
					   double& result,
					   double& absolute_error ) const;

  //! Integrate the function over an infinite interval (-infinity,+infinity)
  template<typename Functor>
  void integrateInfiniteInterval( Functor& integrand,
				  double& result,
				  double& absolute_error ) const;
*/
  //! Integrate a function with integrable singularities adaptively
  template<typename Functor>
  void integrateAdaptivelyWynnEpsilon( Functor& integrand,
				       double lower_limit,
				       double upper_limit,
				       double& result,
				       double& absolute_error ) const;
/*
  //! Integrate a function with known integrable singularities adaptively
  template<typename Functor>
  void integrateAdaptivelyWynnEpsilon( 
			  Functor& integrand,
			  const Teuchos::ArrayView<double>& points_of_interest,
			  double& result,
			  double& absolute_error ) const;
*/
private:
  // Function wrapper for evaluating the functor
  template<typename Functor>
  static double functorWrapper( const double x, void* indirected_functor );

  // Calculate the quadrature upper and lower integrand values at an abscissa
  template<typename Functor>
  void calculateQuadratureIntegrandValuesAtAbscissa( 
    Functor& integrand, 
    double abscissa,
    double half_length,
    double midpoint,
    double& integrand_value_lower,
    double& integrand_value_upper ) const;

  // Rescale absolute error from integration
  void rescaleAbsoluteError( 
    double& absolute_error, 
    double result_abs, 
    double result_asc ) const;

  // Test if subinterval is too small
  template<int Points>
  bool subintervalTooSmall( double& lower_limit_1, 
                                   double& lower_limit_2, 
                                   double& upper_limit_2 ) const;

  // Update the integral results and errors
  void updateIntegral( Teuchos::Array<double>& bin_lower_limit, 
                              Teuchos::Array<double>& bin_upper_limit, 
                              Teuchos::Array<double>& bin_result, 
                              Teuchos::Array<double>& bin_error,
                              double& lower_limit_1, 
                              double& upper_limit_1,
                              double& area_1, 
                              double& error_1,
                              double& lower_limit_2,
                              double& upper_limit_2, 
                              double& area_2, 
                              double& error_2,
                              int& last,
                              int& bin_with_max_error ) const;

  // Sort the bin order from highest to lowest error 
  void sortErrorList( Teuchos::Array<double>& bin_error,
                      Teuchos::Array<double>& bin_order, 
                      double& maximum_bin_error, 
                      int& bin_with_larger_error,
                      int bin_with_smaller_error, 
                      int nr_max ) const;


  // The relative error tolerance
  double d_relative_error_tol;

  // The absolute error tolerance
  double d_absolute_error_tol;

  // The subinterval limit
  size_t d_subinterval_limit;
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_GaussKronrodIntegrator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_GUASS_KRONROD_INTEGRATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator.hpp
//---------------------------------------------------------------------------//
