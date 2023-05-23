#include <iostream>
#include "hw2.h"
int main() {
    //ImageProcess a("MyFile.txt");//MyFile.txt
    //a.loadImgFromFile("MyFile.txt");
    ImageProcess a;
    /*int* ar =new int[25]{0,0,1,0,0,
                         0,0,1,0,0,
                         1,1,1,1,1,
                         0,0,1,0,0,
                         0,0,1,0,0,};*/
    int* ar =new int[9]{0,1,0,
                       1,1,1,
                       0,1,0};
         /*int* ar=new int[12]{0,0,1,0,
                       1,1,1,1,
                       0,0,1,0};*/
    Img* m = new Img{ar, 3,3};
    a.updateMask( *m);
    a.loadImgFromFile("MyFile.txt");
    a.dilatation(1);
    //a.saveImgToFile("MyFile0.txt", 1);
    a.erosion(1);
    //a.dilatation(1);
    a.saveImgToFile("MyFile1.txt", 1);
    return 0;}
