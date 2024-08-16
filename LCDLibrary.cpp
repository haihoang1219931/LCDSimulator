#include "LCDLibrary.h"

void copyShiftArray(unsigned char* dest, int destLen, unsigned char* src, int srcLen, int pos, bool invertBG = false) {
    int copyBits = pos + srcLen*8 <= destLen*8 ? srcLen*8: destLen*8 - pos;
    int rShift = pos % 8;
    for(int i=0;i <= copyBits / 8; i++) {
        if(i == 0) {
            dest[pos/8+i] =  (invertBG?0x00:dest[pos/8+i]) |
                    ((invertBG?(~src[i]):src[i]) >> rShift);
        }
        else {
            dest[pos/8+i] = (i < srcLen?(invertBG?(~src[i]):src[i])>>rShift :
                                        dest[pos/8+i]) |
                    ((invertBG?(~src[i-1]):src[i-1]) << (8-rShift));
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

    if(posX >=0 && posX < displayWidth &&
            posY >=0 && posY < displayHeight)
    display[(posY*displayWidth+posX)/8] = display[(posY*displayWidth+posX)/8] | (value << (7-posX%8));
}
void LCDLibrary::drawObject(unsigned char* display, int displayWidth, int displayHeight,
                            unsigned char* object, int objectWidth, int objectHeight,
                            int posX, int posY) {
    for(int row = 0; row < objectHeight; row ++) {
        copyShiftArray(&display[(posY+row)*displayWidth/8],displayWidth/8,(unsigned char*)&object[row*objectWidth/8],objectWidth/8,posX);
    }
//    printObject(object,objectWidth,objectHeight);
//    printf("\r\n");
}


void LCDLibrary::drawChar(unsigned char* display, int displayWidth, int displayHeight,
                          const unsigned char** fonts, char character, int posX, int posY, bool invertBG) {
    const unsigned char* characterData = openGLletters[character - ' '];
    unsigned char objectWidth = 8;
    unsigned char objectHeight = 13;
    for(int row = 0; row < objectHeight; row ++) {
        copyShiftArray(&display[(posY+row)*displayWidth/8],displayWidth/8,
                (unsigned char*)&characterData[objectHeight - 1 -row],
                objectWidth/8,posX, invertBG);
    }
//    printObject(display,displayWidth,displayHeight);
}
void LCDLibrary::drawString(unsigned char* display, int displayWidth, int displayHeight,
                            const unsigned char** fonts, const char* data, int posX, int posY, bool invertBG) {
    for(int i =0; i< strlen(data); i++) {
        drawChar(display,displayWidth,displayHeight,fonts,data[i],posX+i*(8),posY, invertBG);
    }

}
void LCDLibrary::drawLine(unsigned char* display, int displayWidth, int displayHeight,
                          int startX, int startY, int endX, int endY, int thickness) {
    if(startX == endX) {
        float fStartX = (float)startX;
        float fStartY = (float)startY;
        float fEndX = (float)endX;
        float fEndY = (float)endY;
        float a = 1;
        float b = -(fStartX-fEndX)/(fStartY-fEndY);
        float c = a*fStartX + b*fStartY;
        for(float py = fStartY; py < fEndY; py++){
            float px = (c-b*py)/a;
            for(int i=0; i< thickness; i++)
                drawPixel(display,displayWidth,displayHeight,1,(int)px+i-thickness/2,(int)py);
        }
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
                drawPixel(display,displayWidth,displayHeight,1,(int)px,(int)py+i-thickness/2);
        }    
    }
}
void LCDLibrary::drawRect(unsigned char* display, int displayWidth, int displayHeight,
                          int posX, int posY, int rectWidth, int rectHeight, int thickness, bool fill) {
    int rectWidthRemainder = rectWidth % 8;
    int roundRectWidth = (rectWidth - rectWidthRemainder);
    unsigned char* rect = new unsigned char[rectHeight*(roundRectWidth/8)];

    if(fill) {
        int halfThickness = thickness/2;
        for(int row = 0; row < rectHeight-halfThickness; row++){
            drawLine(display,displayWidth,displayHeight,posX,posY+halfThickness+row,posX+rectWidth,posY+halfThickness+row,thickness);
        }
    } else {
        int halfThickness = thickness/2;
        drawLine(display,displayWidth,displayHeight,posX,posY+halfThickness,posX+rectWidth,posY+halfThickness,thickness);
        drawLine(display,displayWidth,displayHeight,posX+halfThickness,posY,posX+halfThickness,posY+rectHeight,thickness);
        drawLine(display,displayWidth,displayHeight,posX+rectWidth-halfThickness-1,posY,posX+rectWidth-halfThickness-1,posY+rectHeight,thickness);
        drawLine(display,displayWidth,displayHeight,posX,posY+rectHeight-halfThickness-1,posX+rectWidth,posY+ rectHeight-halfThickness-1,thickness);
    }

    delete[] rect;
}
void LCDLibrary::drawOval(unsigned char* display, int displayWidth, int displayHeight,
                          int posX, int posY, int ovalWidth, int ovalHeight, bool fill) {
    
}
