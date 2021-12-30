
#include "Number.h"
/*
void NumberDrawing_initialize(NumberDrawing *d,int canvasWidth){
    if(canvasWidth<=32){
        d->settings.digitWidth=5;
        d->settings.digitHeight=7;
        d->settings.spacing=1;
    }else{
        d->settings.digitWidth=8;
        d->settings.digitHeight=15;
        d->settings.spacing=2;
    }
    for(char i=0;i<7;i++) d->settings.segmentWidth[i]=1;
    d->canvasWidth=canvasWidth;
}
*/
    void NumberDrawing_hor(NumberDrawing *d,int x,int y){
      for(int i=0;i<d->settings.digitWidth;i++) (*d->setPixel)(d,i+x,y);
    }
    void NumberDrawing_ver(NumberDrawing *d,int x,int y,int len){
        for(int i=0;i<len;i++) (*d->setPixel)(d,x,y+i);
    }
    void NumberDrawing_drawDigit(NumberDrawing *d,char num,int x,int y){
        if(num<0 || num>9) num=0;
        static const char *segments[10]={
            "1111110",
            "0110000",
            "1101101",
            "1111001",
            "0110011",
            "1011011",
            "1011111",
            "1110000",
            "1111111",
            "1111011"
        };
        const char *segs=segments[num];
  
        int mid=(d->settings.digitHeight/2)-((d->settings.digitHeight%2)==0?1:0);
        
        int top=y;
        int bottom=y+d->settings.digitHeight-1;
        int right=x+d->settings.digitWidth-1;
        int left=x;
      
        if(segs[0]=='1'){
            for(int i=0;i<d->settings.segmentWidth[0];i++)
                NumberDrawing_hor(d,left,top+i);
        }
        
        if(segs[1]=='1'){
            for(int i=0;i<d->settings.segmentWidth[1];i++)
                NumberDrawing_ver(d,right-i,top,mid+1);
        }
        if(segs[2]=='1'){
            for(int i=0;i<d->settings.segmentWidth[2];i++)
                NumberDrawing_ver(d,right-i,top+mid,(d->settings.digitHeight-mid));
       }
       
        if(segs[3]=='1'){
            for(int i=0;i<d->settings.segmentWidth[3];i++)
                NumberDrawing_hor(d,left,bottom-i);
        }
        
        if(segs[4]=='1'){
            for(int i=0;i<d->settings.segmentWidth[4];i++)
                NumberDrawing_ver(d,left+i,top+mid,(d->settings.digitHeight-mid));
        }
        if(segs[5]=='1'){
            for(int i=0;i<d->settings.segmentWidth[5];i++)
                NumberDrawing_ver(d,left+i,top,mid+1);
        } 
        if(segs[6]=='1'){
            if(d->settings.segmentWidth[6]>1){
                int seghalf=d->settings.segmentWidth[6]/2;
                for(int i=-seghalf;i<seghalf;i++){
                    NumberDrawing_hor(d,left,top+mid+i);
                }
            }else{
                NumberDrawing_hor(d,left,top+mid);
            }
        }
    }
    void NumberDrawing_drawWithDot(NumberDrawing *d,int x,int y,int v,int dotpos){
        int pos=d->canvasWidth;
        if(v==0) 
            NumberDrawing_drawDigit(d,0,pos-d->settings.digitWidth,y);
        else{
            char drawMinus=v<0;
            if(drawMinus) v=-v;
            char count=0;
            while(v>0){
                if(count++==dotpos){
                    (*d->setPixel)(d,pos,y+d->settings.digitHeight-1);
                    pos-=d->settings.spacing;
                }
                int nn=v/10;
                NumberDrawing_drawDigit(d,v-(nn*10),pos-d->settings.digitWidth,y);
                pos-=d->settings.digitWidth+d->settings.spacing;
                v/=10;
            }
            if(drawMinus){
                int mid=y+(d->settings.digitHeight/2);
                for(int i=0;i<d->settings.digitWidth;i++)
                    (*d->setPixel)(d,pos+i,mid);
            }
        }
    }
    void NumberDrawing_drawNumber(NumberDrawing *d,int x,int y,int v){
        NumberDrawing_drawWithDot(d,x,y,v,-1);
    }
    int NumberDrawing_round(float f){
        int n=f;
        return (f-n)>=0.5f?n+1:n;
    }
    void NumberDrawing_drawFloatingNumber(NumberDrawing *d,int x,int y,float num,int decPlace){
        int n=1;
        int i;
        for(i=0;i<decPlace;i++){
            n*=10;
        }
        NumberDrawing_drawWithDot(d,x,y,NumberDrawing_round(num*n),decPlace);
    }