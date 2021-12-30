#ifndef NUMBER_H
#define NUMBER_H


    typedef struct{
        int digitWidth,digitHeight;
        int spacing;
        int segmentWidth[7];
    }NumberSettings;

    typedef struct NumberDrawing NumberDrawing;

    typedef void(*Number_setPixel)(NumberDrawing *d,int x,int y);

    struct NumberDrawing{
        Number_setPixel setPixel;
        NumberSettings settings;
        int canvasWidth;
        void *userData;
    };

    void NumberDrawing_drawNumber(NumberDrawing *,int x,int y,int number);
        


#endif
