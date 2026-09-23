#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"

float g = SimulationConfig::GRAVITY;

void applyGravity(Particle& particle, float dt)
{
    particle.velocity.y += g * dt * particle.mass;
}