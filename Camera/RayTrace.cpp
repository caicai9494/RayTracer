#include <Camera/RayTrace.h>
#include <iostream>
using namespace std;

RayTrace::RayTrace(const Scene &s)
{
    Scn = &s;

    MaxDepth = 5;

    // Statistics
    PrimaryRays = 0;
    SecondaryRays = 0;
    ShadowRays = 0;
}

bool RayTrace::TraceRay(const Ray &ray, Intersection &hit, int depth)
{
    if(depth == MaxDepth)
	return true;
    // didn't hit any object.
    if(!Scn->Intersect(ray, hit))
    {
	hit.Shade = Scn->GetSkyColor();
	return false;
    }

    // hit 
    hit.Shade = Color::BLACK;
    //hit.Shade = Color(0.2f, 0.1f, 0.1f);
    //hit.Shade.Scale(0.5f);
    for (UINT i = 0; i < Scn->GetNumLights(); ++i) 
    {
	Color lightColor = Color::BLACK;
	//compute lighting with this light 
	Vector3 toLight, ltPos;
	float intensity = Scn->GetLight(i).Illuminate(hit.Position, lightColor, toLight, ltPos);
	float dotProduct = (toLight).Dot(hit.Normal);
	float coeff = intensity * dotProduct;

	//oppose the light
	if(coeff <= 0)
	    continue;

	//shadow
	Intersection shadowHit;

	Ray shadowRay;
	shadowRay.Origin = hit.Position;
	shadowRay.Direction = toLight;
	bool isBlocked = false;
	if(Scn->Intersect(shadowRay, shadowHit))
	{
	    float blockDistance = shadowHit.Position.Distance(shadowRay.Origin);
	    float lightDistance = ltPos.Distance(hit.Position);
	    if(blockDistance < lightDistance)
		isBlocked = true;
	}


	if(!isBlocked)
	{
	    
	    Color reflectance = lightColor;
	    reflectance.Scale(PI * coeff);
	    if(hit.Mtl)
		hit.Mtl->ComputeReflectance(reflectance, toLight, -ray.Direction, hit);

	    //lightColor.Scale(coeff);
	    //lightColor.Multiply(reflectance);

	    hit.Shade.Add(reflectance);
	    //add this lighting to the pixel
	    
	    /*
	    Intersection rHit;
	    Ray rRay;
	    rRay.Origin = hit.Position;
	    rRay.Direction = r;
	    rRay.Direction.Normalize();
	    TraceRay(rRay, rHit, depth + 1);

	    rHit.Shade.Scale(pow(0.1f,depth));
	    hit.Shade.Add(rHit.Shade);
	    */


	}
    }


		/*
    if(!hit.Mtl)
    {
	Vector3 out;
	Color reflectColor;
	Intersection secondaryHit;

	Ray secondaryRay;
	//hit.Mtl->ComputeReflectance(reflectColor, hit.Position, out, secondaryHit);
	secondaryRay.Origin = hit.Position;
	secondaryRay.Direction = out;

	//RayTrace(secondaryRay, secondaryHit, depth + 1);
	//hit.Shade.Mu
    }
    */

    return true;
}

void RenderPixel(int x, int y);
