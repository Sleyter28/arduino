const int sensorPin = A0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int sensorValue = analogRead(sensorPin);
    float voltage = sensorValue * (5.0 / 1024.0);
    float temperatureC = (voltage - 0.5) * 100.0;

    Serial.println(temperatureC);

    delay(5000);
}
