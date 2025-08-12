// Neutrino.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// This header file defines the `Neutrino` class, which represents a neutrino particle in the
// detector simulation. It extends the abstract `Particle` base class, inheriting general particle
// properties and providing specific implementations for neutrinos, including charge and detection
// logic.
//
// Key features of this class include:
// - Specific initialisation for neutrino charge (0) and particle name ("Neutrino")
// - Rule of 5 implementation for proper memory management (constructors, assignment operators, and destructor)
// - A `print` method to display particle information
// - A `can_be_detected_by` method to check if the neutrino can be detected by a given detector type
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include "Particle.h"

namespace ParticleSystem
{
  class Neutrino : public Particle
  {
  private:
    // Any specific properties for neutrinos could go here
  public:
    // [RULE OF 5]
    // Default constructor
    Neutrino() : Particle("Neutrino", 1, FourMomentum()) {set_charge(0);}
    // Parameterised constructor
    Neutrino(int id, const FourMomentum& momentum);
    // Copy constructor
    Neutrino(const Neutrino& other);
    // Move constructor
    Neutrino(Neutrino&& other) noexcept;
    // Copy assignment operator
    Neutrino& operator=(const Neutrino& other);
    // Move assignment operator
    Neutrino& operator=(Neutrino&& other) noexcept;
    // Destructor
    ~Neutrino();

    // [SETTERS]
    void set_name(std::string name) override;
    void set_charge(double charge) override;
    
    // [PRINT METHOD]
    void print() const override;
    
    // [DETECTION METHOD]
    // Method to check if particle can be detected by a detector type
    bool can_be_detected_by(const std::string& detectorType) const override;
  };
} // namespace ParticleSystem

#endif // NEUTRINO_H
