#include <Camera2/Camera.h>

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

void Camera::Render(Scene &s) {

	//create the corners of the rendering window:

	//calculate modifiedB
	Vector3 modifiedB = WorldMatrix.b;
	modifiedB.Scale(tan(VerticalFOV / 2));
	Vector3 modifiedA = WorldMatrix.a;
	//calculate hfov and modifiedB
	float hfov = 2 * atan(Aspect * tan((VerticalFOV / 2)));
	modifiedA.Scale(tan(hfov / 2));

	topLeft = WorldMatrix.d - WorldMatrix.c + modifiedB - modifiedA;
	//topLeft.Print("upleft");
	topRight = WorldMatrix.d - WorldMatrix.c + modifiedB + modifiedA;
	//topRight.Print("upright");
	bottomLeft = WorldMatrix.d - WorldMatrix.c - modifiedB - modifiedA;
	//bottomLeft.Print("downleft");
	bottomRight = WorldMatrix.d - WorldMatrix.c - modifiedB + modifiedA;
	//bottomRight.Print("downright");
	right = (topRight - topLeft);
	rightDelta = right.Magnitude() / XRes;
	right.Normalize();
	up = (topLeft - bottomLeft);
	downDelta = up.Magnitude() / YRes;
	up.Normalize();

	for (int y = 0; y < YRes; ++y) {
		for (int x = 0; x < XRes; ++x) {
			RenderPixel(x, y, s);
		}
	}
}
void Camera::SaveBitmap(char *filename) {
	BMP->SaveBMP(filename);
}

void Camera::RenderPixel(int x, int y, Scene &s) {
	Ray sentRay;
	sentRay.Origin = WorldMatrix.d;
	
	//compute ray direction:
	sentRay.Direction = bottomLeft;
	sentRay.Direction.AddScaled(right, (x + 0.5) * rightDelta);
	sentRay.Direction.AddScaled(up, (y + 0.5) * downDelta);

	sentRay.Direction = sentRay.Direction - WorldMatrix.d;
	sentRay.Direction.Normalize();

	Intersection hit;
	if (!s.Intersect(sentRay, hit)) {
		//no hits so skycolor:
		BMP->SetPixel(x, y, s.GetSkyColor().ToInt());
	}
	else {
		Color newColor = Color(0.0,0.0,0.0);
		for (int i = 0; i < s.GetNumLights(); ++i) {
			//compute lighting with this light 
			Color lightColor, C;
			Vector3 toLight, ItPos, in, out;
			float intensity = s.GetLight(i).Illuminate(hit.Position, lightColor, toLight, ItPos);
			C = lightColor;
			float dotResult = (toLight).Dot(hit.Normal);
			C.Scale(((dotResult < 0) ? 0 : dotResult) * intensity);

			//add this lighting to the pixel
			newColor.Add(C);
		}
		BMP->SetPixel(x, y, newColor.ToInt());
	}
}
