#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int val;    // variable to read the value from the analog pin

int trigPin = 11;    // TRIG pin
int echoPin = 12;    // ECHO pin
float duration_us, distance_cm;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  // begin serial port
  Serial.begin (9600);
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}

void loop() {

  for (val = 0 ; val < 180; val++)
  {
    if(radar_sensor_signal())
    {
      val+=50;
    }
    if(val>180)
    {
      val = 180;
    }
    myservo.write(val);             // sets the servo position according to the scaled value
      delay(15); 
  }

  for (val = 180 ; val > 0; val--)
  {
    if(radar_sensor_signal())
    {
      val-=50;
    }
    if(val<0)
    {
      val =0;
    }
    myservo.write(val);             // sets the servo position according to the scaled value
      delay(15); 
  }


}


bool radar_sensor_signal()
{
    // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  //Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.print(",");
  Serial.print(val);
  Serial.println(".");
  delay(50);

  if (distance_cm < 10)
  {
     return true;
  }
  else 
  {
    return false;
  }
}