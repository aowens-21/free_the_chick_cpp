#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window {sf::VideoMode(600, 600), "Free The Chick!"};

  sf::CircleShape circle {100};
  circle.setPosition(50, 50);
  circle.setFillColor(sf::Color::Red);

  sf::Event current_event;
  while (window.isOpen())
  {
    while (window.pollEvent(current_event))
    {
      if (current_event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(circle);
    window.display();
  }

  return EXIT_SUCCESS;
}