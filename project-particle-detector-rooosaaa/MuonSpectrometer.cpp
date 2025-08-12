// MuonSpectrometer.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// Implementation file for the MuonSpectrometer class. This component models the
// outermost layer of a high-energy physics detector system, focusing on identifying
// and measuring the momentum of muons.
//
// This class handles:
// - Construction and configuration of muon chamber types
// - Validation of input chamber specifications
// - Print functionality for detector diagnostics
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<iostream>
#include<set>
#include<map>

#include "MuonSpectrometer.h"

using namespace DetectorSubsystems;

// [RULE OF 5]

// Default constructor: perfect resolution and no energy loss
MuonSpectrometer::MuonSpectrometer() : SubDetector("Muon Spectrometer", 0, 1)
{
  std::cout<<"Calling MuonSpectrometer parametrised constructor."<<std::endl;
  std::list<std::string> chambers = {"MDT", "RPC", "TGC", "CSC"};
  set_chamber_types(chambers);
}

MuonSpectrometer::MuonSpectrometer(int resolution, double energy_loss, std::list<std::string> chambers)
  : SubDetector("Muon Spectrometer", resolution, energy_loss)
{
  // Base constructor handles random seeding and resolution validation
  set_chamber_types(chambers);
}

MuonSpectrometer::~MuonSpectrometer()
{
  std::cout<<"Calling MuonSpectrometer destructor."<<std::endl;
}

// [SETTERS]

void MuonSpectrometer::set_sub_detector_name(const std::string& name)
{
  if(name == "Muon Spectrometer") {sub_detector_type = name;}
  else {throw std::invalid_argument("Invalid sub-detector type. Must be 'Muon Spectrometer'.");}
}

void MuonSpectrometer::set_chamber_types(std::list<std::string> chambers)
{
  // Set types allowed using std::set for fast lookup
  static const std::set<std::string> valid_types = {"MDT", "RPC", "TGC", "CSC", "sTGC", "MM"};
  for(const auto& type : chambers)
  {
    if(valid_types.find(type) == valid_types.end()) {throw std::invalid_argument(
      "Invalid chamber type. Valid types are 'MDT', 'RPC', 'TGC', 'CSC', 'sTGC' & 'MM'.");}
  }
  chamber_types = chambers;
}

// [METHODS]

// Returns a full textual description of a chamber type
std::string MuonSpectrometer::chamber_descriptions(const std::string& chamber)
{
  // Using a map for fast lookup of chamber descriptions
  static const std::map<std::string, std::string> chamber_descriptions =
  {
    {"MDT", "Monitored Drift Tubes (MDT)"},
    {"RPC", "Resistive Plate Chambers (RPC)"},
    {"TGC", "Thin Gap Chambers (TGC)"},
    {"CSC", "Cathode Strip Chambers (CSC)"},
    {"sTGC", "Small Thin Gap Chambers (sTGC)"},
    {"MM", "MicroMegas (MM)"}
  };

  auto it = chamber_descriptions.find(chamber);
  // Return full description or just the chamber type if not found
  return (it != chamber_descriptions.end()) ? it->second : chamber;
}

// Prints the properties of the Muon Spectrometer
void MuonSpectrometer::print() const
{
  std::cout<<"Sub-Detector: "<<sub_detector_type<<std::endl;
  std::cout<<"Resolution: "<<detector_resolution<<"%"<<std::endl;
  // Mapping of chamber types to full descriptions
  std::cout<<"Chamber Types: ";
  if(chamber_types.empty()) {std::cout<<"None";}
  else 
  {
    for(const auto& chamber : chamber_types)
    {
      std::cout<<"\n- "<<chamber_descriptions(chamber);
    }
  }
  std::cout<<std::endl;
}
