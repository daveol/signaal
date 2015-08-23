const int num_images = 15;

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
    1, 0, 100, 2,  // *100*
    1, 0, 120, 2,  // *120*
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
    int n = random() % num_images;
    static int old = -1;
    if (n != old) {
        show(n);
//        Serial.println(n);
        old = n;
        delay(100);
    }
}
