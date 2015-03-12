#include <RayTrace.h>

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
	Color temp = Color::BLACK;
	//compute lighting with this light 
	Vector3 toLight, ltPos;
	float intensity = Scn->GetLight(i).Illuminate(hit.Position, temp, toLight, ltPos);
	float dotProduct = (toLight).Dot(hit.Normal);
	float coeff = intensity * dotProduct;
	if(coeff > 0)
	{
	    Intersection shadowHit;

	    Ray shadowRay;
	    shadowRay.Origin = hit.Position;
	    shadowRay.Direction = toLight;
	    if(!Scn->Intersect(shadowRay, shadowHit))
	    {
	        temp.Scale(coeff);
	        //add this lighting to the pixel
	        hit.Shade.Add(temp);
	    }
	}
    }

    if(depth == MaxDepth)
	return true;

    return true;
}

void RenderPixel(int x, int y);
