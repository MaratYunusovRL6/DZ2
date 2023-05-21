//
// Created by Admin on 14.05.2023.
//
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#ifndef HW2PICTURES_HW2_H
#define HW2PICTURES_HW2_H
using namespace std;
struct Img{
    int* srcImg;
    int width;
    int height;
    int x_c;
    int y_c;
    Img();
    Img(int w, int h);
    Img(const int* src, int w, int h);
    ~Img();
};

class ImageProcess{
private:
    Img* srcImg;
    Img* processedImg;
    Img* mask;
    //здесь можно обьявлять другие переменные и функции
public:
    //здесь нельзя обявлять другие функции и  переменные
    ImageProcess();// будут изначальные данные для картинни
    ImageProcess(int w, int h);//здесь выделяется память для картинки размера w*h
    ImageProcess(const Img* img);//выделяется память для картинки размера w*h и копируется картинка
    ImageProcess(const char* fileName);//выделяется память для картинки, копируется картинка из файла, первая  строчка в файле содержит ширину и высоту картинки
    ~ImageProcess();

    int updateMask(const Img& mask);//новое????? задание маски почему интовая???
    int updateSrcImg();//перезаписать исходную картинку картинкой,которая была получена в результате дил и или эрозии
    int dilatation(int srcImg=1);//дилатация картинки результат записать в processedImg  А КАК Я БУДУ ИСПОЛЬЗОВАЬ srcImg как указатель???
    int erosion(int srcImg=1);//эрозия картинки результат записать в processedImg заменю на поинт, а иначе хз???
    int loadImgFromFile(const char* fileName, int format=1);//0-последовательно 1-с с переходом на новую матрица
    int saveImgToFile(const char* fileName, int format=1);//0-последовательно 1-с с переходом на новую матрица
};
#endif //HW2PICTURES_HW2_H
