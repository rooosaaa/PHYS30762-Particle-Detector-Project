// Electron.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// This file contains the implementation of the `Electron` class defined in the header file `electron.h`.
// It provides constructors, destructors, assignment operators, and methods for managing the properties and behavior of 
// electron particles within the detector simulation.
//
// Key functionalities of this class include:
// - Rule of 5 implementation for proper resource management
// - Setter methods for validating and setting electron-specific properties (charge and name)
// - Methods for printing electron information and checking detector compatibility
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>

#include "Electron.h"

using namespace ParticleSystem;

// [RULE OF 5]

Electron::Electron(int id, const FourMomentum& momentum) : Particle("Electron", id, momentum)
{
  set_charge(-1);
}

Electron::~Electron()
{
  std::cout<<"Electron destructor called. "<<std::endl;
}

Electron::Electron(const Electron& other) : Particle(other)
{
  std::cout<<"Electron copy constructor called. "<<std::endl;
  // Copy the electron properties
  particle_name = other.particle_name;
  particle_four_momentum = other.particle_four_momentum;
  particle_id = other.particle_id;
  particle_charge = other.particle_charge;
}

Electron::Electron(Electron&& other) noexcept : Particle(std::move(other))
{
  std::cout<<"Electron move constructor called. "<<std::endl;
  // Move the electron properties
  particle_name = std::move(other.particle_name);
  // Call move assignment operator for FourMomentum
  particle_four_momentum = std::move(other.particle_four_momentum);
  // Reset the moved-from object
  other.particle_name = "Electron";
  // FourMomentum will be reset in its own move assignment operator
  other.particle_id = 1;
  other.particle_charge = -1;
}

Electron& Electron::operator=(const Electron& other)
{
  std::cout<<"Electron copy assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Copy the electron properties
    particle_name = other.particle_name;
    particle_four_momentum = other.particle_four_momentum;
    particle_id = other.particle_id;
    particle_charge = other.particle_charge;
  }
  return *this;
}

Electron& Electron::operator=(Electron&& other) noexcept
{
  std::cout<<"Electron move assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Move the electron properties
    particle_name = std::move(other.particle_name);
    particle_four_momentum = std::move(other.particle_four_momentum);
    // Reset the moved-from object
    other.particle_name = "Electron";
    // FourMomentum will be reset in its own move assignment operator
    other.particle_id = 1;
    other.particle_charge = -1;
  }
  return *this;
}

// [SETTERS]

void Electron::set_charge(double charge)
{
  // Validate the charge
  if(is_valid_charge(charge) && charge == -1) {particle_charge = charge;}
  else {throw std::invalid_argument("Invalid charge for Electron. Must be -1.");}
}

void Electron::set_name(std::string name)
{
  // Validate the name
  if(is_valid_name(name) && name == "Electron") {particle_name = name;}
  else {throw std::invalid_argument("Invalid name for Electron. Must be 'Electron'.");}
}

// [METHODS]

void Electron::print() const
{
  std::cout<<"Particle: "<<particle_name<<std::endl;
  particle_four_momentum.print();
  std::cout<<"ID: "<<particle_id<<std::endl;
  std::cout<<"Charge (e): "<<particle_charge<<std::endl;
}

// Detection method
bool Electron::can_be_detected_by(const std::string& detector_type) const
{
  // Check if the electron can be detected by the given detector type
  if(detector_type == "EM Calorimeter" || detector_type == "Tracker") {return true;}
  else {return false;}
}
