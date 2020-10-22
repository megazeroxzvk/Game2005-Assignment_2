#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include <math.h>  

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScene::update()
{
	updateDisplayList();
	/*std::cout << "Distance Covered = " << m_pThermalDetonator->getDistance() << std::endl;
	std::cout << "Time = " << m_pThermalDetonator->getTime() << std::endl;*/
	/*m_pSpeedLabel->setText("Y Velocity = " + std::to_string(fabs(m_pThermalDetonator->getRigidBody()->velocity.y)) + " m");
	m_pAngleLabel->setText("Angle = " + std::to_string(m_pThermalDetonator->getAngle()) + " deg");
	m_pTimeLabel->setText("Time = " + std::to_string(m_pThermalDetonator->getTime()) + " sec");
	m_pDistanceLabel->setText("Distance = " + std::to_string(m_pThermalDetonator->getDistance()) + " m");
	m_pEnemyLocationLabel->setText("Enemy Location(x) = " + std::to_string(m_pStormTroopers->getTransform()->position.x));
	m_pLandingPositionLabel->setText("Landing Location(x) = " + std::to_string(m_pThermalDetonator->getLandingLocation()));*/
	//
	//std::cout << "height of lootbox= " << m_pLootbox->getHeight() << std::endl;
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	/*if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}*/


	// handle player movement if no Game Controllers found
	/*if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
	}
	*/

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	//if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	//{
	//	TheGame::Instance()->changeSceneState(START_SCENE);
	//}

	//if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	//{
	//	TheGame::Instance()->changeSceneState(END_SCENE);
	//}
}

void PlayScene::start()
{
	//Set Background Tatooine
	m_pBackground = new Background("../Assets/textures/owbkg.jpg","background_playscene");
	addChild(m_pBackground);
	
	// Set GUI Title
	m_guiTitle = "Play Scene";

	//Ramp
	m_pRamp = new Ramp();
	addChild(m_pRamp);

	//Lootbox
	m_pLootbox = new Lootbox();
	addChild(m_pLootbox);
	m_pLootbox->setPosition(m_pRamp->getPositionTop1().x, m_pRamp->getPositionTop1().y - m_pLootbox->getHeight());
	//m_pLootbox->setAcceleration({ 7.8400 * SCALE , 5.8799 * SCALE });
	
	//Wookie
	/*m_pWookie = new Wookie();
	addChild(m_pWookie);*/

	//Stormtroopers
	/*m_pStormTroopers = new StormTroopers();
	addChild(m_pStormTroopers);*/

	//Thermal Detonator
	/*m_pThermalDetonator = new ThermalDetonator();
	m_pThermalDetonator->setAngle(15.88963282f);
	m_pThermalDetonator->setSpeed(95.0f);
	addChild(m_pThermalDetonator);*/
	
	// Plane Sprite
	/*m_pPlaneSprite = new Plane();
	addChild(m_pPlaneSprite);*/

	// Player Sprite
	/*m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;*/

	// Ship Sprite
	/*m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pShip);*/

	// Throw Button
	m_pThrowButton = new Button("../Assets/textures/throwbutton.png", "throwbutton", BACK_BUTTON);
	m_pThrowButton->getTransform()->position = glm::vec2(700.0f, 150.0f);
	m_pThrowButton->addEventListener(CLICK, [&]()-> void
	{
		m_pThrowButton->setActive(false);
		m_pRamp->setNecessaryValues();
		m_pLootbox->setNecessaryValues(m_pRamp->m_getAngle(),m_pRamp->m_getHypotenuse());
		m_pLootbox->startSimulation = true;
		//std::cout << m_pLootbox->getMass()<< std::endl;
		//TheGame::Instance()->changeSceneState(START_SCENE);
		//m_pThermalDetonator->m_kickoff = true;
		//m_pThermalDetonator->setPosition(m_pThermalDetonator->getResetPositon());
		//m_pThermalDetonator->setAngle(m_pThermalDetonator->getAngle());
		//m_pThermalDetonator->setSpeed(m_pThermalDetonator->getSpeed());	
	});

	m_pThrowButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pThrowButton->setAlpha(128);
	});

	m_pThrowButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pThrowButton->setAlpha(255);
	});
	addChild(m_pThrowButton);

	// Reset Button
	m_pResetButton = new Button("../Assets/textures/resetbutton.png", "resetbutton", NEXT_BUTTON);
	m_pResetButton->getTransform()->position = glm::vec2(700.0f, 210.0f);
	m_pResetButton->addEventListener(CLICK, [&]()-> void
	{
		m_pResetButton->setActive(false);
		m_pLootbox->startSimulation = false;
		m_pRamp->reset();
		m_pLootbox->reset(m_pRamp->getPositionTop1().x, m_pRamp->getPositionTop1().y - m_pLootbox->getHeight());
		//TheGame::Instance()->changeSceneState(END_SCENE);
		/*m_pThermalDetonator->m_kickoff = false;
		m_pThermalDetonator->setAngle(m_pThermalDetonator->getResetAngle());
		m_pThermalDetonator->setPosition(m_pThermalDetonator->getResetPositon());
		m_pThermalDetonator->setSpeed(m_pThermalDetonator->getResetSpeed());
		m_pStormTroopers->getTransform()->position.x = m_pStormTroopers->getResetPosition();*/
		
	});

	m_pResetButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pResetButton->setAlpha(128);
	});

	m_pResetButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pResetButton->setAlpha(255);
	});

	addChild(m_pResetButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) for Physics Simulation Control", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 575.0f);
	addChild(m_pInstructionsLabel);

	m_pSpeedLabel = new Label("", "digi",20,{0,0,0,255});
	m_pSpeedLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.55f, 30.0f);
	addChild(m_pSpeedLabel);

	m_pAngleLabel = new Label("", "digi", 20, { 0,0,0,255 });
	m_pAngleLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.85f, 30.0f);
	addChild(m_pAngleLabel);

	m_pTimeLabel = new Label("", "digi", 20, { 0,0,0,255 });
	m_pTimeLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.55f, 60.0f);
	addChild(m_pTimeLabel);

	m_pLandingPositionLabel = new Label("", "digi", 20, { 150,0,0,255 });
	m_pLandingPositionLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.85f, 60.0f);
	addChild(m_pLandingPositionLabel);

	m_pEnemyLocationLabel = new Label("", "digi", 20, { 0,0,0,255 });
	m_pEnemyLocationLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.85f, 90.0f);
	addChild(m_pEnemyLocationLabel);

	m_pDistanceLabel = new Label("", "digi", 20, { 0,0,0,255 });
	m_pDistanceLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.55f, 90.0f);
	addChild(m_pDistanceLabel);
}

