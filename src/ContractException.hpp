//---------------------------------------------------------------------------//
//!
//! \file ContractException.hpp
//! \author Alex Robinson (aprobinson@wisc.edu)
//! \brief Design-by-Contract exception handling and error policy declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CONTRACT_EXCEPTION_HPP
#define CONTRACT_EXCEPTION_HPP

// Std Lib Includes
#include <exception>
#include <string>

// Trilinos Includes
#include <Teuchos_TestForException.hpp>

// FACEMC Includes
#include "FACEMC_config.hpp"

namespace FACEMC
{

//---------------------------------------------------------------------------//
// Design-By-Contract Exceptions
//---------------------------------------------------------------------------//

/*!
 * \brief Exception class to be thrown when function contract is not met
 * met.
 *
 * The ContractExpection class is a key part of \ref DBC. 
 */
class ContractException : public std::logic_error
{
public:
  ContractException( const std::string &msg )
    : std::logic_error( msg )
  { /* ... */ }
  
  virtual ~ContractException() throw()
  { /* ... */ }
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Design-by-Contract macros.
//---------------------------------------------------------------------------//
/*! \page DBC Design-by-Contract
 *
 * Design-by-Contract (DBC) functionality is provided to verify function
 * preconditions, postconditions, and invariants. These checks are separated
 * from the debug build and can be activated for both release and debug
 * builds. They can be activated by setting the following in a CMake
 * configure:
 *
 * -D FACEMC_ENABLE_DBC:BOOL=ON
 *
 * By default, DBC is deactivated. Although they will require additional
 * computational overhead, these checks provide a mechanism for veryifing
 * library input arguments. Note that the bounds-checking functionality used
 * within FACEMC is only provided by a debug build.
 *
 * In addition, remember is provided to store values used only for DBC
 * checks and no other place in executed code.
 */

#if HAVE_FACEMC_DBC

//! Test a function precondition
#define testPrecondition(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),					\
			      FACEMC::ContractException,		\
			      "Precondition exception" << std::endl ) 

//! Test a function postcondition
#define testPostcondition(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),					\
			      FACEMC::ContractException,		\
			      "Postcondition exception" << std::endl ) 

//! Test a function invariant
#define testInvariant(c) \
  TEUCHOS_TEST_FOR_EXCEPTION( !(c),					\
                              FACEMC::ContractException,		\
			      "Invariant exception" << std::endl )

//! Remember a variable that is needed for testing DBC conditions
#define remember(c) c

#else
			      
#define testPrecondition(c)
#define testPostcondition(c)
#define testInvariant(c)
#define remember(c)

#endif

#endif // end CONTRACT_EXCEPTION_HPP

//---------------------------------------------------------------------------//
// end Exception.hpp
//---------------------------------------------------------------------------//
