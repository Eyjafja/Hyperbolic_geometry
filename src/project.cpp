#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>
#include <cstdlib>
#include "project.hpp"

/*Функции*/
std::array<std::array<double, 3>, 3> MultMatrix(std::array<std::array<double, 3>, 3> First, std::array<std::array<double, 3>, 3> Second){ //Перемножение матриц
    std::array<std::array<double, 3>, 3> ret = {};
    for(int i = 0; i < First.size(); i++){//i - Номер строки в первой матрице
        for(int k = 0; k < Second.size(); k++){//k - Номер столбца во второй матрице
            double Res = 0;
            for(int j = 0; j < Second.size(); j++){//j - Номер строки во второй матрице
                Res += First[i][j] * Second[j][k];
            }
            ret[i][k] = Res;
        }
    }
    return ret;
}

double Randfloat(int min, int max){//Функция для выдачи случайного числа

    double value;

    value = rand() % abs(min - max) + min + rand() / 32767.0;

    return value;
}



//=======================================Класс Точки========================================
Dot::Dot(){
    double fi = Randfloat(-180, 180);
    double teta = Randfloat(-90, 90);
    x = cos(fi) * cos(teta);
    y = sin(fi) * cos(teta);
    z = sin(teta);
}

std::array<double, 3> Dot::GetCoords(){
    std::array<double, 3> Coords {x, y, z};
    return Coords;
}

void Dot::DrawDot(sf::RenderWindow &window, double drawx, double drawy, double drawz) const {//Отрисовка по точкам
    sf::CircleShape sh(r);
    sh.setPosition({static_cast<float>(drawx * SpaceRadius + centerx - r), static_cast<float>(drawy * SpaceRadius + centery - r)});
    if(drawz >= 0) {
        sh.setFillColor(sf::Color::Black);
    }
    else{
        sf::Color color(128,128,128);
        sh.setFillColor(color);
    }
    window.draw(sh);
}

void Dot::FrontDraw(sf::RenderWindow &window, std::array<std::array<double, 3>, 3> DirMat){//Отрисовка передней стороны сферы
    std::array<std::array<double, 3>, 3> DrawXYZ = MultMatrix({{{x, y, z},{0, 0, 0},{0, 0, 0}}}, DirMat);
    if(DrawXYZ[0][2] >= 0) DrawDot(window, DrawXYZ[0][0], DrawXYZ[0][1], DrawXYZ[0][2]);
}

void Dot::BackDraw(sf::RenderWindow &window, std::array<std::array<double, 3>, 3> DirMat){//Отрисовка задней стороны сферы
    std::array<std::array<double, 3>, 3> DrawXYZ = MultMatrix({{{x, y, z},{0, 0, 0},{0, 0, 0}}}, DirMat);
    if(DrawXYZ[0][2] < 0) DrawDot(window, DrawXYZ[0][0], DrawXYZ[0][1], DrawXYZ[0][2]);
}
//=======================================Класс FPS========================================
FPS::FPS(){
    lastTime = 0;
    ticks = 0;
    fps = 0;
}

int FPS::getFPS(){
    ticks += 1;
    if (ticks % 10 == 0) {
        fps = 10.f / (clock.restart().asSeconds() - lastTime);
        lastTime = clock.restart().asSeconds();
        ticks = 0;
    }
    return fps;
}

