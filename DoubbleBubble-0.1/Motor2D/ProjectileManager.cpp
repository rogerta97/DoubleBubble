#include "ProjectileManager.h"
#include "j1Entity.h"
#include "Entity.h"
#include "j1Input.h"
#include "j1Viewports.h"
#include "GameObject.h"
#include <math.h>
#include "Player.h"

void ProjectileManager::Start()
{

	App->LoadXML("player.xml", doc);

	CreateProjectile(PARENT_P1); 
	//CreateProjectile(PARENT_P2);

	projectiles_texture = App->tex->LoadTexture("textures/players_spritesheet.png");

	//prefab_proj2.projectile->animator->LoadAnimationsFromXML(doc);
	//prefab_proj2.projectile->animator->SetAnimation("projectilep2");

}

void ProjectileManager::Update(float dt)
{

	//First we add new projectiles if there are

	for (int i = 0; i < 2; i++)
	{
		if (App->input->GetControllerButton(i, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == KEY_DOWN)
		{
			ShotProjectile((parent)i);
		}
	}

	//We update the rest

	for (vector<Projectile>::iterator it = projectiles_on_screen.begin(); it != projectiles_on_screen.end(); it++)
	{
		(*it).projectile->SetPos({ (float)(*it).projectile->GetPos().x + ((*it).velocity.x*0.05f),  (float)(*it).projectile->GetPos().y + ((*it).velocity.y*0.05f)});
		App->view->LayerBlit(3, (*it).projectile->GetTexture(), (*it).projectile->GetPos(), (*it).projectile->GetCurrentAnimationRect(dt)); 
	}


}

void ProjectileManager::CleanUp()
{
}

void ProjectileManager::CreateProjectile(parent who)
{

	/*Player* player_entity = (Player*)App->entity->GetEntity(PARENT_NULL);

	switch (who)
	{
	case PARENT_P1:


		prefab_proj1.projectile = new GameObject(iPoint(0, 0), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_projectile, 0);

		player_entity = (Player*)App->entity->GetEntity(PARENT_P1);
		prefab_proj1.projectile->SetPos({0,0});
		prefab_proj1.active = false; 
		prefab_proj1.parent = PARENT_P1;
		
		prefab_proj1.velocity = { 0,0 };

		prefab_proj1.projectile->SetTexture(projectiles_texture);
		
		break;

	case PARENT_P2:


		prefab_proj2.projectile = new GameObject(iPoint(0, 0), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_projectile, 0);

		player_entity = (Player*)App->entity->GetEntity(PARENT_P2);
		prefab_proj2.projectile->SetPos({0,0});
		prefab_proj2.active = false;
		prefab_proj2.parent = PARENT_P2;

		prefab_proj2.velocity = { 0,0 };

		prefab_proj2.projectile->SetTexture(projectiles_texture);

		break;

	case PARENT_NULL:
		break;
	}*/

}

void ProjectileManager::ShotProjectile(parent who)
{

	Player* player_entity = (Player*)App->entity->GetEntity(PARENT_NULL);

	Projectile new_projectile; 

	switch (who)
	{
	case PARENT_P1:

		player_entity = (Player*)App->entity->GetEntity(PARENT_P1);

		new_projectile.projectile = new GameObject(iPoint(0, 0), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_projectile, 0);

		new_projectile.active = true;
		new_projectile.parent = PARENT_P1;

		new_projectile.projectile->SetPos({ (float)player_entity->player_go->GetPos().x - 15, (float)player_entity->player_go->GetPos().y - 27 });

		switch (player_entity->arrow.quadrant)
		{
		case 1:
			new_projectile.velocity = iPoint((cos(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY), -(sin(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY));
			break;

		case 2:
			new_projectile.velocity = iPoint(-(cos(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY), (sin(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY));
			break; 

		case 3: 
			new_projectile.velocity = iPoint(-(cos(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY), -(sin(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY));
			break; 

		case 4:
			new_projectile.velocity = iPoint((cos(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY), (sin(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY));
			break; 
		}
		

		new_projectile.projectile->SetTexture(projectiles_texture);

		new_projectile.projectile->animator->LoadAnimationsFromXML(doc);
		new_projectile.projectile->animator->SetAnimation("projectilep1");
		
		projectiles_on_screen.push_back(new_projectile);

		break;

	case PARENT_P2:


	
		//prefab_proj2.velocity = iPoint((cos(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY), (sin(player_entity->arrow.arrow_angle*(PI / 180))*MODULAR_PROJECTILE_VELOCITY));

		break;

	case PARENT_NULL:
		break;
	}
}
