#include "EnemyManager.h"

void EnemyManager::update(RenderWindow& wn, Time game_time)
{
	if (this->enemy_spawn.is_up(game_time) && this->enemies.size() < this->max) //Create an Enemy is store it in its vector after a certain time (capped at max)
	{
		Enemy enemy(spawn(this->player));
		this->enemies.push_back(enemy);
	}

	for (auto e = this->enemies.begin(); e != this->enemies.end();) //Chec for player collision and bullet collsion for each enemy on screen
	{
		if (e->collided_with(this->player)) { this->player.kill(); } //Kill player if enemy collide with it

		auto& player_bullets = this->player.get_bullets();
		if (e->is_dead(player_bullets)) { e = this->enemies.erase(e); } //Kill enenemy and remove bullet if they collide
		else
		{
			e->update(wn, this->player);
			++e;
		}
	}
}