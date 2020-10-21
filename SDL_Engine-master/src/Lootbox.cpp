#include "Lootbox.h"

#include "Renderer.h"
#include "TextureManager.h"
#include "Util.h"

Lootbox::Lootbox()
{
	TextureManager::Instance()->load(
		"../Assets/sprites/owlootbox.png", "lootbox");

	//const auto size = TextureManager::Instance()->getTextureSize("lootbox");

	setWidth(50);
	setHeight(50);

	getTransform()->position.x = 50.0f;
	getTransform()->position.y = 50.0f;
	m_angle = 0;
	setType(PLAYER);
	
}

Lootbox::~Lootbox()
{
	
}

void Lootbox::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	SDL_Rect srcRect;
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 180;
	srcRect.h = 180;

	destRect.x = x;
	destRect.y = y;
	destRect.w = getWidth();
	destRect.h = getHeight();

	//std::cout << "Position of lootBox = " <<x << ", " << y << std::endl;
	
	// draw
	//TextureManager::Instance()->draw("lootbox", x, y, m_angle, 255, false,SDL_FLIP_NONE);
	SDL_RenderCopyEx(Renderer::Instance()->getRenderer(), TextureManager::Instance()->getTexture("lootbox"), &srcRect, &destRect, m_angle, &bottomLeft, SDL_FLIP_NONE);
}

void Lootbox::update()
{
	bottomLeft = { 0, destRect.h };
	bottomRight = { destRect.w, destRect.h };
	//getRigidBody()->velocity += 2.0f;
	//getTransform()->position += getRigidBody()->velocity * deltaTime;
	//std::cout << "Update - Position of lootBox = " << getTransform()->position.x << ", " << getTransform()->position.y << std::endl;
	glm::vec2 direction = { sin(Util::Deg2Rad *m_angle) , cos(Util::Deg2Rad* m_angle) };
	getRigidBody()->velocity += (getRigidBody()->acceleration) * deltaTime;
	//getRigidBody()->velocity *= direction;
	getTransform()->position += getRigidBody()->velocity * deltaTime;
	
	//std::cout << "Update - Position of lootBox = " << getTransform()->position.x << ", " << getTransform()->position.y << std::endl;
	std::cout << "v y = " << getRigidBody()->velocity.y << std::endl;
	std::cout << "v x = " << getRigidBody()->velocity.x << std::endl;

}

void Lootbox::clean()
{
}

glm::vec2 Lootbox::getPosition()
{
	return getTransform()->position;
}

void Lootbox::setPosition(float x, float y)
{
	getTransform()->position.x = x;
	getTransform()->position.y = y;
}


float Lootbox::getAngle()
{
	return m_angle;
}

void Lootbox::setAngle(float angle)
{
	m_angle = angle;
}


void Lootbox::setAcceleration(glm::vec2 acc)
{
	getRigidBody()->acceleration.x = acc.x;
	getRigidBody()->acceleration.y = acc.y;
//	std::cout << "Acc = " << getRigidBody()->acceleration.y << std::endl;
}