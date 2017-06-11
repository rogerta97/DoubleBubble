#ifndef _SCROLLMANAGER_H_
#define _SCROLLMANAGER_H_

#include "p2List.h"
#include "j1App.h"
#include "j1Textures.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class ScrollManager
{
public:

	ScrollManager() {};

	void Start(SDL_Texture* texture, uint img_w, uint img_h); 
	void Update(); 

	~ScrollManager() {}; 

private:
	SDL_Texture* texture; 
	float speed = 0.0f; 

	iPoint pivot = NULLPOINT; 
};

#endif
