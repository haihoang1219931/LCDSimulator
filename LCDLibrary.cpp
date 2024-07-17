#include "LCDLibrary.h"

void LCDLibrary::drawObject(unsigned char* display, int displayWidth, int displayHeight,
                            unsigned char* object, int objectWidth, int objectHeight,
                            int posX, int posY) {

    int rectWidth = objectWidth + posX > displayWidth ? displayWidth - posX:objectWidth;
    int rectHeight = objectHeight + posY > displayHeight ? displayHeight - posY:objectHeight;
    if(rectWidth>=objectWidth && rectHeight >= objectHeight)
    for(int row = 0; row < rectHeight; row ++) {
        memcpy(&display[displayWidth * (posY + row) + posX]
               ,&object[row*objectWidth],rectWidth);

    }
}


void LCDLibrary::drawChar(unsigned char* display, int displayWidth, int displayHeight,
                          const unsigned char** fonts, char character, int posX, int posY) {
    const unsigned char* characterData = openGLletters[character - ' '];
    unsigned char objectWidth = 8;
    unsigned char objectHeight = 13;
    unsigned char * object = new unsigned char [objectWidth * objectHeight];
    for(int row = 0; row < objectHeight; row ++) {
        for(int col = 0; col < objectWidth; col ++) {
            object[row*objectWidth + col] = ((characterData[objectHeight - 1 - row] >> (objectWidth - col -1))) << 7;
        }
    }

    LCDLibrary::drawObject(display,displayWidth,displayHeight,
                           object,objectWidth,objectHeight,
                           posX,posY);
    delete[] object;
}
void LCDLibrary::drawString(unsigned char* display, int displayWidth, int displayHeight,
                            const unsigned char** fonts, const char* data, int posX, int posY) {
    for(int i =0; i< strlen(data); i++) {
        drawChar(display,displayWidth,displayHeight,fonts,data[i],posX+i*(8+1),posY);
    }
}
