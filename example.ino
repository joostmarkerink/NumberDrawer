#include <Adafruit_SSD1306.h>
extern "C"{
  #include "Number.h"
}

#define SSD1306_ADDRESS 0x3C

Adafruit_SSD1306 SSD1306(128, 64);



void SSD1306Number_setPixel(NumberDrawing *d,int x,int y){
    SSD1306.drawPixel(x,y,1);  
}
static NumberDrawing numDrawing={
  SSD1306Number_setPixel,
  32,32,8,
  { 1,8,8,1,1,1,1 },
  128
};


void setup(){
    if(!SSD1306.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
}

int counter=0;

void loop(){
    SSD1306.clearDisplay();
    NumberDrawing_drawNumber(&numDrawing,0,0,counter++);
    SSD1306.display();
}