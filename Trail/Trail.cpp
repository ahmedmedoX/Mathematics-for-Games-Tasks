#include<SFML/Graphics.hpp>
using namespace sf;

float ClampValue(float d) {
    const float t = d < 0 ? 0 : d;
    return t > 1 ? 1 : t;
}

class TrailPoint {
public:
    CircleShape my_circle;
    TrailPoint(const float radius, Vector2f position) : my_circle(radius)
    {
        my_circle.setOrigin(Vector2f(radius, radius));
        my_circle.setPosition(position);
    }

    void lerp(Vector2f start, Vector2f end, float alpha) {
        my_circle.setPosition(((1 - ClampValue(alpha)) * start) + (ClampValue(alpha) * end));
    }

    Vector2f getPosition() {
        return my_circle.getPosition();
    }
};

int main() {
    RenderWindow window(VideoMode(1600, 900), "Trail");
    window.setFramerateLimit(60);

    float deltaTime = 0;
    float totalTime = 0;
    Clock clock;

    Vector2f Originalposition(400, 300);

    TrailPoint Circle1(40, Originalposition);
    TrailPoint Circle2(35, Originalposition);
    TrailPoint Circle3(25, Originalposition);
    TrailPoint Circle4(15, Originalposition);

    Vector2f mousePosition;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        mousePosition = (Vector2f)Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        Circle1.lerp(Circle1.getPosition(), mousePosition, 10 * deltaTime);
        Circle2.lerp(Circle2.getPosition(), Circle1.getPosition(), 9 * deltaTime);
        Circle3.lerp(Circle3.getPosition(), Circle2.getPosition(), 8 * deltaTime);
        Circle4.lerp(Circle4.getPosition(), Circle3.getPosition(), 7 * deltaTime);

        window.clear();
        window.draw(Circle4.my_circle);
        window.draw(Circle3.my_circle);
        window.draw(Circle2.my_circle);
        window.draw(Circle1.my_circle);
        window.display();
    }
    return 0;
}
