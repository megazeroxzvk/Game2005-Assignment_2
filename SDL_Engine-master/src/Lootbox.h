#pragma once
#ifndef __LOOTBOX__
#define __LOOTBOX__

#include "Sprite.h"

class Lootbox : public Sprite
{
public:
	Lootbox();
	~Lootbox();
	
	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	glm::vec2 getPosition();
	float getAngle();
	
	void setPosition(float x, float y);
	void setAngle(float angle);
	void setAcceleration(glm::vec2 acc);
	
private:
	float m_angle;
	SDL_Point bottomLeft = { 0, 0 };
	SDL_Point bottomRight = { 0,0 };
	SDL_Rect destRect;

	float m_mass = 12.8f;
	float m_force = 75.2638f;
	
};

#endif /* defined (__LOOTBOX__) */
