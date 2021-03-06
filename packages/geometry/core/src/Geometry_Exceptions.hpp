//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Exceptions.hpp
//! \author Alex Robinson
//! \brief  Geometry exception classes
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_EXCEPTIONS_HPP
#define GEOMETRY_EXCEPTIONS_HPP

//! The invalid geometry representation error
class InvalidGeometryRepresentation : public std::logic_error
{

public:

  InvalidGeometryRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

#endif // end GEOMETRY_EXCEPTIONS_HPP

//---------------------------------------------------------------------------//
// end Geometry_Exceptions.hpp
//---------------------------------------------------------------------------//
