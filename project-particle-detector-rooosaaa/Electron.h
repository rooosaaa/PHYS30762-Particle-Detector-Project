// Electron.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// This header file defines the `Electron` class, which represents an electron particle in the
// detector simulation. It extends the abstract `Particle` base class, inheriting general particle
// properties and providing specific implementations for electrons, including charge and detection
// logic.
//
// Key features of this class include:
// - Specific initialisation for electron charge (-1) and particle name ("Electron")
// - Rule of 5 implementation for proper memory management (constructors, assignment operators, and destructor)
// - A `print` method to display particle information
// - A `can_be_detected_by` method to check if the electron can be detected by a given detector type
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef ELECTRON_H
#define ELECTRON_H

#include "Particle.h"

namespace ParticleSystem
{
  class Electron : public Particle
  {
  private:
    // Any specific properties for electrons could go here
  public:
    // [RULE OF 5]
    // Default constructor
    Electron() : Particle("Electron", 1, FourMomentum()) {set_charge(-1);}
    // Parameterised constructor
    Electron(int id, const FourMomentum& momentum);
    // Copy constructor
    Electron(const Electron& other);
    // Move constructor
    Electron(Electron&& other) noexcept;
    // Copy assignment operator
    Electron& operator=(const Electron& other);
    // Move assignment operator
    Electron& operator=(Electron&& other) noexcept;
    // Destructor
    ~Electron();

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

#endif // ELECTRON_H
