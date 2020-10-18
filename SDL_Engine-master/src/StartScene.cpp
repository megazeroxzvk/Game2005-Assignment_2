#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{

	m_pBackground = new Background("../Assets/textures/start_screen.png", "background_startscene");
	addChild(m_pBackground);
	const SDL_Color white = { 255, 255, 255, 255 };
	/*m_pStartLabel = new Label("START SCENE", "Consolas", 80, white, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);*/

	m_pAngryWookie = new Label("angry wookie", "starwars", 80, white, glm::vec2(400.0f, 40.0f));
	m_pAngryWookie->setParent(this);
	addChild(m_pAngryWookie);

	m_pTeamMember1 = new Label("Vineet Kumar - 101273532", "Consolas", 40, white, glm::vec2(300.0f, 140.0f));
	m_pTeamMember1->setParent(this);
	addChild(m_pTeamMember1);

	m_pTeamMember2 = new Label("Raquel Andre Da Costa - 101247804", "Consolas", 40, white, glm::vec2(400.0f, 180.0f));
	m_pTeamMember2->setParent(this);
	addChild(m_pTeamMember2);

	/*m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, white, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);*/

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 500.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

