#include "SPH2D.h"
#include "Objects/Particle.h"
#include "Config/SimulationConfig.h"
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <vector>

float h = SimulationConfig::SMOOTHING_KERNEL_RADIUS;

//Smoothing Kernels (TODO: add mor for benchmarking later)
//Poly6

float SmoothingKernelPoly(float r, float h)
{
    if (r < 0 || r > h)
    {
        return 0;
    }

    float value = pow((h*h - r*r),3);

    return (315/(64*PI*pow(h,9))) * value;
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
density:

rho_S(r) = sum(m_j * (rho_j/rho_j) * W(r - r_j, h)) = sum(m_j * W(r - r_j, h))
*/

float getDenistyAtParticle(Particle particle, std::vector<Particle> particles)
{
    float sum = 0;

    for (auto& p : particles)
    {
        sum += p.mass * SmoothingKernelPoly(Vector2Length(Vector2Subtract(particle.position, p.position)), h);
    }

    return sum;
}