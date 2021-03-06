//---------------------------------------------------------------------------//
//!
//! \file   tstTabularDistribution.cpp
//! \author Alex Robinson
//! \brief  Tabular distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;
Teuchos::RCP<Utility::TabularOneDDistribution> tab_distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;
Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> >
unit_aware_tab_distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  typedef Utility::LinLin LinLin;					\
  typedef Utility::LogLin LogLin;					\
  typedef Utility::LinLog LinLog;					\
  typedef Utility::LogLog LogLog;					\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLin )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LogLin )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLog )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LogLog )	

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy, typename BaseDistribution>
void initialize( Teuchos::RCP<BaseDistribution>& dist )
{
  // Use the basic constructor
  Teuchos::Array<typename BaseDistribution::IndepQuantity> 
    independent_values( 4 );
  Utility::setQuantity( independent_values[0], 1e-3 );
  Utility::setQuantity( independent_values[1], 1e-2 );
  Utility::setQuantity( independent_values[2], 1e-1 );
  Utility::setQuantity( independent_values[3], 1.0 );
  
  Teuchos::Array<typename BaseDistribution::DepQuantity> dependent_values( 4 );
  Utility::setQuantity( dependent_values[0], 1e2 );
  Utility::setQuantity( dependent_values[1], 1e1 );
  Utility::setQuantity( dependent_values[2], 1.0 );
  Utility::setQuantity( dependent_values[3], 1e-1 );

  dist.reset(new Utility::UnitAwareTabularDistribution<InterpolationPolicy,typename BaseDistribution::IndepUnit, typename BaseDistribution::DepUnit>(
							  independent_values,
							  dependent_values ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluate,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-3 ), 1e2 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-2 ), 1e1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1e-1 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 1e-1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   evaluate,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1e-3*MeV ), 
		       1e2*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1e-2*MeV ), 
		       1e1*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1e-1*MeV ), 
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV ), 
		       1e-1*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV ), 
		       0.0*si::mole );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluatePDF,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-3 ), 
			  67.340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-2 ), 
			  6.7340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1e-1 ), 
			  0.67340006734, 
			  1e-6 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 1.0 ), 
			  0.067340006734, 
			  1e-6 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   evaluatePDF,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*MeV ), 
		       0.0/MeV );
  UTILITY_TEST_FLOATING_EQUALITY( 
			     unit_aware_distribution->evaluatePDF( 1e-3*MeV ), 
			     67.340006734/MeV,
			     1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			     unit_aware_distribution->evaluatePDF( 1e-2*MeV ), 
			     6.7340006734/MeV,
			     1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			     unit_aware_distribution->evaluatePDF( 1e-1*MeV ), 
			     0.67340006734/MeV,
			     1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			      unit_aware_distribution->evaluatePDF( 1.0*MeV ), 
			      0.067340006734/MeV,
			      1e-6 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2.0*MeV ), 
		       0.0/MeV );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   evaluateCDF,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-3 ), 
			  0.0000000000, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-2 ), 
			  0.33333333333, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1e-1 ), 
			  0.66666666667, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 1.0 ), 
			  1.0000000000, 
			  1e-10 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 2.0 ), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, evaluateCDF );

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated 
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution, 
				   evaluateCDF,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 0.0*MeV ), 
		       0.0 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-3*MeV ),
			  0.0000000000, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-2*MeV ),
			  0.33333333333, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1e-1*MeV ),
			  0.66666666667, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( unit_aware_tab_distribution->evaluateCDF( 1.0*MeV ), 
			  1.0000000000, 
			  1e-10 );
  TEST_EQUALITY_CONST( unit_aware_tab_distribution->evaluateCDF( 2.0*MeV ), 
		       1.0 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, evaluateCDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sample,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e-3 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = distribution->sample();
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
                                   sample,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 1e-3*MeV );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = unit_aware_distribution->sample();
  TEST_COMPARE( sample, >=, 1e-3*MeV );
  TEST_COMPARE( sample, <=, 1.0*MeV );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleAndRecordTrials,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1.0 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleAndRecordTrials );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
                                   sampleAndRecordTrials,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<MegaElectronVolt> sample = 
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 1e-3*MeV );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, 1e-3*MeV );
  TEST_COMPARE( sample, <=, 1.0*MeV );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, sampleAndRecordTrials );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleAndRecordBinIndex,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleAndRecordBinIndex );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
                                   sampleAndRecordBinIndex,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  quantity<MegaElectronVolt> sample = 
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 1e-3*MeV );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 2u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, 1e-3*MeV );
  TEST_COMPARE( sample, <=, 1.0*MeV );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, 
			 sampleAndRecordBinIndex );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleWithRandomNumber,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 1e-3 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 1.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleWithRandomNumber );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
                                   sampleWithRandomNumber,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<MegaElectronVolt> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 1e-3*MeV );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1.0*MeV, 1e-12 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, 
			 sampleWithRandomNumber );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 1e-1  );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  
  sample = tab_distribution->sampleInSubrange( 1e-1 );
  TEST_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = tab_distribution->sampleInSubrange( 1e-1 );
  TEST_COMPARE( sample, >=, 1e-3 );
  TEST_COMPARE( sample, <=, 1e-1 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, sampleInSubrange );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
                                   sampleInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample = 
    unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV  );
  TEST_EQUALITY_CONST( sample, 1e-3*MeV );
  
  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1e-1*MeV, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();
  
  sample = unit_aware_tab_distribution->sampleInSubrange( 1e-1*MeV );
  TEST_COMPARE( sample, >=, 1e-3*MeV );
  TEST_COMPARE( sample, <=, 1e-1*MeV );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, sampleInSubrange );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
                                   sampleWithRandomNumberInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( tab_distribution );

  double sample = 
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1e-1  );
  TEST_EQUALITY_CONST( sample, 1e-3 );
  
  sample = tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 1e-1 );
  TEST_FLOATING_EQUALITY( sample, 1e-1, 1e-12 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, 
			 sampleWithRandomNumberInSubrange );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
                                   sampleWithRandomNumberInSubrange,
                                   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_tab_distribution );

  quantity<MegaElectronVolt> sample = 
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 
							       0.0, 1e-1*MeV );
  TEST_EQUALITY_CONST( sample, 1e-3*MeV );
  
  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 
							       1.0, 1e-1*MeV );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 1e-1*MeV, 1e-12 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, 
			 sampleWithRandomNumberInSubrange );

