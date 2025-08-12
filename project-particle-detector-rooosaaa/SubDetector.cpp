// SubDetector.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This implementation file defines the abstract base class `SubDetector`, which serves as the foundation
// for simulating detector components in a high-energy physics experiment. Each derived class
// represents a specific detector subsystem (e.g., electromagnetic calorimeter, muon detector)
// and models how it responds to incoming particles.
//
// Key features implemented in this file:
// - Base constructor and destructor for detector subsystems
// - Interface for applying energy resolution and simulating energy loss using a RNG
// - Validation of input parameters such as resolution and energy loss fraction
// - Particle detection logic with Gaussian smearing to model detector resolution
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include <iostream>

#include "SubDetector.h"

using namespace DetectorSubsystems;

// Since SubDetector is an abstract base class, the implementation here serves as a common 
// foundation for all sub-detectors, with core functions like setting resolution, energy loss 
// fraction, and basic detection mechanisms.

// [CONSTRUCTORS/DESTRUCTORS]

SubDetector::SubDetector(const std::string& name, int resolution, double energy_loss)
 : sub_detector_type(name)
{
  set_resolution(resolution);
  set_energy_loss_fraction(energy_loss);
  random_generator.seed(random_device()); // Seed the random generator
}

SubDetector::~SubDetector()
{
  //std::cout<<"SubDetector base class destructor called."<<std::endl;
}

// Helper function to validate the sub-detector name
bool SubDetector::is_valid_string_entry(const std::string& name)
{
    // Set an arbitrary maximum length for sub_detector name
  const size_t MAX_NAME_LENGTH = 100;
  // Check if the name is not empty and does not contain invalid characters
  if(!name.empty() && name.length() <= MAX_NAME_LENGTH &&
   name.find_first_not_of(
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") == std::string::npos) {return true;}
  else {return false;}
}

// [SETTERS]

void SubDetector::set_resolution(int resolution)
{
  // Validate resolution to ensure it is between 0 and 100
  if(resolution < 0 || resolution > 100) {throw std::invalid_argument(
    "Invalid resolution value. Must be between 0 and 100.");}
  else {detector_resolution = resolution;}
}

// Set how much energy is lost in each subdetector
void SubDetector::set_energy_loss_fraction(double energy_loss)
{
  // Validate energy loss fraction to ensure it is between 0.0 and 1.0
  if(energy_loss < 0.0 || energy_loss > 1.0) {throw std::invalid_argument(
    "Invalid energy loss fraction. Must be between 0.0 and 1.0.");}
  energy_loss_fraction = energy_loss;
}

// [METHODS]

// Method to detect a particle
double SubDetector::detect_particle(const Particle& particle, const double particle_energy) const
{
  // Calculate energy loss in the detector based on the particle's energy
  double energy_loss_in_detector = particle_energy * energy_loss_fraction;
  // If the particle cannot be detected by this sub-detector, return 0 energy
  if(!can_detect(particle)) {return 0.0;}
  // If the detector has perfect resolution (0%), return the energy loss directly
  if(detector_resolution == 0) {return energy_loss_in_detector;}
  // For realistic detection, apply resolution effects by generating a distribution
  double mean = energy_loss_in_detector;
  double std_dev = energy_loss_in_detector * (detector_resolution / 100.0);
  // Create a normal distribution with mean and standard deviation
  std::normal_distribution<double> distribution(mean, std_dev);
  // Generate a random measured energy based on the detector resolution
  double measured_energy = distribution(const_cast<std::minstd_rand&>(random_generator));
  // Use absolute value to ensure the measured energy is not negative
  return std::abs(measured_energy);
}