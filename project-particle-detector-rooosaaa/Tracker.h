// Tracker.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file defines the Tracker class, a type of sub-detector used in the particle detector
// simulation. Inheriting from the SubDetector base class, the Tracker includes specific
// attributes such as its material and number of subsystems.
//
// The Tracker class follows the Rule of 5, explicitly deleting copy/move constructors and 
// assignment operators to reflect the physical non-reusability of real detector components.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef TRACKER_H
#define TRACKER_H

#include "SubDetector.h"

namespace DetectorSubsystems
{
  class Tracker : public SubDetector
  {
  private:
    // Material of the tracker (e.g. silicon)
    std::string tracker_material;
    // Number of distinct subsystems within the tracker (e.g. pixel detector)
    int number_of_subsystems;
    // Any additional properties of the Tracker can be added here

  public:
    // [RULE OF 5]
    // Default constructor
    // Sets resolution to 0 and energy loss to 1.0 (ideal, lossless tracker)
    Tracker();
    // Parameterised constructor
    Tracker(int resolution, double energy_loss, const std::string& material, int number);
    // Prevent copying and moving of trackers:
    // Physically, detectors are not copied or transferred;
    // Logically, prevents mishandling of internal state like RNG or identification
    // Copy constructor
    Tracker(const Tracker& other) = delete;
    // Move constructor
    Tracker(Tracker&& other) = delete;
    // Copy assignment operator
    Tracker& operator=(const Tracker& other) = delete;
    // Move assignment operator
    Tracker& operator=(Tracker&& other) = delete;
    // Destructor
    ~Tracker();

    // [GETTERS]
    std::string get_tracker_material() const {return tracker_material;}
    int get_number_of_subsystems() const {return number_of_subsystems;}

    // [SETTERS]
    // Set the name of the sub-detector (overrides virtual function in base class)
    void set_sub_detector_name(const std::string& name) override;
    void set_tracker_material(const std::string& material);
    void set_number_of_subsystems(const int number);
    
    // [METHODS]
    // Print Tracker information
    void print() const override;
};
} // namespace DetectorSubsystems

#endif // TRACKER_H
