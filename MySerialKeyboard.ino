/* Simple USB Keyboard Example
   Teensy becomes a USB keyboard and types characters

   You must select Keyboard from the "Tools > USB Type" menu

   This example code is in the public domain.
*/
int count = 0;
int debounce = 0;
int incomingByte = 0;   // for incoming serial data

// inputs for arcade buttons...
int teensyLED = 13;
int kGrn = 0; // goes to PTD0
int kRed = 1; // goes to PTD1
int kYel = 2; // goes to PTD2
int lGrn = 8; // goes to PTC0
int lRed = 9; // goes to PTC2
int lYel = 10; // goes to PTC4
int lLooksee = 11; // goes to PTC6

bool printline = false;

void setup() {
//  Serial.begin(9600);
  Serial.begin(115200);
  delay(1000);
  pinMode(teensyLED, OUTPUT);
  pinMode(kRed, INPUT_PULLUP);      // sets the digital pin as input
  pinMode(kGrn, INPUT_PULLUP);      // sets the digital pin as input
  pinMode(kYel, INPUT_PULLUP);      // sets the digital pin as input  
  
  DDRB = B00001111; // set pins 8-11 as outputs
  PORTB = B00000000; // default them all to off...
 
}

void loop() {
  
  printline = false;
  
  // send data only when you receive data:
  if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      printline = true; // flag that a println should be occur...

      // say what you got:
  //    Serial.print("Received: 0x");
  //    Serial.print(incomingByte, HEX);
  //    Serial.print("     ");
                
      PORTB = 0xf & incomingByte; // send received character to port B pins..

      // have to explicity do LED here because PORTB above extinguishes LED if it was already on...
      //digitalWrite(teensyLED, HIGH);
      // delay(1);
      //digitalWrite(teensyLED, LOW);

  }

  //Keyboard.print("* "); 
  //Keyboard.print(count);

  if (digitalRead(kRed)==LOW && debounce==0){
 //   Serial.print("R ");Serial.print(debounce, DEC);
    printline = true;
    debounce = 4;
    Keyboard.print("r");
  } 
  if (digitalRead(kGrn)==LOW && debounce==0){
  //  Serial.print("G "); Serial.print(debounce, DEC);
    printline = true;
    debounce = 4;
    Keyboard.print("g");
  }
  if (digitalRead(kYel)==LOW && debounce==0){
 //   Serial.print("Y ");Serial.print(debounce, DEC);
    printline = true;
    debounce = 4;
    Keyboard.print("y");
  }
 // if (printline) Serial.println(" ");
  
  if (debounce > 0) debounce -= 1; // decrement debounce if it's non-zero...

  // typing too rapidly can overwhelm a PC
  delay(50);
}
