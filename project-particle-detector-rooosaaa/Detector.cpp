// Detector.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Implementation file for the Detector class, providing the core functionality
// for a high-energy particle detector simulation. The class manages multiple
// sub-detectors and performs physics analysis on detected particles.
//
// Key functionalities implemented:
// - Detection and identification of various particle types
// - Missing transverse energy (MET) calculation
// - Invariant mass calculations for particle systems
// - Support for different detector configurations (ATLAS and CMS)
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this
// program.

#include<iostream>
#include<iomanip>
#include<vector>

#include "Detector.h"
#include "Tracker.h"
#include "EMCalorimeter.h"
#include "HadronicCalorimeter.h"
#include "MuonSpectrometer.h"
#include "SubDetector.h"
#include "Particle.h"
#include "FourMomentum.h"
#include "DetectorConfig.h"

using namespace ParticleDetector;

// [RULE OF 5]

Detector::Detector()
{
  std::cout<<"Calling Detector default constructor."<<std::endl;
  // Set default detector name
  detector_name = "ATLAS";
  std::cout<<"Detector "<<detector_name<<" initialised."<<std::endl;
  // Add sub-detectors
  create_standard_detectors();
  detector_status = false;
}

Detector::Detector(const std::string& name)
{
  // Validate detector name
  set_detector_name(name);
  std::cout<<"Detector "<<detector_name<<" initialised."<<std::endl;
  // Add sub-detectors
  create_standard_detectors();
  detector_status = false;
}

Detector::~Detector()
{
  std::cout<<"Detector "<<detector_name<<" destroyed."<<std::endl;
}

bool Detector::validate_detector_name(const std::string& name)
{
  // Check if the detector name is valid - currently only "ATLAS" is supported
  if(name != "ATLAS" && name != "CMS") {return false;}
  return true;
}

// [SETTERS]

void Detector::set_detector_name(std::string name)
{
  // Validate before setting the name
  if(validate_detector_name(name)) {detector_name = name;}
  else {throw std::invalid_argument(
    "Invalid detector name. Must be 'ATLAS' or 'CMS'. Exiting program.");}
}

// Set the detector status (off or on)
void Detector::set_detector_status(bool status)
{
  if(status == true) {std::cout<<"Detector switched on."<<std::endl;}
  else if (status == false) {std::cout<<"Detector switched off."<<std::endl;}
  detector_status = status;
}

// [DETECTOR METHODS]

// Function to validate the sub-detector configuration:
// - Ensures the detector contains exactly four sub-detectors to aid in
//   particle detection and identification
// - Checks that one of each required type is present:
//   Tracker, EM Calorimeter, Hadronic Calorimeter, and Muon Spectrometer
// - Throws descriptive logic errors if the configuration is invalid
void Detector::validate_sub_detector_configuration() const
{
  // Check total number of sub-detectors; must be exactly 4
  if(sub_detectors.size() != 4) {throw std::logic_error(
    "Error: Detector must have exactly 4 sub-detectors.");}
  int tracker_count = 0;
  int em_cal_count = 0;
  int had_cal_count = 0;
  int muon_spec_count = 0;
  // Loop through all sub-detectors and count how many of each type we have
  for(const auto& subDetector : sub_detectors)
  {
    const std::string& type = subDetector->get_sub_detector_type();
    if(type == "Tracker") tracker_count++;
    else if(type == "EM Calorimeter") em_cal_count++;
    else if(type == "Hadronic Calorimeter") had_cal_count++;
    else if(type == "Muon Spectrometer") muon_spec_count++;
    else throw std::logic_error("Error: Unknown sub-detector type: " + type);
  }
  // Verify exactly one of each required sub-detector type
  if(tracker_count != 1) {throw std::logic_error(
    "Error: Detector must have exactly 1 Tracker. Found " +
      std::to_string(tracker_count));}
  if(em_cal_count != 1) {throw std::logic_error(
    "Error: Detector must have exactly 1 EM Calorimeter. Found " +
      std::to_string(em_cal_count));}
  if(had_cal_count != 1) {throw std::logic_error(
    "Error: Detector must have exactly 1 Hadronic Calorimeter. Found " +
      std::to_string(had_cal_count));}
  if(muon_spec_count != 1) {throw std::logic_error(
    "Error: Detector must have exactly 1 Muon Spectrometer. Found " +
      std::to_string(muon_spec_count));}
}

