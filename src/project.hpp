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



sf::RenderWindow window(sf::VideoMode(1366, 700), "SFML works!");
/*Классы*/
class Dot{ //Класс точки
private:

    double x, y, z;
    float r = 5;

public:

    Dot(){ //Конструктор
        double fi = Randfloat(-180, 180);
        double teta = Randfloat(-90, 90);
        x = cos(fi) * cos(teta);
        y = sin(fi) * cos(teta);
        z = sin(teta);
    }

    std::array<double, 3> GetCoords(){//Геттер для координат
        std::array<double, 3> Coords {x, y, z};
        return Coords;
    }

    void DrawDot(double drawx, double drawy, double drawz) const {//Отрисовка по точкам
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


    void BackDraw(std::array<std::array<double, 3>, 3> DirMat){//Отрисовка задней стороны сферы
        std::array<std::array<double, 3>, 3> DrawXYZ = MultMatrix({{{x, y, z},{0, 0, 0},{0, 0, 0}}}, DirMat);
        if(DrawXYZ[0][2] < 0) DrawDot(DrawXYZ[0][0], DrawXYZ[0][1], DrawXYZ[0][2]);
    }

    void FrontDraw(std::array<std::array<double, 3>, 3> DirMat){//Отрисовка передней стороны сферы
        std::array<std::array<double, 3>, 3> DrawXYZ = MultMatrix({{{x, y, z},{0, 0, 0},{0, 0, 0}}}, DirMat);
        if(DrawXYZ[0][2] >= 0) DrawDot(DrawXYZ[0][0], DrawXYZ[0][1], DrawXYZ[0][2]);
    }
};

class FPS { //Класс фпс
private:
    sf::Clock clock;
    float lastTime;
    int fps;
    int ticks;

public:

    FPS(){
        lastTime = 0;
        ticks = 0;
        fps = 0;
    }

    int getFPS(){
        ticks += 1;
        if (ticks % 10 == 0) {
            fps = 10.0 / (clock.restart().asSeconds() - lastTime);
            lastTime = clock.restart().asSeconds();
            ticks = 0;
        }
        return fps;
    }
};
