void setup() {
  Serial.begin(9600);
  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);
}

const int wet = 1500;
const int dry = 3500;

double totalHumidity = 0;
int count = 0;
void loop() {
  int sensorValue = analogRead(34);
  Serial.println("Sensor:");
  Serial.println(sensorValue);

  double percentageDry = map(sensorValue, wet, dry, 0, 100);
  double percentageHumidity = 100 - percentageDry;
  Serial.println("Humidity:");
  Serial.println(percentageHumidity);

  totalHumidity += percentageHumidity;

  if (count == 0) {
    // take the average humidity of an hour
    double averageHumidity = totalHumidity/3600.0;

    // if humidity is above 55, pump water for 10 seconds
    if (averageHumidity < 55) {
      Serial.println("Start Pumping");
      digitalWrite(32, HIGH);
    }

    totalHumidity = 0;
  }

  // after pumping for 10 seconds, stop pumping
  if (count == 10 && digitalRead(32) == HIGH) {
    Serial.println("Pumped 10 Seconds. Stop Pumping");
    digitalWrite(32, LOW);
  }

  // every hour is a cycle
  if (count == 60*60) {
    count = 0;
  }

  // repeat loop every second
  delay(1000);
  count++;
}
