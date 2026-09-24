#include "Simulation2D.h"
#include "Solutions/SPH2D.h"
#include "ParticleSpawner.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"
#include "UniversalFunctions/Gravity.h"
#include "UniversalFunctions/UpdatePos.h"
#include "raylib.h"
#include "raymath.h"

#include <iostream>
#include <float.h>

Vector2 minPositionR = SimulationConfig::BOUNDING_BOX_MIN_POSITION;
Vector2 maxPositionR = SimulationConfig::BOUNDING_BOX_MAX_POSITION;


Simulation2D::Simulation2D()
{
}

void Simulation2D::run()
{
    InitWindow(1200, 800, "WoS Fluid Simulation");
    SetTargetFPS(120);

    std::vector<Particle> particles = spawnParticles();


    float minDensity = FLT_MAX;
    float maxDensity = 0.0f;
    float averageDensity = 0.0f;

    for (auto& particle : particles)
    {
        particle.density =
            getDenistyAtParticle(particle, particles);

        minDensity = std::min(minDensity, particle.density);
        maxDensity = std::max(maxDensity, particle.density);
        averageDensity += particle.density;
    }

    averageDensity /= particles.size();

    std::cout << "Min density:     " << minDensity << '\n';
    std::cout << "Average density: " << averageDensity << '\n';
    std::cout << "Max density:     " << maxDensity << '\n';

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        
        //Apply Gravity to every particle
        for (auto& particle : particles)
        {
            applyGravity(particle, dt);
        }
        
        
        //Calculate the density as well as pressure of all the particles
        for (auto& particle : particles)
        {
            particle.density = getDenistyAtParticle(particle, particles);
        }

        //Calculate pressure force and add it to velocity
        for (auto& particle : particles)
        {
            Vector2 pressureForce = CalculatePressureForce(particle, particles);

            //std::cout << "(" << pressureForce.x << "," <<pressureForce.y << ")" << std::endl;

            Vector2 pressureAcceleration = Vector2Scale(pressureForce, 1.0f / particle.mass);

            particle.velocity = Vector2Add(particle.velocity, Vector2Scale(pressureAcceleration, dt));
        }

        //Update the position of all particles
        for (auto& particle : particles)
        {
            updatePosition(particle, dt);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        //Drawing bounding box
        DrawRectangleLines(minPositionR.x, minPositionR.y, (maxPositionR.x - minPositionR.x), (maxPositionR.y - minPositionR.y), RED);

        DrawFPS(0,0);

        // pressure field
        /*
        
        for (int y = minPositionR.y; y < maxPositionR.y; y += 8)
        {
            for (int x = minPositionR.x; x < maxPositionR.x; x += 8)
            {
                Vector2 position = {
                    static_cast<float>(x),
                    static_cast<float>(y)
                };

                float pressure = getPressureAtPosition(position, particles);

                // Map pressure to 0..1
                float t = pressure / 10.0f;
                t = Clamp(t, 0.0f, 1.0f);

                Color color;

                if (t < 0.5f)
                {
                    // Blue -> White
                    float a = t * 2.0f;

                    color = {
                        static_cast<unsigned char>(255 * a),
                        static_cast<unsigned char>(255 * a),
                        255,
                        255
                    };
                }
                else
                {
                    // White -> Red
                    float a = (t - 0.5f) * 2.0f;

                    color = {
                        255,
                        static_cast<unsigned char>(255 * (1.0f - a)),
                        static_cast<unsigned char>(255 * (1.0f - a)),
                        255
                    };
                }

                DrawRectangle(x, y, 10, 10, color);
            }
        }
        */

        //Drawing particles
        for (auto& particle : particles)
        {
            //std::cout << particle.pressure << std::endl;
            DrawCircle(particle.position.x, particle.position.y, particle.radius, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}