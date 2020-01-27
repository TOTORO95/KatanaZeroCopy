#pragma once
#ifndef __ENUM_H__

enum OBJ_TYPE
{
	BACKGROUND,
	TERRAIN,
	TILE,
	DOOR,
	AFTERIMAGE,
	BULLETTIME,
	MONSTER,
	PLAYER,
	BOSS,
	BLOOD,
	EXPLOSION,
	TRAP,
	BULLET,
	FLAT,
	FG,
	BUTTON,
	UI,
	OBJ_END

};
enum OBJ_STATE
{
	STATE_IDLE,
	STATE_RUN,
	STATE_JUMP,
	STATE_ROLL,
	STATE_FALL,
	STATE_ATTACK,
	STATE_WALLJUMP,
	STATE_WALLGRIP,
	STATE_KNOCKBACK,
	STATE_MELEE,
	STATE_AIMING,
	STATE_WALK,
	STATE_DEAD,
	STATE_IN_DOOR,
	STATE_EXIT_DOOR,
	STATE_TELEPORT_VERTICAL_LASER,
	STATE_TELEPORT_HORIZON_LASER,
	STATE_TELEPORT_SWIP_LASER,
	STATE_LASER_SHOT,
	STATE_DASH_READY,
	STATE_DASH_ATTACK,
	STATE_TAKEOUT_LASERGUN,
	STATE_PUTBACK_LASERGUN,
	STATE_DASH_END,
	STATE_END,
};
enum SCENE_TYPE
{
	SCENE_LOGO,
	SCENE_EDIT,
	SCENE_TITLE,
	SCENE_STAGE1,
	SCENE_STAGE2,
	SCENE_BOSS1,
	SCENE_BOSS2,
	SCENE_END

};
enum OBJ_DIRECTION
{
	OBJ_LEFT,
	OBJ_RIGHT,
	OBJ_IDLE,
	DIRECTION_END
};
enum BULLET_TAG
{
	MONSTER_BULLET,
	PLAYER_BULLET,
	BULLET_END
};
enum MONSTER_TYPE
{
	GRUNT,
	GUNSTER,
	POMP,
	HEADHUNTER,
	MONSTER_END

};
#define __ENUM_H__
#endif // !__ENUM_H__
