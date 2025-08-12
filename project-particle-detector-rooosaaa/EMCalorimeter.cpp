// EMCalorimeter.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// Implementation file for the EMCalorimeter class, which is part of the DetectorSubsystems namespace.
// The EMCalorimeter class models the Electromagnetic Calorimeter (EM Calorimeter) detector, providing:
// - Constructors for initializing the calorimeter's parameters
// - Setters for configuring layers and materials
// - A print method for outputting details about the calorimeter
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>
#include<set>
#include<map>
#include<climits>  // For INT_MAX

#include "EMCalorimeter.h"

using namespace DetectorSubsystems;

// [RULE OF 5]

EMCalorimeter::EMCalorimeter() : Calorimeter("EM Calorimeter", 0, 1, 3)
{
  std::cout<<"Calling EMCalorimeter class default constructor."<<std::endl;
  // Using a list so that we can easily add or remove materials
  std::list<std::string> materials = {"LAr", "W", "Pb"};
  set_em_cal_materials(materials);
}

EMCalorimeter::EMCalorimeter(int resolution, double energy_loss, int layers, std::list<std::string> materials)
  : Calorimeter("EM Calorimeter", resolution, energy_loss, layers)
{
  set_em_cal_materials(materials);
  // The SubDetector base class contructor seeds the random generator and validates the resolution
}

EMCalorimeter::~EMCalorimeter()
{
  std::cout<<"Calling EMCalorimeter class destructor."<<std::endl;
}

// [SETTERS]

void EMCalorimeter::set_sub_detector_name(const std::string& name)
{
  if(name == "EM Calorimeter") {sub_detector_type = name;}
  else {throw std::invalid_argument("Invalid sub-detector type. Must be 'EM Calorimeter'.");}
}

// Set the EM calorimeter materials
void EMCalorimeter::set_em_cal_materials(std::list<std::string> materials)
{
  // Set types allowed
  // Using a set for O(1) lookups
  static const std::set<std::string> valid_types = {"LAr", "W", "Pb", "Cu", "PbWO4"};
  // Check for invalid materials
  for(const auto& type : materials)
  {
    if(valid_types.find(type) == valid_types.end()) {throw std::invalid_argument(
      "Invalid EM Calorimeter chamber type. Valid types are 'LAr', 'W', 'PbWO4', 'Pb' & 'Cu'.");}
  }
  em_calorimeter_materials = materials;
}

// [METHODS]

// Helper function to get the description of the material
std::string EMCalorimeter::material_descriptions(const std::string& material)
{
  // Using a map as it is more efficient for lookups
  static const std::map<std::string, std::string> material_descriptions =
  {
    {"LAr", "Liquid Argon (LAr)"},
    {"W", "Tungsten (W)"},
    {"Pb", "Lead (Pb)"},
    {"PbWO4", "Lead-Tungsten Crystals (PbWO4)"},
    {"Cu", "Copper (Cu)"}
  };

  auto it = material_descriptions.find(material);
  // Return full description or just the material if not found
  return (it != material_descriptions.end()) ? it->second : material;
}

// Print method to output the details of the em calorimeter
void EMCalorimeter::print() const
{
  std::cout<<"Sub-detector: "<<sub_detector_type<<std::endl;
  std::cout<<"Resolution: "<<detector_resolution<<"%"<<std::endl;
  std::cout<<"Number of layers: "<<calorimeter_layers<<std::endl;
  std::cout<<"Materials: ";
  if(em_calorimeter_materials.empty()) {std::cout<<"None";}
  else
  {
    for(const auto& material : em_calorimeter_materials)
    {
      std::cout<<"\n- "<<material_descriptions(material);
    }
  }
  std::cout<<std::endl;
}