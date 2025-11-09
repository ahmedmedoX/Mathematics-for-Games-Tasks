#include<SFML/Graphics.hpp>
using namespace sf;

void TranslateBackground(Sprite& Tex, float speed) {
    IntRect TexRect = Tex.getTextureRect();
    TexRect.left += speed;
    Tex.setTextureRect(TexRect);
}

int main()
{
    RenderWindow window(VideoMode(1084, 544), "Parallax Assignment");
    window.setFramerateLimit(60);

    float deltaTime = 0;
    float totalTime = 0;
    Clock clock;

    Texture* T_Background1 = new Texture();
    Texture* T_Background2 = new Texture();
    Texture* T_Background3 = new Texture();
    Texture* T_Background4 = new Texture();

    T_Background1->loadFromFile("background_1.png");
    T_Background2->loadFromFile("background_2.png");
    T_Background3->loadFromFile("background_3.png");
    T_Background4->loadFromFile("background_4.png");

    T_Background1->setRepeated(true);
    T_Background2->setRepeated(true);
    T_Background3->setRepeated(true);
    T_Background4->setRepeated(true);

    Sprite Sp_Background1;
    Sprite Sp_Background2;
    Sprite Sp_Background3;
    Sprite Sp_Background4;

    Sp_Background1.setTexture(*T_Background1);
    Sp_Background2.setTexture(*T_Background2);
    Sp_Background3.setTexture(*T_Background3);
    Sp_Background4.setTexture(*T_Background4);

    Sp_Background1.setScale(2,2);
    Sp_Background2.setScale(2,2);
    Sp_Background3.setScale(2,2);
    Sp_Background4.setScale(2,2);

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

        TranslateBackground(Sp_Background1,0);
        TranslateBackground(Sp_Background2,1);
        TranslateBackground(Sp_Background3,2);
        TranslateBackground(Sp_Background4,3);

        window.clear();
        window.draw(Sp_Background1);
        window.draw(Sp_Background2);
        window.draw(Sp_Background3);
        window.draw(Sp_Background4);
        window.display();
    }
    return 0;
}