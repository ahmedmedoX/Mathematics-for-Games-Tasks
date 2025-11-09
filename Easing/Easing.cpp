#include<SFML/Graphics.hpp>
#include"Elastic.h"
using namespace sf;

int main() {
    RenderWindow window(VideoMode(1000, 500), "Easing Assignment");
    window.setFramerateLimit(60);

    CircleShape my_Circle(50);
    my_Circle.setFillColor(Color::Red);

    float Time = 0;
    Clock clock;

    Vector2f position(350, 350);

    Vector2f startPosition = position;
    Vector2f targetPosition = position;

    bool isMoving = false;

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonReleased)
            {
                targetPosition = (Vector2f)Mouse::getPosition(window);

                startPosition = position;
                clock.restart();
            }
        }

        Time = clock.getElapsedTime().asSeconds();

        isMoving = Time < 3;
        if (isMoving) {
            position.x = Elastic::easeInOut(Time, startPosition.x, targetPosition.x - startPosition.x, 3);
            position.y = Elastic::easeInOut(Time, startPosition.y, targetPosition.y - startPosition.y, 3);
        }
        
        my_Circle.setFillColor(Color::Magenta);
        my_Circle.setPosition(position);

        window.clear();
        window.draw(my_Circle);
        window.display();
    }
    return 0;
}