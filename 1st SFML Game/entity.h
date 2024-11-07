#include <SFML/Graphics.hpp>

using namespace sf;

#pragma once
class Entity
{
private: 
	RectangleShape object;
public:
	Entity(Vector2f position, Vector2f size, Color color); //Constructor
	~Entity() = default;
	void move(Vector2i target, int speed); //Moving Entity
	bool collide(Entity& other) const; //Collision Detection
	RectangleShape getRect() const; //Get the RectangeShape
	Vector2f get_component(Vector2i target, int distance) const; //Get the x and y component distance from the entity to target
};

float get_angle(Vector2f point1, Vector2i point2); //Get the angle from the entity to a target