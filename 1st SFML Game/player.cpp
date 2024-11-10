#include "player.h"
#include <iostream>

/*
* @brief update the player movement and their abilities (dash, shoot, wall)
* @param wn: the window to draw the player on
*/
void Player::update(RenderWindow& wn, Clock game_timer)
{
	if (Mouse::isButtonPressed(Mouse::Right) && !this->dashing) //Move
	{
		this->target_pos = new Vector2i(Mouse::getPosition(wn)); //Allocate a new Vector2i pointer pointing to a mouse position
		this->speed = MOVING_SPEED;
	}

	if (Keyboard::isKeyPressed(Keyboard::E) && this->can_dash(game_timer)) //Dash
	{
		this->dashing = 1;
		this->dash_timer = game_timer.getElapsedTime();
		this->target_pos = new Vector2i(this->get_component(Mouse::getPosition(wn), DASH_DISTANCE)); //Allocate a new Vector2i pointer pointing to a mouse position
		this->speed = DASH_SPEED;
	}

	if (Keyboard::isKeyPressed(Keyboard::Q) && this->can_shoot(game_timer)) //Shoot
	{
		this->shoot_timer = game_timer.getElapsedTime();
		float angle = get_angle(this->object.getPosition(), Mouse::getPosition(wn));
		this->shoot(angle);
	}

	if (this->target_pos) //Check if player has reach target
	{
		Vector2f curr = this->object.getPosition(); //The curr player postion
		bool reach_dest = point_collide(curr, *(this->target_pos));

		if (!reach_dest) //Keep moving if it hasn't reach its destination
		{
			this->move(*(this->target_pos), this->speed);
		}

		else //if it has set it to a nullptr so that it doesn't try to keep moving
		{
			this->target_pos = nullptr;
			this->speed = MOVING_SPEED;
			this->dashing = 0;
		}
	}
	wn.draw(this->object);

	//Update player bullets
	for (auto b = this->bullets.begin(); b != this->bullets.end();)
	{
		if (b->is_dead()) { b = this->bullets.erase(b); } //Remove if bullet is not alive
		else 
		{ 
			b->update(wn);
			++b; 
		}
	}
}

/*
* @brief Player's shoot ability
* @param angle: the angle of the bullet in radians
*/
void Player::shoot(float angle) //Create a new bullet and add it to player list
{
	Bullet bullet = Bullet(*this, angle);
	bullet.set_target();//Set the bullet target_destination

	this->bullets.push_back(bullet);
}

bool Player::can_shoot(Clock game_timer)
{
	return game_timer.getElapsedTime() - shoot_timer >= SHOOT_CD;
}

bool Player::can_dash(Clock game_timer)
{
	return game_timer.getElapsedTime() - dash_timer >= DASH_CD;
}
