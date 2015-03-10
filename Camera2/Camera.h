#pragma once


#ifndef CSE168_CAMERA_H
#define CSE168_CAMERA_H

#include <Core/Matrix34.h>
#include <Core/Vector3.h>
#include <Core/Bitmap.h>
#include <Scene.h>
#include <Material/Material.h>
#include <iostream>

class Camera
{
public:
	Camera();
	~Camera();

	void SetFOV(float f);
	void SetAspect(float a);
	void SetResolution(int x, int y);
	void LookAt(const Vector3 &pos, const Vector3 &target, const Vector3 &up = Vector3::YAXIS);

	void Render(Scene &s);
	void SaveBitmap(char *filename);
	void RenderPixel(int x, int y, Scene &s);


private:

	int XRes, YRes;
	Matrix34 WorldMatrix;
	float VerticalFOV;
	float Aspect;
	Bitmap *BMP;
	Vector3 topLeft, topRight, bottomLeft, bottomRight, right, up;
	float rightDelta;
	float downDelta;
};

#endif

