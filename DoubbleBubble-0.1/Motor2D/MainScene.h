#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "Scene.h"
#include <vector>
#include "j1Render.h"

class GameObject;
class b2Fixture;
class Parallax;
class Player;
class Player2;
class ScrollManager;

class MainScene : public Scene 
{
public:
	MainScene();
	~MainScene();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void OnColl(PhysBody* bodyA, PhysBody* bodyB, b2Fixture* fixtureA, b2Fixture* fixtureB);
	void OnCommand(std::list<std::string>& tokens);
	
	void CreateMapCollisions(); 

	GameObject* go = nullptr;
	Parallax* p1 = nullptr;

	fPoint pos;

private:

	Player* player1 = nullptr; 
	Player* player2 = nullptr; 

	SDL_Texture* ring = nullptr; 
	SDL_Texture* obstacles = nullptr; 

	vector<PhysBody*>	map_collisions;

	ScrollManager* s_manager = nullptr; 
	
	uint w, h; 

};


#endif // !_MAINSCENE_H_