#ifndef _SCROLLMANAGER_H_
#define _SCROLLMANAGER_H_

#include "p2List.h"
#include "j1App.h"
#include "j1Textures.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

enum scroll_state
{
	S_S_UP,
	S_S_DOWN,
	S_S_LEFT,
	S_S_RIGHT,

	S_S_NULL
};

class ScrollManager
{
public:

	ScrollManager() {};

	void Start(SDL_Texture* texture, uint img_w, uint , float speed); 
	void Update(float dt); 
	void Draw(); 

	scroll_state UpdateState(); 
	bool		 NeedToSwitch(); 

	~ScrollManager() {}; 

private:

	SDL_Texture*		texture; 
	int					texture_w = -1; 
	int					texture_h = -1; 

	int					switch_time = 5; 
	j1PerfTimer			switch_counter; 

	iPoint				pivot = NULLPOINT; 
	scroll_state	    current_state = S_S_NULL; 
};

#endif
