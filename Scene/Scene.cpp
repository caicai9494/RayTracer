#include <Scene/Scene.h>

bool Scene::Intersect(const Ray &ray,Intersection &hit)const
{
    bool success=false;
    for(unsigned int i=0;i<Objects.size();i++)
    {
	if(Objects[i]->Intersect(ray,hit)) 
	    success=true;
    }
    return success;
}
