#include "Entity.h"


//=============================================================================
// constructor
//============================================================================
Entity::Entity() :Image()
{
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	deltaV.x = 0.0f;
	deltaV.y = 0.0f;
	active = true;			// the Entity is active
	health = 100;
	dx = 0.0f;
	dy = 0.0f;
}


//=============================================================================
// activate the entity	
//=============================================================================
void Entity::activate()
{
	active = true;
}

// get coordinate of entity
void Entity::getBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = spriteData.x;
	top = spriteData.y;
	right = left + spriteData.width;
	bottom = top + spriteData.height;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Entity::update(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Image::update(frameTime);
}

bool Entity::outsideRect(RECT rect)
{
	if (spriteData.x + spriteData.width * getScale() < rect.left ||
		spriteData.x > rect.right ||
		spriteData.y + spriteData.height * getScale() < rect.top ||
		spriteData.y + rect.bottom)
		return true;
	return false;
}

//=============================================================================
// damage
// This entity has been damaged by a weapon.
// Override this function in the inheriting class.
//=============================================================================
void Entity::damage(int weapon)
{}