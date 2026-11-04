#include <Servo.h>

Servo esc;

const int POT_PIN = A0;
const int ESC_PIN = 9;

// Conservative initial throttle range
const int THROTTLE_MIN = 1000;
const int THROTTLE_MAX = 1300;

void setup() {
  Serial.begin(115200);

  // Attach ESC control signal
  esc.attach(ESC_PIN, 1000, 2000);

  // Keep throttle at minimum during ESC startup
  esc.writeMicroseconds(THROTTLE_MIN);

  Serial.println("ESC Motor Test");
  Serial.println("Keep the potentiometer at minimum throttle.");
  Serial.println("Waiting for ESC initialization...");

  delay(5000);

  Serial.println("Ready. Turn the potentiometer to control throttle.");
}

void loop() {
  int potValue = analogRead(POT_PIN);

  // Convert potentiometer reading to throttle pulse width
  int throttle = map(
    potValue,
    0, 1023,
    THROTTLE_MIN,
    THROTTLE_MAX
  );

  // Send throttle command to ESC
  esc.writeMicroseconds(throttle);

  // Display diagnostic information
  Serial.print("Potentiometer: ");
  Serial.print(potValue);

  Serial.print(" | Throttle: ");
  Serial.print(throttle);
  Serial.println(" us");

  delay(50);
}
