#include<SFML/Graphics.hpp>
using namespace sf;

#define PI (22/7.0)

void updateArc(ConvexShape& shape, const Vector2f& center, float radius, float startAngle, float endAngle) {
    int pointsCount = shape.getPointCount();

    float deltaAngle = (((endAngle - startAngle) * PI) / 180) / (pointsCount-2);
    float angle = startAngle;

    shape.setPoint(0, center);

    for (int i = 1; i < pointsCount; i++) {
        Vector2f Point;
        Point.x = center.x + (radius * cos(angle));
        Point.y = center.y + (radius * sin(angle));
        shape.setPoint(i, Point);
        angle += deltaAngle;
    }
}

int main() {
    RenderWindow window(VideoMode(1000, 600), "Arc Assignment");
    window.setFramerateLimit(60);

    float deltaTime = 0;
    float totalTime = 0;
    Clock clock;

    ConvexShape my_Arc(32);
    updateArc(my_Arc, Vector2f(150, 150), 100, 0, 150);

    while (window.isOpen())
    {
        totalTime += deltaTime;
        deltaTime = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(my_Arc);
        window.display();
    }
    return 0;
}