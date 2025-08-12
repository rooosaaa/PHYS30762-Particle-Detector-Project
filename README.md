# PHYS30762 - Particle Detector Simulation
## Author
Rosa Roberts (Student ID: 11016395)

## Date
12.08.2025

## Code Archive
This codebase is archived on Zenodo:
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.16813735.svg)](https://doi.org/10.5281/zenodo.16813735)

## Overview

This project simulates a high-energy particle detector system similar to those used in particle physics experiments like ATLAS or CMS at the Large Hadron Collider (LHC). It demonstrates object-oriented programming principles in C++ by modelling how different particles interact with various detector components.

## Features:

- **Particle Types**: Simulates various elementary particles (electrons, positrons, photons, muons, hadrons, neutrinos)
- **Detector Components**: Models different sub-detector systems (tracker, electromagnetic calorimeter, hadronic calorimeter, muon spectrometer)
- **Physics Processes**: Simulates particle decay scenarios including:
  - Higgs boson decay to diphoton
  - Z boson decay to electron-positron pair
  - Anti-top quark decay
- **Physics Measurements**:
  - Four-momentum calculations
  - Invariant mass for a system of particles
  - Missing transverse energy (MET) calculation
- **Additional Features**:
  - Detector resolution simulation using a random number generator (RNG)
  - Energy loss modelling in each sub detector
  - Particle identification based on detector signatures
  - Static data and functions
  - Template function to configure detectors with varying setups.
  - Exceptions to catch user error
  - Exploration of the standard library (maps, list, set, random_device & limits)
  - Namespaces for modularity and to avoid future name clashes
  - Lambda function for validating hadron charge 

## Project Structure

### Particle Class Hierarchy
- `Particle` (abstract base class)
  - `Electron`
  - `Positron`
  - `Muon`
  - `Photon`
  - `Hadron`
  - `Neutrino`

### Detector Class Hierarchy
- `SubDetector` (abstract base class)
  - `Tracker`
  - `EMCalorimeter`
  - `HadronicCalorimeter`
  - `MuonSpectrometer`
- `Detector` (container for sub-detectors)
  - Detection methods for ATLAS and CMS detector configurations

### Support Classes
- `FourMomentum` (handling of particle kinematics)
- `DetectorConfig` (configuration for ATLAS/CMS detector setups)

## Compilation and Execution

This program consists of multiple files that need to be compiled together.

### Method 1: Compile manually with g++-11
- To compile all files together:
```bash
g++-11 -std=gnu++17 project_particle_detector.cpp FourMomentum.cpp Particle.cpp Electron.cpp Neutrino.cpp Photon.cpp Muon.cpp Hadron.cpp Positron.cpp SubDetector.cpp Tracker.cpp Calorimeter.cpp EMCalorimeter.cpp HadronicCalorimeter.cpp MuonSpectrometer.cpp Detector.cpp DetectorConfig.cpp -o project_particle_detector.o
```
- To run the compiled program:
```bash
./project_particle_detector.o
```
### Method 2: Using a Makefile
The Makefile should contain the following:
```bash
CXX = g++
CXXFLAGS = -std=gnu++17

all: project_particle_detector.out

project_particle_detector.out: 

project_particle_detector.out: project_particle_detector.o FourMomentum.o Particle.o Electron.o Neutrino.o Photon.o Muon.o Hadron.o Positron.o SubDetector.o Tracker.o Calorimeter.o EMCalorimeter.o HadronicCalorimeter.o MuonSpectrometer.o Detector.o DetectorConfig.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o project_particle_detector.out
```
- Then compile by typing:
```bash
make
```
- To clean up compiled files:
```bash
make clean
```

## Simulation Output

The program will output:

1. **Detector Configuration**: Details of the configured detector (ATLAS by default)
2. **Physics Event Simulations**:
   - Higgs boson decay to two photons
   - Z boson decay to electron-positron pair
   - Top quark decay to b quark, muon, and neutrino
3. **Detection Results**:
   - Raw detector readings for each particle
   - Identified particle types based on detector signatures
   - Invariant mass calculations for each event
   - Missing transverse energy (MET) measurements

## Ideas for Future Enhancements

- Add more complex decay chains and particle types
- Add support for custom detector configurations
- Add more sub-sub-detectors for higher level particle identification (e.g. muon chamber hits)

## Acknowledgments

This project was inspired by my recent lab work, ‘Analysing Events with the Z Boson with the ATLAS Experiment’. The calculations implemented through the FourMomentum class reflect the quantities I worked with during that experiment. The simulated decay processes featured in this project were selected based on the interactions I studied as part of the lab.

## References

- ATLAS Detector: https://atlas.cern/
- CMS Detector: https://cms.cern/
- Particle Data Group: https://pdg.lbl.gov/
- Instructions for how to create Make files were found [here](https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html)
- References for exploration of the standard library were found [here](https://en.cppreference.com/w/cpp/numeric/random/random_device)
