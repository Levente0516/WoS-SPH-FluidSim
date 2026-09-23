#pragma once

#include "raylib.h"

struct Particle
{
    Vector2 position;
    Vector2 velocity;

    float density;
    float mass;
    float pressure;

    float radius;

    Particle(Vector2 position, float mass, float radius)
    {
        this->position = position;
        this->mass = mass;
        this->radius = radius;
        
        velocity = {0.0f,0.0f};
        density = 0.0f;
        pressure = 0.0f;
    }
};