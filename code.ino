// import Libraries
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// initialize constants
#define SmokeSensor  A1
#define DHTTYPE    DHT11
#define DHTSensor 4 // Digital pin connected to the DHT sensor 
#define UltraSonicTriggerA 5 // Ultra Sonic Sensor-A Trigger pin
#define UltraSonicEchoA 6 // Ultra Sonic Sensor-A Echo pin
#define UltraSonicTriggerB 3 // Ultra Sonic Sensor-B Trigger pin
#define UltraSonicEchoB 2 // Ultra Sonic Sensor-B Echo pin 
#define WaterSensor A0 // Water Sensor Analog pin 
#define SDA A4 // LCD Screen SDA Analog pin 
#define SCL A5 // LCD Screen SCL Analog pin
#define servoMotor 9 // servoMotor pin
#define red 13 // RGB LED red pin
#define green 12 // RGB LED green pin
#define blue 11 // RGB LED blue pin
#define buzzer 7 // Buzzer pin



// global variables
bool full=false;
bool smoke=false;
bool leakage=false;
bool opened=false;
bool highTemp=false;
bool highHumid=false;
uint32_t delayMS;
DHT_Unified dht(DHTSensor, DHTTYPE);
Servo myservo;  // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() { //  put your setup code here {runs once}
  pinMode(SmokeSensor, INPUT);
    
  pinMode(UltraSonicEchoA,INPUT); 
  pinMode(UltraSonicEchoB,INPUT); 
  pinMode(DHTSensor,INPUT); // Humidity and Temperature Sensor
  pinMode(A0,INPUT); // Water Sensor
  pinMode(A4,INPUT); // SDA
  pinMode(A5,INPUT); // SCL
  
  pinMode(UltraSonicTriggerA,OUTPUT); 
  pinMode(UltraSonicTriggerB,OUTPUT); 
  pinMode(servoMotor,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(buzzer,OUTPUT);
  
  Serial.begin(9600);
  
  myservo.attach(servoMotor);  // attaches the servo on pin 9 to the servo object
  
  lcd.begin(16,2);
  lcd.backlight();
  
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
} 

void setLightColor(bool r=false,bool g=false,bool b=false){
  digitalWrite(red, r);
  digitalWrite(green, g);
  digitalWrite(blue, b);
}

void statusLCD(int height=40){  // default trash height is set to 40 cm
  int percent;   // variable for the trash level measurement
  int distance;  // variable for the distance measurement
  long duration; // variable for the duration of sound wave travel
  int pos;    // variable to store the servo position
  int temp;   // variable to store tempreature value
  int humd;   // variable to store the servo position
  sensors_event_t event;

  delay(1000); // delay for 1 second
  
  // Measure distance from trashcan
  // Clears the trigPin condition
  digitalWrite(UltraSonicTriggerA, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(UltraSonicTriggerA, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonicTriggerA, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(UltraSonicEchoA, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (to and from)
  
  percent=map(height-distance,0,height,0,100);

  percent = percent<0?0:percent; // fix unwanted negative values
  if(percent<80){ // display trash level up to 80% 
    // update LCD output
    delay(delayMS); // minimum delay time between readings
    // Get temperature 
    dht.temperature().getEvent(&event);
    temp = event.temperature;
    // Get humidity 
    dht.humidity().getEvent(&event);
    humd = event.relative_humidity;

    // update LCD output
    lcd.clear();
    lcd.setCursor(1,1);
    lcd.print("Trash level:"+(String)percent+"%");
    lcd.setCursor(0,0);
    lcd.print("Temp:"+(String)temp+"C");
    lcd.print(" Hum:"+(String)humd+"%");
    full = false;
  }
  else{  // display full if above 80%
    // update LCD output
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Trash is full!");
    lcd.setCursor(2,1);
    lcd.print("Replace bag.");
    full = true;
    setLightColor(true,false,false); // set led color to red
  }
}

void personDetected(int threshold=100){
  
  long duration; // variable for the duration of sound wave travel
  int distance; // variable for the distance measurement
  
  // Measure distance from trashcan
  // Clears the trigPin condition
  digitalWrite(UltraSonicTriggerB, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(UltraSonicTriggerB, HIGH);
  delayMicroseconds(10);
  digitalWrite(UltraSonicTriggerB, LOW);
  
  duration = pulseIn(UltraSonicEchoB, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (to and from)
  // control servo motor
  if(distance<threshold && distance>0){ // opened the trashcan if distance is less than threshold
    if(not opened){
      for (int pos = 0; pos <= 180; pos+=1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);                       // waits 5ms for the servo to reach the position
      }
      opened = true;
    }
  }
  else{ // close the trash can and update the trash  level 
    if(opened){
      statusLCD(40);  // calculate new trash level 
      for (int pos = 180; pos >= 0; pos-=1) { // goes from 180 degrees to 0 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(5);                       // waits 5ms for the servo to reach the position
      }
      opened = false;
    }
  }
}

void smokeDetected(){
  int smokeValue; 
  smokeValue = analogRead(SmokeSensor); 
  Serial.println("smoke value:\t"+(String)smokeValue);
  if( smokeValue>600){
    // update LCD output
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Danger!");
    lcd.setCursor(0,1);
    lcd.print("Smoke Detected");
    smoke = true;
    setLightColor(true,true,true); // set led color to white
    tone(buzzer, 700, 5000);  // turn on alarm system
  }else{
    smoke = false;
  }
}

void leakageDetected(){
  int waterValue; 
  waterValue = analogRead(WaterSensor); 
  if( waterValue>100){
    // update LCD output
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Leakage detected!");
    lcd.setCursor(2,1);
    lcd.print("Replace bag.");
    leakage = true;
    setLightColor(false,false,true); // set led color to blue
  }else{
    leakage = false;
  }
}

void highTempDetected(){
  int temp; 
  sensors_event_t event;
  
  delay(delayMS); // minimum delay time between readings
  
  // Get temperature 
  dht.temperature().getEvent(&event);
  temp = event.temperature;

  if( temp>=50){
    // update LCD output
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Danger!");
    lcd.setCursor(0,1);
    lcd.print("High Temperature");
    highTemp = true;
    setLightColor(true,true,false); // set led color to orange
    tone(buzzer, 300, 5000);  // turn on alarm system
  }else{
    highTemp = false;
  }
}

void highHumidDetected(){
  int humd; 
  sensors_event_t event;
  
  delay(delayMS); // minimum delay time between readings
  
  // Get humidity 
  dht.humidity().getEvent(&event);
  humd = event.relative_humidity;

  if( humd>=80){
    // update LCD output
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Danger!");
    lcd.setCursor(2,1);
    lcd.print("High Humidity");
    highHumid = true;
    setLightColor(true,false,true); // set led color to violet
    tone(buzzer, 1400, 5000);  // turn on alarm system
  }else{
    highHumid = false;
  }
}

void loop() { //  put your main code here {runs repeatedly}
  // reset the led light color
  if (not leakage and not full and not smoke and not highTemp and not highHumid){
    setLightColor(false,true, false);// reset led color to green
  }
  statusLCD();
  personDetected();
  leakageDetected();
  highTempDetected();
  highHumidDetected();
  smokeDetected();
}
