#include "GameObject.h"



GameObject::GameObject(Vector3 _position)
{
	position = _position;
}


GameObject::GameObject()
{
	position = Vector3();
}


GameObject::~GameObject()
{
}
