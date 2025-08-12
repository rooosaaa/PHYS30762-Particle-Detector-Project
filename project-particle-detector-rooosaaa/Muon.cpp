// Muon.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// This source file implements the `Muon` class, providing the functionality for managing the properties
// and behaviors of muon particles within the particle detector simulation. It includes the:
// - Rule of 5 for proper memory management,
// - Methods for setting and printing properties
// - Method for detecting muons in specific detectors.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>

#include "Muon.h"

using namespace ParticleSystem;

// [RULE OF 5]

Muon::Muon(int id, const FourMomentum& momentum) : Particle("Muon", id, momentum)
{
  set_charge(-1);
}

Muon::~Muon()
{
  std::cout<<"Muon destructor called. "<<std::endl;
}

Muon::Muon(const Muon& other) : Particle(other)
{
  std::cout<<"Muon copy constructor called. "<<std::endl;
  // Copy the muon properties
  particle_name = other.particle_name;
  particle_four_momentum = other.particle_four_momentum;
  particle_id = other.particle_id;
  particle_charge = other.particle_charge;
}

Muon::Muon(Muon&& other) noexcept : Particle(std::move(other))
{
  std::cout<<"Muon move constructor called. "<<std::endl;
  // Move the muon properties
  particle_name = std::move(other.particle_name);
  // Call move assignment operator for FourMomentum
  particle_four_momentum = std::move(other.particle_four_momentum);
  // Reset the moved-from object
  other.particle_name = "Moved Muon";
  other.particle_id = 1;
  other.particle_charge = -1;
  // FourMomentum will be reset in its own move assignment operator
}

Muon& Muon::operator=(const Muon& other)
{
  std::cout<<"Muon copy assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Copy the muon properties
    particle_name = other.particle_name;
    particle_four_momentum = other.particle_four_momentum;
    particle_id = other.particle_id;
    particle_charge = other.particle_charge;
  }
  return *this;
}

Muon& Muon::operator=(Muon&& other) noexcept
{
  std::cout<<"Muon move assignment operator called. "<<std::endl;
  if(this != &other)
  {
    // Move the muon properties
    particle_name = std::move(other.particle_name);
    // Call move assignment operator for FourMomentum
    particle_four_momentum = std::move(other.particle_four_momentum);
    // Reset the moved-from object
    other.particle_name = "Moved Muon";
    other.particle_id = 1;
    other.particle_charge = -1;
    // FourMomentum will be reset in its own move assignment operator
  }
  return *this;
}

// [SETTERS]

void Muon::set_name(std::string name)
{
  if(is_valid_name(name) && name == "Muon") {particle_name = name;}
  else {throw std::invalid_argument("Invalid name for Muon. Must be 'Muon'.");}
}

void Muon::set_charge(double charge)
{
  // Validate the charge
  if(is_valid_charge(charge) && charge == -1) {particle_charge = charge;}
  else {throw std::invalid_argument("Invalid charge for Muon. Must be -1.");}
}

// [METHODS]

void Muon::print() const
{
  std::cout<<"Particle: "<<particle_name<<std::endl;
  particle_four_momentum.print();
  std::cout<<"ID: "<<particle_id<<std::endl;
  std::cout<<"Charge (e): "<<particle_charge<<std::endl;
}

// Detection method
bool Muon::can_be_detected_by(const std::string& detector_type) const
{
  // Example logic for muon detection
  if(detector_type == "Muon Spectrometer" || detector_type == "Tracker") {return true;}
  else {return false;}
}
