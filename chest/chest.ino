int lightPin = 0;
int lightLast[3] = {1000, 1000, 1000};
bool lightOn = false;
bool playedAlready = false;

int buzzPin = 9;
int length = 15;
char notes[] = "ccggaagffeeddc ";
int beats[] = {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4};
int tempo = 300;

int bendPin = 5;
bool bendOn = false;
int bendLast[3] = {1000, 1000, 1000};

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
}

void play(){
  for (int i = 0; i < length; i++){
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    
    // pause between notes
    delay(tempo / 2); 
  }
}   

void loop(){
  int lightLevel = analogRead(lightPin);
  Serial.print("Light: ");
  Serial.println(lightLevel);
  lightLast[0] = lightLast[1];
  lightLast[1] = lightLast[2];
  lightLast[2] = lightLevel;
  
  int bendLevel = analogRead(bendPin);
  Serial.print("Bend: ");
  Serial.println(bendLevel);
  bendLast[0] = bendLast[1];
  bendLast[1] = bendLast[2];
  bendLast[2] = bendLevel;
  
  if (lightLast[0] < 300 && lightLast[1] < 300 && lightLast[2] < 300 && !lightOn ){
    Serial.println("Light ON");
    lightOn = true;
  }
  
  if (bendLast[0] < 220 && bendLast[1] < 220 && bendLast[2] < 220 && !bendOn ){
    Serial.println("Bend ON");
    bendOn = true;
  }
  
  if ((lightOn || bendOn) && !playedAlready){
    play();
    playedAlready = true;
  }

  delay(500);
}
  
