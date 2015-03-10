////////////////////////////////////////
// Camera.cpp
////////////////////////////////////////

#include <Camera.h>
#include <Intersection.h>

Vector3 CX, CY;
float CW, CH;

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
    VerticalFOV = angle / 180 * PI;
}


void Camera::SetAspect(float asp)
{
    Aspect = asp;
}

void Camera::RenderPixel(const Scene &s, int x, int y)
{
    Intersection intrs;

    Ray ray;
    ray.Origin = Position;

    ray.Direction = -WorldMatrix.c + 
	           (static_cast<float>(x) / XRes - 0.5f) * CW * CX +
	           (static_cast<float>(y) / YRes - 0.5f) * CH * CY;
    ray.Direction.Normalize();
    
    if(s.Intersect(ray, intrs))
    {
	Color color = Color::WHITE;
	for(UINT k = 0; k < s.GetNumLights(); k++)
	{
	    Vector3 toLight, ltPos;
	    float iten = s.GetLight(k).Illuminate(intrs.Position, intrs.Shade, toLight, ltPos);

	    float lightDot = toLight.Dot(intrs.Normal);
	    if(lightDot > 0)
		intrs.Shade.Scale(lightDot * iten);

	    color.Add(intrs.Shade);
	}
	BMP->SetPixel(x, y, color.ToInt());
    }
    else
	BMP->SetPixel(x, y, s.GetSkyColor().ToInt());

}
void Camera::Render(const Scene &s)
{
    BMP = new Bitmap(XRes, YRes);

    CX.Cross(-WorldMatrix.c, WorldMatrix.b);
    CY.Cross(CX, -WorldMatrix.c);

    CW = 2.0f * tan(VerticalFOV / 2.0f);
    CH = CW / Aspect;

    for(UINT i = 0; i < XRes; i++)
    {
	for(UINT j = 0; j < YRes; j++)
	{
	    RenderPixel(s, i, j);
	}
    }
}

void Camera::SaveBitmap(const char* path)
{
    BMP->SaveBMP(path);
}
