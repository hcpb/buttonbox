/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
int count = 0;
int debounce = 0;
int incomingByte = 0;   // for incoming serial data
int Red, Grn, Yel, Wht, Blu, Camcorder, Ringlight;

// inputs for arcade buttons, outputs for leds and things...
int teensyLED = 13;
int kGrn = 0; // goes to PTD0
int kRed = 1; // goes to PTD1
int kYel = 2; // goes to PTD2
int kWht = 12; // this pin seemed to need an extrernal pull, too, 1k
int kBlu = 13; // This is also the LED pin... external pull needed, 470

int lGrn = 8; // goes to PTC0
int lRed = 9; // goes to PTC2
int lYel = 10; // goes to PTC4
int lLooksee = 11; // historical... unconnected on 5 button box...
int lWht = 4; // 
int lBlu = 5; //
int lCamcorder = 6; //
int lRinglight = 7; //

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(teensyLED, OUTPUT);
  pinMode(kRed, INPUT_PULLUP);     // sets the digital pin as input
  pinMode(kGrn, INPUT_PULLUP);     // sets the digital pin as input
  pinMode(kYel, INPUT_PULLUP);     // sets the digital pin as input  
  pinMode(kWht, INPUT_PULLUP);       // external pull required, 1k
  pinMode(kBlu, INPUT_PULLUP);       // external pull required, 470

  pinMode(lRed, OUTPUT);
  pinMode(lGrn, OUTPUT);
  pinMode(lYel, OUTPUT);
  pinMode(lLooksee, OUTPUT); // historical, unconnected on 5 button box...
  pinMode(lWht, OUTPUT);
  pinMode(lBlu, OUTPUT);
  pinMode(lCamcorder, OUTPUT);
  pinMode(lRinglight, OUTPUT);
}

void loop() {
 // send data only when you receive data:
  if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      
      digitalWrite(lRed, incomingByte&1);  Red = incomingByte&1;
      incomingByte = incomingByte>>1;
      digitalWrite(lYel, incomingByte&1);  Yel = incomingByte&1; 
      incomingByte = incomingByte>>1;
      digitalWrite(lGrn, incomingByte&1);  Grn = incomingByte&1;
      incomingByte = incomingByte>>1;
      digitalWrite(lRinglight, incomingByte&1);  Ringlight = incomingByte&1;     
      
      incomingByte = incomingByte>>1;
      digitalWrite(lWht, incomingByte&1);  Wht = incomingByte&1;
      incomingByte = incomingByte>>1;
      digitalWrite(lBlu, incomingByte&1);  Blu = incomingByte&1;
      incomingByte = incomingByte>>1;
      digitalWrite(lCamcorder, incomingByte&1);  Camcorder = incomingByte&1;
      incomingByte = incomingByte>>1;
      // this bit can/should be used as a flag...
      //digitalWrite(lRinglight, incomingByte&1);
  }

  if (digitalRead(kRed)==LOW && debounce==0){
    digitalWrite(lRed, HIGH);
    debounce = 4;
    Keyboard.print("r");
  } 
  if (digitalRead(kGrn)==LOW && debounce==0){
    digitalWrite(lGrn, HIGH);
    debounce = 4;
    Keyboard.print("g");
  }
  if (digitalRead(kYel)==LOW && debounce==0){
    digitalWrite(lYel, HIGH);
    debounce = 4;
    Keyboard.print("y");
  }
  if (digitalRead(kWht)==LOW && debounce==0){
    digitalWrite(lWht, HIGH);
    debounce = 4;
    Keyboard.print("w");
  }
  if (digitalRead(kBlu)==LOW && debounce==0){
    digitalWrite(lBlu, HIGH);
    debounce = 4;
    Keyboard.print("b");
  }

  if (debounce > 0) debounce -= 1; // decrement debounce if it's non-zero...
  // typing too rapidly can overwhelm a PC
  delay(50);
  
  digitalWrite(lRed, Red);
  digitalWrite(lGrn, Grn);
  digitalWrite(lYel, Yel);
  digitalWrite(lWht, Wht);
  digitalWrite(lBlu, Blu);
}
