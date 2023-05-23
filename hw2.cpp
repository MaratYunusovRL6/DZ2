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
    FILE* f = fopen(fileName, "r");
    int w, h;
    fscanf(f, "%d\t%d", &w, &h);
    int* ar = new int[w * h];
    string matrix;
    char* buf = new char[255];
    while (fscanf(f, "%s", buf) != EOF)
        matrix += buf;
    for (int i = 0; i < h * w; i++)
        ar[i] = (int)matrix[i] - '0';
    fclose(f);
    Img* buf1 = new Img{ ar, w, h };
    delete srcImg;
    srcImg=new Img(buf1->srcImg,buf1->width,buf1->height);
    processedImg=new Img(buf1->srcImg,buf1->width,buf1->height);
    delete buf1;
    delete[] ar;
    delete[] buf;
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
int ImageProcess::dilatation(int srcImg){
    int iw;
    int ih;
    int* img;
    if(srcImg==1){
       iw=this->srcImg->width;
       ih=this->srcImg->height;
       img=this->srcImg->srcImg;
    }
    else{
        iw=processedImg->width;
        ih=processedImg->height;
        img=processedImg->srcImg;
    }
    int mw=this->mask->width;
    int mh=this->mask->height;
    int* mask=this->mask->srcImg;
    int rw=iw+(mw/2)*2;
    int rh=ih+(mh/2)*2;
    int j=0;
    int d=0;
    int q=(rw*(mh/2)+mw/2);
    int w=(rw*rh-(rw*(mh/2)+mw/2)-1);
    int* imgr=new int[rw*rh];
    for(int i=0;i<rw*rh;i++){
        imgr[i]=0;
    }
    for(int i=0;i<rw*rh;i++){
        if (q<=i && w>=i){
            if(0<=j && j<iw){
                imgr[i]=img[d];
                j++;
                d++;
                continue;
            }
            else{
                i=i+(mw/2)*2-1;
                j=0;
                continue;
            }
        }
    }
    ////////////delatation
    d=0;
    int p=0;
    int* imgr1= new int[rw*rh];
    for(int i=0;i<rw*rh;i++){
        imgr1[i]=imgr[i];
    }
    for(int i=0;i<rw*rh;i++){
        if(imgr[i]==mask[(mw*mh)/2]){
            for(int j=(i-(mh/2)*rw-(mw/2));j<=(i+(mh/2)*rw+(mw/2));j++){
                if(0<=d && d<mw){
                    if(mask[p]==1){
                        imgr1[j]=mask[p];
                        d++;
                        p++;
                        continue;
                    }
                    else{
                        d++;
                        p++;
                        continue;
                    }
                }
                else{
                    j=(j-mw)+rw-1;
                    d=0;
                    continue;
                }

            }
            d=0;
            p=0;
        }
    }
    d=0;
    j=0;
    for(int i=0;i<rw*rh;i++){
        if (q<=i && w>=i){
            if(0<=j && j<iw){
                img[d]=imgr1[i];
                j++;
                d++;
                continue;
            }
            else{
                i=i+(mw/2)*2-1;
                j=0;
                continue;
            }
        }
    }
    for(int i=0;i<iw*ih;i++){
            processedImg->srcImg[i]=img[i];
    }
    for (int i=0;i<iw*ih;i++){
        img[i]=0;
    }
    mask=nullptr;
    imgr=nullptr;
    imgr1=nullptr;
    return 0;


}
int ImageProcess::erosion(int srcImg){
    int iw;
    int ih;
    int* img;
    if(srcImg==1){
        iw=this->srcImg->width;
        ih=this->srcImg->height;
        img=this->srcImg->srcImg;
    }
    else{
        iw=this->processedImg->width;
        ih=this->processedImg->height;
        img=this->processedImg->srcImg;
    }
    int mw=this->mask->width;
    int mh=this->mask->height;
    int* mask=this->mask->srcImg;
    int rw=iw+(mw/2)*2;
    int rh=ih+(mh/2)*2;
    int j=0;
    int d=0;
    int q=(rw*(mh/2)+mw/2);
    int w=(rw*rh-(rw*(mh/2)+mw/2)-1);
    int* imgr=new int[rw*rh];
    for(int i=0;i<rw*rh;i++){
        imgr[i]=1;
    }
    for(int i=0;i<rw*rh;i++){
        if (q<=i && w>=i){
            if(0<=j && j<iw){
                imgr[i]=img[d];
                j++;
                d++;
                continue;
            }
            else{
                i=i+(mw/2)*2-1;
                j=0;
                continue;
            }
        }
    }
    d=0;
    int p=0;
    int* imgr1= new int[rw*rh];
    for(int i=0;i<rw*rh;i++){
        imgr1[i]=imgr[i];
    }
    for(int i=0;i<rw*rh;i++){
        if(imgr[i]==mask[(mw*mh)/2]-1){
            for(int j=(i-(mh/2)*rw-(mw/2));j<=(i+(mh/2)*rw+(mw/2));j++){
                if(0<=d && d<mw){
                    if(mask[p]==1){
                        imgr1[j]=mask[p]-1;
                        d++;
                        p++;
                        continue;
                    }
                    else{
                        d++;
                        p++;
                        continue;
                    }
                }
                else{
                    j=(j-mw)+rw-1;
                    d=0;
                    continue;
                }

            }
            d=0;
            p=0;
        }
    }
    d=0;
    j=0;
    for(int i=0;i<rw*rh;i++){
        if (q<=i && w>=i){
            if(0<=j && j<iw){
                img[d]=imgr1[i];
                j++;
                d++;
                continue;
            }
            else{
                i=i+(mw/2)*2-1;
                j=0;
                continue;
            }
        }
    }
    for(int i=0;i<iw*ih;i++) {
        this->processedImg->srcImg[i] = img[i];
    }
    for (int i=0;i<iw*ih;i++){
        img[i]=0;
    }
    mask=nullptr;
    imgr=nullptr;
    imgr1=nullptr;
    return 0;
}
int ImageProcess::loadImgFromFile(const char* fileName, int format){
    FILE* f = fopen(fileName, "r");
    int w, h;
    fscanf(f, "%d\t%d", &w, &h);
    int* ar = new int[w * h];
    string matrix;
    char* buf = new char[255];
    while (fscanf(f, "%s", buf) != EOF)
        matrix += buf;
    for (int i = 0; i < h * w; i++)
        ar[i] = (int)matrix[i] - '0';
    fclose(f);
    Img* buf1 = new Img{ ar, w, h };
    delete srcImg;
    srcImg=new Img(buf1->srcImg,buf1->width,buf1->height);
    processedImg=new Img(buf1->srcImg,buf1->width,buf1->height);
    delete buf1;
    delete[] ar;
    delete[] buf;
    return 0;
}

int ImageProcess::saveImgToFile(const char* fileName, int format){
    FILE* f = fopen(fileName, "w");
    fprintf(f, "%d\t%d\n", processedImg->width, processedImg->height);
    for (int i = 0; i < processedImg->height; i++) {
        for (int j = 0; j < processedImg->width; j++) {
            fprintf(f, "%d", processedImg->srcImg[i * processedImg->width + j]);
        }
        if (format == 1) {
            fprintf(f, "\n");
        }
    }
    fclose(f);
    return 0;

}