#include<SFML/Graphics.hpp>
#include"Quad.h"
using namespace sf;

float clamp(float d, float min, float max) {
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

int main() {
    RenderWindow window(VideoMode(1000, 500), "Jump Assignment");
    window.setFramerateLimit(60);

    float Time = 0;
    Clock clock;

    RectangleShape Ground;
    Ground.setPosition(Vector2f(0,450));
    Ground.setFillColor(Color::Green);
    Ground.setSize(Vector2f(1000,100));

    CircleShape my_Circle(50);
    my_Circle.setFillColor(Color::Red);

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
        }

        if (Keyboard::isKeyPressed(Keyboard::Scan::Space))
        {
            targetPosition = Vector2f(350,270);
            startPosition = position;
            clock.restart();
        }

        Time = clock.getElapsedTime().asSeconds();

        isMoving = Time < 1.0;

        if (isMoving)
        {
            position.x = Quad::easeInOut(Time, startPosition.x, targetPosition.x - startPosition.x, 0.5);
            position.y = clamp(Quad::easeInOut(Time, startPosition.y, targetPosition.y - startPosition.y, 0.5), 270.0, 350.0);
        }
        else {
            position = Vector2f(350, 350);
        }
        my_Circle.setPosition(position);
        window.clear(Color(39,111,150));
        window.draw(Ground);
        window.draw(my_Circle);

        window.display();
    }
    return 0;
}