// Function to add the correct sub detectors to the detector
void Detector::create_standard_detectors()
{
  // Don't let the programmer add anymore sub-detectors if sub_detectors is not empty
  if(!sub_detectors.empty()) {throw std::logic_error(
    "Sub-detectors have already been added. Cannot add more. Exiting program.");}
  // Use the template-based configuration system in DetectorConfig.h
  if(detector_name == "ATLAS") {configure_detector<ATLASConfig>(sub_detectors);}
  else if(detector_name == "CMS") {configure_detector<CMSConfig>(sub_detectors);}
  // Validate the configuration
  validate_sub_detector_configuration();
  std::cout<<"Standard "<<detector_name<<" detector configured with all required sub-detectors.";
}

// Function to print the configuration of the detector
void Detector::print_configuration() const
{
std::cout<<"\n\n==================================\n";
std::cout<<"         Detector: "<<detector_name<<"   \n";
std::cout<<"==================================\n\n";
  std::cout<<"Number of sub-detectors: "<<sub_detectors.size()<<std::endl;
  
  for(const auto& subDetector : sub_detectors)
  {
    std::cout<<"\n";
    subDetector->print();
  }
  std::cout<<"=================================="<<std::endl;
}

// Function to detect a particle and return the energy measured by each sub-detector:
// - Throws an error if the detector is switched off or the particle has zero momentum
// - Simulates detection by passing the particle through a sequence of sub-detectors
// - Each sub-detector returns the amount of energy it measures
// - The particle's remaining energy is updated after each detection step
// - Returns a map associating each sub-detector's name with its recorded energy
std::map<std::string, double> Detector::detect_particle(const Particle& particle) const
{
  // Check if detector is active; throw error if not
  // Check that the particle has valid non-zero momentum; throw error if not
  if(detector_status == false) {throw std::invalid_argument(
    "Error: Detector is switched off. Cannot detect particles. Exiting program.");}
  else
  {
    if(particle.get_momentum().get_energy() <= 0 && particle.get_momentum().get_px() == 0 &&
      particle.get_momentum().get_py() == 0 &&  particle.get_momentum().get_pz() == 0)
      {throw std::invalid_argument("Error: Particle has no momentum. Cannot detect particle.");}
    // Initialise map to store energy readings per sub-detector
    // Using a map allows easy access to readings by sub-detector type
    std::map<std::string, double> readings;
    // Extract particle's total true energy
    double true_energy = particle.get_momentum().get_energy();

    // Loop through each sub-detector and simulate detection
    // - Call detect_particle on sub-detector with current energy
    // - Store detected energy in readings map, using sub-detector type as key
    // - Using a map for easy access to readings by sub-detector type
    // - Update the remaining energy if any energy was detected
    for(const auto& sub_detector : sub_detectors)
    {
      double detected_energy = sub_detector->detect_particle(particle, true_energy);
      readings[sub_detector->get_sub_detector_type()] = detected_energy;
      if(detected_energy != 0.0) {true_energy = detected_energy;} // Update remaining energy
    }
    // Return the full set of recorded detector readings
    std::cout<<"Particle has passed through the detector."<<std::endl;
    std::cout<<"Detector readings recorded."<<std::endl;
    return readings;
  }
}

// Function to identify a particle based on detector readings
std::string Detector::identify_particle(const std::map<std::string, double>& detector_readings)
{
  // Initialise boolean flags for each sub-detector
  // These flags will be set to true if the corresponding sub-detector has detected the particle
  bool detected_by_tracker = false;
  bool detected_by_em_calorimeter = false;
  bool detected_by_hadronic_calorimeter = false;
  bool detected_by_muon_spectrometer = false;

  // Iterate through the detector readings
  // Each entry contains the name of a sub-detector and the energy it recorded
  for(const auto& reading : detector_readings)
  {
    const std::string& type = reading.first; // Name of that sub-detector
    double energy = reading.second; // Energy recorded in that sub-detector
    // If energy > 0, the particle interacted with this sub-detector
    if(energy > 0)
    {
      // Set the flag based on the sub-detector name
      if(type == "Tracker") detected_by_tracker = true;
      else if(type == "EM Calorimeter") detected_by_em_calorimeter = true;
      else if(type == "Hadronic Calorimeter") detected_by_hadronic_calorimeter = true;
      else if(type == "Muon Spectrometer") detected_by_muon_spectrometer = true;
    }
  }

  // Encode the detection pattern using a 4-bit bitmask
  // Each bit corresponds to a sub-detector: 
  // For example, bitmask = 0b0011 means Tracker + EM Calorimeter were triggered
  int bitmask = 0;
  if(detected_by_tracker) {bitmask |= 1;}  // 0001
  if(detected_by_em_calorimeter) {bitmask |= 2;}  // 0010
  if(detected_by_hadronic_calorimeter) {bitmask |= 4;}  // 0100
  if(detected_by_muon_spectrometer) {bitmask |= 8;}  // 1000
  // Use the bitmask to identify the particle based on known interaction signatures
  switch (bitmask)
  {
    case 0b0010: return "Photon"; // EM Calorimeter only
    case 0b0011: return "Electron or Positron"; // Tracker + EM Calorimeter
    case 0b0101: return "Hadron"; // Tracker + Hadronic Calorimeter
    case 0b1001: return "Muon"; // Tracker + Muon Spectrometer
    case 0b0000: return "Nothing Detected (Possible Neutrino)"; // No sub-detector triggered
    default: return "Unknown"; // Any other pattern not explicitly handled
  }
}

