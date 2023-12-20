const int numPins = 11;
const int numSubPins = 5;
int pot = A0;
int flevel = 0;
int mosfetPin = 11; // MOSFET control pin
int subRange = 0;

int controlPins[numPins] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
int subControlPins[numSubPins] = {A5, A4, A3, A2, A1};

void setup() {
  pinMode(13, OUTPUT);
  pinMode(pot, INPUT);
  pinMode(mosfetPin, OUTPUT); // Control MOSFET
  digitalWrite(mosfetPin, LOW); // Initialize MOSFET to LOW
}

void subcntrl(int sublevel) {
  if (flevel <= 325){
    pinMode(A1, OUTPUT);
    digitalWrite(A1, LOW);
  }else{
  for (int i = 0; i < numSubPins; i++) {
    pinMode(subControlPins[i], i == sublevel ? OUTPUT : INPUT);
    digitalWrite(subControlPins[i], LOW);
  }
  }
}

void cntrl(int level) {
  for (int i = 0; i < numPins; i++) {
    pinMode(controlPins[i], i <= level ? OUTPUT : INPUT);
    digitalWrite(controlPins[i], LOW); // Set to LOW to turn off pins that are not in use
  }
}

void loop() {
  flevel = analogRead(pot);
  int level = map(flevel, 490, 135, 0, 11);

  subRange = map(flevel, 490, 325, 0, 5);

  digitalWrite(mosfetPin, flevel > 380);

  cntrl(level);
  subcntrl(subRange);
  hrtbeat();
}
void hrtbeat(){
  digitalWrite(13, HIGH);
  delay(1);
  digitalWrite(13, LOW);
  delay(50);
}