#pragma once
#include "EnumerationList.hpp"
#include "Elements.hpp"
#include <vector>
class CubikRubik
{

public:
    CubikRubik();

    void getFile();

    void UpAndDown(std::vector<int>, std::vector<int>, int, double);//����� � ����
    void LeftAndRight(std::vector<int>, std::vector<int>, int, double);//����� � ������
    void Clockwise(std::vector<int>, std::vector<int>, int, double);//������ �� ������� �������
    void CenterUpAndDown(std::vector<int>, std::vector<int>, double);//����������� ����������� ����� ����� � ������
    void CenterLeftAndRight(std::vector<int>, std::vector<int>, double);//����������� ������� ����� ����� � ����

    void UP_LEFT();//������� ����� ������ 
    void UP_RIGHT();//������� ����� ����� 
    void RIGHT_UP();//������ ������� ����� �����
    void RIGHT_DOWN();//������ ������� ����� ����
    void LEFT_DOWN();//����� ������� ����� ����
    void LEFT_UP();//����� ������� ����� �����
    void DOWN_RIGHT();//������ ����� ������
    void DOWN_LEFT();//������ ����� �����
    void FRONT_RIGHT();//����������� ����� �������
    void FRONT_LEFT();//����������� ����� ������
    void CENTER_UP();//����������� ������� ����� �����
    void CENTER_DOWN();//���������� ������� ����� ����
    void CENTER_LEFT();//����������� ����������� ����� ������
    void CENTER_RIGHT();//����������� ����������� ����� �����

    void PifPaf();//������������ ���-���. ������ �� ����, ������� �����, ������ �� ����, ������� ������.
    void ReversedPifPaf();//���������� ���-���. �� �� �����, �� ��� ����� �������.
    void AllLeft();//�� ������
    void AllRight();//�� �������
    void AllUp();//�� �����
    void AllDown();//�� ����

    void RubiksCubeDisassembler();//���������� ������
    void RubiksCubeAssembler();//����������� ������

    void StepOne();//���������� �����
    void StepTwo();//����� ������� ����
    void StepThree();//���� ������� ����
    void StepFour();//и��� �������� ����
    void StepFive();//����� ���������� ����
    void StepSix();//���������� ����� ���������� ����
    void StepSeven();//����������� ����� ���������� ����
    void StepEight();//�������� ����� �������� ����

    int FindElement(�olour, ElementType);
    void draw();

    ~CubikRubik();

private:

    std::vector<std::vector<Element*>>_elements;
};
