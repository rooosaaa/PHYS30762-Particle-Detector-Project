// Hadron.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// This project...
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef HADRON_H
#define HADRON_H

#include "Particle.h"

namespace ParticleSystem
{
  class Hadron : public Particle
  {
  private:
    // Any specific properties for hadrons could go here
  public:
    // [RULE OF 5]
    // Default constructor
    Hadron() : Particle("Neutron", 1, FourMomentum()) {set_charge(0);}
    // Parametrised constructor
    Hadron(int id, const FourMomentum& momentum, std::string name, double charge);
    // Copy constructor
    Hadron(const Hadron& other);
    // Move constructor
    Hadron(Hadron&& other) noexcept;
    // Copy assignment operator
    Hadron& operator=(const Hadron& other);
    // Move assignment operator
    Hadron& operator=(Hadron&& other) noexcept;
    // Destructor
    ~Hadron();

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

#endif // HADRON_H
