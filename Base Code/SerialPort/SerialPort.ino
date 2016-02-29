//Created by Enyil Valle (pdllvlle)
//Basic Serial communication for either bluetooth & cable

int command = -1; //stores the command in ACSII code.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  Serial.println("Please enter 0 or 1 to turn on/off LED on PIN 13");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    command = Serial.read();
    switch(command){
      case 48:
       digitalWrite(13, LOW);
      break;
      
      case 49;
        digitalWrite(13, HIGH);
      break;

      case 50;
        digitalWrite(13, HIGH);
      break;

      case 51;
        digitalWrite(13, HIGH);
      break;
  }
}
