//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronDistributionGenerator.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron distribution generator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTRON_DISTRIBUTION_GENERATOR_HPP
#define DATA_GEN_ADJOINT_ELECTRON_DISTRIBUTION_GENERATOR_HPP

// Std Lib Includes
#include <functional>
#include <memory>

// FRENSIE Includes
#include "DataGen_AdjointElectronCrossSectionEvaluator.hpp"
#include "Utility_TwoDGridGenerator.hpp"

namespace DataGen{

//! The adjoint electron distribution generator
template<typename TwoDInterpPolicy>
class AdjointElectronDistributionGenerator : public Utility::TwoDGridGenerator<TwoDInterpPolicy>
{

public:

  //! Basic Constructor
  AdjointElectronDistributionGenerator(
          const double max_energy = 20.0,
          const double max_energy_nudge_value = 0.2,
          const double energy_to_outgoing_energy_nudge_value = 1e-6,
          const double convergence_tol = 0.001,
          const double absolute_diff_tol = 1e-10,
          const double distance_tol = 1e-8 );

  //! Advanced Constructor
  AdjointElectronDistributionGenerator(
          const std::vector<double>& primary_energy_grid,
          const double max_energy = 20.0,
          const double max_energy_nudge_value = 0.2,
          const double energy_to_outgoing_energy_nudge_value = 1e-6,
          const double convergence_tol = 0.001,
          const double absolute_diff_tol = 1e-10,
          const double distance_tol = 1e-8 );

  //! Destructor
  virtual ~AdjointElectronDistributionGenerator()
  { /* ... */ }

  //! Get the primary energy grid
  double getPrimaryEnergyGrid() const;

  //! Set the primary energy grid
  void setPrimaryEnergyGrid( const std::vector<double> primary_energy_grid );

  //! Get the max energy
  double getMaxEnergy() const;

  //! Set the max energy nudge value
  void setMaxEnergyNudgeValue( const double max_energy_nudge_value );
  
  //! Get the nudged max energy
  double getNudgedMaxEnergy() const;

  //! Set the energy to outgoing energy nudge value
  void setEnergyToOutgoingEnergyNudgeValue(
                               const double energy_to_outgoing_energy_nudge_value );

  //! Get the nudged energy
  double getNudgedEnergy( const double energy ) const;

  //! Generate and evaluate the distribution grid in place
  template< typename ElectroatomicReaction >
  void generateAndEvaluateDistribution(
    std::vector<double>& outgoing_energy_grid,
    std::vector<double>& evaluated_pdf,
    const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_evaluator,
    const double evaluation_tol,
    const double incoming_adjoint_energy,
    const double adjoint_cross_section ) const;

  //! Generate and evaluate the distribution grid in place on a primary energy grid
  template< typename ElectroatomicReaction >
  void generateAndEvaluateDistributionOnPrimaryEnergyGrid(
    std::map<double,std::vector<double> >& outgoing_energy_grid,
    std::map<double,std::vector<double> >& evaluated_pdf,
    const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_evaluator,
    const double evaluation_tol,
    const std::vector<double> adjoint_cross_sections,
    const unsigned threshold_index ) const;
                              

protected:

  //! Initialize the outgoing energy grid at an energy grid point
  void initializeSecondaryGrid( std::vector<double>& outgoing_energy_grid,
                                const double energy ) const;
  
private:

  // The primary energy grid
  std::vector<double> d_primary_energy_grid;

  // The max table energy (highest energy grid point)
  double d_max_energy;

  // The max table energy nudge value 
  double d_nudged_max_energy;

  // The energy to outgoing energy nudge value
  double d_energy_to_outgoing_energy_nudge_value;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_AdjointElectronDistributionGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_ADJOINT_ELECTRON_DISTRIBUTION_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronDistributionGenerator.hpp
//---------------------------------------------------------------------------//