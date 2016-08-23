void setup() {
  pinMode(7, INPUT);
   pinMode(8, OUTPUT);
   digitalWrite(8, HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(7) == LOW){
    Serial.println("LOW");
  }
  else{
    Serial.println("high");
  }
}
