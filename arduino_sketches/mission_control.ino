#include <MIDI.h>

// this is the code for the MISSION CONTROL module

MIDI_CREATE_DEFAULT_INSTANCE();


#include <MozziGuts.h> // 3rd party MIDI library

// digital pins
static const unsigned pin2 = 2;      
static const unsigned pin4 = 4;      
static const unsigned pin7 = 7;
static const unsigned pin8 = 8;      
static const unsigned pin12 = 12;      
static const unsigned pin13 = 13;    

// PWM pins
int pin3 = 3;
int pin5 = 5;
int pin6 = 6;
int pin9 = 9;
int pin10 = 10;
int pin11 = 11;

// analog input pins
int pinA0 = A0;
int pinA1 = A1;
int pinA2 = A2;
int pinA3 = A3;
int pinA4 = A4;
int pinA5 = A5;

// create places to hold values
int pinA0val = 0;
int pinA0midi = 0;
int pinA1val = 0;
int pinA1midi = 0;
int pinA2val = 0;
int pinA2midi = 0;
int pinA3val = 0;
int pinA3midi = 0;
int pinA4val = 0;
int pinA4midi = 0;
int pinA5val = 0;
int pinA5midi = 0;

// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// http://arduinomidilib.fortyseveneffects.com/a00022.html

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.
    //Serial.print("midi note: ");
    //Serial.print(pitch);
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.

  // map the white keys to the top row of pins
  // C1=36  D1=38 E=40 F=41 G=43 A=45

  if (pitch == 36){
        digitalWrite(pin2, HIGH);
  }

  if (pitch == 38){
        digitalWrite(pin4, HIGH);
  }

  if (pitch == 40){
        digitalWrite(pin7, HIGH);
  }

  if (pitch == 41){
        digitalWrite(pin8, HIGH);
  }

  if (pitch == 43){
        digitalWrite(pin12, HIGH);
  }

  if (pitch == 45){
        digitalWrite(pin13, HIGH);
  }


}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // map the white keys to the top row of pins
          
  if (pitch == 36){
        digitalWrite(pin2, LOW);
  }

  if (pitch == 38){
           digitalWrite(pin4, LOW);  
  }

  if (pitch == 40){
        digitalWrite(pin7, LOW);
  }

  if (pitch == 41){
        digitalWrite(pin8, LOW);
  }

  if (pitch == 43){
           digitalWrite(pin12, LOW);  
  }

  if (pitch == 45){
        digitalWrite(pin13, LOW);
  }
}

// -----------------------------------------------------------------------------

void setup()
{
    // Connect the handleNoteOn function to the library, 
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(3);

    // TOP ROW - digital pins
    pinMode(pin2, OUTPUT);
    pinMode(pin4, OUTPUT);
    pinMode(pin7, OUTPUT);
    pinMode(pin8, OUTPUT);
    pinMode(pin12, OUTPUT);
    pinMode(pin13, OUTPUT);

    // MIDDLE ROW - PWM pins
    pinMode(pin3, INPUT);
    pinMode(pin5, OUTPUT);
    pinMode(pin6, OUTPUT);
    pinMode(pin9, OUTPUT);
    pinMode(pin10, OUTPUT);
    pinMode(pin11, OUTPUT);


    // BOTTOM ROW - analog input pins
    pinMode(pinA0, INPUT);
    pinMode(pinA1, INPUT);
    pinMode(pinA2, INPUT);
    pinMode(pinA3, INPUT);
    pinMode(pinA4, INPUT);
    pinMode(pinA5, INPUT);

    //MIDI.begin(1);
    Serial.begin(115200); // opens serial port, sets data rate to ? bps
}

//  Send a three byte midi message  
void midiSend(char status, char data1, char data2) {
  Serial.print(status);
  Serial.print(data1);
  Serial.print(data2);
}


void loop()
{
    // read incoming MIDI messages and do stuff
    MIDI.read();

    // read values of pins and generate MIDI messages
    // more info about midi cc bytes here:
    // https://www.midi.org/specifications/item/table-3-control-change-messages-data-bytes-2

    // I should really figure out how to do a function here
    // until then, I'll just copy-paste like a hack :-)

    pinA0val = analogRead(pinA0);   // read the input pin
    pinA0midi = map(pinA0val, 0, 1023, 0, 127);
    // format:
    // midiSend(channel, control number, value)
    //midiSend(0xB1, 0x72, pinA0midi);


    pinA1val = analogRead(pinA1);   // read the input pin
    pinA1midi = map(pinA1val, 0, 1023, 0, 127);
    //midiSend(0xB0, 0x73, pinA1midi);

    // experimenting with generating voltages from MIDI ccs
    



   
    

    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}