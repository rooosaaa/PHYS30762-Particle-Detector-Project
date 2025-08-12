// Positron.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file implements the methods of the `Positron` class, which represents a positron (the antiparticle of the electron)
// in the particle detection system. The class inherits from the `Particle` base class and provides functionality
// specific to positrons.
//
// The file includes the following:
// - The Rule of 5 methods for memory management, ensuring proper copying and moving of positron objects.
// - Setter methods for validating and setting the name and charge of the Positron.
// - Print method for displaying information about the Positron.
// - Detection method to check if the Positron can be detected by specific detector types.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>

#include "Positron.h"

using namespace ParticleSystem;

// [RULE OF 5]

Positron::Positron(int id, const FourMomentum& momentum) : Particle("Positron", id, momentum)
{
  set_charge(+1);
}

Positron::~Positron()
{
  std::cout<<"Positron destructor called. "<<std::endl;
}

Positron::Positron(const Positron& other) : Particle(other)
{
  std::cout<<"Positron copy constructor called. "<<std::endl;
  // Copy the positron properties
  particle_name = other.particle_name;
  particle_four_momentum = other.particle_four_momentum;
  particle_id = other.particle_id;
  particle_charge = other.particle_charge;
}

Positron::Positron(Positron&& other) noexcept : Particle(std::move(other))
{
  std::cout<<"Positron move constructor called. "<<std::endl;
  // Move the electron properties
  particle_name = std::move(other.particle_name);
  // Call move assignment operator for FourMomentum
  particle_four_momentum = std::move(other.particle_four_momentum);
  // Reset the moved-from object
  other.particle_name = "Moved Positron";
  other.particle_id = 1;
  other.particle_charge = +1;
  // FourMomentum will be reset in its own move assignment operator
}

Positron& Positron::operator=(const Positron& other)
{
  std::cout<<"Positron copy assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Copy the positron properties
    particle_name = other.particle_name;
    particle_four_momentum = other.particle_four_momentum;
    particle_id = other.particle_id;
    particle_charge = other.particle_charge;
  }
  return *this;
}

Positron& Positron::operator=(Positron&& other) noexcept
{
  std::cout<<"Positron move assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Move the positron properties
    particle_name = std::move(other.particle_name);
    particle_four_momentum = std::move(other.particle_four_momentum);
    // Reset the moved-from object
    other.particle_name = "Moved Positron";
    other.particle_id = 1;
    other.particle_charge = +1;
    // FourMomentum will be reset in its own move assignment operator
  }
  return *this;
}

// [SETTERS]

void Positron::set_name(std::string name)
{
  // Validate the particle name
  if(is_valid_name(name) && name == "Positron") {particle_name = name;}
  else {throw std::invalid_argument("Invalid name for Positron. Must be 'Positron'.");}
}

void Positron::set_charge(double charge)
{
  // Validate the charge
  if(is_valid_charge(charge) && charge == +1) {particle_charge = charge;}
  else {throw std::invalid_argument("Invalid charge for Positron. Must be +1.");}
}

// [METHODS]

// Print method
void Positron::print() const
{
  std::cout<<"Particle: "<<particle_name<<std::endl;
  particle_four_momentum.print();
  std::cout<<"ID: "<<particle_id<<std::endl;
  std::cout<<"Charge (e): "<<particle_charge<<std::endl;
}

// Detection method
bool Positron::can_be_detected_by(const std::string& detector_type) const
{
  // Check if the electron can be detected by the given detector type
  if(detector_type == "EM Calorimeter" || detector_type == "Tracker") {return true;}
  else {return false;}
}
