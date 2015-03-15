////////////////////////////////////////
// Intersection.h
////////////////////////////////////////

#ifndef CSE168_INTERSECTION_H
#define CSE168_INTERSECTION_H

#include <Core/Vector3.h>
#include <Core/Color.h>
#include <Object/Object.h>
#include <Material/Material.h>

class Material;
class Object;

////////////////////////////////////////////////////////////////////////////////

class Intersection {
public:
	Intersection()			{HitDistance=1e10; Mtl=0; Obj = 0;}

public:
	// Ray intersection data
	float HitDistance;

	Vector3 Position;
	Vector3 Normal;

	Vector3 TangentU;
	Vector3 TangentV;

	Material *Mtl;

	// Shaded color
	Color Shade;

	//obj
	Object *Obj;
};

////////////////////////////////////////////////////////////////////////////////

#endif