// Function to return the detected energy as the final entry in detector readings
double Detector::get_detected_energy(const std::map<std::string, double>& readings) const
{
  // Iterate through the readings in reverse order (from last to first)
  // The assumption is that the last non-zero energy entry corresponds to the final detection
  for(auto it = readings.rbegin(); it != readings.rend(); ++it)
  {
    // Return the first non-zero energy found in reverse order
    if(it->second > 0.0) {return it->second;}
  }
  // If no non-zero readings are found, return 0 (i.e., no detection)
  return 0.0;
}

// Function to update the running totals to calculate MET
void Detector::update_totals_for_particle(const Particle& particle, double detected_energy,
  double& true_px, double& true_py, double& true_energy, double& detected_px, double& detected_py,
   double& detected_energy_sum) const
{
  // Extract the true four-momentum of the particle
  const auto& momentum = particle.get_momentum();
  // Accumulate the true momentum components and energy
  true_px += momentum.get_px();
  true_py += momentum.get_py();
  true_energy += momentum.get_energy();
  // Approximate the detected transverse momenta by scaling the true momenta
  // using the ratio of detected energy to true energy.
  // Assumes direction is preserved and only magnitude is reduced by detector response.
  if(momentum.get_energy() > 0)
  {
    double scale = detected_energy / momentum.get_energy();
    detected_px += momentum.get_px() * scale;
    detected_py += momentum.get_py() * scale;
  }
  // Add to the total detected energy sum
  detected_energy_sum += detected_energy;
}

// Function to print the results of the missing transverse energy (MET) calculation
void Detector::print_missing_energy_results(const std::string& event_name, double true_energy,
 double detected_energy, double true_met, double detected_met) const
{
  // Output a nicely formatted summary of the energy balance and MET
  std::cout<<"\n=== [Missing Energy Calculation for "<<event_name<<"] ===\n"<<std::endl;
  std::cout<<"True total energy: "<<true_energy<<" GeV"<<std::endl;
  std::cout<<"Detected total energy: "<<detected_energy<<" GeV"<<std::endl;
  std::cout<<"Invisible energy: "<<(true_energy - detected_energy)<<" GeV"<<std::endl;
  std::cout<<"True missing transverse energy (MET): "<<true_met<<" GeV"<<std::endl;
  std::cout<<"Detected missing transverse energy (MET): "<<detected_met<<" GeV\n"<<std::endl;
  // Print a warning if the detected MET is larger than the true MET
  // This may happen due to random detector effects or mis-measured momenta
  if(detected_met > true_met)
  {
    std::cout<<"Warning: Detected MET is greater than true MET."
    " Please check if your momentum values are entered correctly.\n"<<std::endl;
  }
  // Print another warning if MET is abnormally large (using 10 GeV as a threshold)
  // This could suggest missing particles (like neutrinos) or mistakes in input
  else if(detected_met > 10)
  {
    std::cout<<"Detected MET is > 10 GeV."<<std::endl;
    std::cout<<"Please check if your momentum values are entered correctly and if"
    " neutrinos are expected reaction products.\n"<<std::endl;
  }
}

// Function to calculate missing transverse energy
void Detector::calculate_missing_energy(const std::vector<std::unique_ptr<Particle>>& particles,
  const std::vector<std::map<std::string, double>>& all_readings, const std::string& event_name)
{
  // Ensure each particle has a corresponding set of detector readings
  if(particles.size() != all_readings.size()) {throw std::invalid_argument(
    "Mismatch between particles and readings in calculate_missing_energy.");}
  // Initialise running totals for true and detected quantities
  double true_total_px = 0.0, true_total_py = 0.0, true_total_energy = 0.0;
  double detected_total_px = 0.0, detected_total_py = 0.0, detected_total_energy = 0.0;
  // Loop over each particle and update the totals using its corresponding detector readings
  for(size_t i = 0; i < particles.size(); ++i)
  {
    const auto& particle = particles[i];
    // Get the detected energy from the sub-detectors for this particle
    double detected_energy = get_detected_energy(all_readings[i]);
    // Update totals for MET calculation
    update_totals_for_particle(*particle, detected_energy, true_total_px, true_total_py, true_total_energy,
      detected_total_px, detected_total_py, detected_total_energy);
  }
  // Calculate missing transverse energy as the magnitude of the transverse momentum vector
  double true_met = std::sqrt(true_total_px * true_total_px + true_total_py * true_total_py);
  double detected_met = std::sqrt(detected_total_px * detected_total_px + detected_total_py * detected_total_py);
  // Print the final results for this event
  print_missing_energy_results(event_name, true_total_energy, detected_total_energy, true_met, detected_met);
}

