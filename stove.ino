#include <Arduino.h>

// Define stove sensors and relay pins
#define STOVE_SENSOR1 A0
#define STOVE_SENSOR2 A1
#define STOVE_SENSOR3 A2
#define STOVE_SENSOR4 A3
#define RELAY_PUSH_PIN 4
#define RELAY_PULL_PIN 5

// Enable debug mode
#define DEBUG

void setup()
{
    // Set pin modes for sensors and relays
    pinMode(STOVE_SENSOR1, INPUT);
    pinMode(STOVE_SENSOR2, INPUT);
    pinMode(STOVE_SENSOR3, INPUT);
    pinMode(STOVE_SENSOR4, INPUT);
    pinMode(RELAY_PUSH_PIN, OUTPUT);
    pinMode(RELAY_PULL_PIN, OUTPUT);

    // Start serial communication for debugging
#ifdef DEBUG
    Serial.begin(9600);
#endif
}

void loop()
{
    // Read values from stove sensors
    int stove1Value = analogRead(STOVE_SENSOR1);
    int stove2Value = analogRead(STOVE_SENSOR2);
    int stove3Value = analogRead(STOVE_SENSOR3);
    int stove4Value = analogRead(STOVE_SENSOR4);

    // Print sensor values for debugging
#ifdef DEBUG
    Serial.println("Sensor values: " + String(stove1Value) + " " + String(stove2Value) + " " + String(stove3Value) + " " + String(stove4Value));
#endif

    // Check if sensor values are within the expected range
    if (stove1Value >= 210 && stove1Value <= 300 &&
        stove2Value >= 50 && stove2Value <= 125 &&
        stove3Value >= 1010 && stove3Value <= 1025 &&
        stove4Value >= 460 && stove4Value <= 550)
    {
#ifdef DEBUG
        Serial.println("Triggered");
#endif

        // Activate push relay and wait
        digitalWrite(RELAY_PUSH_PIN, HIGH);
        delay(2000);
        digitalWrite(RELAY_PUSH_PIN, LOW);
        delay(100);

#ifdef DEBUG
        Serial.println("Waiting for reset: " + String(stove1Value) + " " + String(stove2Value) + " " + String(stove3Value) + " " + String(stove4Value));
#endif

        // Wait for sensor values to return to normal range
        while (stove1Value < 950 || stove2Value < 1000 || stove3Value > 10 || stove4Value < 1000)
        {
            // Update sensor values
            stove1Value = analogRead(STOVE_SENSOR1);
            stove2Value = analogRead(STOVE_SENSOR2);
            stove3Value = analogRead(STOVE_SENSOR3);
            stove4Value = analogRead(STOVE_SENSOR4);

#ifdef DEBUG
            Serial.println("Waiting for trigger. Values: " + String(stove1Value) + " " + String(stove2Value) + " " + String(stove3Value) + " " + String(stove4Value));
#endif
            delay(200);
        }

#ifdef DEBUG
        Serial.println("Reset");
#endif

        // Activate pull relay and wait
        digitalWrite(RELAY_PULL_PIN, HIGH);
        delay(1000);
        digitalWrite(RELAY_PULL_PIN, LOW);
        delay(100);
    }
    delay(200);
}
