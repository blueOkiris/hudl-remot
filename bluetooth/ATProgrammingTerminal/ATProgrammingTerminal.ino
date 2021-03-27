#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 3); // RX | TX

char c = ' ';
void setup() {
    Serial.begin(9600);
    
    // HC-05 default serial speed for AT mode is 38400
    btSerial.begin(38400);
}

void loop() {
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if(btSerial.available()) {
        c = btSerial.read();
        if((c >= ' ' && c <= '~') || c == '\r' || c == '\n') {
          Serial.print(c);
        } else {
          Serial.print(F(" 0x"));
          Serial.print(c, HEX);
          Serial.print(' ');
        }
    }

    // Keep reading from Arduino Serial Monitor and send to HC-05
    if(Serial.available()) {
        c = Serial.read();
        btSerial.write(c);
   }
}
