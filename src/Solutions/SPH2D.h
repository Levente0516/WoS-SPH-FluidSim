#pragma once

#include "SPH2D.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"

#include <vector>

float SmoothingKernelPoly6_2D(float r, float h);
float getDenistyAtParticle(Particle particle, std::vector<Particle> particles);
Vector2 CalculatePressureForce(Particle& particle, std::vector<Particle>& particles);
Vector2 DerivateSmoothingKernelSpiky2D(Vector2 rVec, float h);
float ConvertDensityToPressure(float density);

float getPressureAtPosition(
    Vector2 position,
    const std::vector<Particle>& particles);