// Function to print the detection results for a given particle:
// - Prints the true particle properties and momentum characteristics
// - Displays detector energy readings in a specific order
// - Computes and prints total detected energy
// - Shows which particle the system identified this as
void Detector::print_detection_results(const Particle& particle, const std::map<std::string, double>& readings,
  const std::string& identified_as) const
{
  double true_energy = particle.get_momentum().get_energy();
  double detected_energy = 0.0;
  const auto& momentum = particle.get_momentum();
  // Set precision to 2 d.p.
  std::cout<<std::fixed<<std::setprecision(2);
  std::cout<<"-------------------------------------------------------------------"<<std::endl;
  std::cout<<"True particle information: "<<std::endl;
  particle.print();
  std::cout<<"\nTrue particle momentum details:"<<std::endl;
  std::cout<<"  - Transverse momentum (pT): "<<momentum.calculate_transverse_momentum()<<" GeV"<<std::endl;
  std::cout<<"  - Invariant mass: "<<momentum.calculate_invariant_mass()<<" GeV"<<std::endl;
  std::cout<<"  - Total momentum magnitude: "<<momentum.calculate_momentum_magnitude()<<" GeV"<<std::endl;
  std::cout<<"  - Pseudorapidity: "<<momentum.calculate_pseudorapidity()<<std::endl;

  std::cout<<"\nDetector energy readings:"<<std::endl;
  // Iterate through detector subsystems in order and print each energy reading, if available
  const std::vector<std::string> order = {"Tracker", "EM Calorimeter", "Hadronic Calorimeter", "Muon Spectrometer"};
  for(const auto& key : order)
  {
    if(readings.count(key))
    {
      std::cout<<"  - "<<key<<": "<<readings.at(key)<<" GeV"<<std::endl;
      detected_energy += readings.at(key);
    }
  }
  // Output the particle type this was classified as, based on detection signatures
  std::cout<<"Identified as: "<<identified_as<<std::endl;
}

// Function to calculate the invariant mass of a system of particles:
// - Requires at least two particles to be meaningful
// - Extracts FourMomentum objects from the given particle list
// - Computes and prints the invariant mass of the full system
// - Matches the result to known particle masses for Higgs, Z, and top quark decays
void Detector::calculate_invariant_mass(const std::vector<std::unique_ptr<Particle>>& particles,
  const std::string& event_name) const
{
  // Ensure at least two particles are in the vector
  if(particles.size() < 2) {throw std::invalid_argument(
    "Need at least two particles to calculate invariant mass. Exiting program.");}
  // Extract momenta from each particle to build the system
  std::vector<ParticleProperties::FourMomentum> momenta;
  for(const auto& particle : particles)
  {
    momenta.push_back(particle->get_momentum());
  }
  // Calculate system invariant mass using FourMomentum static method
  double invariant_mass = ParticleProperties::FourMomentum::calculate_system_invariant_mass(momenta);
  // Output results, and provide interpretation if consistent with known particles
  std::cout<<"\n=== [Invariant Mass Calculation for " << event_name << "] ==="<<std::endl;
  std::cout<<"Invariant mass of the system: " << invariant_mass << " GeV"<<std::endl;
  
  // Display additional information for known particles
  if(event_name == "Higgs Decay" && std::abs(invariant_mass - 125.0) < 10.0) {std::cout<<
    "This is consistent with the Higgs boson mass (~125 GeV)."<<std::endl;}
  else if(event_name == "Z Boson Decay" && std::abs(invariant_mass - 91.2) < 5.0) {std::cout<<
    "This is consistent with the Z boson mass (~91.2 GeV)."<<std::endl;}
  else if(event_name == "Anti-Top Quark Decay" && std::abs(invariant_mass - 173.0) < 10.0) {std::cout<<
    "This is consistent with the top quark mass (~173 GeV)."<<std::endl;}
}

