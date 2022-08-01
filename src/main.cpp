#include "project.h"

int main()
{
    window.setVerticalSyncEnabled(true);//Вертикальная синхронизация

    sf::CircleShape Space(SpaceRadius);//Пространство
    Space.setPosition({static_cast<float>(centerx - SpaceRadius), static_cast<float>(centery - SpaceRadius)});
    Space.setFillColor(sf::Color::White);
    Space.setOutlineColor(sf::Color::Black);
    Space.setOutlineThickness(5);

    std::array<std::array<double, 3>, 3> DirMat = {{{1, 0, 0},//Прямая Матрица
                                                    {0, 1, 0},
                                                    {0, 0, 1}}};
    std::vector<Dot> DotVec;
    for(int i = 0; i < Number_Of_dots; i++){//Создание точек
        Dot dot{};
        DotVec.push_back(dot);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();
        window.clear(sf::Color::White);
        window.draw(Space);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) DirMat = MultMatrix(DirMat, XSpin); //Повороты сферы
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) DirMat = MultMatrix(DirMat, YSpin);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) DirMat = MultMatrix(DirMat, NegativeXSpin);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) DirMat = MultMatrix(DirMat, NegativeYSpin);

        for(int i = 0; i < Number_Of_dots; i++) DotVec[i].BackDraw(DirMat); //Отрисовка точек на сфере
        for(int i = 0; i < Number_Of_dots; i++) DotVec[i].FrontDraw(DirMat);

        window.display();
    }

    return 0;
}