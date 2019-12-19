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
	unTouchable = false;
	firstX = firstY = 0.0f;
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

void Entity::RenderBoundingBox(Camera* camera)
{
	float l, t, r, b;
	getBoundingBox(l, t, r, b);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (LONG)r - (LONG)l;
	rect.bottom = (LONG)b - (LONG)t;

	D3DXVECTOR2 pos = camera->CameraTransform(l, t);

	Graphics::getInstance()->drawSprite(pos.x, pos.y, TextureManager::getIntance()->getTexture(BBOX)->getTexture(),
		rect.left, rect.top, rect.right, rect.bottom, graphicsNS::ALPHA50);
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
	dx = velocity.x * frameTime;
	dy = velocity.y * frameTime;
	Image::update(frameTime);
}

void Entity::draw(COLOR_ARGB color)
{
	Image::draw(color);
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

#pragma region Collision

LPCOLLISIONEVENT Entity::SweptAABBEx(Entity* ent2, float frameTime)
{
	float sl, st, sr, sb;		//static object bbox (Rect của object)
	float ml, mt, mr, mb;		//move object bbox (Rect của main)
	float t, nx, ny;

	ent2->getBoundingBox(sl, st, sr, sb); //get tọa độ của object

	//deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	svx = ent2->getVelocity().x;
	svy = ent2->getVelocity().y;

	float sdx = svx * frameTime; //khoảng cách x object đi được sau khoảng dt
	float sdy = svy * frameTime; //khoảng cách y object đi được sau khoảng dt

	float dx = this->getDX() - sdx; //khoảng cách dx giữa main và object
	float dy = this->getDY() - sdy; //khoảng cách dy giữa main và object

	this->getBoundingBox(ml, mt, mr, mb);

	//Xét va chạm
	SweptAABB(
		ml, mt, mr, mb, //tọa độ main
		dx, dy, //khoảng cách giữa main vs object
		sl, st, sr, sb, //tọa độ object
		t, nx, ny); //điều kiện xét có va chạm hay không?

	LPCOLLISIONEVENT e = new CCollisionEvent(t, nx, ny, ent2);
	return e;
}

void Entity::SweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float& t, float& nx, float& ny)
{
	float xInvEntry, yInvEntry, xEntry, yEntry;
	float xInvExit, yInvExit, xExit, yExit;

	float EntryTime;
	float ExitTime;

	t = -1.0f;		//no collision
	nx = ny = 0;

	//
	// Board-phase test: kiểm tra main và object CÓ THỂ va chạm hay không?
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br <sl || bl>sr || bb<st || bt>sb) return;

	if (dx == 0 && dy == 0) return; // moving object is not moving > obvious no collision

	if (dx > 0)
	{
		xInvEntry = sl - mr;
		xInvExit = sr - ml;
	}
	else if (dx < 0)
	{
		xInvEntry = sr - ml;
		xInvExit = sl - mr;
	}

	if (dy > 0)
	{
		yInvEntry = st - mb;
		yInvExit = sb - mt;
	}
	else if (dy < 0)
	{
		yInvEntry = sb - mt;
		yInvExit = st - mb;
	}

	if (dx == 0)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / dx;
		xExit = xInvExit / dx;
	}

	if (dy == 0)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / dy;
		yExit = yInvExit / dy;
	}

	if ((xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f) return;

	EntryTime = max(xEntry, yEntry); //thời gian bắt đầu va chạm lớn nhất ( vì nếu thời gian lớn nhất sẽ thỏa điều kiện va chạm)
	ExitTime = min(xExit, yExit); //thời gian ngắn nhất khi 2 vật thể hết va chạm nhau

	if (EntryTime > ExitTime) return;

	t = EntryTime;

	if (xEntry > yEntry)
	{
		ny = 0.0f;
		nx = dx > 0 ? -1.0f : 1.0f;
	}
	else
	{
		nx = 0.0f;
		ny = dy > 0 ? -1.0f : 1.0f;
	}
}

void Entity::CalcPotentialCollisions(std::vector<Entity*>* coEntities, std::vector<LPCOLLISIONEVENT>& coEvents, float frameTime)
{
	for (UINT i = 0; i < coEntities->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coEntities->at(i), frameTime);

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void Entity::FilterCollision(std::vector<LPCOLLISIONEVENT>& coEvents, std::vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0)
		{
			min_tx = c->t; nx = c->nx; min_ix = i;
		}
		if (c->t < min_ty && c->ny != 0)
		{
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

bool Entity::checkAABB(Entity* ent)
{
	float l, t, r, b;
	float l1, t1, r1, b1;
	this->getBoundingBox(l, t, r, b);
	ent->getBoundingBox(l1, t1, r1, b1);

	if (checkAABB(l, t, r, b, l1, t1, r1, b1))
		return true;
	return false;
}

bool Entity::checkAABB(float b1left, float b1top, float b1right, float b1bottom, float b2left, float b2top, float b2right, float b2bottom)
{
	return !(b1right < b2left || b1left > b2right || b1top > b2bottom || b1bottom < b2top);
}

bool Entity::isCollitionObjectWithObject(Entity* ent, float frameTime)
{
	if (checkAABB(ent)) // kiểm tra va chạm bằng AABB trước
		return true;

	LPCOLLISIONEVENT e = SweptAABBEx(ent, frameTime); // kt va chạm giữa 2 object bằng sweptAABB
	bool res = e->t > 0 && e->t <= 1.0f; // ĐK va chạm
	safeDelete(e);
	return res;
}

CCollisionEvent::CCollisionEvent(float t, float nx, float ny, Entity* entity)
{
	this->t = t; this->nx = nx; this->ny = ny; this->entity = entity;
}
#pragma endregion
