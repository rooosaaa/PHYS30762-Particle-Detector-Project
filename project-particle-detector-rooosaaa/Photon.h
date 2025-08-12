// Photon.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file defines the header for the `Photon` class, which represents a photon particle 
// in the particle detector simulation. The `Photon` class inherits from the `Particle` base class 
// and implements the Rule of 5 for proper memory management.
//
// Key features of this file include:
// - The Rule of 5 methods
// - The setter methods to set the photon’s properties (name and charge)
// - The `print` method that outputs the photon's properties
// - The `can_be_detected_by` method which checks if the photon can be detected by a given detector
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef PHOTON_H
#define PHOTON_H

#include "Particle.h"

namespace ParticleSystem
{
  class Photon : public Particle {
  private:
    // Any specific properties for photons could go here
  public:
    // [RULE OF 5]
    // Default constructor
    Photon() : Particle("Photon", 1, FourMomentum()) {set_charge(0);}
    // Parameterised constructor
    Photon(int id, const FourMomentum& momentum);
    // Copy constructor
    Photon(const Photon& other);
    // Move constructor
    Photon(Photon&& other) noexcept;
    // Copy assignment operator
    Photon& operator=(const Photon& other);
    // Move assignment operator
    Photon& operator=(Photon&& other) noexcept;
    // Destructor
    ~Photon();
    
    // [SETTERS]
    void set_name(std::string name) override;
    void set_charge(double charge) override;

    // [PRINT METHOD]
    void print() const override;
    
    // [DETECTION METHOD]
    // Method to check if particle can be detected by a detector type
    bool can_be_detected_by(const std::string& detector_type) const override;
  };
} // namespace ParticleSystem

#endif // PHOTON_H
