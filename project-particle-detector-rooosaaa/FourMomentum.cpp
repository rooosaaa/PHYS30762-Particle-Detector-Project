// FourMomentum.cpp
// PHYS30762 - Project: Particle Detector
// Author: Rosa Roberts
// Student ID: 11016395
// Date: 11-05-2025
//
// Implementation file for the FourMomentum class that represents a relativistic four-momentum
// vector (px, py, pz, E) used in particle physics.
//
// This implementation includes:
// - Memory management (constructors, destructors, and assignment operators)
// - Component setters with validation for physical constraints
// - Enforcement of relativistic constraints (E² ≥ p², non-negative energy)
// - Functions to perform several calculations using the four momentum, including
//   calculating the invariant mass for a system of particles.
//
// === COMPILATION AND EXECUTION ===
//
// Please see the README file for details on compilation and execution of this program.

#include<vector>

#include "FourMomentum.h"
#include "Particle.h"

using namespace ParticleProperties;

// [RULE OF 5]

FourMomentum::FourMomentum() : particle_px(0.0), particle_py(0.0), particle_pz(0.0), particle_energy(0.0)
{
  // Initialise four-momentum to zero
  std::cout<<"FourMomentum default constructor called. Four-momentum initialised to zero."<<std::endl;
}

FourMomentum::FourMomentum(double px, double py, double pz, double energy)
{
  set_momentum_components(px, py, pz, energy);
}

FourMomentum::FourMomentum(const FourMomentum& other)
  : particle_px(other.particle_px), particle_py(other.particle_py), particle_pz(other.particle_pz),
    particle_energy(other.particle_energy) {}


FourMomentum::FourMomentum(FourMomentum&& other) noexcept
  : particle_px(other.particle_px), particle_py(other.particle_py), particle_pz(other.particle_pz),
    particle_energy(other.particle_energy)
{
  // Move four-momentum components
  other.particle_px = 0.0;
  other.particle_py = 0.0;
  other.particle_pz = 0.0;
  other.particle_energy = 0.0;
}

FourMomentum::~FourMomentum()
{
  //std::cout<<"Four-momentum object destroyed."<<std::endl;
}

FourMomentum& FourMomentum::operator=(const FourMomentum& other)
{
  // Check for self-assignment
  if (this == &other) return *this;
  // Copy four-momentum components
  particle_px = other.particle_px;
  particle_py = other.particle_py;
  particle_pz = other.particle_pz;
  particle_energy = other.particle_energy;
  std::cout<<"FourMomentum copy assignment operator called."<<std::endl;
  return *this;
}

FourMomentum& FourMomentum::operator=(FourMomentum&& other) noexcept
{
  // Check for self-assignment
  if (this == &other) return *this;
  // Move four-momentum components
  particle_px = other.particle_px;
  particle_py = other.particle_py;
  particle_pz = other.particle_pz;
  particle_energy = other.particle_energy;
  std::cout<<"FourMomentum move assignment operator called."<<std::endl;
  // Reset the moved-from object
  other.particle_px = 0.0;
  other.particle_py = 0.0;
  other.particle_pz = 0.0;
  other.particle_energy = 0.0;
  return *this;
}

// [SETTERS AND VALIDATION]

// Helper method to validate four-momentum components
bool FourMomentum::validate_components(double px, double py, double pz, double energy)
{
   // Check for values exceeding maximum double
  const double max_double = std::numeric_limits<double>::max();
  if(std::fabs(px) >= max_double || std::fabs(py) >= max_double || 
    std::fabs(pz) >= max_double || std::fabs(energy) >= max_double) {return false;}
  // Energy must be non-negative
  if(energy < 0.0) {return false;}
  
  // Check mass-shell constraint: E^2 >= p^2 (in natural units where c=1)
  double p_squared = (px * px) + (py * py) + (pz * pz);
  double mass_squared = (energy * energy) - p_squared;
  
  // Allow for small numerical errors
  const double epsilon = 1e-10;
  return mass_squared >= -epsilon;
}

// Method to set all components at once with validation
void FourMomentum::set_momentum_components(double px, double py, double pz, double energy)
{
  // Only having one set function to set all components because having individual setters
  // could violate the mass-shell condition
  if(validate_components(px, py, pz, energy))
  {
    particle_px = px;
    particle_py = py;
    particle_pz = pz;
    particle_energy = energy;
  }
  else
  {
    throw std::runtime_error(
      "Invalid four-momentum components! Energy must be non-negative and E^2 >= p^2 must be satisfied.");
  }
}

// [PHYSICS METHODS]

double FourMomentum::calculate_invariant_mass() const
{
  double momentum_squared = (particle_px * particle_px) +  (particle_py * particle_py) +
    (particle_pz * particle_pz);
  double mass_squared = (particle_energy * particle_energy) - momentum_squared;
  
  // Handle potential numerical errors for massless particles
  if(mass_squared < 0 && mass_squared > -1e-10)
    return 0.0;
    
  return std::sqrt(mass_squared);
}

double FourMomentum::calculate_transverse_momentum() const
{
  return std::sqrt(particle_px * particle_px + particle_py * particle_py);
}

double FourMomentum::calculate_momentum_magnitude() const
{
  return std::sqrt(particle_px * particle_px + particle_py * particle_py + particle_pz * particle_pz);
}

double FourMomentum::calculate_pseudorapidity() const
{
  double momentum_magnitude = calculate_momentum_magnitude();
  
  // Handle case where momentum is zero
  if(momentum_magnitude < 1e-10) {return 0.0;}
    
  double cos_theta = particle_pz / momentum_magnitude;
  
  // Handle edge cases
  if(cos_theta >= 1.0) {return std::numeric_limits<double>::infinity();}
  if(cos_theta <= -1.0) {return -std::numeric_limits<double>::infinity();}
    
  // Compute pseudorapidity
  double theta = std::acos(cos_theta);
  if(theta < 1e-10) {return std::numeric_limits<double>::infinity();}
    
  return -std::log(std::tan(theta / 2.0));
}

// Static method to calculate invariant mass of a system of particles
double FourMomentum::calculate_system_invariant_mass(const std::vector<FourMomentum>& momenta)
{
  // Throw an error if the input vector is empty (no particles to process)
  if(momenta.empty()) {throw std::invalid_argument(
    "Four Momentum vector is empty. Cannot calculate system invariant mass. Exiting program.");}
  // Variables to accumulate the total momentum components and energy
  double total_px = 0.0;
  double total_py = 0.0;
  double total_pz = 0.0;
  double total_energy = 0.0;
  // Loop through each particle's four-momentum and sum the components
  for(const auto& momentum : momenta)
  {
    total_px += momentum.get_px();
    total_py += momentum.get_py();
    total_pz += momentum.get_pz();
    total_energy += momentum.get_energy();
  }
  // Create temporary four-momentum for the total system
  FourMomentum total_momentum(total_px, total_py, total_pz, total_energy);
  return total_momentum.calculate_invariant_mass();
}

void FourMomentum::print() const
{
  std::cout<<"Four-momentum (p_x, p_y, p_z, E) : ("
    <<particle_px<<", "
    <<particle_py<<", "
    <<particle_pz<<", "
    <<particle_energy<<") GeV"<<std::endl;
}

