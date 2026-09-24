#include "Simulation2D.h"
#include "Solutions/SPH2D.h"
#include "ParticleSpawner.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"
#include "UniversalFunctions/Gravity.h"
#include "UniversalFunctions/UpdatePos.h"
#include "raylib.h"
#include "raymath.h"

Vector2 minPositionR = SimulationConfig::BOUNDING_BOX_MIN_POSITION;
Vector2 maxPositionR = SimulationConfig::BOUNDING_BOX_MAX_POSITION;

Simulation2D::Simulation2D()
{
}

void Simulation2D::run()
{
    InitWindow(1200, 800, "WoS Fluid Simulation");
    SetTargetFPS(60);

    std::vector<Particle> particles = spawnParticles();

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();

        ClearBackground(BLACK);

        //Drawing bounding box
        DrawRectangleLines(minPositionR.x, minPositionR.y, (maxPositionR.x - minPositionR.x), (maxPositionR.y - minPositionR.y), RED);
        
        //Apply Gravity to every particle
        for (auto& particle : particles)
        {
            applyGravity(particle, dt);
        }

        //Calculate the density of all the particles
        for (auto& particle : particles)
        {
            particle.density = getDenistyAtParticle(particle, particles);
        }

        //Update the position of all particles
        for (auto& particle : particles)
        {
            updatePosition(particle, dt);
        }

        //Drawing particles
        for (auto& particle : particles)
        {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
}