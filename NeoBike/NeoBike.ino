
#include <Servo.h>

Servo s;
Servo r;// create servo object to control a servo
int temp = 2;
int led = 8;
int val;
int gaspotmeter = 0;
int rempotmeter = 1;
int motor = 11;
int rempot = 1;
int rempin = 12;
int rem;
int richtingpin = 13;
int achteruit;
int reverseknop = 10;
int reverse;
//int snelservo = 8;
int valsnelheid;
int valv;
int valrem;
int templed = 2;
int achterled = 3;

//int potMeter = A0;  // analog pin used to connect the potentiometer
int servopin = 9;
int ledpin = 6;
void setup() {
  Serial.begin(9600);
  
  s.attach(servopin);  // attaches the servo on pin 9 to the servo object
  r.attach(rempin);
   pinMode(reverseknop, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(gaspotmeter, INPUT);
  pinMode(rempot, INPUT);
  pinMode(richtingpin, OUTPUT);

  reverse = 0;
}

void loop() {
  
  int servoValue = map(analogRead(gaspotmeter), 0, 1023, 0, 270);     // scale it to use it with the servo (value between 0 and 180)
  Serial.println(reverse);
  s.write(servoValue);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
    valsnelheid = analogRead(gaspotmeter);
  valsnelheid = map(valsnelheid, 0, 1023, 0, 254);
  valsnelheid = constrain(valsnelheid, 0, 254);
  analogWrite(motor, valsnelheid);
  val = analogRead(temp);
  rem = analogRead(rempot);
  rem = map(rem, 0, 1023, 0, 250);
  r.write(rem);// put your main code here, to run repeatedly:
  if (digitalRead(reverseknop) == HIGH){
    reverse = reverse +1;
    delay(500);
  }
  else if (digitalRead(reverseknop) == LOW){
    reverse = reverse;
  }
  if (reverse == 0){
      digitalWrite(richtingpin, HIGH);
  }
  if (reverse == 1){
    digitalWrite(richtingpin, LOW);
  }
  if(reverse == 2){
    reverse = 0;
  }
  if (val < 925){
    digitalWrite(led, HIGH);
    
  }
  else if (val > 925) {
    digitalWrite(led, LOW);
  }
  if (servoValue > 179){
  digitalWrite(ledpin, HIGH);
  } 
  else if (servoValue < 179){ 
  digitalWrite(ledpin, LOW); 
  }
  
}
