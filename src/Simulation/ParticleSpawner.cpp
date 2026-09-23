#include <cstdlib>
#include "raylib.h"
#include "ParticleSpawner.h"
#include "Config/SimulationConfig.h"
#include "Objects/Particle.h"

int particleCount = SimulationConfig::PARTICLE_COUNT;
Vector2 minPosition = SimulationConfig::BOUNDING_BOX_MIN_POSITION;
Vector2 maxPosition = SimulationConfig::BOUNDING_BOX_MAX_POSITION;
float particleRadius = SimulationConfig::PARTICLE_RADIUS;

std::vector<Particle> spawnParticles()
{
    std::vector<Particle> particles;
    particles.reserve(particleCount);

    float midY = (minPosition.y + maxPosition.y) / 2.0f;

    for (int i = 0; i < particleCount; ++i)
    {
        float x = minPosition.x + static_cast<float>(rand()) / RAND_MAX * (maxPosition.x - minPosition.x);

        float y = midY  + static_cast<float>(rand()) / RAND_MAX * (maxPosition.y - midY);

        float particleMass = 10 + static_cast<float>(rand()) / RAND_MAX * 30;

        Particle p({x, y}, particleMass, particleRadius);

        particles.push_back(p);
    }

    return particles;
}