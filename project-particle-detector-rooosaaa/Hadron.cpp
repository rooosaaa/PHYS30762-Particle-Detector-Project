// Hadron.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// This file implements the methods for the `Hadron` class, which is derived from the `Particle` class.
// It provides functionality for managing the properties of hadrons (e.g., neutrons) in the context
// of a particle detector simulation.
//
// The implementation includes:
// - Rule of 5 methods for proper memory management
// - Setter methods for the name and charge of the hadron with validation
// - Methods for printing the hadron's properties and checking detection compatibility with various
//   detector types
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>

#include "Hadron.h"

using namespace ParticleSystem;

// [RULE OF 5]

Hadron::Hadron(int id, const FourMomentum& momentum, std::string name, double charge)
  : Particle(name, id, momentum)
{
  set_name(name);
  set_charge(charge);
}

Hadron::~Hadron()
{
  std::cout<<"Hadron destructor called. "<<std::endl;
}

Hadron::Hadron(const Hadron& other) : Particle(other)
{
  std::cout<<"Hadron copy constructor called. "<<std::endl;
  // Copy the hadron properties
  particle_name = other.particle_name;
  particle_four_momentum = other.particle_four_momentum;
  particle_id = other.particle_id;
  particle_charge = other.particle_charge;
}

Hadron::Hadron(Hadron&& other) noexcept : Particle(std::move(other))
{
  std::cout<<"Hadron move constructor called. "<<std::endl;
  // Move the hadron properties
  particle_name = std::move(other.particle_name);
  // Call move assignment operator for FourMomentum
  particle_four_momentum = std::move(other.particle_four_momentum);
  // Reset the moved-from object
  other.particle_name = "Moved Neutron";
  other.particle_id = 1;
  other.particle_charge = 0.0;
  // FourMomentum will be reset in its own move assignment operator
}

Hadron& Hadron::operator=(const Hadron& other)
{
  std::cout<<"Hadron copy assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Copy the hadron properties
    particle_name = other.particle_name;
    particle_four_momentum = other.particle_four_momentum;
    particle_id = other.particle_id;
    particle_charge = other.particle_charge;
  }
  return *this;
}

Hadron& Hadron::operator=(Hadron&& other) noexcept
{
  std::cout<<"Hadron move assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Move the hadron properties
    particle_name = std::move(other.particle_name);
    // Call move assignment operator for FourMomentum
    particle_four_momentum = std::move(other.particle_four_momentum);
    // Reset the moved-from object
    other.particle_name = "Moved Neutron";
    other.particle_id = 1;
    other.particle_charge = 0.0;
  }
  return *this;
}

// [SETTERS]

void Hadron::set_name(std::string name)
{
  // Validate the particle name
  if(is_valid_name(name)) {particle_name = name;}
  else {throw std::invalid_argument("Invalid Hadron name. Must consist of only letters and underscores.");}
}

// The charge must be a valid particle charge and also a multiple of 1/3.
void Hadron::set_charge(double charge)
{
  // Helper lambda to validate if charge is a multiple of 1/3
  auto is_valid_hadron_charge = [](double charge)
  {
    // Scale the value by 3.0 and round it to the nearest integer
    double scaled = charge * 3.0;
    double rounded = std::round(scaled);
    // Check if the absolute difference is within a small epsilon
    double epsilon = std::numeric_limits<double>::epsilon() * 100;
    // Check if the scaled value is close to the rounded value
    return std::abs(scaled - rounded) < epsilon;
  };
  // Validate the charge
  if(is_valid_charge(charge) && is_valid_hadron_charge(charge)) {particle_charge = charge;}
  else {throw std::invalid_argument("Invalid charge.");}
}

// [METHODS]

void Hadron::print() const
{
  std::cout<<"Hadron: "<<particle_name<<std::endl;
  particle_four_momentum.print();
  std::cout<<"ID: "<<particle_id<<std::endl;
  std::cout<<"Charge (e): "<<particle_charge<<std::endl;
}

// Detection method
bool Hadron::can_be_detected_by(const std::string& detector_type) const
{
  // Check if the hadron can be detected by the given detector type
  if(detector_type == "Hadronic Calorimeter" || detector_type == "Tracker") {return true;}
  else {return false;}
}
