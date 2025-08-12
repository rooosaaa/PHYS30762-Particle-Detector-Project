// project_particle_detector.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// Main program file for the Particle Detector simulation project.
// This project simulates a high-energy particle detector similar to ATLAS or CMS
// at the Large Hadron Collider, tracking how different particles interact with 
// various detector components.
//
// The simulation demonstrates:
// - Detection of different particle types (electrons, photons, muons, hadrons, neutrinos)
// - Physics event simulations (Higgs decay, Z boson decay, top quark decay)
// - Measurement of key physics quantities (invariant mass, missing transverse energy)
// - Simulated detector response and particle identification algorithm
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>
#include<vector>

#include "FourMomentum.h"
#include "Particle.h"
#include "Electron.h"
#include "Neutrino.h"
#include "Photon.h"
#include "Muon.h"
#include "Hadron.h"
#include "Positron.h"

#include "SubDetector.h"
#include "Tracker.h"
#include "Calorimeter.h"
#include "EMCalorimeter.h"
#include "HadronicCalorimeter.h"
#include "MuonSpectrometer.h"
#include "Detector.h"

#include "DetectorConfig.h"

// Using namespaces to keep things modular and avoid name clashes
using namespace ParticleDetector;
using ParticleSystem::Particle;
using ParticleDetector::Detector;

// Function to simulate the decay of a Higgs boson to two photons (H → γγ)
std::vector<std::unique_ptr<Particle>> simulate_higgs_decay()
{
  std::cout<<"\n\n=== [ Simulating Higgs decay to diphoton ] ==="<<std::endl;
  std::cout<<"Theoretical Higgs boson mass: ~125 GeV\n"<<std::endl;
  std::vector<std::unique_ptr<Particle>> particles;
  // Two back-to-back photons with given momenta
  particles.emplace_back(std::make_unique<Photon>(1, FourMomentum(30.0, 25.0, 0.0, 60.0)));
  particles.emplace_back(std::make_unique<Photon>(2, FourMomentum(-25.0, -28.0, 0.0, 65.0)));
  return particles;
}

// Function to simulate the decay of a Z boson to an electron-positron pair
std::vector<std::unique_ptr<Particle>> simulate_z_decay()
{
  std::cout<<"\n=== [ Simulating Z boson decay to electron-positron pair ] ==="<<std::endl;
  std::cout<<"Theoretical Z boson mass: ~91.2 GeV\n"<<std::endl;
  std::vector<std::unique_ptr<Particle>> particles;
  particles.emplace_back(std::make_unique<Electron>(1, FourMomentum(20.0, 30.0, 10.0, 45.0)));
  particles.emplace_back(std::make_unique<Positron>(1, FourMomentum(-15.0, -25.0, -5.0, 35.0)));
  return particles;
}

// Function to simulate the decay of a anti-top quark via a W boson into a muon and neutrino
std::vector<std::unique_ptr<Particle>> simulate_top_decay()
{
  std::cout<<"\n=== [ Simulating anti-top quark decay to a b-quark, muon and an anti-neutrino ] ==="
    <<std::endl;
  std::cout<<"Theoretical top quark mass: ~173 GeV\n"<<std::endl;
  std::vector<std::unique_ptr<Particle>> particles;
  // Simulating the b quark from the top decay
  particles.emplace_back(std::make_unique<Hadron>(1, FourMomentum(40.0, 10.0, 30.0, 80.0), "b_quark", -1.0/3));
  // Muon from W boson decay
  particles.emplace_back(std::make_unique<Muon>(1, FourMomentum(15.0, 25.0, 10.0, 40.0)));
  // Muon anti-neutrino
  particles.emplace_back(std::make_unique<Neutrino>(1, FourMomentum(5.0, 15.0, 20.0, 45.0)));
  return particles;
}

// Function that takes a set of particles and processes them through the detector,
// collecting and printing the detector readings, and computing derived physics quantities.
void process_physics_event(Detector& detector, const std::string& event_name,
  std::vector<std::unique_ptr<Particle>>& particles)
{
  std::cout<<"\n===================================================================="<<std::endl;
  std::cout<<"\n============= [Detection Results for "<<event_name<<"] ============="<<std::endl;
  std::cout<<"\n===================================================================="<<std::endl;
  std::vector<std::map<std::string, double>> readings;
  // Loop through all particles in the event
  for(const auto& particle : particles)
  {
    std::cout<<"\n";
    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    std::cout<<"\n";
    detector.set_detector_status(true); // Turn the detector "on"
    auto reading = detector.detect_particle(*particle); // Collect simulated readings
    readings.push_back(reading);
    detector.set_detector_status(false); // Turn the detector "off"
    std::cout<<"\n";
    // Identify particle based on the detector response
    std::string identified = detector.identify_particle(reading);
    // Print a summary of the detection and identification results
    detector.print_detection_results(*particle, reading, identified);
  }
  // Compute and print event-level physics metrics
  std::cout<<"\n===================================================================="<<std::endl;
  detector.calculate_invariant_mass(particles, event_name);
  detector.calculate_missing_energy(particles, readings, event_name);
}

// Function that runs a full simulation for Higgs, Z, and top quark events
void run_complex_simulation()
{
  std::cout<<"\n=== Running complex simulation with multiple particles ===\n"<<std::endl;
  // Create a detector
  Detector detector("ATLAS");
  detector.print_configuration(); // Print setup
  // Generate particle collections for each event type
  auto higgs_decay_particles = simulate_higgs_decay();
  auto z_decay_particles = simulate_z_decay();
  auto top_decay_particles = simulate_top_decay();
  // Process each event in turn
  process_physics_event(detector, "Higgs Decay", higgs_decay_particles);
  process_physics_event(detector, "Z Boson Decay", z_decay_particles);
  process_physics_event(detector, "Top Quark Decay", top_decay_particles);
  std::cout<<"\n===================================================================="<<std::endl;
}

// Main function
int main()
{
  std::cout<<"\n=================================================="<<std::endl;
  std::cout<<"PHYS30762 - Project: Particle Detector Simulation"<<std::endl;
  std::cout<<"==================================================\n"<<std::endl;
  try
  {
    // Start simulation of particle decays and their interactions with the detector
    run_complex_simulation();
  }
  catch (const std::exception& e)
  {
    // Catch and display any runtime errors
    std::cerr<<"Error: "<<e.what()<<std::endl;
    return -1;
  }
  std::cout<<"\n=================================================="<<std::endl;
  std::cout<<"========= Simulation Complete - Goodbye! ========="<<std::endl;
  std::cout<<"==================================================\n"<<std::endl;
  std::cout<<R"(
         o/
        /|
        / \    < Bye!
  )"<<std::endl;
  return 0;
}