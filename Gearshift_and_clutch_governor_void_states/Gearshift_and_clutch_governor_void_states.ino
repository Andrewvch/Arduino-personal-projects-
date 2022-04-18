#include <Servo.h>
Servo clutch;
int led = 3;
int clutchled = 4;
int throttleled = 5;
int shiftled = 6;
int throttlepin = 0;
int throttle;
int downbutton = 7;
int upbutton = 8;
int up;
int down;
int upp;
int downn;
int delayval;
int delayvar;
int sportmodepin = 47;
int sportmode;
int Sport;
int Sportled = 9;
int motorpin = 10;
int clutchpin = 11;
int val;

void setup() {
  clutch.attach(clutchpin);
  pinMode(led, OUTPUT);
  pinMode(clutchled, OUTPUT);
  pinMode(throttleled, OUTPUT);
  pinMode(shiftled, OUTPUT);
  pinMode(downbutton, INPUT);
  pinMode(upbutton, INPUT);
  pinMode(throttlepin, INPUT);
  pinMode(Sportled, OUTPUT);
  pinMode(clutchpin, OUTPUT);// put your setup code here, to run once:
  Serial.begin(9600);
  Sport = 0;
}

void loop() {

  sportmode = digitalRead(sportmodepin);
  clutch.write(159);

  if (sportmode == HIGH) {
    Sport = Sport + 1;
    delay(1100);
  }

  if (Sport == 0) {
    Comfortmode();
  }
  if (Sport == 1) {
    Sportmode();
  }

  if (Sport == 2 ) {
    Sport = 0;
  }

  Serial.println(val);
}


void Upshift() {
  digitalWrite(led, LOW);
  digitalWrite(motorpin, 0);
  delay(5);
  digitalWrite(clutchled, HIGH);
  clutch.write(148);
  delay(delayval);
  digitalWrite(shiftled, HIGH);
  delay(delayval);
  digitalWrite(shiftled, LOW);
  delay(5);
  digitalWrite(clutchled, LOW);
  clutch.write(159);
  delay(100);

}

void Downshift() {
  digitalWrite(led, LOW);
  digitalWrite(motorpin, 0);
  delay(5);
  digitalWrite(clutchled, HIGH);
  clutch.write(154);
  delay(80);
  digitalWrite(throttleled, HIGH);
  digitalWrite(motorpin, throttle);
  delay(50);
  digitalWrite(throttleled, LOW);
  digitalWrite(motorpin, 0);
  delay(50);
  digitalWrite(shiftled, HIGH);
  delay(80);
  digitalWrite(shiftled, LOW);
  delay(5);
  digitalWrite(clutchled, LOW);
  clutch.write(159);
  delay(100);


}
void Comfortmode() {
  throttle = analogRead(throttlepin);
  throttle = map(throttle, 0, 1023, 0, 254);// put your main code here, to run repeatedly:
  analogWrite(led, throttle);
  analogWrite(motorpin, throttle);
  up = digitalRead(upbutton);
  down = digitalRead(downbutton);
  delayvar  = analogRead(throttlepin);
  delayvar = map(delayvar, 0, 1023, 0, 25);
  delayval = 100 - (delayvar);
  digitalWrite(Sportled, LOW);
  val = analogRead(throttlepin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 500);     // scale it to use it with the servo (value between 0 and 180)
  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
  if (up == HIGH) {
    Upshift();
  }


  if (down == HIGH) {
    Downshift();
  }

}


void Sportmode() {
  throttle = analogRead(throttlepin);
  throttle = map(throttle, 0, 1023, 0, 254);// put your main code here, to run repeatedly:
  analogWrite(led, throttle);
  analogWrite(motorpin, throttle);
  up = digitalRead(upbutton);
  down = digitalRead(downbutton);
  delayvar  = analogRead(throttlepin);
  delayvar = map(delayvar, 0, 1023, 0, 50);
  delayval = 80 - (delayvar);
  digitalWrite(Sportled, HIGH);

  if (up == HIGH) {
    Upshift();
  }


  if (down == HIGH) {
    Downshift();
  }

}
