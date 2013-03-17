#define FORWARD_PIN 2
#define BACKWARD_PIN 3

//  pulse duration
int relayPulse = 700;

unsigned long seconds;

// position counter for each carousel with initial positions (1-1-1-1)
int cPos = 1;

// arrays with intervals for each carousel
int cTime[81] = {
// 00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,60,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80
   00,05,05,05,05,05,05,05,05,00,05,05,05,05,05,05,05,05,05,00,05,05,05,05,05,05,05,05,00,05,05,05,05,05,05,05,05,00,05,05,05,05,05,05,05,05,05,00,05,05,05,05,05,05,05,05,05,05,00,05,05,05,05,05,05,05,05,05,00,05,05,05,05,05,05,05,05,05,05,05,00
};
int cDir[81] = {
// 00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,60,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80
   00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00
}; 

void setup() {
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(BACKWARD_PIN, OUTPUT);
  Serial.begin(9600);
  delay(5000); // wait 5 seconds until everything's running.
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
     // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 'b') {
          Serial.print("Backward\n");
  	  digitalWrite(BACKWARD_PIN,HIGH);
	  delay(relayPulse);
	  digitalWrite(BACKWARD_PIN,LOW);

	  cPos--;  // advance position for current car

    } 
    if (inChar == 'f')
    {    
	  Serial.print("Forward\n");
	  digitalWrite(FORWARD_PIN,HIGH);
	  delay(relayPulse);
	  digitalWrite(FORWARD_PIN,LOW);

	  cPos++;  // advance position for current car

  }
  }
}
void loop() {       
  for(int i=0;i<4;i++) {
    //advanceSlide();
  }
}

void advanceSlide() {
  seconds = cTime[cPos] * 1000; // duration of next step

  Serial.print("Moving carousel ");

  if (cDir[cPos] == 0)
  {    
	  Serial.print("Forward\n");
	  digitalWrite(FORWARD_PIN,HIGH);
	  delay(relayPulse);
	  digitalWrite(FORWARD_PIN,LOW);

	  cPos++;  // advance position for current car

  }
  else
  {   
      Serial.print("Backward\n");
  	  digitalWrite(BACKWARD_PIN,HIGH);
	  delay(relayPulse);
	  digitalWrite(BACKWARD_PIN,LOW);

	  cPos--;  // advance position for current car

  }
	
  if (cPos > 80) { cPos = 0; }
  if (cPos < 0) { cPos = 80; }
  
  Serial.print("now at: ");
  Serial.println(cPos);

  Serial.print("waiting: ");
  Serial.print(seconds/1000);
  Serial.println(" seconds.");
  Serial.println("--");     

  delay(seconds);
}
