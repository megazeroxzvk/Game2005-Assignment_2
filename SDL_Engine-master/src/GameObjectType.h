#pragma once
#ifndef __GAME_OBJECT_TYPE__
#define __GAME_OBJECT_TYPE__
enum GameObjectType {
	NONE = -1,
	PLAYER,
	TARGET,
	SHIP,
	PLANE,
	START_BUTTON,
	RESTART_BUTTON,
	BACK_BUTTON,
	NEXT_BUTTON,
	NUM_OF_TYPES
};
#endif /* defined (__GAME_OBJECT_TYPE__) */