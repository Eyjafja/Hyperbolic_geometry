#include "project.h"

int main()
{
    window.setVerticalSyncEnabled(false);//Вертикальная синхронизация

    sf::CircleShape Space(SpaceRadius);//Пространство
    Space.setPosition({static_cast<float>(centerx - SpaceRadius), static_cast<float>(centery - SpaceRadius)});
    Space.setFillColor(sf::Color::White);
    Space.setOutlineColor(sf::Color::Black);
    Space.setOutlineThickness(5);

    std::array<std::array<double, 3>, 3> DirMat = {{{1, 0, 0},//Прямая Матрица
                                                    {0, 1, 0},
                                                    {0, 0, 1}}};
    bool up = false, down = false, left = false, right = false;
    std::vector<Dot> DotVec;
    for(int i = 0; i < Number_Of_Dots; i++){//Создание точек
        Dot dot{};
        DotVec.push_back(dot);
    }
    FPS fps;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) up = true;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) down = true;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) left = true;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) right = true;
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) up = false;
                if (event.key.code == sf::Keyboard::S) down = false;
                if (event.key.code == sf::Keyboard::A) left = false;
                if (event.key.code == sf::Keyboard::D) right = false;
            }
        }
        window.clear(sf::Color::White);
        window.draw(Space);

        if(up){
                DirMat = MultMatrix(DirMat, XSpin);
        }
        if(down){
            DirMat = MultMatrix(DirMat, NegativeXSpin);
        }
        if(left){
            DirMat = MultMatrix(DirMat, YSpin);
        }
        if(right){
            DirMat = MultMatrix(DirMat, NegativeYSpin);
        }

        for(int i = 0; i < Number_Of_Dots; i++) DotVec[i].BackDraw(DirMat); //Отрисовка точек на сфере
        for(int i = 0; i < Number_Of_Dots; i++) DotVec[i].FrontDraw(DirMat);

        window.display();
        std::cout << fps.getFPS() << std::endl;
    }

    return 0;
}