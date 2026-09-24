#pragma once

#include <raylib.h>

namespace SimulationConfig
{
    // Particle configuration
    constexpr int PARTICLE_COUNT = 500;
    constexpr float PARTICLE_RADIUS = 4.0f;

    // Initial particle region
    constexpr Vector2 BOUNDING_BOX_MIN_POSITION = {100.0f, 100.0f}; //X Y
    constexpr Vector2 BOUNDING_BOX_MAX_POSITION = {1100.0f, 750.0f}; // X Y

    // Simulation
    constexpr float GRAVITY = 9.81f;
    constexpr float PARTICLE_BOUNCE_DAMPENING = 0.8f;
    constexpr float PARTICLE_VELOCITY_THRESHOLD = 0.1f;
    constexpr float SMOOTHING_KERNEL_RADIUS = 10.0F;
}