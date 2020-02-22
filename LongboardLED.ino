#include <FastLED.h>
#include <SoftwareSerial.h>

#define NUM_LEDS 112
#define DATA_PIN 6
#define BTN 2
#define BTNUP 3
#define BTNDWN 4
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

SoftwareSerial mySerial(0,1);
CRGB leds[NUM_LEDS];
float brightness = 0.5;
uint8_t modeNumber = 0;
uint8_t gHue = 0;
uint8_t gHueSpeed = 5;
bool pressed = false; //for registering 1 button press until button is released
char data;  //BT data
typedef void (*SimplePatternList[])();
const uint8_t maxBrightness[] =       {170      , 170       , 220          , 100         , 100         , 100        };

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600); //BT serial
  pinMode(BTN, INPUT);
  pinMode(BTNUP, INPUT);
  pinMode(BTNDWN, INPUT);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness((int)(brightness*maxBrightness[modeNumber]));
  leds[0] = CHSV(0,0,0); //Must be called so that there arent any artifacts in rainbow
}

SimplePatternList gPatterns = {solidGreen, solidWhite, gradientGreen, rainbowRound, rainbowSolid, rainbowDown};

void loop(){
  gPatterns[modeNumber]();
  FastLED.show();
  FastLED.delay(1000/120);
  EVERY_N_MILLISECONDS( 1 ) { gHue+=gHueSpeed;} 
  if(digitalRead(BTN)==HIGH && !pressed){pressed=true;nextMode();}
  else if (digitalRead(BTN)==LOW && pressed) pressed=false;
  if(digitalRead(BTNUP)==HIGH && brightness<1) FastLED.setBrightness((int)((brightness+=0.01)*maxBrightness[modeNumber]));
  if(digitalRead(BTNDWN)==HIGH && brightness>0.05) FastLED.setBrightness((int)((brightness-=0.01)*maxBrightness[modeNumber]));
  Serial.println((int)((brightness)*maxBrightness[modeNumber]));
  if(mySerial.available() > 0){ data = mySerial.read(); Serial.println(data);}
  if(Serial.available()) mySerial.write(Serial.read());
}

//Switch between modes
void nextMode(){modeNumber = (modeNumber+1)% ARRAY_SIZE(gPatterns);} 
//Solid green mode
void solidGreen(){fill_solid(leds, NUM_LEDS, CRGB(0,255,0));}
//Solid white mode
void solidWhite(){fill_solid(leds, NUM_LEDS, CRGB(50,70,85));}
//Green on one end, white on the other -- since it loops i used a cosine function to vary the R and B values
void gradientGreen(){for(float i=0;i<NUM_LEDS;i++){uint8_t val = floor(0.2*cos8(floor((i/NUM_LEDS)*255)));leds[(int)i] = CRGB(val,120,val);}}
//Cycle rainbow clockwise
void rainbowRound(){fill_rainbow(leds, NUM_LEDS, gHue, 7);gHueSpeed=5;}
//All lights cycle through the same colours at the same time
void rainbowSolid(){fill_rainbow(leds, NUM_LEDS, gHue, 0);gHueSpeed=2;}
//Rainbow starts from the top and moves down on both sides
void rainbowDown(){fill_rainbow(leds, NUM_LEDS, gHue+84, -3); fill_rainbow(leds, NUM_LEDS/2, gHue, 3);gHueSpeed=2;}
