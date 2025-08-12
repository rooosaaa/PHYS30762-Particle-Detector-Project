// Particle.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file implements the base functionality of the abstract Particle class,
// which is inherited by all specific particle types in the detector simulation.
// It includes constructor logic and helper methods for validating particle attributes,
// such as name, ID, charge, and four-momentum.
//
// Although most functionality is implemented in derived classes, this file ensures
// basic consistency and error handling across all particle types through its core logic.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<climits>  // For INT_MAX

#include "Particle.h"

using namespace ParticleSystem;

// [CONSTRUCTORS/DESTRUCTORS]

Particle::Particle(const std::string& name, int id, const FourMomentum& momentum)
  : particle_name(name), particle_four_momentum(momentum)
{
  // FourMomentum class parameterised constructor should validate the momentum entered
  set_id(id);
}

Particle::~Particle()
{
  //std::cout<<"Calling Particle base class destructor."<<std::endl;
}

// [VALIDATION]

bool Particle::is_valid_id(int id)
{
  // Check if the ID is a positive integer
  return (id > 0) && (id <= INT_MAX);
}

bool Particle::is_valid_name(const std::string& name)
{
  // Set an arbitrary maximum length for the particle name
  const size_t MAX_NAME_LENGTH = 100;
  // Check if the name is not empty and does not contain invalid characters
  if(!name.empty() && name.length() <= MAX_NAME_LENGTH &&
   name.find_first_not_of(
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") ==
      std::string::npos) {return true;}
  else {return false;}
}

bool Particle::is_valid_charge(double charge)
{
  const double max_double = std::numeric_limits<double>::max();
  // Check if the charge exceeds the maximum double value
  if(charge > max_double || charge < -max_double) {return false;}
  return true;
}

// [SETTERS]

void Particle::set_id(int id)
{
  // Validate ID
  if(is_valid_id(id)) {particle_id = id;}
  else {throw std::invalid_argument("Invalid particle ID. Must be a positive integer.");}
}

void Particle::set_momentum(const FourMomentum& momentum)
{
  // Validate the four-momentum components
  if(!momentum.validate_components(momentum.get_px(), momentum.get_py(), momentum.get_pz(),
   momentum.get_energy())) {throw std::invalid_argument("Invalid four-momentum components for: "
    + particle_name);}
  else {particle_four_momentum = momentum;}
}
