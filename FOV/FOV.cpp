#include<SFML/Graphics.hpp>
using namespace sf;

#define PI (22/7.0)

void Arc(ConvexShape& shape, const Vector2f& center, float radius, float startAngle, float endAngle) {
    int pointsCount = shape.getPointCount();

    float deltaAngle = (((endAngle - startAngle) * PI) / 180) / (pointsCount - 2);
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

void MovePlayer(CircleShape& body, ConvexShape& FOV, float deltatime) {
    Vector2f Movement(0, 0);
    //float Speed = 1.0;

    if (Keyboard::isKeyPressed(Keyboard::Scan::Right) || Keyboard::isKeyPressed(Keyboard::Scan::D))
        Movement.x += 200 * deltatime;

    if (Keyboard::isKeyPressed(Keyboard::Scan::Left) || Keyboard::isKeyPressed(Keyboard::Scan::A))
        Movement.x -= 200 * deltatime;

    if (Keyboard::isKeyPressed(Keyboard::Scan::Up) || Keyboard::isKeyPressed(Keyboard::Scan::W))
        Movement.y -= 200 * deltatime;

    if (Keyboard::isKeyPressed(Keyboard::Scan::Down) || Keyboard::isKeyPressed(Keyboard::Scan::S))
        Movement.y += 200 * deltatime;

    body.move(Movement);
    FOV.move(Movement);
}

void RotatePlayer(ConvexShape& FOV, Vector2f& mousePosition, float FOV_Angle) {
    Vector2f mouse_Vector = FOV.getPosition() - mousePosition;
    float angle = atan2f(mouse_Vector.y, mouse_Vector.x);
    FOV.setRotation(180 - (FOV_Angle / 2) + ((angle * 180) / PI));
}

float dotproduct(const Vector2f& v1, const Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

bool In_FOV_Range(ConvexShape& FOV, const CircleShape& Enemy, const float FOV_Angle, const float FOV_Radius, const Vector2f &mousePosition) {
    Vector2f Vector_Mouse = mousePosition - FOV.getPosition();
    Vector2f Vector_Enemy = Enemy.getPosition() - FOV.getPosition();
    float MouseV_Mag = std::sqrt(Vector_Mouse.x * Vector_Mouse.x + Vector_Mouse.y * Vector_Mouse.y);
    float EnemyV_Mag = std::sqrt(Vector_Enemy.x * Vector_Enemy.x + Vector_Enemy.y * Vector_Enemy.y);
    float Angle = dotproduct(Vector_Mouse, Vector_Enemy) / (MouseV_Mag * EnemyV_Mag);
    float RadiustoDist = Enemy.getRadius() / EnemyV_Mag;
    Angle = std::acos(Angle);
    if(EnemyV_Mag<FOV_Radius+Enemy.getRadius())
        return (Angle < ((FOV_Angle / 2) * PI / 180.0f) + RadiustoDist * 0.81);
    return 0;
}

int main() {
    RenderWindow window(VideoMode(700, 700), "FOV Assignment");
    window.setFramerateLimit(60);
    Vector2f mousePosition;

    float deltaTime = 0;
    float totalTime = 0;
    Clock clock;

    CircleShape player(30);
    player.setOrigin(30, 30);
    player.setPosition(250, 250);
    player.setFillColor(Color::Cyan);

    float FOV_Angle = 70.0;
    float FOV_Radius = 100.0;

    ConvexShape FOV(16);
    FOV.setOrigin(100, 100);
    Arc(FOV, Vector2f(100, 100), FOV_Radius, 0, FOV_Angle);
    FOV.setPosition(250, 250);
    FOV.setFillColor(Color::Green);

    CircleShape Enemy(15);
    Enemy.setOrigin(15, 15);
    Enemy.setPosition(400, 100);
    Enemy.setFillColor(Color::Magenta);

    while (window.isOpen())
    {
        mousePosition = (Vector2f)Mouse::getPosition(window);
        deltaTime = clock.restart().asSeconds();

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        MovePlayer(player, FOV, deltaTime);
        RotatePlayer(FOV, mousePosition, FOV_Angle);

        if (In_FOV_Range(FOV, Enemy, FOV_Angle, FOV_Radius, mousePosition)) {
            FOV.setFillColor(Color::Red);
        }
        else {
            FOV.setFillColor(Color::Green);
        }

        window.clear();
        window.draw(Enemy);
        window.draw(FOV);
        window.draw(player);
        window.display();
    }
    return 0;
}