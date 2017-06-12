#include "ScrollManager.h"
#include "j1Window.h"
#include "j1Render.h"

void ScrollManager::Start(SDL_Texture * texture, uint img_w, uint img_h, float time)
{

	pivot = iPoint(0, 0); 

	this->switch_time = time;
	this->texture = texture;

	texture_w = img_w; 
	texture_h = img_h; 

	int first_state = rand() % 4;
	current_state = static_cast<scroll_state> (first_state);

	switch_counter.Start(); 
	 
}

void ScrollManager::Update(float dt)
{

	if (switch_counter.ReadMs() > switch_time)
	{

		if(NeedToSwitch())
			UpdateState(); 

		switch (current_state)
		{

		case S_S_UP:
			pivot.y--;
			break;

		case S_S_DOWN:
			pivot.y++;
			break;

		case S_S_LEFT:
			pivot.x--;
			break;

		case S_S_RIGHT:
			pivot.x++;
			break;
		}

		switch_counter.Start(); 
	}


}

void ScrollManager::Draw() 
{	
	App->render->Blit(texture, pivot.x, pivot.y);
}

scroll_state ScrollManager::UpdateState()
{
	scroll_state state_ret = S_S_NULL;

	uint win_w, win_h; 
	App->win->GetWindowSize(win_w, win_h);

	bool assigned = false;

	while (assigned == false)
	{
		int random_state = rand() % 4; 
	
		switch (random_state)
		{
		case S_S_UP:

			if (pivot.y + texture_h > win_h)
			{
				current_state = S_S_UP;
				assigned = true; 
			}
				

			break;

		case S_S_DOWN:

			if (pivot.y < 0)
			{
				current_state = S_S_DOWN;
				assigned = true;
			}
				

			break;

		case S_S_LEFT:
			
			if (pivot.x + texture_w > win_w)
			{
				current_state = S_S_LEFT;
				assigned = true;
			}
				

			break;

		case S_S_RIGHT:

			if (pivot.x < 0)
			{
				current_state = S_S_RIGHT;
				assigned = true;
			}
				

			break;
		}
	}





	return state_ret;
}

bool ScrollManager::NeedToSwitch()
{
	bool ret = false; 

	uint win_w, win_h;
	App->win->GetWindowSize(win_w, win_h);

	if (pivot.x == 0 && pivot.y == 0)
		ret = true;

	else if (pivot.x == -(texture_w - (int)win_w) && pivot.y == 0)
		ret = true; 

	else if (pivot.x == 0 && pivot.y == -(texture_h - (int)win_h))
		ret = true;

	else if (pivot.x == -(texture_w - (int)win_w) && pivot.y == -(texture_h - (int)win_h))
		ret = true; 

	return ret;
}
