////////////////////////////////////////
// Intersection.h
////////////////////////////////////////

#ifndef CSE168_INTERSECTION_H
#define CSE168_INTERSECTION_H

#include "Vector3.h"
#include "Color.h"
class Material;

////////////////////////////////////////////////////////////////////////////////

class Intersection {
public:
	Intersection()			{HitDistance=1e10; Mtl=0; Obj = 0;}

public:
	// Ray intersection data
	float HitDistance;
	Vector3 Position;
	Vector3 Normal;
	Material *Mtl;

	// Shaded color
	Color Shade;


	//obj
	Object *Obj;
};

////////////////////////////////////////////////////////////////////////////////

#endif
