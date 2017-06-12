#ifndef _PLAYER_
#define _PLAYER_

#include "Entity.h"
#include "j1Gui.h"

class GameObject;
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

	// Set the position of the arrow 
	void SetArrowPos(float angle, int radius, int quadrant, float dt); 

public:
	GameObject* player_go = nullptr;

	GameObject* direction_arrow = nullptr; 

private:
	uint gamepad_num = 0;
	int camera = 1;

	char* color = "";

	//UI
	UI_Window* window = nullptr; 

};

#endif