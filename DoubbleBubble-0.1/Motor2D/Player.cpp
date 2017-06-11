#include "Player.h"
#include "GameObject.h"
#include "Scene.h"
#include "j1App.h"
#include "j1Input.h"
#include "CollisionFilters.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "Functions.h"
#include "j1Textures.h"
#include "p2Log.h"
#include "j1Viewports.h"


Player::Player()
{
}

Player::~Player()
{
}

bool Player::LoadEntity()
{
	bool ret = true;

	player_go = new GameObject(iPoint(50, 50), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_player, 0);

	player_go->CreateCollision(iPoint(0, 0), 25, 25, fixture_type::f_t_null);
	player_go->SetListener((j1Module*)App->entity);
	player_go->SetFixedRotation(true);

	player_go->SetTexture(App->tex->LoadTexture("textures/players_spritesheet.png"));

	pugi::xml_document doc;
	App->LoadXML("player.xml", doc);
	player_go->LoadAnimationsFromXML(doc);

	player_go->SetAnimation("idlep1");

	return ret;
}

bool Player::Start()
{
	bool ret = true;



	return ret;
}

bool Player::PreUpdate()
{
	bool ret = true;



	return ret;
}

bool Player::Update(float dt)
{
	bool ret = true;

	float speed = (200 * dt);
	float angle = 0.0f; 


	if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_LEFT) > 12000)
	{

		if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_UP) > 5000)
		{	
			angle = App->input->GetJoystickAngle(0, LEFTJOY_LEFT_UP); 

			player_go->SetPos({ player_go->fGetPos().x - speed*cos(angle*(PI/ 180)), player_go->fGetPos().y - speed *sin(angle*(PI / 180))});
		}

		else if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_DOWN) > 5000)
		{
			angle = App->input->GetJoystickAngle(0, LEFTJOY_LEFT_DOWN);

			player_go->SetPos({ player_go->fGetPos().x - speed*cos(angle*(PI / 180)), player_go->fGetPos().y + speed *sin(angle*(PI / 180)) });
		}

	
		else
		player_go->SetPos({ player_go->fGetPos().x - speed, player_go->fGetPos().y });

	}
	else if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_RIGHT) > 12000)
	{
		if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_UP) > 5000)
		{
			angle = App->input->GetJoystickAngle(0, LEFTJOY_RIGHT_UP);

			player_go->SetPos({ player_go->fGetPos().x + speed*cos(angle*(PI / 180)), player_go->fGetPos().y - speed *sin(angle*(PI / 180)) });
		}

		else if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_DOWN) > 5000)
		{
			angle = App->input->GetJoystickAngle(0, LEFTJOY_RIGHT_DOWN);

			player_go->SetPos({ player_go->fGetPos().x + speed*cos(angle*(PI / 180)), player_go->fGetPos().y + speed *sin(angle*(PI / 180)) });
		}

		else
		player_go->SetPos({ player_go->fGetPos().x + speed, player_go->fGetPos().y });

	}
	else if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_UP) > 12000)
	{
	
		player_go->SetPos({ player_go->fGetPos().x, player_go->fGetPos().y - speed });

	}
	else if (App->input->GetControllerJoystickMove(gamepad_num, LEFTJOY_DOWN) > 12000)
	{
		
		player_go->SetPos({ player_go->fGetPos().x, player_go->fGetPos().y + speed });
	}

	return ret;
}

bool Player::Draw(float dt)
{
	bool ret = true;

	App->render->Blit(player_go->GetTexture(), player_go->GetPos().x - 23, player_go->GetPos().y - 35, &player_go->GetCurrentAnimationRect(dt));

	return ret;
}

bool Player::PostUpdate()
{
	bool ret = true;



	return ret;
}

bool Player::CleanUp()
{
	bool ret = true;



	return ret;
}

void Player::OnColl(PhysBody* bodyA, PhysBody * bodyB, b2Fixture * fixtureA, b2Fixture * fixtureB)
{
	switch (bodyA->type)
	{
	case pbody_type::p_t_player:
		if (bodyB->type == pbody_type::p_t_world)
		{
		}
		break;
	
	}
}

void Player::SetGamePad(int id)
{
	gamepad_num = id-1;
}

void Player::SetCamera(int id)
{
	if (id > 0 && id < 5)
	{
		camera = id;
	}
}
