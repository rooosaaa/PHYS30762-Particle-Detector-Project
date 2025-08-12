// Calorimeter.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Header file for the abstract Calorimeter class. This forms the base class
// for all calorimeter subsystems used in the detector (e.g., electromagnetic 
// and hadronic calorimeters). It inherits from the SubDetector base class.
//
// This class provides:
// - A parameterised constructor for all calorimeters
// - A pure virtual method for custom printing
// - A pure virtual method for setting the detector name
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this
// program.

#ifndef CALORIMETER_H
#define CALORIMETER_H

#include<random>
#include<string>

#include "SubDetector.h"

namespace DetectorSubsystems
{
  // Pure abstract base class for all calorimeter types
  class Calorimeter : public SubDetector
  {
  protected:
    int calorimeter_layers; // Number of layers in the calorimeter
  public:
    // [CONSTRUCTORS/DESTRUCTORS]
    // Parameterised constructor
    Calorimeter(const std::string& calorimeter_name, int resolution,
      double energy_loss, int layers);
    // Destructor
    virtual ~Calorimeter();
    
    // [GETTERS]
    int get_calorimeter_layers() const {return calorimeter_layers;}
    
    // [SETTERS]
    void set_calorimeter_layers(int layers);
  };
} // namespace DetectorSubsystems

#endif // CALORIMETER_H
