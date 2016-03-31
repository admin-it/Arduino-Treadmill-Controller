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
int inclineCount = 11; 
void setup()
{
  //USE THIS SKETCH FOR SPEED CHANGE TREADMILL USE HI ON PIN 13 TO CHANGE INCLINE
  pinMode(inUpRelay, OUTPUT);
  pinMode(inDownRelay, OUTPUT);
  pinMode(inUp, OUTPUT);
  pinMode(inDown, OUTPUT);
  pinMode(spdPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{

  if (Serial.available()) {
    command = Serial.read();
   
    switch (command) {
      case 48: //Slow Down
        
        if (spd - .01 >= 0.0) {
          spd = spd - .01;
          //setMotorSpeed(spd);
        }
        break;
      case 49: //Speed Up
        if (spd + .01 <= 1.0) {
          
          spd = spd + .01;
          //setMotorSpeed(spd);
      }
      //change speed
      break;
      case 50:
        up = true;
        down = false;
        inclineCount = 0; 
      break;

      case 51:
        up = false;
        down = true;
        inclineCount = 0; 
      break;
      default:
        Serial.print("invalid command");
      break;
    }
}

if(inclineCount <= 10){
  Serial.print("in if");
  setIncline(up,down);
  inclineCount++;
}
Serial.print(spd);
Serial.print("\n");
setMotorSpeed(spd);
}

void setMotorSpeed(float spd){
  onTime = floor(spd * 50);
  digitalWrite(spdPin, HIGH);
  delay(onTime);
  digitalWrite(spdPin, LOW);
  delay(50 - onTime); 
}

void setIncline(boolean up, boolean down){
  
  if(up == true && down == false){
    digitalWrite(inUpRelay,HIGH); 
    digitalWrite(inDownRelay,LOW);
    digitalWrite(inUp,HIGH);
    digitalWrite(inDown,LOW);
    
  }else if(up == false && down == true){
    digitalWrite(inUpRelay,LOW); 
    digitalWrite(inDownRelay,HIGH);
    digitalWrite(inUp,LOW);
    digitalWrite(inDown,HIGH);
    
  }
  if(inclineCount == 10){
    digitalWrite(inUpRelay,LOW); 
    digitalWrite(inDownRelay,LOW);
    digitalWrite(inUp,LOW);
    digitalWrite(inDown,LOW);
  
  }
  
}





