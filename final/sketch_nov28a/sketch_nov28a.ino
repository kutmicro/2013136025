#include "U8glib.h"
 
U8GLIB_NHD_C12864 u8g(13, 11, 10, 9, 8);  // SPI Com: SCK = 13, MOSI = 11, CS = 10, CD = 9, RST = 8
 
int draw_state = 0;
 
#define PIN_DIGITAL_A 30
#define PIN_DIGITAL_B 32
#define PIN_DIGITAL_C 34
#define PIN_DIGITAL_F 28
#define PIN_DIGITAL_E 36  
#define PIN_DIGITAL_D 38  
const byte PIN_ANALOG_X = 1;
const byte PIN_ANALOG_Y = 2;
  int stage_state =1;
#define DELAY 500
  int flag =0;
     
  long randx=0;
  long randy=0;
 int ax=0;
 int ay=0;
int dead = 0;
int x = 20;
int y = 20;
int life =2;
void page1(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 30, 20, "KUTMICRO");
  u8g.drawStr( 20, 50, "2013136025");
}
 
void menu(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 12, 20, "A : [START] ");
  u8g.drawStr( 12, 50, "B : [EDIT] ");
  u8g.drawDisc(x,y,4);
  u8g.drawFrame(0,0,128,64);
  
}
void edit(void){
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 10, 20, "  koreaTech");
  u8g.drawStr( 10, 50, " Kim Yong GYu ");
  u8g.drawFrame(0,0,128,64);
  }
 
 void game(void){
   u8g.drawFrame(0,0,115,64);
   
   if(x<5 ){
    x=5;}
   if(x>109){
   x=109;}
   if(y<5){
   y=5;}
   if(y>58){
   y=58;}
   if(stage_state == 1)
    u8g.drawDisc(x,y,4); 
   
    
  int daad = 0;
    switch(stage_state){
    case 1: stage1();break;
    case 2: gameover();break;
    }
    if(life ==2){
    u8g.drawDisc(118,3,2);
    u8g.drawDisc(124,3,2);
    }
    if(life ==1){
      u8g.drawDisc(118,3,2);
     flag++;
     if(flag==1){
      x=random(1,100);
      y=random(1,50);
     }
      }
      if(life==0){
      stage_state = 2;
      daad++;
      if(daad==1){
        ax=x;
        ay=y;
        }
     }
  }
void stage1(void){
  int dir = random(1,100)%8;
switch(dir){
    case 0: randx++;randy--; break;
    case 1: randx++;randy  ; break;
    case 2: randx++;randy++; break;
    case 3: randx  ;randy++; break;
    case 4: randx--;randy++; break;
    case 5: randx--;randy  ; break;
    case 6: randx--;randy--; break;
    case 7: randx  ;randy--; break;
    }
    if(randx<5 ){
    randx=5;}
   if(randx>109){
   randx=109;}
   if(randy<5){
   randy=5;}
   if(randy>58){
   randy=58;}
   if(randx-x>-8 and randy-y>-8)
   if(randx-x<8 and randy-y<8)
   life--;
   delay(15);
  u8g.drawCircle(randx,randy,4);
  }
  
  void gameover(void){
    u8g.drawStr( 10, 30, " Game Over ");
    u8g.drawCircle(randx,randy,4);
      u8g.drawDisc(ax,ay,4);
    }
void setup(void) {
  
  Serial.begin(9600);
  randomSeed(analogRead(A10));
  
  pinMode(PIN_DIGITAL_A, INPUT);  
  digitalWrite(PIN_DIGITAL_A, HIGH);
  
   pinMode(PIN_DIGITAL_B, INPUT);  
  digitalWrite(PIN_DIGITAL_B, HIGH);
 
  pinMode(PIN_DIGITAL_C, INPUT);  
  digitalWrite(PIN_DIGITAL_C, HIGH);
 
  pinMode(PIN_DIGITAL_F, INPUT);  
  digitalWrite(PIN_DIGITAL_F, HIGH);
 
  pinMode(PIN_DIGITAL_E, INPUT);  
  digitalWrite(PIN_DIGITAL_E, HIGH);
  
  pinMode(PIN_DIGITAL_D, INPUT);  
  digitalWrite(PIN_DIGITAL_D, HIGH);
  
  u8g.setContrast(0); // Config the contrast to the best effect
  u8g.setRot180();// rotate screen, if required
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);
 
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
 
  
}
 
void loop() {
 
  u8g.firstPage();  //OLED 루프
  do {
    switch(draw_state){
      case 0:page1();break;
      case 1:menu();break;
      case 2:game();break;
      case 3:edit();break;  
      case 4:gameover();break;  
    }
    }
  while( u8g.nextPage() );
 
  
 if(digitalRead(PIN_DIGITAL_A) == LOW) {
   Serial.println("Button A is pressed");
  if(draw_state == 1)draw_state=2;
   }
 
 else if(digitalRead(PIN_DIGITAL_B) == LOW) {
   Serial.println("Button B is pressed");
   if(draw_state ==1) draw_state=3;
 }
 else if(digitalRead(PIN_DIGITAL_C) == LOW) {
   Serial.println("Button C is pressed");
   }
 
 else if(digitalRead(PIN_DIGITAL_F) == LOW) {
   Serial.println("Button F is pressed");
   
 }
  else if(digitalRead(PIN_DIGITAL_E) == LOW) {
   Serial.println("Button E is pressed");
   draw_state=1;
   stage_state=1;
   life=2;
   flag=0;
   }
 
 else if(digitalRead(PIN_DIGITAL_D) == LOW) {
   Serial.println("Button D is pressed");
   draw_state=0;
   stage_state=1;
life=2;
flag=0;
 }
  Serial.print("x:");
  Serial.print(analogRead(PIN_ANALOG_X));
  Serial.print(" ");
 
  Serial.print("y:");
  Serial.print(analogRead(PIN_ANALOG_Y));
  Serial.print(" ");  
 
 Serial.print(x);
 Serial.print(y);
  Serial.print(randx);
 Serial.print(randy);
 Serial.println();
if(analogRead(PIN_ANALOG_X)<100){
  y+=5;
  } 
else if(analogRead(PIN_ANALOG_X)>900){
  y-=5;
  }
 else if(analogRead(PIN_ANALOG_Y)<100){
  x-=5;
  } 
else if(analogRead(PIN_ANALOG_Y)>900){
  x+=5;
  }
 
}
