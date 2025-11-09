#include<SFML/Graphics.hpp>
using namespace sf;

#define PI (22/7.0)

float SinTime(float time) {
    return abs(sin(time));
}

void Pacman_Shape(ConvexShape& shape, const Vector2f& center, float radius, int Open_Mouth_Angle, float time) {
    shape.setPosition(center);
    int pointsCount = shape.getPointCount();

    float deltaAngle = (360 - Open_Mouth_Angle) / (pointsCount - 2);
    deltaAngle = (deltaAngle * PI) / 180;
    float angle = ((Open_Mouth_Angle / 2) * PI) / 180;

    float deltaAngle_closed = (2 * PI) / (pointsCount - 2);
    float angle_closed = 0;

    for (int i = 1; i < pointsCount; i++) {
        Vector2f Point;
        Point.x = 0 + radius * cos((SinTime(time) * angle) + ((1 - SinTime(time)) * angle_closed));
        Point.y = 0 + radius * sin((SinTime(time) * angle) + ((1 - SinTime(time)) * angle_closed));
        shape.setPoint(i, Point);
        angle += deltaAngle;
        angle_closed += deltaAngle_closed;
    }
}

void Pacman_Rotate(ConvexShape& shape) {
    if (Keyboard::isKeyPressed(Keyboard::Scan::Right))
        shape.setRotation(0);
    if (Keyboard::isKeyPressed(Keyboard::Scan::Left))
        shape.setRotation(180);
    if (Keyboard::isKeyPressed(Keyboard::Scan::Up))
        shape.setRotation(-90);
    if (Keyboard::isKeyPressed(Keyboard::Scan::Down))
        shape.setRotation(90);
}

int main(){
    RenderWindow window(VideoMode(500, 500), "Pacman Assignment");
    window.setFramerateLimit(60);

    float deltaTime = 0;
    float totalTime = 0;
    Clock clock;

    ConvexShape my_Pacman(64);
    my_Pacman.setFillColor(Color::Yellow);

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

        Pacman_Shape(my_Pacman, Vector2f(250, 250), 150, 50, totalTime * 5);
        Pacman_Rotate(my_Pacman);

        window.clear();
        window.draw(my_Pacman);
        window.display();
    }
    return 0;
}