// DetectorConfig.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Header file for defining detector configurations in the particle detector project.
// This file includes the declaration of configuration classes for different detector systems
// (e.g., ATLAS, CMS) and provides functionality to add sub-detectors to a detector configuration.
// It also contains a template function to configure detectors with varying setups.
//
// This class structure is useful because it allows for modular configuration of various
// detector systems.
// By using template functions and inheritance, the user can easily extend and modify
// detector setups for different configurations, without affecting other parts of the system.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef DETECTOR_CONFIG_H
#define DETECTOR_CONFIG_H

#include<vector>
#include<memory>
#include<string>
#include<list>

#include "SubDetector.h"
#include "Tracker.h"
#include "EMCalorimeter.h"
#include "HadronicCalorimeter.h"
#include "MuonSpectrometer.h"

namespace ParticleDetector
{
  // Template function to add a sub-detector of any type to the sub_detectors vector
  template<typename T, typename... Args>
  void add_sub_detector(std::vector<std::unique_ptr<DetectorSubsystems::SubDetector>>& sub_detectors,
    Args&&... args)
  {
    // Creates a unique pointer to a sub-detector and adds it to the sub_detectors vector
    sub_detectors.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
  }

  // Base configuration class for the detector
  // This class provides a static method for configuring sub-detectors, which can be overridden in derived classes.
  struct DetectorConfig
  {
    static void configure(std::vector<std::unique_ptr<DetectorSubsystems::SubDetector>>& sub_detectors) {}
  };

  // ATLAS-specific configuration class
  // This class overrides the configure method to set up the ATLAS detector configuration
  struct ATLASConfig : DetectorConfig
  {
    static void configure(std::vector<std::unique_ptr<DetectorSubsystems::SubDetector>>& sub_detectors);
  };

  // CMS-specific configuration class
  // This class overrides the configure method to set up the CMS detector configuration
  struct CMSConfig : DetectorConfig
  {
    static void configure(std::vector<std::unique_ptr<DetectorSubsystems::SubDetector>>& sub_detectors);
  };

  // Template function to configure a detector using a specific configuration class
  // This function forwards the configuration process to the provided DetectorConfig class.
  template<typename DetectorConfig>
  void configure_detector(std::vector<std::unique_ptr<DetectorSubsystems::SubDetector>>& sub_detectors)
  {
    DetectorConfig::configure(sub_detectors);
  }
} // namespace ParticleDetector

#endif // DETECTOR_CONFIG_H