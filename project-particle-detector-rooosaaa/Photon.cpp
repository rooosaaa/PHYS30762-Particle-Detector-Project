// Photon.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file defines the implementation of the `Photon` class methods.
// The `Photon` class inherits from the `Particle` base class and represents a photon in the particle detector
// simulation.
//
// Key methods implemented in this file include:
// - The Rule of 5 methods for memory management.
// - Setter methods for setting the name and charge of the photon (both properties are validated).
// - The `print` method to display the photon's details, such as name, four-momentum, ID, and charge.
// - The `can_be_detected_by` method, which checks whether the photon can be detected by a given detector type.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>

#include "Photon.h"

using namespace ParticleSystem;

// [RULE OF 5]

Photon::Photon(int id, const FourMomentum& momentum) : Particle("Photon", id, momentum)
{
  set_charge(0);
}

Photon::~Photon()
{
  std::cout<<"Photon destructor called. "<<std::endl;
}

Photon::Photon(const Photon& other) : Particle(other)
{
  std::cout<<"Photon copy constructor called. "<<std::endl;
  // Copy the photon properties
  particle_name = other.particle_name;
  particle_four_momentum = other.particle_four_momentum;
  particle_id = other.particle_id;
  particle_charge = other.particle_charge;
}

Photon::Photon(Photon&& other) noexcept : Particle(std::move(other))
{
  std::cout<<"Photon move constructor called. "<<std::endl;
  // Move the photon properties
  particle_name = std::move(other.particle_name);
  // Call move assignment operator for FourMomentum
  particle_four_momentum = std::move(other.particle_four_momentum);
  // Reset the moved-from object
  other.particle_name = "Moved Photon";
  other.particle_id = 1; // Reset ID to a default value
  other.particle_charge = 0.0; // Reset charge to a default value
  // FourMomentum will be reset in its own move assignment operator
}

Photon& Photon::operator=(const Photon& other)
{
  std::cout<<"Photon copy assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Copy the photon properties
    particle_name = other.particle_name;
    particle_four_momentum = other.particle_four_momentum;
    particle_id = other.particle_id;
    particle_charge = other.particle_charge;
  }
  return *this;
}

Photon& Photon::operator=(Photon&& other) noexcept
{
  std::cout<<"Photon move assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Move the photon properties
    particle_name = std::move(other.particle_name);
    particle_four_momentum = std::move(other.particle_four_momentum);
    // Reset the moved-from object
    other.particle_name = "Moved Photon";
    other.particle_id = 1; // Reset ID to a default value
    other.particle_charge = 0.0; // Reset charge to a default value
    // FourMomentum will be reset in its own move assignment operator
  }
  return *this;
}

// [SETTERS]

void Photon::set_name(std::string name)
{
  if(is_valid_name(name) && name == "Photon") {particle_name = name;}
  else {throw std::invalid_argument("Invalid name for Photon. Must be 'Photon'.");}
}

void Photon::set_charge(double charge)
{
  // Validate the charge
  if(is_valid_charge(charge) && charge == 0) {particle_charge = charge;}
  else {throw std::invalid_argument("Invalid charge for Photon. Must be 0.");}
}

// [METHODS]

void Photon::print() const
{
  std::cout<<"Particle: "<<particle_name<<std::endl;
  particle_four_momentum.print();
  std::cout<<"ID: "<<particle_id<<std::endl;
  std::cout<<"Charge (e): "<<particle_charge<<std::endl;
}

// Detection method
bool Photon::can_be_detected_by(const std::string& detector_type) const
{
  // Photons are neutral and can only be detected by calorimeters
  if(detector_type == "EM Calorimeter") {return true;}
  else {return false;}
}
