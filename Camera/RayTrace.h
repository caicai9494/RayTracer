////////////////////////////////////////
// RayTrace.h
////////////////////////////////////////

#ifndef CSE168_RAYTRACE_H
#define CSE168_RAYTRACE_H

#include <Core/Vector3.h>
#include <Scene.h>
#include <Material/LambertMaterial.h>
#include <Camera/Ray.h>
#include <Camera/Intersection.h>

////////////////////////////////////////////////////////////////////////////////

class RayTrace {
public:
    RayTrace(const Scene &s);
    bool TraceRay(const Ray &ray, Intersection &hit, int depth = 1);

private:
    const Scene *Scn;

    // settings 
    int MaxDepth;

    // Statistics
    int PrimaryRays;
    int SecondaryRays;
    int ShadowRays;

    void RenderPixel(int x, int y);
};

////////////////////////////////////////////////////////////////////////////////

#endif