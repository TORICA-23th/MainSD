#include <TORICA_SD.h>
#include <Adafruit_NeoPixel.h>

#define SerialIN  Serial1

int cs_SD = 26;
TORICA_SD sd(cs_SD);
char SD_BUF[256]; 

int Power = 11;
int PIN  = 12;
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial1.setFIFOSize(1024);
  Serial.begin(115200);
  Serial1.begin(115200);

  sd.begin();

  pinMode(16, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(17, OUTPUT);

  delay(100);
  
  pinMode(Power, OUTPUT);
  digitalWrite(Power, HIGH);
  pixels.begin();

  while (SerialIN.available()) {
    SerialIN.read();
  }

}

const int readUART_BUF_SIZE = 256;
char readUART_BUF[256];
char sendUART_BUF[256];

void LEDtoggle(){
  digitalWrite(25, !digitalRead(25));
  digitalWrite(17, !digitalRead(25));
  digitalWrite(16, !digitalRead(25));
}

void loop() {
  // put your main code here, to run repeatedly:
  while (SerialIN.available()) {
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    int read_length = SerialIN.available();
    if (read_length >= readUART_BUF_SIZE - 1) {
      read_length = readUART_BUF_SIZE - 1;
    }
    SerialIN.readBytes(readUART_BUF, read_length);
    readUART_BUF[read_length] = '\0';
    sd.add_str(readUART_BUF);
    if (!SerialIN.available()) {
      delay(1);
    }
  
    pixels.clear();
    pixels.show();
  }

  sd.flash();
  LEDtoggle();
  
}
