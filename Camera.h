////////////////////////////////////////
// Camera.h
////////////////////////////////////////

#ifndef CSE168_CAMERA_H
#define CSE168_CAMERA_H

#include <Object/Vertex.h>
#include <Core/Matrix34.h>
#include <Scene.h>
#include <Core/Bitmap.h>

class Camera{
    public:
	Camera();
	~Camera();


	void LookAt(const Vector3 &p, const Vector3 &obj, const Vector3 &up = Vector3::YAXIS);
	void SetResolution(int w, int h);
	void SetFOV(float angle);
	void SetAspect(float asp);

	void Render(const Scene &s);
	void SaveBitmap(const char* path);

    private:
	Matrix34 WorldMatrix;
	UINT XRes, YRes;
	float VerticalFOV;
	float Aspect;
	Bitmap *BMP;

	Vector3 Position;
	Vector3 Target;


	void RenderPixel(const Scene &s, int x, int y);

};

#endif
