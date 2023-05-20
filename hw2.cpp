#include "hw2.h"
Img::Img(){
    srcImg=nullptr;
    width=0;
    height=0;
    x_c=0;
    y_c=0;
}
Img::Img(int w, int h) {
    width=w;
    height=h;
    x_c=w/2;
    y_c=h/2;
    srcImg=new int[w*h];
}
Img::Img(const int *src, int w, int h) {
    width=w;
    height=h;
    x_c=w/2;
    y_c=h/2;
    srcImg=new int[w*h];
    for(int i=0; i<w*h;i++){
        srcImg[i]=src[i];
    }
}
Img::~Img(){
    delete[] srcImg;
}
//////////////////////////////////////////////

ImageProcess::ImageProcess() {
    srcImg=new Img;
    processedImg=new Img;
    int* ar =new int[9]{0,1,0,1,1,1,0,1,0};
    mask = new Img{ar, 3,3};
}
ImageProcess::ImageProcess(int w, int h){
    srcImg=new Img(w,h);
    processedImg= new Img(w,h);
    int* ar=new int[]{0,1,0,1,1,1,0,1,0};
    mask= new Img{ar,3,3};
    delete[] ar;
}
ImageProcess::ImageProcess(const Img* img){
    srcImg=new Img(img->srcImg, img->width, img->height);
    processedImg=new Img(img->srcImg, img->width, img->height);
    int* ar= new int[9]{0,1,0,1,1,1,0,1,0};
    mask= new Img{ar,3,3};
    delete[] ar;
}
ImageProcess::ImageProcess(const char* fileName) {
    ifstream fin;
    fin.open(fileName);
    if (!fin.is_open()){
        cout << "!! dont open !!" << endl;
        srcImg = new Img;// если вдруг файл не открывается, то все равно надо выделить память иначе диструктор будет собираться удалять память не ту
        processedImg = new Img;
    }
    else {
        srcImg = new Img;
        processedImg = new Img;
        char q;
        int h;
        int w;
        int k = 0;
        int i = 0;
        while (fin.get(q)) {

            if (k == 0 && (int)q-48>=0 ) {
                h = ((int)q)-'0';//жеско переводим в инт(запомнить!!!!!!)
                k++;
                continue;
            }
            if (k == 1 && (int)q-48>=0) {
                w = (int)q-'0';
                break;
            }
        }
        int *ar = new int[w * h];
        while (fin.get(q)) {
            if((int)q-48==0 ||(int)q-48==1){
                ar[i] = (int)q-'0';
                i++;
            }
        }
        srcImg = new Img{ar, w, h};
        processedImg = new Img{ar, w, h};
        int *ar1 = new int[9]{0, 1, 0, 1, 1, 1, 0, 1, 0};
        mask = new Img{ar1, 3, 3};
        fin.close();
        delete[] ar;
        delete[] ar1;
    }
}
ImageProcess::~ImageProcess(){
    delete srcImg;
    delete processedImg;
    delete mask;
    srcImg=nullptr;
    processedImg=nullptr;
    mask=nullptr;
}
int ImageProcess::updateMask(const Img& Newmask){
    delete mask;
    mask= new Img(Newmask.srcImg,Newmask.width,Newmask.height);
    return 0;
}
int ImageProcess::updateSrcImg(){
    delete srcImg;
    srcImg= new Img(processedImg->srcImg, processedImg->width, processedImg->height);
}
int ImageProcess::dilatation(int point){
    // надо чтобы пимг и симг было одинаковое наверное
    int w = srcImg->width;
    int h = srcImg->height;
    if(point==1){
        for(int j=mask->width;j>=3;j=j-2){
            for(int i=0; i<h*w;i++){
                if(srcImg->srcImg[i]==1){
                    if((i-h)>=0 )
                        processedImg->srcImg[i-h]=1;
                    if((i+h)<=h*w )
                        processedImg->srcImg[i+h]=1;
                    if((i-1)>=0 )
                        processedImg->srcImg[i-1]=1;
                    if((i+1)<=h*w )
                        processedImg->srcImg[i+1]=1;
                }
            }

        }
    }
    if(point==0){
        int* ar=new int [w*h];
        for(int i=0; i<w*h;i++){
            ar[i]=processedImg->srcImg[i];
        }
        for(int j=mask->width;j>=3;j=j-2){
            for(int i=0; i<h*w;i++){
                if(ar[i]==1){
                    if((i-h)>=0 )
                        processedImg->srcImg[i-h]=1;
                    if((i+h)<=h*w )
                        processedImg->srcImg[i+h]=1;
                    if((i-1)>=0 )
                        processedImg->srcImg[i-1]=1;
                    if((i+1)<=h*w )
                        processedImg->srcImg[i+1]=1;
                }

            }
        }

        delete[] ar;
    }
    return 0;
}
int ImageProcess::erosion(int point){
    int w = srcImg->width;
    int h = srcImg->height;
    if(point==1){
        for(int j=mask->width;j>=3;j=j-2){
            for(int i=0; i<h*w;i++){
                if(srcImg->srcImg[i]==1){
                    if((i-h)>=0 )
                        processedImg->srcImg[i-h]=0;
                    if((i+h)<=h*w )
                        processedImg->srcImg[i+h]=0;
                    if((i-1)>=0 )
                        processedImg->srcImg[i-1]=0;
                    if((i+1)<=h*w )
                        processedImg->srcImg[i+1]=0;
                }
            }

        }
    }
    if(point==0){
        int* ar=new int [w*h];
        for(int i=0; i<w*h;i++){
            ar[i]=processedImg->srcImg[i];
        }
        for(int j=mask->width;j>=3;j=j-2){
            for(int i=0; i<h*w;i++){
                if(srcImg->srcImg[i]==1){
                    if((i-h)>=0 )
                        processedImg->srcImg[i-h]=0;
                    if((i+h)<=h*w )
                        processedImg->srcImg[i+h]=0;
                    if((i-1)>=0 )
                        processedImg->srcImg[i-1]=0;
                    if((i+1)<=h*w )
                        processedImg->srcImg[i+1]=0;
                }
            }
        }
        delete[] ar;
    }
    return 0;
}
int ImageProcess::loadImgFromFile(const char* fileName, int format){
    FILE* fLog = fopen(fileName, "r");
    int w, h;
    if (fscanf(fLog, "%d\t%d", &w, &h) == false) {
        cout << "wrong input" << endl;
        fclose(fLog);
        return 1;
    }
    int* ar = new int[w * h];
    string text;
    char* buf = new char[255];
    while (fscanf(fLog, "%s", buf) != EOF) {
        text += buf;
    };
    for (int i = 0; i < h * w; i++) {
        ar[i] = (int)text[i] - '0';
    }
    fclose(fLog);
    Img* NEWsrcImg = new Img{ ar, w, h };
    delete srcImg;
    srcImg=new Img(NEWsrcImg->srcImg,NEWsrcImg->width,NEWsrcImg->height);
    processedImg=new Img(NEWsrcImg->srcImg,NEWsrcImg->width,NEWsrcImg->height);
    delete NEWsrcImg;
    delete[] ar;
    delete[] buf;
    return 0;
}

int ImageProcess::saveImgToFile(const char* fileName, int format){
    FILE* fLog = fopen(fileName, "w");
    fprintf(fLog, "%d\t%d\n", processedImg->width, srcImg->height);
    for (int i = 0; i < processedImg->height; i++) {
        for (int j = 0; j < processedImg->width; j++) {
            fprintf(fLog, "%d", processedImg->srcImg[i * srcImg->width + j]);
        }
        if (format == 1) {
            fprintf(fLog, "\n");
        }
    }
    fclose(fLog);
    return 0;

}