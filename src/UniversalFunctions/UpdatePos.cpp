#include <cmath>
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"
#include "raylib.h"

Vector2 minPositionU = SimulationConfig::BOUNDING_BOX_MIN_POSITION;
Vector2 maxPositionU = SimulationConfig::BOUNDING_BOX_MAX_POSITION;
float particleRadiusU = SimulationConfig::PARTICLE_RADIUS;
float dampening = SimulationConfig::PARTICLE_BOUNCE_DAMPENING;
float velocityThreshold = SimulationConfig::PARTICLE_VELOCITY_THRESHOLD;

void updatePosition(Particle& particle, float dt)
{
    particle.position.x += particle.velocity.x * dt;
    particle.position.y += particle.velocity.y * dt;

    if (particle.position.y + particleRadiusU >= maxPositionU.y)
    {
        particle.position.y = maxPositionU.y - particleRadiusU;
        particle.velocity.y *= -dampening;
    }

    if (fabs(particle.velocity.y) < velocityThreshold)
    {
        particle.velocity.y = 0.0f;
    }
}