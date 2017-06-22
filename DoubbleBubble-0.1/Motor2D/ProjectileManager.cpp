#include "ProjectileManager.h"
#include "j1Entity.h"
#include "Entity.h"
#include "GameObject.h"
#include <math.h>
#include "Player.h"

void ProjectileManager::Start()
{

	App->LoadXML("player.xml", doc);

}

void ProjectileManager::Update()
{


}

void ProjectileManager::CleanUp()
{
}

void ProjectileManager::CreateProjectile(parent who)
{
	Projectile new_projectile; 

	Player* player = (Player*)App->entity->GetEntity(PARENT_NULL);

	switch (who)
	{
	case PARENT_P1:
		player = (Player*)App->entity->GetEntity(PARENT_P1); 
		new_projectile.position = player->player_go->GetPos(); 
		new_projectile.active = true; 
		new_projectile.parent = PARENT_P1;
		
		new_projectile.velocity = iPoint((cos(player->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY), (sin(player->arrow.arrow_angle*(PI/180))*MODULAR_PROJECTILE_VELOCITY));

		new_projectile.projectile_animation = new Animator();

		new_projectile.projectile->LoadAnimationsFromXML(doc);
		new_projectile.projectile->SetAnimation("projectilep1");
		
		break;

	case PARENT_P2:
		player = (Player*)App->entity->GetEntity(PARENT_P2);
		break;

	case PARENT_NULL:
		break;
	}

	new_projectile.projectile = new GameObject(iPoint(0, 0), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_projectile, 0);


}

bool ProjectileManager::ProjectilesWindow()
{
	return projectiles_on_screen;
}