void PlayScene::lockOnTarget()
{

	
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Physics Simulation Modifiers", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	//if(ImGui::Button("My Button"))
	//{
	//	std::cout << "My Button Pressed" << std::endl;
	//}

	//ImGui::Separator();

	//Lock
	/*static bool lockOnTarget;
	if(ImGui::Checkbox("Lock (first set angle!)",&lockOnTarget))
	{
		m_locked = lockOnTarget;
	}*/
	
	
	//slider_position = (int)m_pStormTroopers->getTransform()->position.x;
	//if (ImGui::SliderInt("Enemy Location", &slider_position, 200.0f, 725.0f))
	//{
	//	m_pStormTroopers->getTransform()->position.x = slider_position;
	//}

	/*slider_speed = m_pThermalDetonator->getSpeed();
	if (ImGui::SliderFloat("Velocity", &slider_speed, 50.0f, 500.0f))
	{
		m_pThermalDetonator->setSpeed(slider_speed);
	}*/

	//if(!m_locked)
	//{
		/*slider_angle = m_pThermalDetonator->getAngle();
		if (ImGui::SliderFloat("Angle", &slider_angle, 1.0f, 89.9f))
		{
			m_pThermalDetonator->setAngle(slider_angle);
		}*/
	/*}*/
	
	/*static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}*/

	static float width = { 4.0f};
	if (ImGui::SliderFloat("Ramp Width (in meters)", &width, 4.0f, 15.0f))
	{
		m_pRamp->setPositionBase2({ m_pRamp->getPositionBase1().x + (width * SCALE),m_pRamp->getPositionBase2().y });
		m_pLootbox->startSimulation = false;
		m_pLootbox->reset(m_pRamp->getPositionTop1().x, m_pRamp->getPositionTop1().y - m_pLootbox->getHeight());
	}

	static float height = { 3.0f };
	if (ImGui::SliderFloat("Ramp Height (in meters)", &height, 3.0f, 15.0f))
	{
		m_pRamp->setPositionTop1({ m_pRamp->getPositionTop1().x, m_pRamp->getPositionBase1().y - (height * SCALE) });
		m_pLootbox->startSimulation = false;
		m_pLootbox->reset(m_pRamp->getPositionTop1().x, m_pRamp->getPositionTop1().y - m_pLootbox->getHeight());
	}

	static float mass = { 12.8f };
	if (ImGui::SliderFloat("Mass (in Kilograms)", &mass, 10.0f, 20.0f))
	{
		m_pLootbox->startSimulation = false;
		m_pLootbox->reset(m_pRamp->getPositionTop1().x, m_pRamp->getPositionTop1().y - m_pLootbox->getHeight());
	}

	static float coefficient = { 0.42 };
	if (ImGui::SliderFloat("Coefficient of Friction", &coefficient, 0.05f, 4.0f))
	{
		m_pLootbox->setCoefficientOfFriction(coefficient);
	}

	if(reset)
	{
		width = 4.0f;
		height = 3.0f;
		mass = 12.8f;
		reset = false;
	}
	ImGui::End();
	ImGui::EndFrame();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
