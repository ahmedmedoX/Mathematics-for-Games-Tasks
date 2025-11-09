#include<SFML/Graphics.hpp>
using namespace sf;

class DraggablePoint {
    bool isDragging;

public:
    CircleShape point;
    DraggablePoint(float x, float y) :point(10) {
        isDragging = false;
        point.setPosition(x, y);
        point.setOrigin(10, 10);
    }

    void onBeginDrag(Vector2f mousePosition) {
        isDragging = point.getGlobalBounds().contains(mousePosition);
    }

    void Drag(Vector2f mousePosition) {
        if (isDragging)
            point.setPosition(mousePosition);
    }

    void endDrag() {
        isDragging = false;
    }

    Vector2f getPosition() {
        return point.getPosition();
    }
};

Color operator * (float s, const Color color) {
    return Color(color.r * s, color.g * s, color.b * s);
}

float clamp(float d, float min, float max) {
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

template<class T>
T lerp(T start, T end, float alpha) {
    return ((1 - clamp(alpha,0,1)) * start) + (clamp(alpha,0,1) * end);
}

void getBezierCurve(const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, VertexArray& curve) {
    float t = 0;
    int VertexCount = curve.getVertexCount();
    float deltaTime = 1.0f / (VertexCount - 1);
    for (int i = 0; i < VertexCount; i++) {
        Vector2f p01 = lerp(p0, p1, t);
        Vector2f p12 = lerp(p1, p2, t);
        Vector2f p23 = lerp(p2, p3, t);
        Vector2f p012 = lerp(p01, p12, t);
        Vector2f p123 = lerp(p12, p23, t);
        curve[i].position = lerp(p012, p123, t);
        curve[i].color = lerp(Color::Red, Color::Cyan, t);
        t += deltaTime;
    }
}

void MoveCircle(CircleShape &my_Circle, const Vector2f& p0, const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, float deltaTime) {
    Vector2f p01 = lerp(p0, p1, deltaTime);
    Vector2f p12 = lerp(p1, p2, deltaTime);
    Vector2f p23 = lerp(p2, p3, deltaTime);
    Vector2f p012 = lerp(p01, p12, deltaTime);
    Vector2f p123 = lerp(p12, p23, deltaTime);
    my_Circle.setPosition(lerp(p012, p123, deltaTime));
    my_Circle.setFillColor(lerp(Color::Red, Color::Cyan, deltaTime));
}

int main() {
    RenderWindow window(VideoMode(1600, 900), "Bezier");
    window.setFramerateLimit(60);

    float deltaTime = 0;
    float TotalTime = 0;
    Clock clock;

    Vector2f mousePosition;

    DraggablePoint p1(300, 300);
    DraggablePoint p2(100, 100);
    DraggablePoint p3(400, 100);
    DraggablePoint p4(200, 300);

    VertexArray myLines(PrimitiveType::LineStrip, 4);
    VertexArray curve(PrimitiveType::LineStrip, 30);

    CircleShape my_Circle(50);
    my_Circle.setOrigin(50, 50);
    my_Circle.setPosition(300, 300);

    bool isMoving = false;
    float speed = 3.0;
    while (window.isOpen())
    {
        
        mousePosition = (Vector2f)Mouse::getPosition(window);
        deltaTime = clock.restart().asSeconds();

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Scan::Space))
            {
                isMoving = true;
            }
            if (event.type == Event::MouseButtonPressed) {
                p1.onBeginDrag(mousePosition);
                p2.onBeginDrag(mousePosition);
                p3.onBeginDrag(mousePosition);
                p4.onBeginDrag(mousePosition);
            }
            if (event.type == Event::MouseButtonReleased) {
                p1.endDrag();
                p2.endDrag();
                p3.endDrag();
                p4.endDrag();
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            p1.Drag(mousePosition);
            p2.Drag(mousePosition);
            p3.Drag(mousePosition);
            p4.Drag(mousePosition);
        }

        myLines[0].position = p1.getPosition();
        myLines[1].position = p2.getPosition();
        myLines[2].position = p3.getPosition();
        myLines[3].position = p4.getPosition();

        getBezierCurve(p1.getPosition(), p2.getPosition(), p3.getPosition(), p4.getPosition(), curve);
        
        if (isMoving) {
            if (TotalTime < (10.0/speed)) {
                TotalTime += deltaTime;
                MoveCircle(my_Circle, p1.getPosition(), p2.getPosition(), p3.getPosition(), p4.getPosition(), TotalTime * (speed / 10.0));
            }
            else {
                TotalTime = 0;
                isMoving = false;
            }
        }

        window.clear();
        window.draw(p1.point);
        window.draw(p2.point);
        window.draw(p3.point);
        window.draw(p4.point);
        window.draw(myLines);
        window.draw(curve);

        if (isMoving)
            window.draw(my_Circle);
        window.display();
    }
    return 0;
}