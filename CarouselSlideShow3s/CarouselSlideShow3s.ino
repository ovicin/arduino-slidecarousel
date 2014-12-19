// based on this:
// Control 4 Kodak Carousel slide projectors with timing for each slide
// (cc) 2012-2013
// by: Gonzalo Ramírez Restucci (gonzalo@resist.cl)
// for "Eigenlicht" by Regina de Miguel.

// quick changes to control one carousel using 2 relays one for advancing forward and the other to go backward

#define RELAY_PIN 5

#define NO_SLIDES 40

/* timer interval in seconds */
#define TIMER_INTERVAL 3

//  pulse duration
int relayPulse = 700;

int cPos = 0;

unsigned long seconds;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  Serial.begin(9600);
  delay(5000); // wait 5 seconds until everything's running.
}

void loop() {       

  if (cPos < NO_SLIDES){
    advanceSlide(RELAY_PIN);
  }
  else
  {

  } 
}

void advanceSlide(int RelayPin) {
  seconds = TIMER_INTERVAL * 1000; // duration of next step

  digitalWrite(RelayPin,HIGH);
  delay(relayPulse);
  digitalWrite(RelayPin,LOW);

  cPos++;  // advance position for current car

  Serial.print("now at: ");
  Serial.println(cPos);

  Serial.print("waiting: ");
  Serial.print(seconds/1000);
  Serial.println(" seconds.");
  Serial.println("--");     

  delay(seconds);
}
