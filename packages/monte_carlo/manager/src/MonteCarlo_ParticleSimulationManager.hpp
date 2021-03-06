//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSimulationManager.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SIMULATION_MANAGER_HPP
#define FACEMC_PARTICLE_SIMULATION_MANAGER_HPP

// Boost Function
#include <boost/function.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_SourceModuleInterface.hpp"
#include "MonteCarlo_EstimatorModuleInterface.hpp"
#include "MonteCarlo_CollisionModuleInterface.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_SimulationManager.hpp"
#include "Geometry_ModuleInterface.hpp"

namespace MonteCarlo{

//! The generic particle simulation manager class
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler>
class ParticleSimulationManager : public SimulationManager
{

protected:

  // Typedef for geometry module interface
  typedef Geometry::ModuleInterface<GeometryHandler> GMI;
  
  // Typedef for source module interface
  typedef SourceModuleInterface<SourceHandler> SMI;
  
  // Typedef for estimator module interface
  typedef EstimatorModuleInterface<EstimatorHandler> EMI;
  
  // Typedef for collision module interface
  typedef CollisionModuleInterface<CollisionHandler> CMI;

public:

  //! Constructor 
  ParticleSimulationManager( 
		const unsigned long long number_of_histories,
		const unsigned long long start_history = 0ull,
		const unsigned long long previously_completed_histories = 0ull,
		const double previous_run_time = 0.0 );

  //! Destructor
  virtual ~ParticleSimulationManager()
  { /* ... */ }

  //! Run the simulation set up by the user
  virtual void runSimulation();

  //! Print the data in all estimators to the desired stream
  virtual void printSimulationSummary( std::ostream &os ) const;

  //! Export the simulation data (to an hdf5 file)
  virtual void exportSimulationData( const std::string& data_file_name ) const;

  // Signal handler
  virtual void signalHandler(int signal);

protected:

  //! Run the simulation batch
  void runSimulationBatch( const unsigned long long start_history, 
			   const unsigned long long end_history );

  //! Return the number of histories
  unsigned long long getNumberOfHistories() const;

  //! Return the number of histories completed
  unsigned long long getNumberOfHistoriesCompleted() const;

  //! Increment the number of histories completed
  void incrementHistoriesCompleted( const unsigned long long histories = 1ull );
  //! Set the number of histories completed
  void setHistoriesCompleted( const unsigned long long histories );

  //! Set the start time
  void setStartTime( const double start_time );
  
  //! Set the end time
  void setEndTime( const double end_time );

  //! Print simulation state info in collision handler
  void printSimulationStateInfo();

private:

  // Simulate an individual particle
  template<typename ParticleStateType>
  void simulateParticle( ParticleStateType& particle,
                         ParticleBank& particle_bank ) const;

  // Dummy function for ignoring a particle
  template<typename ParticleStateType>
  void ignoreParticle( ParticleStateType& particle,
		       ParticleBank& particle_bank ) const;

  // Starting history
  unsigned long long d_start_history;
  
  // Number of particle histories to simulate
  unsigned long long d_history_number_wall;

  // Number of histories completed
  unsigned long long d_histories_completed;

  // Flag for ending simulation early
  bool d_end_simulation;

  // The previous run time
  double d_previous_run_time;

  // The simulation start time
  double d_start_time;

  // The simulation end time
  double d_end_time;

  // The neutron simulation function
  boost::function<void (NeutronState&, ParticleBank&)> d_simulate_neutron;

  // The photon simulation function
  boost::function<void (PhotonState&, ParticleBank&)> d_simulate_photon;

  // The electron simulation function
  boost::function<void (ElectronState&, ParticleBank&)> d_simulate_electron;
};

//! Macro for catching a lost particle and breaking a loop
#define CATCH_LOST_PARTICLE_AND_BREAK( particle )			\
  catch( std::runtime_error& exception )				\
  {									\
    std::cout << exception.what() << std::endl;				\
    std::cout << "Lost particle info: " << std::endl;			\
    std::cout << " History: " << particle.getHistoryNumber() << std::endl; \
    std::cout << " Cell: " << particle.getCell() << std::endl;		\
    std::cout << " Position: " << particle.getXPosition() << " ";	\
    std::cout << particle.getYPosition() << " ";			\
    std::cout << particle.getZPosition() << std::endl;			\
    std::cout << " Direction: " << particle.getXDirection() << " ";	\
    std::cout << particle.getYDirection() << " ";			\
    std::cout << particle.getZDirection() << std::endl;			\
    particle.setAsLost();						\
    break;								\
    }

//! Macro for catching a lost source particle
#define CATCH_LOST_SOURCE_PARTICLE_AND_CONTINUE( bank )			\
  catch( std::runtime_error& exception )				\
  {									\
    std::cout << exception.what() << std::endl;				\
    std::cout << "Lost particle info: " << std::endl;			\
    std::cout << " History: " << bank.top().getHistoryNumber() << std::endl; \
    std::cout << " Cell: " << bank.top().getCell() << std::endl;	\
    std::cout << " Position: " << bank.top().getXPosition() << " ";	\
    std::cout << bank.top().getYPosition() << " ";			\
    std::cout << bank.top().getZPosition() << std::endl;		\
    std::cout << " Direction: " << bank.top().getXDirection() << " ";	\
    std::cout << bank.top().getYDirection() << " ";			\
    std::cout << bank.top().getZDirection() << std::endl;		\
    bank.pop();								\
    continue;								\
  }

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleSimulationManager_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_PARTICLE_SIMULATION_MANAGER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSimulationManager.hpp
//---------------------------------------------------------------------------//
