#include <LCD_I2C.h>

LCD_I2C lcd(0x27,16,2);

unsigned long time1 = 0;
int sensor1 = A0;
int sensor2 = A1;
unsigned long startmillis=0;
unsigned long endmillis=0;

void setup(){
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("SPEED MATCH");
  lcd.setCursor(5,1);
  lcd.print("Ready");
}
enum COUNTSTATES
{
  ST_OFF,
  ST_COUNTING,
  ST_DONE,
};

COUNTSTATES countState=ST_OFF;

void loop (){
  int value1=analogRead(sensor1);
  int value2=analogRead(sensor2);
  switch(countState)
 {
  case ST_OFF:
  countoff(value1,value2);
  break;
  case ST_COUNTING:
  counting(value1,value2);
  break;
  case ST_DONE:
  countdone(value1,value2);
  break;
 }
}

void countoff(int value1, int value2){
  if (value1<500){
   startmillis=(millis());
   countState=ST_COUNTING;
  }
}

void counting(int value1, int value2){
  if (value2<500){
    endmillis=(millis());
    countState=ST_DONE;
  }
}

void countdone(int value1, int value2){
  time1=(endmillis-startmillis);
  Serial.println(time1);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Time in millis");
  lcd.setCursor(6,1);
  lcd.print(time1);
  
}
