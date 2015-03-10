////////////////////////////////////////
// PointLight.h
////////////////////////////////////////

#ifndef CSE168_POINTLIGHT_H
#define CSE168_POINTLIGHT_H

#include <Light/Light.h>

class PointLight: public Light
{
    public:
	PointLight(): Light(){}
	float Illuminate(const Vector3 &pos, Color &col, Vector3 &toLight, Vector3 &ltPos)
	{
	    toLight = Position - pos;
	    float bright = Intensity / toLight.Magnitude2();
	    toLight.Normalize();

	    col = BaseColor;
	    ltPos = Position;

	    return bright;
	}

	void SetPosition(const Vector3 &v)
	{
	    Position = v;
	}


    private:
	Vector3 Position;
};

#endif
