// FourMomentum.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// Implementation file for the FourMomentum class that represents a relativistic four-momentum
// vector (px, py, pz, E) used in particle physics.
//
// This implementation includes:
// - Memory management (constructors, destructors, and assignment operators)
// - Component setters with validation for physical constraints
// - Enforcement of relativistic constraints (E² ≥ p², non-negative energy)
// - Functions to perform several calculations using the four momentum, including
//   calculating the invariant mass for a system of particles.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef FOUR_MOMENTUM_H
#define FOUR_MOMENTUM_H

#include<cmath>
#include<iostream>
#include<stdexcept>
#include<vector>

namespace ParticleProperties
{
  class FourMomentum
  {
  private:
    // Cartesian coordinates
    double particle_px; // x-component of momentum in GeV
    double particle_py; // y-component of momentum in GeV
    double particle_pz; // z-component of momentum in GeV
    double particle_energy; // energy (E) in GeV

  public:
    // [RULE OF 5]
    // Default constructor
    FourMomentum();
    // Parameterized constructor
    FourMomentum(double px, double py, double pz, double energy);
    // Copy constructor
    FourMomentum(const FourMomentum& other);
    // Move constructor
    FourMomentum(FourMomentum&& other) noexcept;
    // Destructor
    ~FourMomentum();
    // Copy assignment operator
    FourMomentum& operator=(const FourMomentum& other);
    // Move assignment operator
    FourMomentum& operator=(FourMomentum&& other) noexcept;

    // [SETTERS & VALIDATION]
    // Method to set all components at once with validation - avoids mass-shell violation
    void set_momentum_components(double px, double py, double pz, double energy);
    // Helper method to validate four momentum components
    static bool validate_components(double px, double py, double pz, double energy);

    // [GETTERS]
    double get_px() const {return particle_px;}
    double get_py() const {return particle_py;}
    double get_pz() const {return particle_pz;}
    double get_energy() const {return particle_energy;}
      
    // [PHYSICS METHODS]
    // Calculate the invariant mass (m^2 = E^2 - p^2)
    double calculate_invariant_mass() const;
    // Calculate the transverse momentum (pT = √(px^2 + py^2))
    double calculate_transverse_momentum() const;
    // Calculate the total momentum magnitude (|p| = √(px^2 + py^2 + pz^2))
    double calculate_momentum_magnitude() const;
    // Calculate pseudorapidity (η = -ln(tan(θ/2)), where θ is the polar angle)
    double calculate_pseudorapidity() const;
    // Static method to calculate invariant mass of a system of particles
    static double calculate_system_invariant_mass(const std::vector<FourMomentum>& momenta);

    // [PRINT METHOD]
    void print() const;
  };
} // namespace ParticleProperties

#endif // FOUR_MOMENTUM_H