// HadronicCalorimeter.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Header file for the HadronicCalorimeter class, which represents a specific
// type of calorimeter used for detecting hadrons. This class inherits from the
// Calorimeter base class and provides functionality for handling materials,
// layers, and physics measurements related to the hadronic calorimeter.
//
// This class includes:
// - Management of materials used in the calorimeter
// - The number of layers in the barrel section
// - Methods to set and retrieve materials and layer information
// - A method to print the details of the calorimeter
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef HADRONIC_CALORIMETER_H
#define HADRONIC_CALORIMETER_H

#include<iostream>
#include<string>
#include<list>

#include "Calorimeter.h"

namespace DetectorSubsystems
{
  class HadronicCalorimeter : public Calorimeter
  {
  private:
    // Material of the Hadronic Calorimeter
    std::list<std::string> hadronic_calorimeter_materials;
    // Helper function to get material descriptions
    static std::string material_descriptions(const std::string& material);
    // Any additional properties of the HadronicCalorimeter can be added here
  
  public:
    // [RULE OF 5]
    // Default constructor - resolution is set to 0 and energy loss to 1 (perfect Tracker)
    HadronicCalorimeter();
    // Parameterised constructor
    HadronicCalorimeter(int resolution, double energy_loss, int layers, std::list<std::string> materials);
    // Prevent copying and moving of trackers:
    // Physically, detectors are not copied or transferred;
    // Logically, prevents mishandling of internal state like RNG or identification
    // Copy constructor
    HadronicCalorimeter(const HadronicCalorimeter& other) = delete;
    // Move constructor
    HadronicCalorimeter(HadronicCalorimeter&& other) = delete;
    // Copy assignment operator
    HadronicCalorimeter& operator=(const HadronicCalorimeter& other) = delete;
    // Move assignment operator
    HadronicCalorimeter& operator=(HadronicCalorimeter&& other) = delete;
    // Destructor
    ~HadronicCalorimeter();

    // [GETTERS]
    std::list<std::string> get_hadronic_cal_materials() const {return hadronic_calorimeter_materials;}

    // [SETTERS]
    void set_sub_detector_name(const std::string& name) override;
    void set_hadronic_cal_materials(std::list<std::string> materials); 
    
    // [METHODS]
    // Print Hadronic Calorimeter information
    void print() const override;
  };
} // namespace DetectorSubsystems

#endif // HADRONIC_CALORIMETER_H