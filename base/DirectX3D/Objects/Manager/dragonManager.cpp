#include "Framework.h"
#include "dragonManager.h"

dragonManager::dragonManager()
{
	alduin = new ModelAnimator("alduin");
	alduin->Scale() *= 0.01;

	alduin->ReadClip("alduin_idle");
	alduin->ReadClip("alduin_bleedidle");
	alduin->ReadClip("alduin_takeoff");
	alduin->ReadClip("alduin_fly");
	alduin->ReadClip("alduin_hover");
	alduin->ReadClip("alduin_flight_forward");
	alduin->ReadClip("alduin_flight_hit");
	alduin->ReadClip("alduin_ascend");
	alduin->ReadClip("alduin_climb");
	alduin->ReadClip("alduin_aproach");
	alduin->ReadClip("alduin_descend");
	alduin->ReadClip("alduin_backward");
	alduin->ReadClip("alduin_injured");
	alduin->ReadClip("alduin_inhale");
	alduin->ReadClip("alduin_exhale_breath");
	alduin->ReadClip("alduin_exhale_fireball");
	alduin->ReadClip("alduin_wingswip_left");
	alduin->ReadClip("alduin_wingswip_right");
	alduin->ReadClip("alduin_bite");
	alduin->ReadClip("alduin_pain");
	alduin->ReadClip("alduin_pain2");
	alduin->ReadClip("alduin_tailwhip");
	alduin->ReadClip("alduin_timetravel");

	hp = 3000.0f;
	moveSpeed = 50.0f;



}

dragonManager::~dragonManager()
{
	delete alduin;


}

void dragonManager::Update()
{
}

void dragonManager::Render()
{
}

void dragonManager::PostRender()
{
}
