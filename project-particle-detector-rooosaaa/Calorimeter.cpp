// Calorimeter.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// Implementation file for the Calorimeter class, which is a pure abstract
// base class for all calorimeter types (e.g., electromagnetic and hadronic).
// It inherits from the SubDetector class and is used to define the common
// properties and methods for different calorimeter subsystems in the detector.
//
// This class provides:
// - A parameterised constructor for initializing calorimeter name, resolution, and energy loss
// - A virtual destructor
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this
// program.

#include<iostream>
#include<climits>  // For INT_MAX

#include "Calorimeter.h"

using namespace DetectorSubsystems;

// [CONSTRUCTORS/DESTRUCTORS]

Calorimeter::Calorimeter(const std::string& calorimeter_name, int resolution,
  double energy_loss, int layers)
  : SubDetector(calorimeter_name, resolution, energy_loss)
{
  sub_detector_type = calorimeter_name;
  set_calorimeter_layers(layers);
  // The SubDetector base class constructor seeds the random generator
  // and validates the resolution
}

// Destructor
Calorimeter::~Calorimeter()
{
  //std::cout<<"Calorimeter base class destructor called."<<std::endl;
}

// [SETTERS]

void Calorimeter::set_calorimeter_layers(int layers)
{
  // Layers must be a non-negative integer, and less than INT_MAX
  if(layers < 0 || layers > INT_MAX) {throw std::invalid_argument(
    "Invalid number of Calorimeter layers. Must be between 0 and INT_MAX.");}
  else {calorimeter_layers = layers;}
}
