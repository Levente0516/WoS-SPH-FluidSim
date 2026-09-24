#include "SPH2D.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <vector>

float h = SimulationConfig::SMOOTHING_KERNEL_RADIUS;

//Smoothing Kernels (TODO: add mor for benchmarking later)
//2D Poly6

float SmoothingKernelPoly2D(float r, float h)
{
    if (r < 0.0f || r > h)
    {
        return 0.0f;
    }

    float value = pow((h*h - r*r),3);

    return (4/(PI*pow(h,8))) * value;
}

//Gradient of the poly smoothing kernel

Vector2 GradientSmoothingKernelPoly2D(Vector2 rVec, float h)
{
    float r = Vector2Length(rVec);

    if (r < 0.0f || r > h)
    {
        return {0.0f,0.0f};
    }

    float value = pow((h*h - r*r),2);

    return Vector2Scale(rVec,  -(24/(PI*pow(h,8))) * value); 
}

Vector2 GradientSmoothingKernelSpiky2D(Vector2 rVec, float h)
{
    float r = Vector2Length(rVec);
    if (r <= 0.0001f || r > h) return {0.0f, 0.0f};

    float coeff = -30.0f / (PI * pow(h, 5)); 
    float value = pow(h - r, 2);

    return Vector2Scale(Vector2Scale(rVec, 1.0f / r), coeff * value);
}


/*
SPH basic intuiton:

A_S(r) = sum(m_j * (A_j/rho_j) * W(r - r_j, h))

where 
m_j is the mass of the j. particle, 
rho_j is the density of the j. particle,
A_j is the is the field quantity at r_j,
W is the smoothing kernel,
h is the radius of the kernel
r is the current particle (i.)
r_j is the j. particle
*/

/*
Density:

rho_S(r) = sum(m_j * (rho_j/rho_j) * W(r - r_j, h)) = sum(m_j * W(r - r_j, h))
*/

float getDenistyAtParticle(Particle particle, std::vector<Particle> particles)
{
    float sum = 0;

    for (auto p : particles)
    {
        sum += p.mass * SmoothingKernelPoly2D(Vector2Length(Vector2Subtract(particle.position, p.position)), h);
    }

    return sum;
}

/*
Pressure force:

f_i^pressure = -sum(m_j * ((p_i + p_j)/2*rho_j) * GradientW(r_i - r_j, h))
*/

Vector2 applyPressureForce(Particle particle, std::vector<Particle>particles)
{
    Vector2 pressureforce = {0.0f, 0.0f};
    float sum = 0;

    for (auto p : particles)
    {
        if (p.density <= 0.0f)
            continue;

        float helper = (particle.pressure + p.pressure)/(2*p.density);
        pressureforce = Vector2Add(pressureforce, Vector2Scale(GradientSmoothingKernelSpiky2D(Vector2Subtract(particle.position, p.position), h), p.mass * helper));
    }

    return Vector2Scale(pressureforce, -1.0f);
}

float getPressureAtPosition(
    Vector2 position,
    const std::vector<Particle>& particles)
{
    float weightedPressure = 0.0f;
    float weightSum = 0.0f;

    for (const auto& p : particles)
    {
        if (p.density <= 0.0f)
            continue;

        float r = Vector2Distance(position, p.position);

        if (r > h)
            continue;

        float weight = p.mass * SmoothingKernelPoly2D(r, h);

        weightedPressure +=
            weight * p.pressure / p.density;

        weightSum +=
            weight / p.density;
    }

    if (weightSum <= 0.0f)
        return 0.0f;

    return weightedPressure / weightSum;
}