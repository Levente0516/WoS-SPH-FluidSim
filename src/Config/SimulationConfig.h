#pragma once

#include "raylib.h"

namespace SimulationConfig
{
    // Particle configuration
    constexpr int PARTICLE_COUNT = 500;
    constexpr float PARTICLE_RADIUS = 4.0f;

    // Initial particle region
    constexpr Vector2 BOUNDING_BOX_MIN_POSITION = {100.0f, 100.0f}; //X Y
    constexpr Vector2 BOUNDING_BOX_MAX_POSITION = {1100.0f, 750.0f}; // X Y

    // Simulation
    constexpr float GRAVITY = 0.981f;
    constexpr float PARTICLE_BOUNCE_DAMPENING = 0.8f;
    constexpr float PARTICLE_VELOCITY_THRESHOLD = 0.001f;
    constexpr float SMOOTHING_KERNEL_RADIUS = 100.0f;
    constexpr float GAS_CONSTANT = 1.0f;
    constexpr float RESTING_DENSITY = 0.0015f;
    constexpr float DENSITY_SCALE = 1.0f;
    constexpr float PRESSURE_SCALE = 100000.0f;
}