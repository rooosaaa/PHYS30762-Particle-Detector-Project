// Particle.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// This header file defines the abstract base class `Particle`, which serves as the foundation
// for representing all fundamental and composite particles in the detector simulation.
// Each derived particle type (e.g., electron, muon, hadron) extends this class with
// specific properties and behaviour relevant to high-energy physics experiments.
//
// Key features of this interface include:
// - Particle identification using name, ID, and charge
// - Encapsulation of four-momentum using a separate `FourMomentum` class
// - Validation of particle properties (name, charge, ID)
// - Polymorphic interface for particle-specific detection and printing logic
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef PARTICLE_H
#define PARTICLE_H

#include<string>
#include<memory>

#include "FourMomentum.h"

using namespace ParticleProperties;

namespace ParticleSystem
{
  // Pure abstract base class for all particles
  class Particle
  {
  protected:
    // Name of the particle
    std::string particle_name;
    // Four-momentum of the particle
    FourMomentum particle_four_momentum;
    // Integer ID for the particle so the user can distinguish between the same
    // particle type.
    int particle_id;
    // Charge of the particle in units of elementary charge (e)
    double particle_charge;
    
    // [VALIDATION]
    // Helper function to validate the particle ID
    static bool is_valid_id(int id);
    // Helper function to validate the particle name
    static bool is_valid_name(const std::string& name);
    // Helper function to validate the charge
    static bool is_valid_charge(double charge);

  public:
    // [CONSTRUCTORS/DESTRUCTORS]
    // Parametrised Constructor
    Particle(const std::string& name, int id, const FourMomentum& momentum);
    // Virtual destructor
    virtual ~Particle();
    
    // [GETTERS]
    std::string get_name() const {return particle_name;}
    const FourMomentum& get_momentum() const {return particle_four_momentum;}
    int get_id() const {return particle_id;}
    double get_charge() const {return particle_charge;}

    // [SETTERS]
    // Set the particle four momentum
    void set_momentum(const FourMomentum& momentum);
    void set_id(int id);
    virtual void set_name(std::string name) = 0;
    virtual void set_charge(double charge) = 0;
    
    // [PHYSICS METHODS]
    // Virtual methods that must be implemented by derived classes
    // Pure virtual print method to display particle information
    virtual void print() const = 0;
    // Pure virtual method to check if particle can be detected by a detector type
    virtual bool can_be_detected_by(const std::string& detector_type) const = 0;
  };
} // namespace ParticleSystem

#endif // PARTICLE_H
