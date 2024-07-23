#include "LCDLibrary.h"


void copyShiftArray(unsigned char* dest, int destLen, unsigned char* src, int srcLen, int pos) {
    int copyBits = pos + srcLen*8 <= destLen*8 ? srcLen*8: destLen*8 - pos;
    int rShift = pos % 8;
    
    for(int i=0;i <= copyBits / 8; i++) {
        if(i == 0) {
            dest[pos/8+i] = (dest[pos/8+i] & (0xFF << (8 - rShift))) | (src[i] >> rShift);
#ifdef DEBUG
            printf("dest[%04d]" BYTE_TO_BINARY_PATTERN "from " 
                    "src[%04d]" BYTE_TO_BINARY_PATTERN "\r\n",
                   pos/8+i,BYTE_TO_BINARY(dest[pos/8+i]),i,BYTE_TO_BINARY(src[i]));
#endif
        }
        else {
            dest[pos/8+i] = (i < srcLen?src[i]>>rShift : (dest[pos/8+i] & (0xFF >> rShift))) | (src[i-1] << (8-rShift));
#ifdef DEBUG
            printf("dest[%04d]" BYTE_TO_BINARY_PATTERN "from " 
                    "src[%04d]" BYTE_TO_BINARY_PATTERN "\r\n",
                   pos/8+i,BYTE_TO_BINARY(dest[pos/8+i]),i-1,BYTE_TO_BINARY(src[i-1]));
#endif
        }
    }
#ifdef DEBUG
    printf("copyBits[%03d]: ",copyBits);
#endif
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
//    for(int row = 0; row < objectHeight; row ++) {
//        for(int col = 0; col < objectWidth / 8; col ++){
//            printf(BYTE_TO_BINARY_PATTERN "",BYTE_TO_BINARY(object[row*objectWidth/8+col]));
//        }
//        printf("\r\n");
//    }
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
//    unsigned char data[32]; //16x16 bit
//    memset(data,0,sizeof(data));
//    for(int row = 0; row < objectHeight; row ++) {
//        printf(BYTE_TO_BINARY_PATTERN "\r\n",BYTE_TO_BINARY(characterData[row]));
//        copyShiftArray(&data[(0+row)*16/8],16/8,(unsigned char*)&characterData[row],1,0);
//    }
//    for(int i=0;i<displayHeight;i++){
//        for(int j=0; j<displayWidth/8; j++)
//            printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(display[i*2+j]));
//        printf("\r\n");
//    }
    
}
void LCDLibrary::drawString(unsigned char* display, int displayWidth, int displayHeight,
                            const unsigned char** fonts, const char* data, int posX, int posY) {
    for(int i =0; i< strlen(data); i++) {
        drawChar(display,displayWidth,displayHeight,fonts,data[i],posX+i*(8+1),posY);
    }
}
