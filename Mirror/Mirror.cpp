#include<SFML/Graphics.hpp>
using namespace sf;

class DragPoint {
    bool isDragging;

public:
    CircleShape point;
    DragPoint(float x, float y) :point(8) {
        isDragging = false;
        point.setPosition(x, y);
        point.setOrigin(10, 10);
        point.setFillColor(Color::Cyan);
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

float dot(const Vector2f& v1, const Vector2f& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

Vector2f proj(const Vector2f& v1, const Vector2f& v2) {
    return (dot(v1, v2) / dot(v2, v2)) * v2;
}

void MirrorShape(VertexArray& Shape, VertexArray& Shape_Mirror, const Vector2f& Mirror_p1, const Vector2f& Mirror_p2) {
    int VertexCount = Shape_Mirror.getVertexCount();
    Vector2f v1 = Mirror_p2 - Mirror_p1;
    for (int i = 0; i < VertexCount; i++) {
        Vector2f v2 = Shape[i].position - Mirror_p1;
        Vector2f Point_on_Line = Mirror_p1 + proj(v2, v1);
        Shape_Mirror[i].position = Point_on_Line - (Shape[i].position - Point_on_Line);
    }
}

int main() {
    RenderWindow window(VideoMode(1600, 900), "Mirror");
    window.setFramerateLimit(60);
    Vector2f mousePosition;

    DragPoint Mirror_p1(300, 100);
    DragPoint Mirror_p2(300, 300);
    DragPoint Triangle_p1(400, 100);
    DragPoint Triangle_p2(400, 300);
    DragPoint Triangle_p3(500, 300);

    VertexArray my_Mirror(PrimitiveType::Lines, 2);
    my_Mirror[0].color = my_Mirror[1].color = Color::Cyan;

    VertexArray Triangle(PrimitiveType::Triangles, 3);
    Triangle[0].color = Color::Yellow;
    Triangle[1].color = Color::Magenta;
    Triangle[2].color = Color::Cyan;

    VertexArray Triangle_Mirror(PrimitiveType::Triangles, 3);
    Triangle_Mirror[0].color = Color::Red;
    Triangle_Mirror[1].color = Color::Green;
    Triangle_Mirror[2].color = Color::Blue;

    while (window.isOpen())
    {
        mousePosition = (Vector2f)Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                Mirror_p1.onBeginDrag(mousePosition);
                Mirror_p2.onBeginDrag(mousePosition);
                Triangle_p1.onBeginDrag(mousePosition);
                Triangle_p2.onBeginDrag(mousePosition);
                Triangle_p3.onBeginDrag(mousePosition);
            }
            if (event.type == Event::MouseButtonReleased) {
                Mirror_p1.endDrag();
                Mirror_p2.endDrag();
                Triangle_p1.endDrag();
                Triangle_p2.endDrag();
                Triangle_p3.endDrag();
            }
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Mirror_p1.Drag(mousePosition);
            Mirror_p2.Drag(mousePosition);
            Triangle_p1.Drag(mousePosition);
            Triangle_p2.Drag(mousePosition);
            Triangle_p3.Drag(mousePosition);
        }

        my_Mirror[0].position = Mirror_p1.getPosition();
        my_Mirror[1].position = Mirror_p2.getPosition();
        Triangle[0].position = Triangle_p1.getPosition();
        Triangle[1].position = Triangle_p2.getPosition();
        Triangle[2].position = Triangle_p3.getPosition();

        MirrorShape(Triangle, Triangle_Mirror, my_Mirror[0].position, my_Mirror[1].position);

        window.clear();

        window.draw(Mirror_p1.point);
        window.draw(Mirror_p2.point);
        window.draw(Triangle_p1.point);
        window.draw(Triangle_p2.point);
        window.draw(Triangle_p3.point);

        window.draw(my_Mirror);
        window.draw(Triangle);
        window.draw(Triangle_Mirror);

        window.display();
    }
    return 0;
}