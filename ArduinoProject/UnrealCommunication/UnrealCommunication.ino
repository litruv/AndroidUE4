bool switch1Last;
bool switch2Last;

void setup() {
  Serial.begin(115200);
  pinMode(13, INPUT);
  pinMode(15, INPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(14, LOW);
  
  switch1Last = digitalRead(13);
  switch2Last = digitalRead(15);
}


void loop() {
  if (digitalRead(13) != switch1Last) {
    switch1Last = digitalRead(13);
    if (switch1Last)
      Serial.println("e1,1");
    else
      Serial.println("e1,0");
  }
  if (digitalRead(15) != switch2Last) {
    switch2Last = digitalRead(15);
    
    if (switch2Last)
      Serial.println("e2,1");
    else
      Serial.println("e2,0");
  }

  if (Serial.available() > 1) {
    String str = Serial.readString();
    if (str.startsWith("id")) {
      Serial.println("iGameController");
    }
    else if (str.startsWith("e")){
      str.trim();
      str.replace("e", "");
      int delimiter = str.indexOf(',');

      int param1 = str.substring(0, delimiter).toInt();
      int param2 = str.substring(delimiter+1, str.length()).toInt();
      
      Serial.println(str.substring(delimiter+1, str.length()));
      Serial.println(param2);


      switch(param1)
      {
        case 1:
          event1(param2);
          break;
        case 2:
          event2(param2);
          break;
        default:
          break;
      }

      str = "";
      param1 = param2 = 0;
    }
    else {
      Serial.print("s");
      Serial.println(str);
    }
  }
}

void event1(int param)
{
  if (param == 1)
    digitalWrite(12, HIGH);
  else
    digitalWrite(12,LOW);

    
      Serial.print("se1: ");
      Serial.println(param);
}

void event2(int param)
{
  if (param == 1)
    digitalWrite(14, HIGH);
  else
    digitalWrite(14,LOW);
}


