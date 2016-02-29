//Created by Enyil Valle (pdllvlle)
//Basic Serial communication for either bluetooth & cable

int command = -1; //stores the command in ACSII code.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Starts serial communication using 9600 baud.
  pinMode(13, OUTPUT); //Pin 13 contains the LED to control.
  //Prints intructions to user over the console.
  Serial.println("Please enter 0 or 1 to turn on/off LED on PIN 13");
}

void loop() {
  // put your main code here, to run repeatedly:
  if( Serial.available() > 0 ) { //only if a new command is received. 
    command = Serial.read(); //Reads the command to ASCII value.
    switch(command){
      case 48: //ASCII code for 0.
       digitalWrite(13, LOW); //Writes to the pin.
      break;
      case 49; //ASCII code for 1. //Writes to the pin.
        digitalWrite(13, HIGH);
      break;
  }
}
