// Detector.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// Header file for the Detector class that represents a high-energy particle detector
// similar to those used at the Large Hadron Collider. Provides functionality for
// particle detection, identification, and physics measurements.
//
// This class handles:
// - Management of multiple sub-detectors (tracker, calorimeters, muon spectrometer)
// - Particle detection and identification based on detector signatures
// - Physics analysis including missing energy and invariant mass calculations
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef DETECTOR_H
#define DETECTOR_H

#include<vector>
#include<memory>
#include<string>
#include<map>

#include "SubDetector.h"
#include "Particle.h"

using namespace DetectorSubsystems;
using namespace ParticleSystem;

namespace ParticleDetector
{
  class Detector
  {
  private:
    std::string detector_name; // ATLAS or CMS
    // The allowed sub_detectors are that of standard ATLAS
    std::vector<std::unique_ptr<SubDetector>> sub_detectors; // Vector of sub-detectors e.g. Calorimeter, Tracker, etc.
    // Function to validate detector name
    static bool validate_detector_name(const std::string& name);
    bool detector_status; // true if on, false if off

    // Get the detected energy of the particle as the final entry in detector readings
    // for MET calculation
    double get_detected_energy(const std::map<std::string, double>& readings) const;
    // Function to update the total energy of an interaction for calculating MET
    void update_totals_for_particle(const Particle& particle, double detected_energy, double& true_px,
     double& true_py, double& true_energy, double& detected_px, double& detected_py,
      double& detected_energy_sum) const;
    // Function to print the results of missing energy
    void print_missing_energy_results(const std::string& event_name, double true_energy,
     double detected_energy, double true_met, double detected_met) const;
    // Calculate missing transverse energy
      
  public:
    // [RULE OF 5]
    // Default constructor
    Detector();
    // Parameterised constructor
    Detector(const std::string& name);
    // Not allowing copy or move operations as it prevents ownership issues with the sub-detector pointers
    // Copy constructor
    Detector(const Detector& other) = delete;
    // Move constructor
    Detector(Detector&& other) = delete;
    // Copy assignment operator
    Detector& operator=(const Detector& other) = delete;
    // Move assignment operator
    Detector& operator=(Detector&& other) = delete;
    // Destructor
    ~Detector();
    
    // [GETTERS]
    std::string get_detector_name() const {return detector_name;}
    const std::vector<std::unique_ptr<SubDetector>>& get_subdetectors() const {return sub_detectors;}
    bool get_detector_status() const {return detector_status;}

    // [SETTERS]
    // Set the name of the detector - currently only 'ALTAS' or 'CMS' are allowed
    void set_detector_name(std::string name);
    // Set the detector as either off or on.
    void set_detector_status(bool status);

    // [DETECTOR METHODS]
    // Function to add sub-detectors to the detector - only certain sub-detectors are allowed.
    void create_standard_detectors();
    // Validate that exactly one of each required sub-detector type exists.
    void validate_sub_detector_configuration() const;
    // Print the detector configuration.
    void print_configuration() const;
    // Detect a particle and return the energy measured by each sub-detector.
    std::map<std::string, double> detect_particle(const Particle& particle) const;
    // Identify a particle based on detector readings.
    static std::string identify_particle(const std::map<std::string, double>& detector_readings);
    // Function to calculate the missing transverse energy (MET) for a system of particles.
    void calculate_missing_energy(const std::vector<std::unique_ptr<Particle>>& particles,
      const std::vector<std::map<std::string, double>>& all_readings, const std::string& event_name);
    // Print detection results.
    void print_detection_results(const Particle& particle, const std::map<std::string, double>& readings,
      const std::string& identified_as) const;
    // Function to calculate the invariant mass of a system of particles.
    void calculate_invariant_mass(const std::vector<std::unique_ptr<Particle>>& particles,
      const std::string& event_name) const;
  };
} // namespace ParticleDetector

#endif // DETECTOR_H
