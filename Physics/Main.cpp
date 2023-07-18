#include <SFML/Graphics.hpp>
#include<SFML/OpenGL.hpp>
struct Object {
	sf::CircleShape circle;
	sf::Vector2f velocity = sf::Vector2f(0.f,0.f);
};
const float gravity = 9.8;
const float damp = 0.89;

void display(Object& circle,sf::RenderWindow& window)
{	
	window.setVerticalSyncEnabled(true);
	window.setActive(true);
	circle.circle.setRadius(25);
	circle.circle.setFillColor(sf::Color::Blue);
	circle.circle.setPosition(0, 0);
}

void moveY(Object& circle,sf::RenderWindow& window, float dt)
{
	circle.velocity.y += gravity*dt;
	circle.circle.move(circle.velocity);
	int diameter = 2 * circle.circle.getRadius();
		if (circle.circle.getPosition().y <= 0)
		{
			circle.velocity.y = -circle.velocity.y * damp;
			circle.circle.setPosition(circle.circle.getPosition().x , 0);
		}
		else if (circle.circle.getPosition().y + diameter >= window.getSize().y)
		{
			circle.velocity.y = -circle.velocity.y * damp;
			circle.circle.setPosition(circle.circle.getPosition().x, window.getSize().y - diameter);
		}

}

void moveX(Object& circle, sf::RenderWindow& window, float dt)
{
	circle.velocity.x += gravity * dt;
	circle.circle.move(circle.velocity);
	int diameter = 2 * circle.circle.getRadius();
	if (circle.circle.getPosition().x <= 0)
	{
		circle.velocity.x = -circle.velocity.x * damp;
		circle.circle.setPosition(0, circle.circle.getPosition().y);
	}
	else if (circle.circle.getPosition().x + diameter >= window.getSize().x)
	{
		circle.velocity.x = -circle.velocity.x * damp;
		circle.circle.setPosition(window.getSize().x - diameter, circle.circle.getPosition().y);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Physics:Simple Gravity simulation", sf::Style::Default, sf::ContextSettings(32));
	Object circle;
	Object circle2, circle3;
	display(circle, window);
	display(circle2, window);
	circle2.circle.setPosition(600, 0);
	display(circle3, window);
	circle3.circle.setPosition(0,300);
	sf::Clock clock;
	sf::Time dt;
	while (window.isOpen())
	{
		dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		moveX(circle, window, dt.asSeconds());
		moveY(circle,window,dt.asSeconds());
		circle2.circle.setFillColor(sf::Color::Green);
		moveX(circle2, window, dt.asSeconds());
		moveY(circle2, window, dt.asSeconds());
		circle3.circle.setFillColor(sf::Color::Red);
		moveX(circle3, window, dt.asSeconds());
		moveY(circle3, window, dt.asSeconds());
		window.clear(sf::Color::White);
		window.draw(circle.circle);
		window.draw(circle2.circle);
		window.draw(circle3.circle);
		window.display();
	}

	return 0;
}
