//---------------------------------------------------------------------------//
//!
//! \file   Utility_EvaporationDistribution.hpp
//! \author Aaron Tumulak
//! \brief  Evaporation distribution class declaration. Modified by Alex
//!         Robinson to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EVAPORATION_DISTRIBUTION_HPP
#define UTILITY_EVAPORATION_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/units/physical_dimensions/energy.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

/*! The unit-aware evaporation distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareEvaporationDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
					 public ParameterListCompatibleObject<UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit> >
{

  // Only allow construction when the independent unit corresponds to energy
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, energy_dimension );

private:

  // The distribution multiplier unit traits typedef
  typedef UnitTraits<typename UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename UnitTraits<IndependentUnit>::InverseUnit>::type> DistMultiplierUnitTraits;
  
  // The distribution multiplier quantity type
  typedef typename DistMultiplierUnitTraits::template GetQuantityType<double>::type DistMultiplierQuantity;
  
  // The distribution normalization quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistMultiplierQuantity>
  typedef QuantityTraits<DistMultiplierQuantity> DMQT;

public:

  //! This distribution type
  typedef UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareEvaporationDistribution( 
                                const InputIndepQuantityA incident_energy = 
                                QuantityTraits<InputIndepQuantityA>::one(),
                                const InputIndepQuantityB nuclear_temperature =
                                QuantityTraits<InputIndepQuantityB>::one(),
				const InputIndepQuantityC restriction_energy = 
                                QuantityTraits<InputIndepQuantityC>::one(),
				const double constant_multiplier = 1.0 );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareEvaporationDistribution( const UnitAwareEvaporationDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareEvaporationDistribution fromUnitlessDistribution( const UnitAwareEvaporationDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareEvaporationDistribution& operator=( const UnitAwareEvaporationDistribution& dist_instance );

  //! Destructor
  ~UnitAwareEvaporationDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a sample from the distribution
  IndepQuantity sample() const;

  //! Return a sample from the distribution
  static IndepQuantity sample( const IndepQuantity incident_energy,
			       const IndepQuantity nuclear_temperature,
			       const IndepQuantity restriction_energy );

  //! Return a random sample from the distribution, and record the number of trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
    const IndepQuantity incident_energy,
    const IndepQuantity nuclear_temperature,
    const IndepQuantity restriction_energy,
    unsigned& trials );

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwareEvaporationDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareEvaporationDistribution( const UnitAwareEvaporationDistribution<void,void>& unitless_dist_instance, int );

private:

  // Calculate the normalization constant of the distribution
  void calculateNormalizationConstant();

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareEvaporationDistribution;
 
  // The distribution type
  static const OneDDistributionType distribution_type = EVAPORATION_DISTRIBUTION;

  // The incident neutron energy of the distribution
  IndepQuantity d_incident_energy;

  // The nuclear temperature of the distribution
  IndepQuantity d_nuclear_temperature;
  
  // The restriction energy of the distribution
  IndepQuantity d_restriction_energy;

  // The distribution multiplier
  DistMultiplierQuantity d_multiplier;

  // The distribution normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The evaporation distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareEvaporationDistribution<void,void> EvaporationDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::EvaporationDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::EvaporationDistribution>
{
public:
  static std::string name()
  {
    return "Evaporation Distribution";
  }
  static std::string concreteName( 
			     const Utility::EvaporationDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the 
 * Utility::UnitAwareEvaporationDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U,typename V>
class TypeNameTraits<Utility::UnitAwareEvaporationDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Evaporation Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
	       const Utility::UnitAwareEvaporationDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_EvaporationDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_EVAPORATION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution.hpp
//---------------------------------------------------------------------------//