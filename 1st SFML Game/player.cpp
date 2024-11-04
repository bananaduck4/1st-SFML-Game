#include "player.h"
#include <iostream>

void Player::update(RenderWindow& wn)
{
	if (Mouse::isButtonPressed(Mouse::Right))
	{
		this->target_pos = new Vector2i(Mouse::getPosition(wn)); //Allocate a new Vector2i pointer pointing to a mouse position
	}

	if (this->target_pos)
	{
		Vector2f curr = this->getRect().getPosition(); //The curr player postion
		bool reach_dest = (abs(curr.x - this->target_pos->x) < 3) && (abs(curr.y - this->target_pos->y) < 3); //Check the player and the target pos is within 3 pixel of each other

		if (!reach_dest) //Keep moving if it hasn't reach its destination
		{
		this->move(*(this->target_pos));
		}

		else //if it has set it to a nullptr so that it doesn't try to keep moving
		{
			this->target_pos = nullptr;
		}
	}

	wn.draw(this->getRect());
}