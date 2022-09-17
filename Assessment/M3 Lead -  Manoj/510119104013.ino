

#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
 
#define red 5
#define blue 4
#define green 3
#define bulb 6

#define motor 2

#define PIR_In 7
 
int sensor_Input;
float temp;
      
void setup() 
	{
    	Serial.begin(9600);
    	lcd.begin(16, 2);
	pinMode(red,OUTPUT);
	pinMode(blue,OUTPUT);	
	pinMode(green, OUTPUT);	
	pinMode(motor, OUTPUT);	
	pinMode(PIR_In, INPUT);
	pinMode(bulb, OUTPUT);
  	}

void loop() 
	{
    	measure_Temp();
    	display_Temp();
  	led_d();
	check_For_Intruder();
  	}
  
void measure_Temp()
  	{
    	sensor_Input = analogRead(A0);
    	temp = (float)sensor_Input / 1024;
    	temp = temp * 5;
    	temp = temp - 0.5;
    	temp = temp * 100;
  	}

void check_For_Intruder()
  	{
    	boolean sensorvalue= digitalRead(PIR_In);
    	if(sensorvalue==1)
     		{
      		digitalWrite(bulb,HIGH);
      		lcd.setCursor(0,0);
      		lcd.print("Welcome Sir_____");
      		lcd.setCursor(0,1);
      		lcd.print("In House________");
          	digitalWrite(motor,HIGH);
      		delay(5000);
      		lcd.clear();
     		}
	else
		{     
      		digitalWrite(bulb,LOW);
         	}
     	delay(10);    
    	}

void display_Temp()
  	{
    	lcd.setCursor(0, 0);
    	Serial.print("Temp. in Celcius: ");
    	Serial.print(temp);
    	Serial.println();
    	lcd.print("Temp. in Celcius: ");
    	lcd.setCursor(5, 1);
    	lcd.print(temp);
if(temp>25){
	lcd.setCursor(11, 1);
	lcd.print("M-ON_");}
else{lcd.setCursor(11, 1);
	lcd.print("M-OFF");}

    	delay(500);
  	}
void led_d(){
	if(temp<25){
		digitalWrite(red,LOW);
		digitalWrite(blue,LOW);
		digitalWrite(green,HIGH);
		}
	if(temp<30 && temp>25){
		digitalWrite(red,LOW);
		digitalWrite(blue,HIGH);
		digitalWrite(green,LOW);
		}
	if(temp>40){
		digitalWrite(red,HIGH);
		digitalWrite(blue,LOW);
		digitalWrite(green,LOW);
		}
	if(temp>25){
		digitalWrite(motor,HIGH);
		}
  	if(temp<25){
		digitalWrite(motor,LOW);
		}
}


