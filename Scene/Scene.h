////////////////////////////////////////
// Scene.h
////////////////////////////////////////

#ifndef CSE168_SCENE_H
#define CSE168_SCENE_H

#include <Object/Object.h>
#include <Light/Light.h>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

class Scene {
public:
	Scene()										{SkyColor.Set(0.2f,0.2f,0.5f);}

	void AddObject(Object &obj)					{Objects.push_back(&obj);}
	void AddLight(Light &lgt)					{Lights.push_back(&lgt);}
	void SetSkyColor(const Color sky)			{SkyColor=sky;}

	UINT GetNumLights()const							{return Lights.size();}
	Light &GetLight(int i)const						{return *Lights[i];}
	Color GetSkyColor()const							{return SkyColor;}

	bool Intersect(const Ray &ray,Intersection &hit) const;

private:
	std::vector<Object*> Objects;
	std::vector<Light*> Lights;
	Color SkyColor;
};

////////////////////////////////////////////////////////////////////////////////

#endif
