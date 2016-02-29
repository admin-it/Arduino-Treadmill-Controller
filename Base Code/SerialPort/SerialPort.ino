//Created by Enyil Valle (pdllvlle) and Cannon Moyer (wcmoyer)
//Basic Serial communication for either bluetooth or cable
int SPEED_PWM_OUT = 9;
int INCLINE_PWM_OUT = 13;
float spd = 0.0;
int onTime;
bool incline = false;
int command = -1; //stores the command in ACSII code.

void setup() {
  Serial.begin(9600); //Starts serial communication using 9600 baud.
  pinMode(13, OUTPUT); //Pin 13 contains the LED to control.
  Serial.println("Please enter 0 or 1 to turn on/off LED on PIN 13");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    command = Serial.read();
    switch (command) {
      case 48: //Slow Down
        if (spd - .1 >= 0) {
          spd = spd - .1;
          setMotorSpeed(spd);
        }
        break;
      case 49: //Speed Up
        if (spd - .1 >= 0) {
          spd = spd - .1;
          setMotorSpeed(spd);
        }
        //change speed
        break;
      case 50: //Incline Up
        if (incline == false) {
          incline = true;
          setIncline(incline);
        }
        //change speed
        break;
      case 51: //Incline Down
        if (incline = true) {
          incline = false;
          setIncline(incline);
        }
        //change speed
        break;
    }
  }
  setMotorSpeed(spd);
}

void setMotorSpeed(int spd) {
  onTime = floor(spd * 50);
  digitalWrite(SPEED_PWM_OUT, HIGH);
  delay(onTime);
  digitalWrite(SPEED_PWM_OUT, LOW);
  delay(50 - onTime);
  delay(50);
}

void setIncline(bool operation) {
  if (operation == true) {
    digitalWrite(INCLINE_PWM_OUT, HIGH);
  } else {
    digitalWrite(INCLINE_PWM_OUT, LOW);
  }
}


