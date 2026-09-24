#pragma once

#include "SPH2D.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"

#include <vector>

float SmoothingKernelPoly2D(float r, float h);
float getDenistyAtParticle(Particle particle, std::vector<Particle> particles);
Vector2 applyPressureForce(Particle particle, std::vector<Particle>particles);
Vector2 GradientSmoothingKernelPoly2D(Vector2 rVec, float h);
Vector2 GradientSmoothingKernelSpiky2D(Vector2 rVec, float h);
float getPressureAtPosition(
    Vector2 position,
    const std::vector<Particle>& particles);