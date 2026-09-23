#include "rendering2D.h"
#include "Solutions/SPH2D.h"
#include "Simulation/ParticleSpawner.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"

#include "raylib.h"

Vector2 minPositionR = SimulationConfig::BOUNDING_BOX_MIN_POSITION;
Vector2 maxPositionR = SimulationConfig::BOUNDING_BOX_MAX_POSITION;

Rendering2D::Rendering2D()
{
}

void Rendering2D::run(SPH2D& simulation)
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
        
        for (auto particle : particles)
        {
            
        }


        //Drawing particles
        for (auto particle : particles)
        {
            DrawCircle(particle.position.x, particle.position.y, particle.radius, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}