#ifndef _PROJECTILEMANAGER_H_
#define _PROJECTILEMANAGER_H_

#include <vector>
#include "PugiXml\src\pugixml.hpp"
#include "p2Point.h"

#define MODULAR_PROJECTILE_VELOCITY 15

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

	iPoint		velocity = { 0,0 }; 
	iPoint		position = { 0,0 };

	Animator*	projectile_animation = nullptr;
};

class ProjectileManager
{
public:

	// Common Methods

	void Start();

	void Update(); 

	void CleanUp();

	// Utility Methods

	void CreateProjectile(parent who); 

	bool ProjectilesWindow();

private:

	vector<Projectile> projectile_list;

	pugi::xml_document docs;

	bool projectiles_on_screen = false; 

};

#endif
