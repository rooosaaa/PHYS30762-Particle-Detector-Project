// SubDetector.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// This header file defines the pure abstract base class `SubDetector` which serves as
// the foundation for all sub-detector components within the particle detection system.
// Each sub-detector represents a specific part of the overall detector (e.g., tracker, 
// calorimeter) and provides functionalities such as particle detection, energy loss modelling, 
// and detector resolution. Derived classes implement specific sub-detector behaviour for 
// various detector types used in high-energy physics experiments.
//
// The `SubDetector` class provides:
// - A base interface for particle detection with energy loss and resolution properties
// - Methods for detecting particles, checking detection capabilities, and printing information
// - A random number generator for simulating realistic detection processes and energy loss
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef SUB_DETECTOR_H
#define SUB_DETECTOR_H

#include<string>
#include<memory>
#include<random>

#include "Particle.h"

using namespace ParticleSystem;
using ParticleSystem::Particle;

namespace DetectorSubsystems
{
  // Pure abstract base class for all sub-detector components
  class SubDetector
  {
  protected:
    // Name of the sub-detector type (e.g., "Tracker", "Calorimeter")
    std::string sub_detector_type;
    // Resolution of the sub-detector, expressed as a percentage
    // (0% = perfect, 100% = no resolution)
    int detector_resolution;
    // Fraction of energy loss in the sub-detector
    double energy_loss_fraction;
    // Random number generator for simulating detection process
    // 'mutable' allows this member to be modified even in a const member function.
    // useful for generating random numbers in otherwise read-only operations.
    mutable std::minstd_rand random_generator;
    // Random device used to seed the random number generator
    // Note: std::random_device is non-copyable, so it must not be copied.
    // Therefore I'm not allowing the user to copy or move sub-detectors.
    // It provides non-deterministic random numbers if supported by the system.
    std::random_device random_device;
    // Helper function to validate if the particle's name is a valid string
    static bool is_valid_string_entry(const std::string& name);

  public:
    // [CONSTRUCTORS/DESTRUCTORS]
    // Parametrised constructor
    SubDetector(const std::string& name, int resolution, double energy_loss);
    // Virtual destructor
    virtual ~SubDetector();

    // [GETTERS]
    std::string get_sub_detector_type() const {return sub_detector_type;}
    int get_resolution() const {return detector_resolution;}
    double get_energy_loss_fraction() const {return energy_loss_fraction;}

    // [SETTERS]
    // Pure abstract method that must be implemented in derived classes to set the sub-detector's name
    virtual void set_sub_detector_name(const std::string& name) = 0;
    void set_resolution(int resolution);
    void set_energy_loss_fraction(double energy_loss);
    
    // [METHODS]
    // Function to detect a particle and return its energy after detection
    double detect_particle(const Particle& particle, const double energy) const;
    // Pure abstract method that must be implemented in derived classes to print details of the sub-detector
    virtual void print() const = 0;
    // Virtual method to check if this detector can detect a specific particle
    // by calling the can_be_detected_by method in the Particle class
    virtual bool can_detect(const Particle& particle) const {
      return particle.can_be_detected_by(get_sub_detector_type());}
  };
} // namespace DetectorSubsystems

#endif // SUB_DETECTOR_H