#pragma once

#include "SPH2D.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"

#include <vector>

float SmoothingKernelPoly(float r, float h);
float getDenistyAtParticle(Particle particle, std::vector<Particle> particles);