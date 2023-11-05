#pragma once
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

struct CTrasnformable
{


};

struct CRenderable
{
	b2Body* body;
	sf::VertexArray vertexArray;

};