//---------------------------------------------------------------------------//
// Check that a distribution can be constructed from a cdf
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution, 
				   cdf_constructor,
				   InterpolationPolicy )
{
  Teuchos::Array<double> indep_values( 4 ), cdf_values( 4 );
  indep_values[0] = 1e-3;
  indep_values[1] = 1e-2;
  indep_values[2] = 1e-1;
  indep_values[3] = 1.0;

  cdf_values[0] = 0.0;
  cdf_values[1] = 0.495;
  cdf_values[2] = 0.99;
  cdf_values[3] = 1.485;
  
  Teuchos::RCP<Utility::TabularOneDDistribution> 
    dist_from_cdf( new Utility::TabularDistribution<InterpolationPolicy>( 
								indep_values,
								cdf_values,
								true ) );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-3 ), 55.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-2 ), 55.0, 1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-1 ), 5.5, 1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1.0 ), 0.55, 1e-15 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluate( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluatePDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-3 ), 
			  37.03703703703703,
			  1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-2 ), 
			  37.03703703703703,
			  1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-1 ), 
			  3.703703703703703,
			  1e-15 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1.0 ), 
			  0.37037037037037046,
			  1e-15 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluatePDF( 2.0 ), 0.0 );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluateCDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-3 ), 
			  0.0000000000, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-2 ), 
			  0.33333333333, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-1 ), 
			  0.66666666667, 
			  1e-10 );
  TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1.0 ), 
			  1.0000000000, 
			  1e-10 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluateCDF( 2.0 ), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, cdf_constructor );

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be constructed from a cdf
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution, 
				   cdf_constructor,
				   InterpolationPolicy )
{
  Teuchos::Array<double> indep_values( 4 ), cdf_values( 4 );
  indep_values[0] = 1e-3;
  indep_values[1] = 1e-2;
  indep_values[2] = 1e-1;
  indep_values[3] = 1.0;

  cdf_values[0] = 0.0;
  cdf_values[1] = 0.495;
  cdf_values[2] = 0.99;
  cdf_values[3] = 1.485;
  
  Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<MegaElectronVolt,si::amount> > 
    dist_from_cdf( new Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount>( 
								indep_values,
								cdf_values,
								true ) );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluate( 0.0*MeV ), 0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-3*MeV ), 
				  55.0*si::mole, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-2*MeV ), 
				  55.0*si::mole, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1e-1*MeV ), 
				  5.5*si::mole, 
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluate( 1.0*MeV ), 
				  0.55*si::mole, 
				  1e-15 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluate( 2.0*MeV ), 0.0*si::mole );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluatePDF( 0.0*MeV ), 0.0/MeV );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-3*MeV ), 
				  37.03703703703703/MeV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-2*MeV ), 
				  37.03703703703703/MeV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1e-1*MeV ), 
				  3.703703703703703/MeV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluatePDF( 1.0*MeV ), 
				  0.37037037037037046/MeV,
				  1e-15 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluatePDF( 2.0*MeV ), 0.0/MeV );

  TEST_EQUALITY_CONST( dist_from_cdf->evaluateCDF( 0.0*MeV ), 0.0 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-3*MeV ), 
				  0.0, 
				  1e-10 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-2*MeV ), 
				  0.33333333333, 
				  1e-10 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1e-1*MeV ), 
				  0.66666666667, 
				  1e-10 );
  UTILITY_TEST_FLOATING_EQUALITY( dist_from_cdf->evaluateCDF( 1.0*MeV ), 
				  1.0, 
				  1e-10 );
  TEST_EQUALITY_CONST( dist_from_cdf->evaluateCDF( 2.0*MeV ), 1.0 );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, cdf_constructor );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getUpperBoundOfIndepVar,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent 
