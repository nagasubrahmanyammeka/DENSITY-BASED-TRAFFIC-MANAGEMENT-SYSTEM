#include <LiquidCrystal.h> 
const int rs =8, en =9, d4 =10, d5 =11, d6 =12, d7 =13; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <Adafruit_NeoPixel.h> 
#ifdef AVR
#include <avr/power.h> 
#endif
#define LED_PIN  2
#define LED_COUNT 4
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB+ NEO_KHZ800);
uint32_t red=strip.Color(255, 0, 0);
uint32_t green=strip.Color(0, 255, 0); int dir=0;
int gs=A5; 
int es=5;
int ws=6; 
int ns=A0;
int ss=A1;
int rf=3; 
int buz=4;
int pt=0;
int et=0,wt=0,nt=0,st=0;
int k=0;
int cnt=0;
int vs=0,gval=0; 
void scan()
{
et=1-digitalRead(es); 
wt=1-digitalRead(ws); 
nt=1-digitalRead(ns); 
st=1-digitalRead(ss);
}
void setup()
{
pinMode(es,INPUT);
pinMode(ws,INPUT); 
pinMode(ns,INPUT); 
pinMode(ss,INPUT); 
pinMode(buz,OUTPUT);
pinMode(rf,INPUT_PULLUP);
Serial.begin(9600);
//wifi.begin(115200);
lcd.begin(16, 2);
lcd.print(" WELCOME");
strip.begin(); strip.show();
strip.setBrightness(50); 
delay(1500); 
lcd.clear(); 
lcd.setCursor(0,0);
lcd.print("SMART & DYNAMIC"); 
lcd.setCursor(0,1);
lcd.print("TRAFFIC SYSTEM");
strip.setPixelColor(0, red); 
strip.setPixelColor(1, red);
strip.setPixelColor(2, red);
strip.setPixelColor(3, red); 
strip.show();
lcd.clear();
lcd.setCursor(0,0); 
lcd.print("E: W: N: S:"); 
lcd.setCursor(0,1); 
lcd.print("G: ");
}
void loop(){
  cnt++;
scan(); 
//Serial.println(k);
if(cnt>150)
{
Serial.print("452399,YQGJDQ59M8HJP43B,0,0,project,12345678,"+String(et)+","+String(wt) + ","+String(nt)+","+String(st) + ","+String(gval)+",\n");
cnt=0;
}
if(k==0)
{
strip.setPixelColor(0, green); strip.setPixelColor(1, red); strip.setPixelColor(2, red); strip.setPixelColor(3, red); strip.show();
dir='E';
if(et==0) pt=10; else pt=20;
}
if(k==1)
{
strip.setPixelColor(0, red); strip.setPixelColor(1, green); strip.setPixelColor(2, red); strip.setPixelColor(3, red); strip.show();
dir='W'; if(wt==0) pt=10; else pt=20;
}
if(k==2)
{
strip.setPixelColor(0, red); strip.setPixelColor(1, red); strip.setPixelColor(2, green); strip.setPixelColor(3, red); strip.show();
dir='N'; 
if(nt==0)
pt=10;
else pt=20;
}
if(k==3)
{
strip.setPixelColor(0, red); 
strip.setPixelColor(1, red);
strip.setPixelColor(2, red);
strip.setPixelColor(3, green);
strip.show();
dir='S';
if(st==0) pt=10; else pt=20;
}
k=k+1; if(k==4) k=0;
for(int ii=pt;ii>0;ii--)
{
gval=analogRead(gs)/5;
lcd.clear(); lcd.setCursor(0,0);
lcd.print("E:" + String(et) + " W:" + String(wt) + " N:" + String(nt) + " S:" + String(st));
lcd.setCursor(0,1);
lcd.print(String(char(dir))+":" + String(ii)+ " G:" + String(gval));
delay(1000);
}
}