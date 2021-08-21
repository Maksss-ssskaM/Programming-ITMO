#pragma once
#include "EnumerationList.hpp"
#include "Elements.hpp"
#include <vector>
class CubikRubik
{

public:
    CubikRubik();

    void getFile();

    void UpAndDown(std::vector<int>, std::vector<int>, int, double);//Вверх и Вниз
    void LeftAndRight(std::vector<int>, std::vector<int>, int, double);//Влево и Вправо
    void Clockwise(std::vector<int>, std::vector<int>, int, double);//Поврот по часовой стрелке
    void CenterUpAndDown(std::vector<int>, std::vector<int>, double);//Центральную фронтальная грань влево и вправо
    void CenterLeftAndRight(std::vector<int>, std::vector<int>, double);//Центральную боковую грань вверх и вниз

    void UP_LEFT();//Верхнюю грань вправо 
    void UP_RIGHT();//Верхнюю грань влево 
    void RIGHT_UP();//Правую боковую грань вверх
    void RIGHT_DOWN();//Правую боковую грань вниз
    void LEFT_DOWN();//Левую боковую грань вниз
    void LEFT_UP();//Левую боковую грань вверх
    void DOWN_RIGHT();//Нижнюю нрань вправо
    void DOWN_LEFT();//Нижнюю грань влево
    void FRONT_RIGHT();//Фронтальную грань направо
    void FRONT_LEFT();//Фронтальную грань налево
    void CENTER_UP();//Центральную боковую грань вверх
    void CENTER_DOWN();//Цетральную боковую грань вниз
    void CENTER_LEFT();//Центральную фронтальную грань вправо
    void CENTER_RIGHT();//Центральную фронтальную грань влево

    void PifPaf();//Классический пиф-паф. Правую от себя, верхнюю влево, правую на себя, верхнюю вправо.
    void ReversedPifPaf();//Ревёрснутый пиф-паф. То же самое, но для левой стороны.
    void AllLeft();//Всё налево
    void AllRight();//Всё направо
    void AllUp();//Всё вверх
    void AllDown();//Всё вниз

    void RubiksCubeDisassembler();//Собиратель кубика
    void RubiksCubeAssembler();//Разбиратель кубика

    void StepOne();//Правильный крест
    void StepTwo();//Ребро первого слоя
    void StepThree();//Углы первого слоя
    void StepFour();//Рёбра среднего слоя
    void StepFive();//Крест последнего слоя
    void StepSix();//Правильный крест последнего слоя
    void StepSeven();//Расстановка углов последнего слоя
    void StepEight();//Разворот углов третьего слоя

    int FindElement(Сolour, ElementType);
    void draw();

    ~CubikRubik();

private:

    std::vector<std::vector<Element*>>_elements;
};
