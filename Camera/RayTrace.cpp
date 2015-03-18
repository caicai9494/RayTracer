#include <Camera/RayTrace.h>
#include <iostream>
using namespace std;

RayTrace::RayTrace(Scene &s)
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
    // didn't hit any object.
    if(!Scn->Intersect(ray, hit))
    {
	hit.Shade = Scn->GetSkyColor();
	return false;
    }

    // hit 
    hit.Shade = Color::BLACK;
    for (UINT i = 0; i < Scn->GetNumLights(); ++i) 
    {
	Color lightColor;// = Color::BLACK;
	//compute lighting with this light 
	Vector3 toLight, ltPos;
	float intensity = Scn->GetLight(i).Illuminate(hit.Position, lightColor, toLight, ltPos);
	if(intensity == 0) 
	    continue;

	/*
	float dotProduct = (toLight).Dot(hit.Normal);
	float coeff = intensity * dotProduct;

	//oppose the light
	if(coeff <= 0)
	    continue;
	    */

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

	    float dotProduct = (toLight).Dot(hit.Normal);
	    float coeff = Max(0.0f,intensity * dotProduct);

	    reflectance.Scale(PI * coeff);
	    if(hit.Mtl != NULL)
		hit.Mtl->ComputeReflectance(reflectance, -ray.Direction, toLight, hit);

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

    if(depth == MaxDepth)
	return true;

    if(hit.Mtl != NULL)
    {

	//cout << "debug\n";
	Color reflectColor;
	Intersection secondaryHit;

	Ray secondaryRay;
	secondaryRay.Origin = hit.Position;
	hit.Mtl->GenerateSample(reflectColor, secondaryRay.Direction, -ray.Direction, hit);
	//black returned
	//if(reflectColor.GetIntVector().Magnitude() == 0)
	 //   return false;

	TraceRay(secondaryRay, secondaryHit, depth + 1);
	secondaryHit.Shade.Multiply(reflectColor);
	hit.Shade.Add(secondaryHit.Shade);

    }

    return true;
}

