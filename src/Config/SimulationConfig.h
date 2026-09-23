#pragma once

#include <raylib.h>

namespace SimulationConfig
{
    // Particle configuration
    constexpr int PARTICLE_COUNT = 1000;

    constexpr float PARTICLE_MASS = 1.0f;
    constexpr float PARTICLE_RADIUS = 4.0f;

    // Initial particle region
    constexpr Vector2 BOUNDING_BOX_MIN_POSITION = {100.0f, 100.0f}; //X Y
    constexpr Vector2 BOUNDING_BOX_MAX_POSITION = {1100.0f, 750.0f}; // X Y

    // SPH parameters
    //constexpr float SMOOTHING_LENGTH = 20.0f;

    // Simulation
    constexpr float TIME_STEP = 0.01f;
    constexpr float GRAVITY = 9.81f;
}