#define LED 5
#define WAKE_PIN 33
#define DISCHARGE_PIN 25

void setup() {
  Serial.begin(115200);

  Serial.println("Booting...");

  pinMode(LED, OUTPUT);
  pinMode(WAKE_PIN, INPUT_PULLUP);

  // Do work
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
  }

  delay(50);
  // Check wake pin BEFORE sleep
  // Serial.print("WAKE PIN: ");
  // Serial.println(digitalRead(WAKE_PIN));  // should be 1

  Serial.println("Discharging capacitor...");

  // Discharge RC node
  pinMode(DISCHARGE_PIN, OUTPUT);
  digitalWrite(DISCHARGE_PIN, LOW);
  delay(1000);  // important
  

  // Release node
  pinMode(DISCHARGE_PIN, INPUT);
  delay(200);  // allow pin to stabilize HIGH
  
  Serial.print("WAKE PIN: ");
  Serial.println(digitalRead(WAKE_PIN));  // should be 1

  Serial.println("Sleeping...");

  digitalWrite(LED, LOW);

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 0);
  esp_deep_sleep_start();
}

void loop() {}
