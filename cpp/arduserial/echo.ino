
/***   Setup  ***/
void setup() {
    Serial.begin(9600);
}


/***   Loop  ***/
void loop() {
    if (Serial.available() > 0) {
        // read the incoming byte:
        int incomingByte = Serial.read();

        // say what you got:
        Serial.print((char) incomingByte);
    }
}