#include <RayTrace.h>

RayTrace::RayTrace(const Scene &s)
{
    Scn = &s;
}

bool RayTrace::TraceRay(const Ray &ray, Intersection &hit, int depth)
{
    if(!Scn->Intersect(ray, hit))
    {
	hit.Shade = Scn->GetSkyColor();
	return false;
    }

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
	    temp.Scale(coeff);
	    //add this lighting to the pixel
	    hit.Shade.Add(temp);
	}
    }

    if(depth == MaxDepth)
	return true;

    return true;
}

void RenderPixel(int x, int y);
