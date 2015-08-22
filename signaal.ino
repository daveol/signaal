// Simpele sketch om de matrixsignaalgever met een schuifpotmeter te besturen,
// totdat we een meerstandenschakelaar (of iets dergelijks) hebben :P


const int fader_max = 890;
const int steps = 13;

const byte images[] = {
    2, 0, 4, 1,    //  X
    1, 0, 50, 1,   //  50
    1, 0, 50, 2,   // *50*
    1, 0, 70, 1,   //  70
    1, 0, 70, 2,   // *70*
    1, 0, 80, 3,   // (80)
    1, 0, 90, 1,   //  90
    1, 0, 100, 3,  // (100)
    1, 0, 120, 3,  // (120)
    2, 0, 1, 2,    // *<*
    2, 0, 2, 2,    // *>*
    2, 0, 3, 1,    // v
    255, 0, 2, 1   // (/)
};

void show (int s) {
    int checksum = 69;
    Serial.print("Y\x08\x14");
    for (int i = 0; i < 4; i++) {
        byte b = images[s * 4 + i];
        checksum ^= b;
        Serial.write(b);
    }
    Serial.write(checksum);
    delay(100);
}

void setup () {
    Serial.begin(9600);
}

void loop () {
    delay(100);
    int f = analogRead(0);

    int s = (fader_max - f) / (fader_max / steps);
    if (s > (steps - 1)) s = steps - 1;
    if (s < 0) s = 0;

    static int old = -1;
    if (s != old) {
        show(s);
        old = s;
    }
}
