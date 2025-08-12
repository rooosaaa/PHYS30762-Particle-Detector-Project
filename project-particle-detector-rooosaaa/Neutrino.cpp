// Neutrino.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file defines the implementation of the `Neutrino` class, which represents a neutrino particle 
// in the detector simulation. It includes the Rule of 5 methods for proper memory management, 
// as well as specific methods for setting the neutrino's properties, printing particle information, 
// and determining whether the neutrino can be detected by a given detector.
//
// Key features of this file include:
// - Implementation of the Rule of 5 (constructors, assignment operators, destructor)
// - Proper handling of neutrino-specific properties like name ("Neutrino") and charge (0)
// - The `print` method outputs neutrino properties, including its four-momentum and ID
// - The `can_be_detected_by` method checks that neutrinos cannot be detected by typical detectors
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>

#include "Neutrino.h"

using namespace ParticleSystem;

// [RULE OF 5]

Neutrino::Neutrino(int id, const FourMomentum& momentum)  : Particle("Neutrino", id, momentum)
{
  set_charge(0);
}

Neutrino::~Neutrino()
{
  std::cout<<"Neutrino destructor called. "<<std::endl;
}

Neutrino::Neutrino(const Neutrino& other) : Particle(other)
{
  std::cout<<"Neutrino copy constructor called. "<<std::endl;
  // Copy the neutrino properties
  particle_name = other.particle_name;
  particle_four_momentum = other.particle_four_momentum;
  particle_id = other.particle_id;
  particle_charge = other.particle_charge;
}

Neutrino::Neutrino(Neutrino&& other) noexcept : Particle(std::move(other))
{
  std::cout<<"Neutrino move constructor called. "<<std::endl;
  // Move the neutrino properties
  particle_name = std::move(other.particle_name);
  // Call move assignment operator for FourMomentum
  particle_four_momentum = std::move(other.particle_four_momentum);
  // Reset the moved-from object
  other.particle_name = "Moved Neutrino";
  other.particle_id = 1;
  other.particle_charge = 0.0;
  // FourMomentum will be reset in its own move assignment operator
}

Neutrino& Neutrino::operator=(const Neutrino& other)
{
  std::cout<<"Neutrino copy assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Copy the neutrino properties
    particle_name = other.particle_name;
    particle_four_momentum = other.particle_four_momentum;
    particle_id = other.particle_id;
    particle_charge = other.particle_charge;
  }
  return *this;
}

Neutrino& Neutrino::operator=(Neutrino&& other) noexcept
{
  std::cout<<"Neutrino move assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Move the neutrino properties
    particle_name = std::move(other.particle_name);
    // Call move assignment operator for FourMomentum
    particle_four_momentum = std::move(other.particle_four_momentum);
    // Reset the moved-from object
    other.particle_name = "Moved Neutrino";
    other.particle_id = 1;
    other.particle_charge = 0.0;
  }
  return *this;
}

// [SETTERS]

void Neutrino::set_name(std::string name)
{
  // Validate the particle name
  if(is_valid_name(name) && name == "Neutrino") {particle_name = name;}
  else {throw std::invalid_argument("Invalid name for Neutrino. Must be 'Neutrino'.");}
}

void Neutrino::set_charge(double charge)
{
  // Validate the charge
  if(is_valid_charge(charge) && charge == 0) {particle_charge = charge;}
  else {throw std::invalid_argument("Invalid charge for Neutrino. Must be 0.");}
}

// [METHODS]

void Neutrino::print() const
{
  std::cout<<"Particle Name: "<<particle_name<<std::endl;
  particle_four_momentum.print();
  std::cout<<"ID: "<<particle_id<<std::endl;
  std::cout<<"Charge (e): "<<particle_charge<<std::endl;
}

// Detection method
bool Neutrino::can_be_detected_by(const std::string& detector_type) const
{
  // Neutrinos are not detected by any of the detectors
  return false;
}
