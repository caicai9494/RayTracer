////////////////////////////////////////
// Camera.h
////////////////////////////////////////

#ifndef CSE168_CAMERA_H
#define CSE168_CAMERA_H

#include "Vertex.h"
#include "Matrix34.h"
#include "Scene.h"
#include "Bitmap.h" 

class Camera{
    public:
	Camera();
	~Camera();

	static Vector3 UP;

	void LookAt(Vector3 p, Vector3 obj);
	void SetResolution(int w, int h);
	void SetFOV(float angle);
	void SetAspect(float asp);

	void Render(Scene s);
	void SaveBitmap(const char* path);

	float GetHorizontalFOV();

    private:
	Matrix34 WorldMatrix;
	UINT XRes, YRes;
	float VerticalFOV;
	float Aspect;
	Bitmap *BMP;

	Vector3 Position;
	Vector3 Target;

};

#endif
