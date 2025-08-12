// EMCalorimeter.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Header file for the EMCalorimeter class, which inherits from the Calorimeter class.
// The EMCalorimeter class models the Electromagnetic Calorimeter detector, providing:
// - Functionality for handling materials used in the calorimeter
// - Managing the number of layers in the detector
// - Methods for printing and accessing calorimeter information
// - Getter and setter methods for materials and layers
// - A method for printing calorimeter information
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef EM_CALORIMETER_H
#define EM_CALORIMETER_H

#include<iostream>
#include<string>
#include<list>

#include "Calorimeter.h"

namespace DetectorSubsystems
{
  class EMCalorimeter : public Calorimeter
  {
  private:
    // Material of the EM Calorimeter
    std::list<std::string> em_calorimeter_materials;
    // Helper function to get material descriptions
    static std::string material_descriptions(const std::string& material);
    // Any additional properties of the EM Calorimeter can be added here
  
  public:
    // [RULE OF 5]
    // Default constructor - resolution is set to 0 and energy loss to 1 (perfect Tracker)
    EMCalorimeter();
    // Parameterised constructor
    EMCalorimeter(int resolution, double energy_loss, int layers, std::list<std::string> materials);
    // Prevent copying and moving of trackers:
    // Physically, detectors are not copied or transferred;
    // Logically, prevents mishandling of internal state like RNG or identification
    // Copy constructor
    EMCalorimeter(const EMCalorimeter& other) = delete;
    // Move constructor
    EMCalorimeter(EMCalorimeter&& other) = delete;
    // Copy assignment operator
    EMCalorimeter& operator=(const EMCalorimeter& other) = delete;
    // Move assignment operator
    EMCalorimeter& operator=(EMCalorimeter&& other) = delete;
    // Destructor
    ~EMCalorimeter();

    // [GETTERS]
    std::list<std::string> get_em_cal_materials() const {return em_calorimeter_materials;}

    // [SETTERS]
    void set_sub_detector_name(const std::string& name) override; 
    void set_em_cal_materials(std::list<std::string> materials);
    
    // [METHODS]
    // Print EM Calorimeter information
    void print() const override;
  };
} // namespace DetectorSubsystems

#endif // EM_CALORIMETER_H