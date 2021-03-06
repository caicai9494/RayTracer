////////////////////////////////////////
// Camera.cpp
////////////////////////////////////////

#include "Camera.h"
#include "Intersection.h"
Camera::Camera()
{
    BMP = 0;
}
Camera::~Camera()
{
    delete BMP;
}

void Camera::LookAt(const Vector3 &p, const Vector3 &obj, const Vector3 &up)
{
    Position = p;
    Target = obj;

    Vector3 c = Position - Target;
    c.Normalize();
    Vector3 a;
    a.Cross(up,c);
    a.Normalize();
    Vector3 b;
    b.Cross(c, a);

    WorldMatrix.a = a;
    WorldMatrix.b = b;
    WorldMatrix.c = c;
    WorldMatrix.d = Position;

}
void Camera::SetResolution(int w, int h)
{
    XRes = w;
    YRes = h;
}
void Camera::SetFOV(float angle)
{
    VerticalFOV = angle;
}

float Camera::GetHorizontalFOV()
{
    return 2 * atan(Aspect * tan(VerticalFOV / 2));
}

void Camera::SetAspect(float asp)
{
    Aspect = asp;
}

void Camera::Render(Scene &s)
{
    BMP = new Bitmap(XRes, YRes);

    float r = XRes / 2.0;
    float l = -r;

    float t = YRes / 2.0;
    float b = -t;

    Ray ray;
    ray.Origin = Position;

    Vector3 dir;
    Intersection intrs;
    for(UINT i = 0; i < XRes; i++)
    {
	for(UINT j = 0; j < YRes; j++)
	{
	    dir.x = l + i;
	    dir.y = b + j;
	    dir.z = 0;
	    dir = dir - ray.Origin;
	    dir.Normalize();

	    //WorldMatrix.Transform(ray.Origin, ray.Origin);
	    //WorldMatrix.Transform(ray.Origin, ray.Origin);
	    ray.Direction = dir;

	    if(s.Intersect(ray, intrs))
	    {
		for(UINT k = 0; k < s.GetNumLights(); k++)
		{
		    Vector3 lsPos, lsDir;
		    float iten = s.GetLight(k).Illuminate(intrs.Position, intrs.Shade, lsPos, lsDir);
		}
		BMP->SetPixel(i, j, intrs.Shade.ToInt());
	    }
	    else
		BMP->SetPixel(i, j, s.GetSkyColor().ToInt());

	}
    }
}

void Camera::SaveBitmap(const char* path)
{
    BMP->SaveBMP(path);
}
