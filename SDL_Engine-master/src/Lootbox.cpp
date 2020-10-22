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

	//simulation start
	if(startSimulation)
	{
		//Friction Surface	__
		if ( getTransform()->position.y  > 499.0f)
		{
			setAngle(0.00f);
			if(!m_reachedRampBase)
			{
				getRigidBody()->velocity.x = sqrt(2 * getRigidBody()->acceleration.y * m_rampHypotenuse);
				std::cout << "Ramp Distance = " << getDistanceTravelledRamp(m_initialPosition, getTransform()->position) << std::endl;
				std::cout << "Acceleration X = " << getRigidBody()->acceleration.x / SCALE  << std::endl;
				std::cout << "Acceleration Y = " << getRigidBody()->acceleration.y / SCALE  << std::endl;
				std::cout << "Velocity Y = " << getRigidBody()->velocity.y / SCALE  << std::endl;
				std::cout << "Velocity X = " << getRigidBody()->velocity.x / SCALE  << std::endl;
				m_rampBasePosition = getTransform()->position;
				m_reachedRampBase = true;
			}
			//friction 
			getRigidBody()->velocity.x += (-gravity.y * SCALE) * deltaTime * m_coefficient;
			getTransform()->position.x += getRigidBody()->velocity.x * deltaTime;
			
			if(getRigidBody()->velocity.x <= 0.0f)
			{
				std::cout << "Friction Distance Travelled = " << getDistanceTravelledFrictionSurface(m_rampBasePosition, getTransform()->position) << std::endl;
				startSimulation = false;
			}
			
		}
		else		//Frictionless Ramp 
		{
			getRigidBody()->velocity += (getRigidBody()->acceleration) * deltaTime;
			getTransform()->position += getRigidBody()->velocity * deltaTime;
			if(getTransform()->position.y > 550.0f - getHeight()*1.88f )
			{
				m_angle--;
			}
			/*std::cout << "velocity at ramp x = " << getRigidBody()->velocity.x / SCALE
				<< "velocity at ramp y = " << getRigidBody()->velocity.y / SCALE << std::endl;*/
		}
	}
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
	getTransform()->position.x = m_initialPosition.x = x;
	getTransform()->position.y = m_initialPosition.y = y;
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

float Lootbox::getDistanceTravelledRamp(glm::vec2 position1, glm::vec2 position2)
{
	float distance = sqrt((
		(position2.x - position1.x) * (position2.x - position1.x)) +
		(((position2.y + getHeight()) - (position1.y + getHeight())) * ((position2.y + getHeight()) - (position1.y + getHeight())))) / SCALE;
	
	//std::cout << "distance = " << distance << std::endl;
	return distance;
}

float Lootbox::getDistanceTravelledFrictionSurface(glm::vec2 position1, glm::vec2 position2)
{
	float distance = (position2.x - position1.x) / SCALE;

	//std::cout << "distance = " << distance << std::endl;
	return distance;
}

void Lootbox::setNecessaryValues(float angle,float hypotenuse)
{
	setAngle(angle);
	std::cout << "Angle = " << angle << std::endl;
	m_rampHypotenuse = hypotenuse;
	m_force.x = m_mass * gravity.y * (sin(Util::Deg2Rad * m_angle)) * SCALE;
	m_force.y = m_mass * gravity.y * (cos(Util::Deg2Rad * m_angle)) * SCALE;
	//********************* magical numbers ********************/
	setAcceleration({ (m_force.y / m_mass), (m_force.x / m_mass)});
}

void Lootbox::setMass(float mass)
{
	m_mass = mass;
}

float Lootbox::getMass()
{
	return m_mass;
}

void Lootbox::reset(float x, float y)
{
	setMass(12.8f);
	setPosition(x,y);
	setCoefficientOfFriction(0.42f);
	m_angle = 0.0f;
	getRigidBody()->velocity = { 0,0 };
	getRigidBody()->acceleration = { 0,0 };
	
}

void Lootbox::setCoefficientOfFriction(float val)
{
	m_coefficient = val;
}

float Lootbox::getCoefficientOfFriction()
{
	return m_coefficient;
}
