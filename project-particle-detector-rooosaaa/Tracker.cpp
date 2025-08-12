// Tracker.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file implements the methods defined in tracker.h for the Tracker class,
// a sub-detector used in the simulation of a particle detector.
// The Tracker is responsible for modelling the material and structure of the inner
// tracking system in a typical high-energy experiment (e.g. ATLAS or CMS).
//
// It includes default and parameterised constructors, validation for material
// and subsystem count, and basic data printing functionality.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<climits>  // For INT_MAX

#include "Tracker.h"
#include "Particle.h"

using namespace DetectorSubsystems;

// [RULE OF 5]

// Default constructor
// Creates an ideal tracker with 0% resolution and no energy loss (perfect efficiency).
// Sets default material to "Silicon" and assumes 3 internal subsystems.
Tracker::Tracker() : SubDetector("Tracker", 0, 1)
{
  std::cout<<"Calling Tracker default constructor."<<std::endl;
  set_tracker_material("Silicon");
  set_number_of_subsystems(3);
}

Tracker::Tracker(int resolution, double energy_loss, const std::string& material, int number)
  : SubDetector("Tracker", resolution, energy_loss)
{
  // The base class constructor validates resolution and seeds the RNG
  set_tracker_material(material);
  set_number_of_subsystems(number);
}

Tracker::~Tracker()
{
  std::cout<<"Calling Tracker destructor."<<std::endl;
}

// [SETTERS]

void Tracker::set_sub_detector_name(const std::string& name)
{
  if(name == "Tracker") {sub_detector_type = name;}
  else {throw std::invalid_argument("Invalid sub-detector type. Must be 'Tracker'.");}
}

// Uses a helper function to validate that the input contains only letters and underscores
void Tracker::set_tracker_material(const std::string& material)
{
  if(is_valid_string_entry(material)) {tracker_material = material;}
  else {throw std::invalid_argument("Invalid Tracker material. Must consist of only letters and underscores.");}
}

// Set the number of subsystems
// Must be non-negative and within the bounds of an int
void Tracker::set_number_of_subsystems(const int number)
{
  if(number < 0 || number > INT_MAX) {throw std::invalid_argument(
    "Invalid number of subsystems. Must be between 0 and INT_MAX.");}
  else {number_of_subsystems = number;}
} 

// [METHODS]

void Tracker::print() const
{
  std::cout<<"Sub-Detector: "<<sub_detector_type<<std::endl;
  std::cout<<"Resolution: "<<detector_resolution<<"%"<<std::endl;
  std::cout<<"Material: "<<tracker_material<<std::endl;
  std::cout<<"Number of Subsystems: "<<number_of_subsystems<<std::endl;
}
