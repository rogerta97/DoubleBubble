#ifndef _PLAYER_
#define _PLAYER_

#include "Entity.h"
#include "ProjectileManager.h"
#include "j1Gui.h"

class GameObject;

struct PlayerArrow
{
	GameObject* go = nullptr;
	float arrow_angle = 0.0f;
	int quadrant = 0;
	bool straight = false;
};

class Player : public Entity
{
public:
	Player();
	~Player();

	// Load animations
	bool LoadEntity();

	// Start variables
	bool Start();

	// PreUpdate
	bool PreUpdate();

	// Update
	bool Update(float dt);

	// Draw and change animations
	bool Draw(float dt);

	// Post Update
	bool PostUpdate();

	// CleanUp
	bool CleanUp();

	// On Collision
	void OnColl(PhysBody* bodyA, PhysBody* bodyB, b2Fixture* fixtureA, b2Fixture* fixtureB);

	//Set Gamepad number to this player. id>0
	void SetGamePad(int id);

	//Set Camera to this player. 1<=id<=4
	void SetCamera(int id);

	void UpdateArrowPos(int quadrant, iPoint offset, bool straight);

public:
	GameObject* player_go = nullptr;

	PlayerArrow arrow; 

	ProjectileManager* proj_manager = nullptr; 

private:
	uint gamepad_num = 0;
	int camera = 1;

	char* color = "";

	//UI
	UI_Window* window = nullptr; 

};

#endif