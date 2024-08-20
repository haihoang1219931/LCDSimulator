#include "LCDLibrary.h"

void copyShiftArray(unsigned char* dest, int destLen, unsigned char* src, int srcLen, int pos, bool invertBG = false) {
    if(pos >=0) {
        int copyBits = pos + srcLen*8 <= destLen*8 ? srcLen*8: destLen*8-pos;
        int rShift = pos % 8;
        for(int i=0;i <= copyBits; i+=8) {
                if((i+pos)/8 < destLen) {
                unsigned char value =
                        (i/8-1>=0 ? (src[i/8-1] << (8-rShift)) : 0x00) |
                        (i/8 <srcLen ? (src[i/8] >> (rShift)) : 0x00);
                if(invertBG) {
                    dest[(i+pos)/8] &= ~(value);
                }else {
                    dest[(i+pos)/8] |= value;
                }
            }
        }
    } else {
        int copyBits = pos + srcLen*8 >0 ? pos + srcLen*8: -1;
        int rShift = 8-(-pos)%8;
        for(int i=0;i <= copyBits; i+=8) {
            unsigned char value =
                    ((i-pos)/8 < srcLen ? (src[(i-pos)/8] << (8-rShift)) : 0x00) |
                ((i-pos)/8+1 < srcLen ? (src[(i-pos)/8+1] >> (rShift)) : 0x00);
            if(invertBG) {
                dest[(i)/8] &= ~(value);
            }else {
                dest[(i)/8] |= value;
            }
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
void LCDLibrary::clear(unsigned char* display, int displayWidth, int displayHeight, bool invertBG) {
    memset((void*)display,invertBG?0xFF:0x00,displayWidth*displayHeight/8);
}

void LCDLibrary::drawPixel(unsigned char* display, int displayWidth, int displayHeight,
                           int posX, int posY, bool invertBG) {

    if(posX >=0 && posX < displayWidth &&
            posY >=0 && posY < displayHeight){
        if(invertBG) {
            display[(posY*displayWidth+posX)/8] &= ~(0x80 >> (posX % 8));
        } else {
            display[(posY*displayWidth+posX)/8] |= 0x80 >> (posX % 8);
        }
    }
}
void LCDLibrary::drawObject(unsigned char* display, int displayWidth, int displayHeight,
                            unsigned char* object, int objectWidth, int objectHeight,
                            int posX, int posY, bool invertBG) {
    for(int row = 0; row < objectHeight; row ++) {
        copyShiftArray(&display[(posY+row)*displayWidth/8],displayWidth/8,
                (unsigned char*)&object[row*objectWidth/8],
                objectWidth/8,posX,invertBG);
    }
//    printObject(object,objectWidth,objectHeight);
//    printf("\r\n");
}


void LCDLibrary::drawChar(unsigned char* display, int displayWidth, int displayHeight,
                          const unsigned char** fonts, char character, int posX, int posY, bool invertBG) {
    const unsigned char* characterData = openGLletters[character - ' '];
    unsigned char objectWidth = 8;
    unsigned char objectHeight = 13;
//    drawObject(display,displayWidth,displayHeight,(unsigned char*)&characterData,objectWidth,objectHeight,posX,posY,invertBG);
    for(int row = 0; row < objectHeight; row ++) {
        copyShiftArray(&display[(posY+row)*displayWidth/8],displayWidth/8,
                (unsigned char*)&characterData[objectHeight - 1 -row],
                objectWidth/8,posX, invertBG);
    }
//    printObject(display,displayWidth,displayHeight);
}
void LCDLibrary::drawString(unsigned char* display, int displayWidth, int displayHeight,
                            const unsigned char** fonts, const char* data, int posX, int posY, int space, bool invertBG) {
    for(int i =0; i< strlen(data); i++) {
        drawChar(display,displayWidth,displayHeight,fonts,data[i],posX+i*(8+space),posY, invertBG);
    }

}
void LCDLibrary::drawLine(unsigned char* display, int displayWidth, int displayHeight,
                          int startX, int startY, int endX, int endY, int thickness, bool invertBG) {
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
                drawPixel(display,displayWidth,displayHeight,(int)px+i-thickness/2,(int)py,invertBG);
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
                drawPixel(display,displayWidth,displayHeight,(int)px,(int)py+i-thickness/2,invertBG);
        }    
    }
}
void LCDLibrary::drawRect(unsigned char* display, int displayWidth, int displayHeight,
                          int posX, int posY, int rectWidth, int rectHeight, int thickness, bool fill, bool invertBG) {
    int rectWidthRemainder = rectWidth % 8;
    int roundRectWidth = (rectWidth - rectWidthRemainder);
    unsigned char* rect = new unsigned char[rectHeight*(roundRectWidth/8)];

    if(fill) {
        int halfThickness = thickness/2;
        for(int row = 0; row < rectHeight-halfThickness; row++){
            drawLine(display,displayWidth,displayHeight,posX,posY+halfThickness+row,posX+rectWidth,posY+halfThickness+row,thickness, invertBG);
        }
    } else {
        int halfThickness = thickness/2;
        drawLine(display,displayWidth,displayHeight,posX,posY+halfThickness,posX+rectWidth,posY+halfThickness,thickness,invertBG);
        drawLine(display,displayWidth,displayHeight,posX+halfThickness,posY,posX+halfThickness,posY+rectHeight,thickness,invertBG);
        drawLine(display,displayWidth,displayHeight,posX+rectWidth-halfThickness-1,posY,posX+rectWidth-halfThickness-1,posY+rectHeight,thickness,invertBG);
        drawLine(display,displayWidth,displayHeight,posX,posY+rectHeight-halfThickness-1,posX+rectWidth,posY+ rectHeight-halfThickness-1,thickness,invertBG);
    }

    delete[] rect;
}
void LCDLibrary::drawOval(unsigned char* display, int displayWidth, int displayHeight,
                          int posX, int posY, int ovalWidth, int ovalHeight, bool fill, bool invertBG) {
    
}
