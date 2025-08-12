// MuonSpectrometer.h
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Date: 11-05-2025
//
// Header file for the MuonSpectrometer class, a specialised sub-detector designed
// to model the outermost detection layers in a particle detector. The muon spectrometer
// identifies muons and measures their momenta.
//
// This class handles:
// - Storage and validation of muon chamber types
// - Configuration of energy loss and resolution parameters
// - Readout and display of detector properties
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#ifndef MUON_SPECTROMETER_H
#define MUON_SPECTROMETER_H

#include<random>
#include<list>

#include "SubDetector.h"

namespace DetectorSubsystems
{
  class MuonSpectrometer : public SubDetector
  {
  private:
    // Stores chamber types (e.g. "MDT", "CSC")
    std::list<std::string> chamber_types;
    // Returns a string description of the given chamber type
    static std::string chamber_descriptions(const std::string& chamber);
    // Any additional properties of the Muon Spectrometer can be added here
      
  public:
    // [RULE OF 5]
    // Default constructor - resolution is set to 0 and energy loss to 1 (perfect Muon Spectrometer)
    MuonSpectrometer();
    // Parameterised onstructor
    MuonSpectrometer(int resolution, double energy_loss, std::list<std::string> chambers);
    // Prevent copying and moving of trackers:
    // Physically, detectors are not copied or transferred;
    // Logically, prevents mishandling of internal state like RNG or identification
    // Copy constructor
    MuonSpectrometer(const MuonSpectrometer& other) = delete;
    // Move constructor
    MuonSpectrometer(MuonSpectrometer&& other) = delete;
    // Copy assignment operator
    MuonSpectrometer& operator=(const MuonSpectrometer& other) = delete;
    // Move assignment operator
    MuonSpectrometer& operator=(MuonSpectrometer&& other) = delete;
    // Destructor
    ~MuonSpectrometer();
    
    // [GETTERS]
    std::list<std::string> get_chamber_types() const {return chamber_types;}
    // [SETTERS]
    void set_sub_detector_name(const std::string& name) override;
    void set_chamber_types(std::list<std::string> chambers);

    // [METHODS]
    void print() const override;
  };
} // namespace DetectorSubsystems

#endif // MUON_SPECTROMETER_H