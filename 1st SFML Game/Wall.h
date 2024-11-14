#pragma once
#include "entity.h"

const Time WALL_LIFESPAN = seconds(3);
const int WALL_SPEED = 2;
const int MAX_WALL_DISTANCE = 50;
const Vector2f WALL_SIZE = Vector2f(40, 10);

class Wall :
    public Entity
{
private:
    int speed = WALL_SPEED;


public:
    Wall(Entity& host) : Entity(host.object.getPosition(), WALL_SIZE, Color::Blue) {}

    void update(RenderWindow& wn);
};

