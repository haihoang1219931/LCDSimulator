#include "LCDLibrary.h"


void copyShiftArray(unsigned char* dest, int destLen, unsigned char* src, int srcLen, int pos) {
    int copyBits = pos + srcLen*8 <= destLen*8 ? srcLen*8: destLen*8 - pos;
    int rShift = pos % 8;
    
    for(int i=0;i <= copyBits / 8; i++) {
        if(i == 0) {
            dest[pos/8+i] = (dest[pos/8+i] & (0xFF << (8 - rShift))) | (src[i] >> rShift);
        }
        else {
            dest[pos/8+i] = (i < srcLen?src[i]>>rShift : (dest[pos/8+i] & (0xFF >> rShift))) | (src[i-1] << (8-rShift));
        }
    }
}
void printObject(unsigned char * object, int width, int height){
    for(int row = 0; row < height; row ++) {
        for(int col = 0; col < width / 8; col ++) {
            printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(object[row*width/8+col]));
        }
        printf("\r\n");
    }
    printf("\r\n");
}
void LCDLibrary::clear(unsigned char* display, int displayWidth, int displayHeight,
                       unsigned char value) {
    memset((void*)display,value,displayWidth*displayHeight/8);
}

void LCDLibrary::drawPixel(unsigned char* display, int displayWidth, int displayHeight,
                           unsigned char value, int posX, int posY) {
    display[(posY*displayWidth+posX)/8] = display[(posY*displayWidth+posX)/8] | (value << (7-posX%8));
}
void LCDLibrary::drawObject(unsigned char* display, int displayWidth, int displayHeight,
                            unsigned char* object, int objectWidth, int objectHeight,
                            int posX, int posY) {
    for(int row = 0; row < objectHeight; row ++) {
        copyShiftArray(&display[(posY+row)*displayWidth/8],displayWidth/8,(unsigned char*)&object[row*objectWidth/8],objectWidth/8,posX);
    }
}


void LCDLibrary::drawChar(unsigned char* display, int displayWidth, int displayHeight,
                          const unsigned char** fonts, char character, int posX, int posY) {
    const unsigned char* characterData = openGLletters[character - ' '];
    unsigned char objectWidth = 8;
    unsigned char objectHeight = 13;
    for(int row = 0; row < objectHeight; row ++) {
        copyShiftArray(&display[(posY+row)*displayWidth/8],displayWidth/8,(unsigned char*)&characterData[objectHeight - 1 -row],objectWidth/8,posX);
    }
    
}
void LCDLibrary::drawString(unsigned char* display, int displayWidth, int displayHeight,
                            const unsigned char** fonts, const char* data, int posX, int posY) {
    for(int i =0; i< strlen(data); i++) {
        drawChar(display,displayWidth,displayHeight,fonts,data[i],posX+i*(8+1),posY);
    }
}
void LCDLibrary::drawLine(unsigned char* display, int displayWidth, int displayHeight,
                          int startX, int startY, int endX, int endY, int thickness) {
    if(startX == endX) {
        drawRect(display,displayWidth,displayHeight,startX,startY,thickness,endY-startY,true);
    } else {
        float fStartX = (float)startX;
        float fStartY = (float)startY;
        float fEndX = (float)endX;
        float fEndY = (float)endY;
        float b = 1;
        float a = -(fStartY-fEndY)/(fStartX-fEndX);
        float c = a*fStartX + b*fStartY;
        for(float px = fStartX; px < fEndX; px++){
            float py = (c-a*px)/b;
            for(int i=0; i< thickness; i++)
                drawPixel(display,displayWidth,displayHeight,1,(int)px,(int)py+i);
        }    
    }
//    if(startY == endY) {
//        drawRect(display,displayWidth,displayHeight,startX,startY,endX-startX,thickness);
//    } else {
//        float fStartX = (float)startX;
//        float fStartY = (float)startY;
//        float fEndX = (float)endX;
//        float fEndY = (float)endY;
//        float a = 1;
//        float b = a*(fStartX-fEndX)/(fEndY-fStartY);
//        float c = a*fStartX + b*fEndX;
//        for(float py = fStartY; py < fEndY; py++){
//            float px = (c-b*py)/a;
//            drawPixel(display,displayWidth,displayHeight,1,(int)px,(int)py);
//        }  
//    }
}
void LCDLibrary::drawRect(unsigned char* display, int displayWidth, int displayHeight,
                          int posX, int posY, int rectWidth, int rectHeight, bool fill) {
    int rectWidthRemainder = 8 - rectWidth % 8;
    int roundRectWidth = (rectWidth + rectWidthRemainder);
    unsigned char* rect = new unsigned char[rectHeight*(roundRectWidth/8)];
    if(fill) {
        memset(rect,0xFF,rectHeight*(roundRectWidth/8));
        if(rectWidthRemainder != 0) {
            int lShift = rectWidthRemainder;
            for(int row = 0; row < rectHeight; row ++) {
                rect[(row+1) * roundRectWidth/8 - 1] &= 0xFF << lShift;
            }
        }
    } else {
        memset(rect,0x00,rectHeight*(roundRectWidth/8));
//        if(rectWidthRemainder != 0) 
        {
            int lShift = rectWidthRemainder;
            for(int row = 1; row < rectHeight-1; row ++) {
                rect[(row+1) * roundRectWidth/8 - 1] |= 0x01 << lShift;
                rect[row*roundRectWidth/8] |= 0x80;
            }
            memset(rect,0xFF,roundRectWidth/8);
            rect[roundRectWidth/8-1] = 0xFF << lShift;
            memset(&rect[(rectHeight-1)*roundRectWidth/8],0xFF,roundRectWidth/8);
            rect[rectHeight*roundRectWidth/8-1] = 0xFF << lShift;
//            printObject(rect,roundRectWidth,rectHeight);
        }
    }
    drawObject(display,displayWidth,displayHeight,rect,roundRectWidth,rectHeight,posX,posY);
    delete[] rect;
}
void LCDLibrary::drawOval(unsigned char* display, int displayWidth, int displayHeight,
                          int posX, int posY, int ovalWidth, int ovalHeight, bool fill) {
    
}