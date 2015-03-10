#include <Camera.h>

Vector3 CX, CY;
float CW, CH;

Camera::Camera()
{
}

Camera::~Camera()
{ 
    delete BMP;
}


void Camera::SetFOV(float f) {
	VerticalFOV = PI * f / 180;
}
void Camera::SetAspect(float a) {
	Aspect = a;
}
void Camera::SetResolution(int x, int y) {
	XRes = x;
	YRes = y;
        BMP = new Bitmap(XRes, YRes);
}
void Camera::LookAt(const Vector3 &pos, const Vector3 &target, const Vector3 &up) {
	WorldMatrix.d = pos;
	WorldMatrix.c = WorldMatrix.d - target;
	WorldMatrix.c.Normalize();
	WorldMatrix.a.Cross(up, WorldMatrix.c);
	WorldMatrix.a.Normalize();
	WorldMatrix.b.Cross(WorldMatrix.c, WorldMatrix.a);
}

void Camera::Render(const Scene &s) {

    CX.Cross(-WorldMatrix.c, WorldMatrix.b);
    CY.Cross(CX, -WorldMatrix.c);

    CW = 2.0f * tanf(VerticalFOV/ 2);
    CH = CW / Aspect;

    for (int y = 0; y < YRes; ++y) {
	    for (int x = 0; x < XRes; ++x) {
		    RenderPixel(s, x, y);
	    }
    }
}
void Camera::SaveBitmap(const char *filename) {
	BMP->SaveBMP(filename);
}

void Camera::RenderPixel(const Scene &s, int x, int y) 
{
    Ray ray;
    ray.Origin = WorldMatrix.d;
    ray.Direction = -WorldMatrix.c / Aspect + (((float)x)/XRes - 0.5) * CW * CX + 
				     (((float)y)/YRes - 0.5) * CH * CY;
    ray.Direction.Normalize();
    Intersection hit;

    if (!s.Intersect(ray, hit)) {
	    //no hits so skycolor:
	    BMP->SetPixel(x, y, s.GetSkyColor().ToInt());
    }
    else {
	    Color color = Color::BLACK;
	    for (UINT i = 0; i < s.GetNumLights(); ++i) {
		    //compute lighting with this light 
		    Vector3 toLight, ltPos;
		    float intensity = s.GetLight(i).Illuminate(hit.Position, hit.Shade, toLight, ltPos);
		    float dotResult = Max(0.0f, (toLight).Dot(hit.Normal));

		    hit.Shade.Scale(intensity * dotResult);
		    //add this lighting to the pixel
		    color.Add(hit.Shade);
	    }
	    BMP->SetPixel(x, y, color.ToInt());
    }
}
