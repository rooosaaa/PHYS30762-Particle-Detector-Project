// DetectorConfig.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Implementation file for configuring particle detector systems.
// This file contains the implementations of the configuration methods for specific detector systems 
// (e.g., ATLAS and CMS) that define the sub-detectors and their properties. The configurations 
// include the setup of tracker, calorimeter, and muon spectrometer subsystems.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include "DetectorConfig.h"

namespace ParticleDetector
{
  // Configuration for the ATLAS detector system
  // This method sets up the sub-detectors specific to the ATLAS detector
  void ATLASConfig::configure(std::vector<std::unique_ptr<DetectorSubsystems::SubDetector>>& sub_detectors)
  {
    add_sub_detector<DetectorSubsystems::Tracker>(sub_detectors, 2, 0.97, "Silicon", 3);
    // Using std::list to allow for easy addition of materials
    std::list<std::string> em_materials = {"LAr", "W", "Pb"};
    add_sub_detector<DetectorSubsystems::EMCalorimeter>(sub_detectors, 2, 0.95, 3, em_materials);
    
    std::list<std::string> hadronic_materials = {"Steel", "PST"};
    add_sub_detector<DetectorSubsystems::HadronicCalorimeter>(sub_detectors, 5, 0.80, 3, hadronic_materials);
    
    std::list<std::string> chambers = {"MDT", "RPC", "TGC", "CSC"};
    add_sub_detector<DetectorSubsystems::MuonSpectrometer>(sub_detectors, 9, 0.95, chambers);
  }

  // Configuration for the CMS detector system
  // This method sets up the sub-detectors specific to the CMS detector
  void CMSConfig::configure(std::vector<std::unique_ptr<DetectorSubsystems::SubDetector>>& sub_detectors)
  {
    add_sub_detector<DetectorSubsystems::Tracker>(sub_detectors, 2, 0.98, "Silicon", 4);
    
    std::list<std::string> em_materials = {"PbWO4"};
    add_sub_detector<DetectorSubsystems::EMCalorimeter>(sub_detectors, 3, 0.96, 4, em_materials);
    
    std::list<std::string> hadronic_materials = {"Brass", "PST"};
    add_sub_detector<DetectorSubsystems::HadronicCalorimeter>(sub_detectors, 6, 0.85, 4, hadronic_materials);
    
    std::list<std::string> chambers = {"MDT", "CSC", "RPC"};
    add_sub_detector<DetectorSubsystems::MuonSpectrometer>(sub_detectors, 10, 0.96, chambers);
  }
} // namespace ParticleDetector