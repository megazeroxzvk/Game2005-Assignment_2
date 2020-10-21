#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Background.h"
#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Ship.h"
#include "Wookie.h"
#include "Label.h"
#include "Ramp.h"
#include "Lootbox.h"
#include "ThermalDetonator.h"
#include "StormTroopers.h"

static int slider_position;
static float slider_speed;
static float slider_angle;


class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	mutable bool m_locked;
	void lockOnTarget();
	
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	// Sprites
	Ramp* m_pRamp;
	Lootbox* m_pLootbox;
	//Wookie* m_pWookie;
	//ThermalDetonator* m_pThermalDetonator;
	//StormTroopers* m_pStormTroopers;
	//Plane* m_pPlaneSprite;
	//Player* m_pPlayer;
	//Ship* m_pShip;
	//bool m_playerFacingRight;
	

	// UI Items
	Button* m_pThrowButton;
	Button* m_pResetButton;
	Label* m_pInstructionsLabel;

	//Status Labels
	Label* m_pSpeedLabel;
	Label* m_pAngleLabel;
	Label* m_pTimeLabel;
	Label* m_pLandingPositionLabel;
	Label* m_pEnemyLocationLabel;
	Label* m_pDistanceLabel;

	

	// Background
	Background* m_pBackground;
};

#endif /* defined (__PLAY_SCENE__) */