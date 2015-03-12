#include <Camera.h>

static Vector3 CX, CY;
static float CW, CH;

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
		    //std::cout << "Working! " << (y * YRes + XRes) / (float)total_pixel << std::endl;
	    }

	float progress = (float)y * 100 / YRes;
	std::cout << "y in process " << progress << "% " << std::endl;
	if(y % 10 == 0)
	    this->SaveBitmap("Temp");

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

    RayTrace rayTrace(s);
    rayTrace.TraceRay(ray, hit);
    BMP->SetPixel(x, y, hit.Shade.ToInt());
}
