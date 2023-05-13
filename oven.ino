  #include <Arduino.h>

#define ocak1 A0
#define ocak2 A1
#define ocak3 A2
#define ocak4 A3

#define RELAY_PUSH 4
#define RELAY_PULL 5

#define DEBUG

void setup()
{
    pinMode(ocak1, INPUT);
    pinMode(ocak2, INPUT);
    pinMode(ocak3, INPUT);
    pinMode(ocak4, INPUT);
    pinMode(RELAY_PUSH, OUTPUT);
    pinMode(RELAY_PULL, OUTPUT);

    #ifdef DEBUG
    Serial.begin(9600);
    #endif
}

void loop()
{

    int deger_ocak1 = analogRead(ocak1);
    int deger_ocak2 = analogRead(ocak2);
    int deger_ocak3 = analogRead(ocak3);
    int deger_ocak4 = analogRead(ocak4);

    #ifdef DEBUG
    Serial.println("Okunan degerler: " + String(deger_ocak1) + " " + String(deger_ocak2) + " " + String(deger_ocak3) + " " + String(deger_ocak4));
    #endif

    // deger_1 150-200
    // deger_2 380-400
    // deger_3 595-1000
    // deger_4 0-10

    if (deger_ocak1 >= 210 && deger_ocak1 <= 300 && deger_ocak2 >= 50 && deger_ocak2 <= 125 && deger_ocak3 >= 1010 && deger_ocak3 <= 1025 && deger_ocak4 >= 460 && deger_ocak4 <= 550)
    {
        #ifdef DEBUG
        Serial.println("Tetiklendi");
        #endif

        digitalWrite(RELAY_PUSH, HIGH);
        delay(2000);
        digitalWrite(RELAY_PUSH, LOW);
        delay(100);

        #ifdef DEBUG
        Serial.println("Sıfırlanma için bekleniyor: " + String(deger_ocak1) + " " + String(deger_ocak2) + " " + String(deger_ocak3) + " " + String(deger_ocak4));
        #endif
        
        while (deger_ocak1 < 950 || deger_ocak2 < 1000 || deger_ocak3 > 10 || deger_ocak4 < 1000)
        {
            deger_ocak1 = analogRead(ocak1);
            deger_ocak2 = analogRead(ocak2);
            deger_ocak3 = analogRead(ocak3);
            deger_ocak4 = analogRead(ocak4);

            #ifdef DEBUG
            Serial.println("Tetiklenme için bekleniyor. Değerler: " + String(deger_ocak1) + " " + String(deger_ocak2) + " " + String(deger_ocak3) + " " + String(deger_ocak4));
            #endif
            delay(200);
        }
        #ifdef DEBUG
        Serial.println("Sıfırlandı");
        #endif

        digitalWrite(RELAY_PULL, HIGH);
        delay(1000);
        digitalWrite(RELAY_PULL, LOW);
        delay(100);
    }
    delay(200);
}
