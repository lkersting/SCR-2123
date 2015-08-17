//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Unit traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TRAITS_DECL_HPP
#define UTILITY_UNIT_TRAITS_DECL_HPP

// Boost Includes
#include <boost/units/unit.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/operators.hpp>
#include <boost/units/io.hpp>
#include <boost/units/dimensionless_unit.hpp>

/*! \defgroup unit_traits Unit Traits
 * \ingroup traits
 */

namespace Utility{

/*! The default unit traits implementation
 *
 * The default traits implementation assumes that a boost::units::unit object
 * is the template parameter. Specializations should be made for other types.
 * \ingroup unit_traits
 */
template<typename Unit>
struct UnitTraits
{
  //! The dimension of the unit
  typedef typename Unit::dimension_type Dimension;

  //! The unit system that the unit belongs to
  typedef typename Unit::system_type System;

  //! The inverse unit type
  typedef typename boost::units::divide_typeof_helper<typename boost::units::dimensionless_unit<System>::type,Unit>::type InverseUnit;

  //! The wrapped quantity type associated with the unit and value type T
  template<typename T>
  struct GetQuantityType
  { typedef boost::units::quantity<Unit,T> value; };

  //! The name string
  static inline std::string name()
  { return boost::units::name_string( Unit() ); }

  //! The symbol string
  static inline std::string symbol()
  { return boost::units::symbol_string( Unit() ); }
};

} // end Utility namespace

#endif // end UTILITY_UNIT_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTraitsDecl.hpp
//---------------------------------------------------------------------------//
