#include "Player.h"
#include "GameObject.h"
#include "Scene.h"
#include "j1App.h"
#include "j1Input.h"
#include "CollisionFilters.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "MainScene.h"
#include "Functions.h"
#include "j1Textures.h"
#include "p2Log.h"
#include "j1Viewports.h"

#define BALL_RADIUS 19


Player::Player()
{
}

Player::~Player()
{
}

bool Player::LoadEntity()
{
	bool ret = true;

	// Create the player 

	player_go = new GameObject(iPoint(0,0), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_player, 0);

	player_go->CreateCollision(iPoint(-11,-23), 25, 25, fixture_type::f_t_null);
	player_go->SetListener((j1Module*)App->entity);
	player_go->SetFixedRotation(true);

	player_go->SetTexture(App->tex->LoadTexture("textures/players_spritesheet.png"));

	// Create the arrow

	direction_arrow = new GameObject(iPoint(0, 0), App->cf->CATEGORY_PLAYER, App->cf->MASK_PLAYER, pbody_type::p_t_player, 0); 

	pugi::xml_document doc;
	App->LoadXML("player.xml", doc);

	player_go->LoadAnimationsFromXML(doc);
	player_go->SetAnimation("idlep1");

	direction_arrow->LoadAnimationsFromXML(doc); 
	direction_arrow->SetAnimation("arrowp1");

	return ret;
}

bool Player::Start()
{
	bool ret = true;

	window = App->gui->UI_CreateWin({0, 0}, App->scene->main_scene->win_w, App->scene->main_scene->win_h);

	

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

	iPoint center_offset = {0, 18};


	// Controlls for the left joystick 

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

	//---

	// Controlls for the arrow 

	if (App->input->GetControllerJoystickMove(gamepad_num, RIGHTJOY_RIGHT) > 12000)
	{
		direction_arrow->SetPos({ (float)player_go->GetPos().x + BALL_RADIUS, (float)player_go->GetPos().y + center_offset.y});
		arrow_angle = 90.0f;

		if (App->input->GetControllerJoystickMove(gamepad_num, RIGHTJOY_UP) > 5000)
		{
			arrow_angle = App->input->GetJoystickAngle(0, RIGHTJOY_RIGHT_UP);
			direction_arrow->SetPos({ player_go->fGetPos().x + cos(angle*(PI / 180)), player_go->fGetPos().y - sin(angle*(PI / 180)) });

		}
	}

	if (App->input->GetControllerJoystickMove(gamepad_num, RIGHTJOY_LEFT) > 12000)
	{
		direction_arrow->SetPos({ (float)player_go->GetPos().x - BALL_RADIUS, (float)player_go->GetPos().y + center_offset.y });
		arrow_angle = -90.0f;
	}

	if (App->input->GetControllerJoystickMove(gamepad_num, RIGHTJOY_UP) > 12000)
	{
		direction_arrow->SetPos({ (float)player_go->GetPos().x , (float)player_go->GetPos().y + center_offset.y - BALL_RADIUS });
		arrow_angle = 0.0f;
	}

	if (App->input->GetControllerJoystickMove(gamepad_num, RIGHTJOY_DOWN) > 12000)
	{
		direction_arrow->SetPos({ (float)player_go->GetPos().x , (float)player_go->GetPos().y + center_offset.y + BALL_RADIUS });
		arrow_angle = 180.0f;
	}

	return ret;
}

bool Player::Draw(float dt)
{
	bool ret = true;

	App->view->LayerBlit(2, player_go->GetTexture(), { player_go->GetPos().x - 23, player_go->GetPos().y - 35 }, player_go->GetCurrentAnimationRect(dt));

	App->view->LayerBlit(2, player_go->GetTexture(), { direction_arrow->GetPos().x - 16, direction_arrow->GetPos().y - 45}, direction_arrow->GetCurrentAnimationRect(dt), 0, 2.0, SDL_FLIP_NONE, arrow_angle);

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

void Player::SetArrowPos(float angle, int radius, int quadrant, float dt)
{

	float speed = (200 * dt); 

	switch (quadrant)
	{
	case 0:

		direction_arrow->SetPos({ player_go->fGetPos().x - speed*cos(angle*(PI / 180)), player_go->fGetPos().y - speed *sin(angle*(PI / 180)) });

		break;

	case 1:
		break; 

	case 2:
		break;

	case 3:
		break;
	}

}
