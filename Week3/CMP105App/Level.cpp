#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	if (!fnt.loadFromFile("font/arial.ttf")) {
		std::cout << "Couldnt load font\n";
	}

	txt.setFont(fnt);

	rectSpd = sf::Vector2f(100, 150);

	// initialise game objects
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(sf::Vector2f(0, 0));
	rect.setFillColor(sf::Color::Red);

	circ.setPosition(sf::Vector2f(100, 100));
	circ.setRadius(25);
	circ.setFillColor(sf::Color::Blue);
	//rect = sf::RectangleShape(sf::Vector2f(0, 0));
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	circSpd = sf::Vector2f(0, 0);

	if (input->isKeyDown(sf::Keyboard::W)) {
		circSpd.y = -400;
	}
	else if (input->isKeyDown(sf::Keyboard::S)) {
		circSpd.y = 400;
	}
	else if (input->isKeyDown(sf::Keyboard::A)) {
		circSpd.x = -400;
	}
	else if (input->isKeyDown(sf::Keyboard::D)) {
		circSpd.x = 400;
	}

	if (input->isKeyDown(sf::Keyboard::Add)) {
		rectSpd.x += 10;
		rectSpd.y += 10;
	}
	if (input->isKeyDown(sf::Keyboard::Subtract)) {
		rectSpd.x -= 10;
		rectSpd.y -= 10;
	}
}

// Update game objects
void Level::update(float dt)
{
	txt.setString("x: " + std::to_string((int)rectSpd.x) + " y:" + std::to_string((int)rectSpd.y));
	int wW = window->getSize().x;
	int wH = window->getSize().y;
	rect.move(rectSpd * dt);
	circ.move(circSpd *dt);

	// RECTANGLE
	if (rect.getPosition().y + rect.getSize().y >= wH || rect.getPosition().y < 0) {
		rectSpd.y *= -1;
		rect.move(rectSpd * dt);
	}
	if (rect.getPosition().x + rect.getSize().x >= wW || rect.getPosition().x < 0) {
		rectSpd.x *= -1;
		rect.move(rectSpd * dt);
	}

	// CIRCLE
	if ((circ.getPosition().y + circ.getRadius()*2) + (circSpd.y * dt) >= wH || circ.getPosition().y < 0) {
		circSpd.y *= -1;
		circ.move(circSpd * dt);
		circSpd.y = 0;
	}
	if ((circ.getPosition().x + circ.getRadius()*2) + (circSpd.x*dt) >= wW || circ.getPosition().x < 0) {
		circSpd.x *= -1;
		circ.move(circSpd * dt);
		circSpd.x = 0;
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(rect);
	window->draw(circ);
	window->draw(txt);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}