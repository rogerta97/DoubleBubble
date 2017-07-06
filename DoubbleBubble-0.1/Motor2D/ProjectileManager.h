#ifndef _PROJECTILEMANAGER_H_
#define _PROJECTILEMANAGER_H_

#include <vector>
#include "PugiXml\src\pugixml.hpp"
#include "j1Textures.h"
#include "j1PerfTimer.h"
#include "p2Point.h"

#define MODULAR_PROJECTILE_VELOCITY 1.5f

class GameObject; 
class Animator; 


enum parent
{ 
	PARENT_P1, 
	PARENT_P2,
	PARENT_NULL,
};

struct Projectile
{
	GameObject* projectile = nullptr; 
	bool		active = false; 
	parent		parent = PARENT_NULL;

	fPoint		velocity = { 0,0 }; 
};

class ProjectileManager
{
public:

	// Common Methods

	void Start();

	void Update(float dt); 

	void CleanUp();

	// Utility Methods

	void ShotProjectile(parent who); 


private:

	pugi::xml_document doc;

	Projectile prefab_proj1;
	Projectile prefab_proj2;

	std::vector<Projectile> projectiles_on_screen;

	SDL_Texture* projectiles_texture = nullptr; 

	j1PerfTimer* bullets_update_timer; 


};

#endif
