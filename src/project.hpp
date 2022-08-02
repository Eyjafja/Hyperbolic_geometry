#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bits/stdc++.h>
#include <cstdlib>

/*Константы*/
const int centerx = 683, centery = 350;//Центральные точки
const int SpaceRadius = 200; //Радиус Гиперболического/Сферического/Евклидового пространсства
const double alpha = 0.03; //Шаг для поворота
const int Number_Of_Dots = 1000; // Количество точек

const std::array<std::array<double, 3>, 3> YSpin = {{{cos(alpha), 0, sin(alpha)},
                                                     {0, 1, 0},
                                                     {-sin(alpha), 0, cos(alpha)}}};

const std::array<std::array<double, 3>, 3> XSpin = {{{1, 0, 0},
                                                     {0, cos(alpha), sin(alpha)},
                                                     {0, -sin(alpha), cos(alpha)}}};

const std::array<std::array<double, 3>, 3>  NegativeYSpin = {{{cos(alpha), 0, -sin(alpha)},
                                                              {0, 1, 0},
                                                              {sin(alpha), 0, cos(alpha)}}};

const std::array<std::array<double, 3>, 3> NegativeXSpin = {{{1, 0, 0}, //
                                                             {0, cos(alpha), -sin(alpha)},
                                                             {0, sin(alpha), cos(alpha)}}};



/*Функции*/
std::array<std::array<double, 3>, 3> MultMatrix(std::array<std::array<double, 3>, 3> First, std::array<std::array<double, 3>, 3> Second); //Перемножение матриц


double Randfloat(int min, int max);//Функция для выдачи случайного числа



//=======================================Класс Точки========================================
class Dot{//Класс точки

private:
    double x, y, z;
    float r = 5;

public:
    Dot();

    std::array<double, 3> GetCoords();

    void DrawDot(sf::RenderWindow &window, double drawx, double drawy, double drawz) const;

    void BackDraw(sf::RenderWindow &window, std::array<std::array<double, 3>, 3> DirMat);

    void FrontDraw(sf::RenderWindow &window, std::array<std::array<double, 3>, 3> DirMat);

    void SetCoords(double x, double y);
};

class FPS { //Класс фпс
private:
    sf::Clock clock;
    float lastTime;
    int fps;
    int ticks;

public:
    FPS();

    int getFPS();
};
