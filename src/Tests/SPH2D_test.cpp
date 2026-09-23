#include "Rendering/rendering2D.h"
#include "Solutions/SPH2D.h"

int main()
{
    SPH2D simulation;
    Rendering2D renderer;

    renderer.run(simulation);

    return 0;
}