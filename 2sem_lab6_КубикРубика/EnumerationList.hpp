#pragma once
//Список цветов
enum Сolour
{

    White, Yellow, Green, Red, Blue, Orange, Black

};

//Список элементов
enum ElementType
{

    _Corner, _Edge, _Centre

};

//Список распложений
enum Orientation
{

    Straight, LeftSide, RightSide, FrontSide, BackSide, BottomSide

};

//Список поворотов
enum Rotation 
{

    Nothing, CenterUpAndDownRotation, CenterLeftAndRightRotation, ClockwiseRotation

};

//Список операций для разбирателя
enum Disassembly
{

    Right1Rotation, Right2Rotation, Left1Rotation, Left2Rotation, Up1Rotation, Up2Rotation, Down1Rotation, Down2Rotation, Front1Rotation, Front2Rotation

};

