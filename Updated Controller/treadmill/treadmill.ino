

#define echoPin 5 // Echo Pin
#define trigPin 6 // Trigger Pin
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

int onTime;
int inUpRelay = 9;
int inDownRelay = 10;
int inUp = 11;
int inDown = 12;
int spdPin = 13;
int command = 5;
float spd = 0.0;
boolean up = false;
boolean down = false;
boolean initialize = true;
int inclineCount = 11;
void setup()
{
  //USE THIS SKETCH FOR SPEED CHANGE TREADMILL USE HI ON PIN 13 TO CHANGE INCLINE
  pinMode(3, OUTPUT); // for relay board
  digitalWrite(3, HIGH); // turns on relay
  pinMode(inUpRelay, OUTPUT);
  pinMode(inDownRelay, OUTPUT);
  pinMode(inUp, OUTPUT);
  pinMode(inDown, OUTPUT);
  pinMode(spdPin, OUTPUT);
  pinMode(2, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);


}

void loop()
{
  if (initialize == true) {
    calibrate();
    initialize = false;
  }
  if (Serial.available()) {
    command = Serial.read();
    switch (command) {
      case 48: //Slow Down
        if (spd <= 0.09) {
          spd = 0.0;
        } else if (spd - 0.01 >= 0.09) {
          spd = spd - .01;
          //setMotorSpeed(spd);
        }
        break;
      case 49: //Speed Up
        if (spd == 0.0) {
          spd = 0.09;
        } else if (spd + .01 <= 0.96) {
          spd = spd + .01;
        }
        //change speed
        break;
      case 50:
        up = true;
        down = false;
        inclineCount = inclineCount - 11;
        break;

      case 51:
        up = false;
        down = true;
        inclineCount = inclineCount - 11;
        break;

      case 52:
        spd = 0.0;
        break;
      default:
        //Serial.print("invalid command");
        break;
    }
    if (spd >= 0.09) {
      Serial.print(spd + 0.04);
    } else {
      Serial.print(0.0);
    }
    Serial.print("\n");
  }

  if (inclineCount <= 20) {
    // Serial.print("in if");
    setIncline(up, down);
    inclineCount++;
  }
  //Serial.print(spd);
  //Serial.print("\n");
  setMotorSpeed(spd);
}

void setMotorSpeed(float spd) {
  onTime = floor(spd * 50);
  digitalWrite(spdPin, HIGH);
  delay(onTime);
  digitalWrite(spdPin, LOW);
  delay(50 - onTime);
}

void setIncline(boolean up, boolean down) {
  updateHeight();

  if (distance < 18 && up == true && down == false) {
    digitalWrite(inUpRelay, HIGH);
    digitalWrite(inDownRelay, LOW);
    digitalWrite(inUp, HIGH);
    digitalWrite(inDown, LOW);

  } else if (distance > 5 && up == false && down == true) {
    digitalWrite(inUpRelay, LOW);
    digitalWrite(inDownRelay, HIGH);
    digitalWrite(inUp, LOW);
    digitalWrite(inDown, HIGH);

  }
  if (inclineCount == 20) {
    digitalWrite(inUpRelay, LOW);
    digitalWrite(inDownRelay, LOW);
    digitalWrite(inUp, LOW);
    digitalWrite(inDown, LOW);

  }

}

void calibrate() {
  boolean calibrate = true;
  updateHeight();
  if (distance > 5) {
    digitalWrite(inUpRelay, LOW);
    digitalWrite(inDownRelay, HIGH);
    digitalWrite(inUp, LOW);
    digitalWrite(inDown, HIGH);
    delay(50);
    while (calibrate == true) {
      updateHeight();
      if (distance < 6) {
        digitalWrite(inUpRelay, LOW);
        digitalWrite(inDownRelay, LOW);
        digitalWrite(inUp, LOW);
        digitalWrite(inDown, LOW);
        calibrate = false;
      }
      delay(50);

    }
  }



}

void updateHeight() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

}