// variable can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   getUpperBoundOfIndepVar,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(), 
		       1.0*MeV );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, 
			 getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getLowerBoundOfIndepVar,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 1e-3 );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent 
// variable can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   getLowerBoundOfIndepVar,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(), 
		       1e-3*MeV );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, 
			 getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   getDistributionType,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_EQUALITY_CONST( distribution->getDistributionType(), 
		       Utility::TABULAR_DISTRIBUTION );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   getDistributionType,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(), 
		       Utility::TABULAR_DISTRIBUTION );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   isTabular,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, isTabular );

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   isTabular,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, isTabular );

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   isContinuous,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  TEST_ASSERT( distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, isContinuous );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   isContinuous,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, isContinuous );

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( TabularDistribution,
				   toParameterList,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( distribution );

  typedef Utility::TabularDistribution<InterpolationPolicy> Distribution;

  Teuchos::RCP<Distribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Distribution>( distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Distribution>( "test distribution", 
				      *true_distribution );

  std::ostringstream xml_file_name;
  xml_file_name << "tabular_" << InterpolationPolicy::name() 
		<< "_dist_test_list.xml";
  
  Teuchos::writeParameterListToXmlFile( parameter_list,
					xml_file_name.str() );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( xml_file_name.str() );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Distribution> 
    copy_distribution( new Distribution );

  *copy_distribution = read_parameter_list->get<Distribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

UNIT_TEST_INSTANTIATION( TabularDistribution, toParameterList );

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( UnitAwareTabularDistribution,
				   toParameterList,
				   InterpolationPolicy )
{
  initialize<InterpolationPolicy>( unit_aware_distribution );

  typedef Utility::UnitAwareTabularDistribution<InterpolationPolicy,MegaElectronVolt,si::amount> Distribution;

  Teuchos::RCP<Distribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Distribution>( unit_aware_distribution );
  
  Teuchos::ParameterList parameter_list;
  
  parameter_list.set<Distribution>( "test distribution", 
				    *true_distribution );

  std::ostringstream xml_file_name;
  xml_file_name << "unit_aware_tabular_" << InterpolationPolicy::name() 
		<< "_dist_test_list.xml";
  
  Teuchos::writeParameterListToXmlFile( parameter_list,
					xml_file_name.str() );
  
  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list = 
    Teuchos::getParametersFromXmlFile( xml_file_name.str() );
  
  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Distribution> 
    copy_distribution( new Distribution );

  *copy_distribution = read_parameter_list->get<Distribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

UNIT_TEST_INSTANTIATION( UnitAwareTabularDistribution, toParameterList );

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( TabularDistribution, fromParameterList )
{
  Utility::TabularDistribution<Utility::LinLin> distribution_1 = 
    test_dists_list->get<Utility::TabularDistribution<Utility::LinLin> >( "Tabular Distribution A" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0.001 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi );
  
  distribution_1 = 
    test_dists_list->get<Utility::TabularDistribution<Utility::LinLin> >( "Tabular Distribution B" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0.001 );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 1.0 );

  Utility::TabularDistribution<Utility::LogLog> distribution_2 = 
    test_dists_list->get<Utility::TabularDistribution<Utility::LogLog> >( "Tabular Distribution C" );

  TEST_EQUALITY_CONST( distribution_2.getLowerBoundOfIndepVar(), 0.001 );
  TEST_EQUALITY_CONST( distribution_2.getUpperBoundOfIndepVar(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareTabularDistribution, fromParameterList )
{
  Utility::UnitAwareTabularDistribution<Utility::LinLin,MegaElectronVolt,si::amount> 
    distribution_1 = 
    test_dists_list->get<Utility::UnitAwareTabularDistribution<Utility::LinLin,MegaElectronVolt,si::amount> >( "Unit-Aware Tabular Distribution A" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0.001*MeV );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 
		       Utility::PhysicalConstants::pi*MeV );
  
  distribution_1 = 
    test_dists_list->get<Utility::UnitAwareTabularDistribution<Utility::LinLin,MegaElectronVolt,si::amount> >( "Unit-Aware Tabular Distribution B" );

  TEST_EQUALITY_CONST( distribution_1.getLowerBoundOfIndepVar(), 0.001*MeV );
  TEST_EQUALITY_CONST( distribution_1.getUpperBoundOfIndepVar(), 1.0*MeV );

  Utility::UnitAwareTabularDistribution<Utility::LogLog,MegaElectronVolt,si::amount> 
    distribution_2 = 
    test_dists_list->get<Utility::UnitAwareTabularDistribution<Utility::LogLog,MegaElectronVolt,si::amount> >( "Unit-Aware Tabular Distribution C" );

  TEST_EQUALITY_CONST( distribution_2.getLowerBoundOfIndepVar(), 0.001*MeV );
  TEST_EQUALITY_CONST( distribution_2.getUpperBoundOfIndepVar(), 10.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareTabularDistribution,
				   explicit_conversion,
				   IndepUnitA,
				   DepUnitA,
				   IndepUnitB,
				   DepUnitB )
{
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;
  
  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;
  
  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  initialize<Utility::LinLin>( distribution );

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::TabularDistribution<Utility::LinLin> >( distribution ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareTabularDistribution<Utility::LinLin,IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a = 
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a = 
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.0 );
  DepQuantityA dep_quantity_a = 
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 0.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 0.1 );
  Utility::setQuantity( inv_indep_quantity_a, 0.67340006734 );
  Utility::setQuantity( dep_quantity_a, 1.0 );			

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( 
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-6 );
}

typedef si::energy si_energy;
typedef cgs::energy cgs_energy;
typedef si::amount si_amount;
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareTabularDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_dists_xml_file;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_dists_xml_file",
		 &test_dists_xml_file,
		 "Test distributions xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LinLin> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LogLin> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LinLog> );
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::TabularDistribution<Utility::LogLog> );
  typedef Utility::UnitAwareTabularDistribution<Utility::LinLin,MegaElectronVolt,si::amount> UnitAwareTabularLinLinDist;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareTabularLinLinDist );
  typedef Utility::UnitAwareTabularDistribution<Utility::LogLin,MegaElectronVolt,si::amount> UnitAwareTabularLogLinDist;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareTabularLogLinDist );
  typedef Utility::UnitAwareTabularDistribution<Utility::LinLog,MegaElectronVolt,si::amount> UnitAwareTabularLinLogDist;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareTabularLinLogDist );
  typedef Utility::UnitAwareTabularDistribution<Utility::LogLog,MegaElectronVolt,si::amount> UnitAwareTabularLogLogDist;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareTabularLogLogDist );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstTabularDistribution.cpp
//---------------------------------------------------------------------------//
