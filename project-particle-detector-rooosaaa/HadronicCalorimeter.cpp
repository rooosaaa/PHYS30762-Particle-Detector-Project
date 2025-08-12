// HadronicCalorimeter.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Implementation file for the HadronicCalorimeter class, which extends the Calorimeter class.
// It provides specific functionality for the hadronic calorimeter detector, including:
// - A default constructor
// - A parameterised constructor
// - Setter methods for the sub-detector name, materials, and layers
// - Handling materials used in the calorimeter
// - Managing the number of layers in the detector
// - Printing information about the calorimeter configuration
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>
#include<set>
#include<map>
#include<climits>  // For INT_MAX

#include "HadronicCalorimeter.h"

using namespace DetectorSubsystems;

// [RULE OF 5]

HadronicCalorimeter::HadronicCalorimeter() : Calorimeter("Hadronic Calorimeter", 0, 1, 3)
{
  std::cout<<"Calling HadronicCalorimeter class default constructor."<<std::endl;
  // Default materials for the calorimeter
  // Using a list so that we can easily add or remove materials
  std::list<std::string> materials = {"Steel", "PST"};
  set_hadronic_cal_materials(materials);
}

HadronicCalorimeter::HadronicCalorimeter(int resolution, double energy_loss, int layers,
  std::list<std::string> materials)
  : Calorimeter("Hadronic Calorimeter", resolution, energy_loss, layers)
{
  // Using a list so that we can easily add or remove materials
  set_hadronic_cal_materials(materials);
  // The SubDetector base class constructor seeds the random generator and validates the resolution
}

HadronicCalorimeter::~HadronicCalorimeter()
{
  std::cout<<"Calling HadronicCalorimeter class destructor."<<std::endl;
}

// [SETTERS]

void HadronicCalorimeter::set_sub_detector_name(const std::string& name)
{
  if(name == "Hadronic Calorimeter") {sub_detector_type = name;}
  else {throw std::invalid_argument("Invalid sub-detector type. Must be 'Hadronic Calorimeter'.");}
}

void HadronicCalorimeter::set_hadronic_cal_materials(std::list<std::string> materials)
{
  // Set types allowed
  // Using a set for O(1) lookups
  static const std::set<std::string> valid_types = {"Steel", "PST", "W", "Cu", "LAr","Brass"};
  // Check for invalid materials
  for(const auto& type : materials)
  {
    if(valid_types.find(type) == valid_types.end()) {throw std::invalid_argument(
      "Invalid Hadronic Calorimeter chamber type. Valid types are 'Steel', 'Brass', 'PST','LAr', 'W' & 'Cu'.");}
  }
  hadronic_calorimeter_materials = materials;
}

// [METHODS]

// Helper function to get the description of the material
std::string HadronicCalorimeter::material_descriptions(const std::string& material)
{
  // Using a map as it is more efficient for lookups
  static const std::map<std::string, std::string> material_descriptions =
  {
    {"LAr", "Liquid Argon (LAr)"},
    {"W", "Tungsten (W)"},
    {"Steel", "Steel"},
    {"Brass", "Brass"},
    {"Cu", "Copper (Cu)"},
    {"PST", "Plastic Scintillator Tiles (PST)"}
  };

  auto it = material_descriptions.find(material);
  // Return full description or just the material if not found
  return (it != material_descriptions.end()) ? it->second : material;
}

// Print method to output the details of the hadronic calorimeter
void HadronicCalorimeter::print() const
{
  std::cout<<"Sub-detector: "<<sub_detector_type<<std::endl;
  std::cout<<"Resolution: "<<detector_resolution<<"%"<<std::endl;
  std::cout<<"Number of layers: "<<calorimeter_layers<<std::endl;
  std::cout<<"Materials: ";
  if(hadronic_calorimeter_materials.empty()) {std::cout<<"None";}
  else
  {
    for(const auto& material : hadronic_calorimeter_materials)
    {
      std::cout<<"\n- "<<material_descriptions(material);
    }
  }
  std::cout<<std::endl;
}