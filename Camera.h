////////////////////////////////////////
// Camera.h
////////////////////////////////////////

#ifndef CSE168_CAMERA_H
#define CSE168_CAMERA_H

#include "Vertex.h"
#include "Matrix34.h"

class Camera{
    public:
	Vector3 pos;
	Vector3 target;
	Vector3 up;
	Vector3 right;

	Matrix34 lookAt()
	{
	    Vector3 c = pos - target;
	    c.Normalize();
	    Vector3 a = up.Cross(c);
	    a.Normalize();
	    Vector3 b = c.Cross(a);

	    Matrix34 viewM;
	    viewM.a = a;
	    viewM.b = b;
	    viewM.c = c;
	    viewM.d = pos;

	    return viewM;
	}
};
