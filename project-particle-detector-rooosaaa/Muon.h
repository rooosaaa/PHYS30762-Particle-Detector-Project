// Muon.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This header file defines the `Muon` class, which is a subclass of `Particle`. It provides functionality
// for representing and managing the properties of a muon particle within a particle detector simulation.
//
// The `Muon` class includes:
// - Rule of 5 methods for proper memory management
// - Setter methods for the name and charge of the muon, with validation
// - Methods for printing the muon's properties and checking detection compatibility with various detector
//   types
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef MUON_H
#define MUON_H

#include "Particle.h"

namespace ParticleSystem
{
  class Muon : public Particle
  {
  private:
    // Any specific properties for muons could go here
  public:
  // [RULE OF 5]
    // Default Constructor
    Muon() : Particle("Muon", 1, FourMomentum()) {set_charge(-1);}
    // Parameterised Constructor
    Muon(int id, const FourMomentum& momentum);
    // Copy Constructor
    Muon(const Muon& other);
    // Move Constructor
    Muon(Muon&& other) noexcept;
    // Copy Assignment Operator
    Muon& operator=(const Muon& other);
    // Move Assignment Operator
    Muon& operator=(Muon&& other) noexcept;
    // Destructor
    ~Muon();

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

#endif // MUON_H
