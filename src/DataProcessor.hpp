//---------------------------------------------------------------------------//
// \file   DataProcessor.hpp
// \author Alex Robinson
// \brief  Data Processor base class declaration
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSOR_HPP
#define DATA_PROCESSOR_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

class DataProcessor
{
  
public:
  
  //! Constructor
  DataProcessor()
  { /* ... */ }

  //! Destructor
  virtual ~DataProcessor()
  { /* ... */ }

  //-------------------------------------------------------------------------//
  // Data Processing Interface
  //-------------------------------------------------------------------------//

  //! Process Data Files
  virtual void processDataFiles() = 0;

protected:

  /*!
   * \brief Process the indepMember and the depMember using the desired 
   * processing policy. This function will only compile if the desired
   * tuple members are actually available in tuple Tuple.
   */
  template<typename DataProcessingPolicy,
	   TupleMember indepMember,
	   TupleMember depMember,
	   typename Tuple>
  void processContinuousData( Teuchos::Array<Tuple> &data );

  /*!
   * \brief Remove elements with a tuple member that is less than the specified
   * value. The element closest to the specified value will be kept to allow
   * for interpolation.
   */
  template<TupleMember member,
	   typename Tuple>
  void removeElementsLessThanValue( Teuchos::Array<Tuple> &data,
				    const double value );

  /*!
   * \brief Remove elements with a tuple member that is greater than the 
   * specified value. The element closest to the specified value will be kept
   * to allow for interpolation
   */
  template<TupleMember member,
	   typename Tuple>
  void removeElementsGreaterThanValue( Teuchos::Array<Tuple> &data,
				       const double value );

  /*!
   * \brief Search the data array for constant regions and reduce the number
   * of bins in these regions to one. Only the Teuchos::Array can be used 
   * because the erase member function is needed.
   */
  template<TupleMember member,
	   typename Tuple>
  void coarsenConstantRegions( Teuchos::Array<Tuple> &data );

  /*!
   * \brief Calculate the slope between indepMember and depMember and store
   * at the slopeMember. This function will only compile if the desired
   * tuple members are actually available in tuple Tuple. This function will
   * compile for Teuchos::Array and Teuchos::ArrayView.
   */
  template<TupleMember indepMember, 
	   TupleMember depMember,
	   TupleMember slopeMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateSlopes( Array<Tuple> &data );

  /*!
   * \brief Create a continuous CDF from an array of data and store at the 
   * desired tuple member. This function will only compile if the desired 
   * tuple member is actually available in tuple Tuple. This function will
   * compile for Teuchos::Array and Teuchos::ArrayView.
   */
  template<TupleMember indepMember,
	   TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple,
	   template<typename> class Array>
  void calculateContinuousCDF( Array<Tuple> &data );

  /*!
   * \brief Create a discrete CDF from an array of data and store at 
   * the desired tuple member. To create the CDF in place the pdfMember and the
   * cdfMember should be the same. This function will only compile if the 
   * desired tuple member is actually available in tuple Tuple.
   */
  template<TupleMember pdfMember,
	   TupleMember cdfMember,
	   typename Tuple>
  void calculateDiscreteCDF( Teuchos::Array<Tuple> &data );

  /*!
   * \brief Copy the data in the desired tuple member of the original tuple to 
   * the desired tuple member of the copy tuple. The two arrays references must
   * refer to the same array (no in place copying). This function will compile 
   * for Teuchos::Array and Teuchos::ArrayView.
   */
  template<TupleMember origMember, 
	   TupleMember copyMember,
	   typename origTuple,
	   typename copyTuple,
	   template<typename> class Array>
  void copyTupleMemberData( const Array<origTuple> &orig_data,
			    Array<copyTuple> &copy_data );

  /*!
   * \brief Swap the data in a desired tuple member with the data in another
   * tuple member. This function will compile for Teuchos::Array and 
   * Teuchos::ArrayView.
   */
  template<TupleMember member1,
	   TupleMember member2,
	   typename Tuple,
	   template<typename> class Array>
  void swapTupleMemberData( Array<Tuple> &data );

  /*!
   * \brief Convert an unsigned int to an electron shell string
   */
  std::string uintToShellStr( unsigned int shell );

  /*!
   * \brief Policy struct for processing data tables that require log-log
   * interpolation between evaluated points.
   */
  struct LogLogDataProcessingPolicy
  {
    //! Process Independent Variable
    template<typename T>
    static T processIndependentVar( const T indep_var );
    
    //! Process Dependent Variable
    template<typename T>
    static T processDependentVar( const T dep_var );
  };

  /*!
   * \brief Policy struct for processing data tables that require square-square
   * interpolation between data points.
   */
  struct SquareSquareDataProcessingPolicy
  {
    //! Process Independent Variable
    template<typename T>
    static T processIndependentVar( const T indep_var );
    
    //! Process Dependent Variable
    template<typename T>
    static T processDependentVar( const T dep_var );
  };

};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "DataProcessor_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_PROCESSOR_HPP

//---------------------------------------------------------------------------//
// end DataProcessor.hpp
//---------------------------------------------------------------------------//
 