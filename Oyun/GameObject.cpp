#include "GameObject.h"

GameObject :: GameObject()
{

}

GameObject::GameObject(const GameObject& pObj)
{

}

GameObject& GameObject::operator = (const GameObject& pObj)
{
	return *this;
}

GameObject:: ~GameObject()
{

}

GameObject* GameObject::getInstanceGameObject()
{
	if (mInstanceGameObject == 0)
		mInstanceGameObject = new GameObject();

	return mInstanceGameObject;
}

void GameObject::Render(SDL_Renderer* renderer)
{

}

void GameObject::Update()
{
	
}

void GameObject::Clean()
{

}
