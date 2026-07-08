#include "arduino_secrets.h"
#include "thingProperties.h"

const int Switch1 = 4;
const int Switch2 = 5;
const int Switch3 = 18;
const int Switch4 = 22;
const int ldr = 12;

void setup() {
  Serial.begin(9600);
  delay(1500);

  pinMode(Switch1, OUTPUT);
  pinMode(Switch2, OUTPUT);
  pinMode(Switch3, OUTPUT);
  pinMode(Switch4, OUTPUT);
  pinMode(ldr, INPUT);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  int LDR = digitalRead(ldr);

  // ---------- BEDROOM LIGHT CONTROL ----------
  if (bEDROOM || LDR == 1) {             // Either Alexa says ON or it's dark
    digitalWrite(Switch1, LOW);          // Relay ON (active LOW)

    if (!bEDROOM) {                      // If Alexa still shows OFF
      bEDROOM = true;
      ArduinoCloud.update();
    }

    Serial.println("BEDROOM LIGHT ON");
  } 
  else {
    digitalWrite(Switch1, HIGH);         // Relay OFF

    if (bEDROOM) {
      bEDROOM = false;
      ArduinoCloud.update();
    }

    Serial.println("BEDROOM LIGHT OFF");
  }

  // ---------- HALL LIGHT CONTROL ----------
  if (hALL) {
    digitalWrite(Switch2, LOW);
    Serial.println("HALL LIGHT ON");
  } else {
    digitalWrite(Switch2, HIGH);
    Serial.println("HALL LIGHT OFF");
  }

  // ---------- KITCHEN LIGHT CONTROL ----------
  if (kITCHEN) {
    digitalWrite(Switch3, LOW);
    Serial.println("KITCHEN LIGHT ON");
  } else {
    digitalWrite(Switch3, HIGH);
    Serial.println("KITCHEN LIGHT OFF");
  }

  // ---------- WASHROOM LIGHT CONTROL ----------
  if (wASHROOM) {
    digitalWrite(Switch4, LOW);
    Serial.println("WASHROOM LIGHT ON");
  } else {
    digitalWrite(Switch4, HIGH);
    Serial.println("WASHROOM LIGHT OFF");
  }

  delay(100);
}


// ---------- CALLBACK FUNCTIONS ----------
void onBEDROOMChange()  { }
void onHALLChange()     { }
void onKITCHENChange()  { }
void onWASHROOMChange() { }

