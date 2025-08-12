// Positron.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file defines the `Positron` class, which represents a positron (the antiparticle of the electron) in
// the particle detector simulation. The class inherits from the `Particle` base class and provides functionality
// specific to positrons.
//
// While a new base class for antiparticles could have been created, this design avoids repeating code since
// the positron shares most of its functionality with other particles, such as the electron (with the difference
// being its charge).
//
// Key methods implemented in this class include:
// - The Rule of 5 methods for memory management, ensuring proper copying and moving of positron objects.
// - Setter methods for setting the name and charge of the positron (both properties are validated).
// - The `print` method to display the positron's details, such as name, four-momentum, ID, and charge.
// - The `can_be_detected_by` method, which checks whether the positron can be detected by a given detector type.
//
// === COMPILATION AND EXECUTION ===
//

#ifndef POSITRON_H
#define POSITRON_H

#include "Particle.h"

namespace ParticleSystem
{
  class Positron : public Particle
  {
  private:
    // Any specific properties for positrons could go here
  public:
    // [RULE OF 5]
    // Default constructor
    Positron() : Particle("Positron", 1, FourMomentum()) {set_charge(+1);}
    // Parameterised constructor
    Positron(int id, const FourMomentum& momentum);
    // Copy constructor
    Positron(const Positron& other);
    // Move constructor
    Positron(Positron&& other) noexcept;
    // Copy assignment operator
    Positron& operator=(const Positron& other);
    // Move assignment operator
    Positron& operator=(Positron&& other) noexcept;
    // Destructor
    ~Positron();

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

#endif // POSITRON_H
