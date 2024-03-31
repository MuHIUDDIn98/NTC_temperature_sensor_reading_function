

#include<Arduino.h>
#define NTC_pin  34      // Pin, to which the voltage divider is connected Temperature sensor..
#define vd_power_pin 2        // 5V for the voltage divider 

int TempThreshold;
float readTemperature();

void setup(void) {
  pinMode(vd_power_pin,OUTPUT);
  Serial.begin(115200);  // initialize serial communication at a baud rate of 9600
}

void loop(void) {
if (Serial.available() > 0) {
  String input = Serial.readStringUntil('\n');  // Read the incoming data as a string
  input.trim();
  TempThreshold = input.toInt();  // Read the incoming integer value
    
      Serial.println(TempThreshold);
  }
float Temp = readTemperature();


}


float readTemperature(){
  float voltageDividerR1 = 9590;
  float BValue = 3576;
  float R1 = 10000;
  float T1 = 298.15;//25degree 273.15+25
  float R2 ;
  float T2 ;
  float a ;
  float b ;
  float c ;
  float d ;
  float e = 2.718281828 ;
  uint8_t i;
  float average = 0;
  float samples = 0; 
  int samplingrate = 100; // Number of samples
  int decimalPrecision = 3;
  digitalWrite(vd_power_pin,HIGH);
  for (i=0; i< samplingrate; i++) {
   samples += analogRead(NTC_pin);
   delay(10);
  }
  digitalWrite(vd_power_pin,LOW);
  average = samples/ samplingrate;

  R2 = (voltageDividerR1*average)/(1023-average);
 
  a = 1/T1;
  b = log10(R1/R2);
  c = b / log10(e);
  d = c / BValue ;
  T2 = 1 / (a- d);
  float Temp = T2 - 273.15;
  Serial.print(Temp,decimalPrecision);
  Serial.println(" °C");
  return Temp;
}


