const int sensorPin = A0;
const float baselineTemp = 20.0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int sensorValue = analogRead(sensorPin);
    float voltage = sensorValue * (5.0 / 1024.0);
    float temperatureC = (voltage - 0.5) * 100.0;

    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");

    if (temperatureC > baselineTemp)
    {
        Serial.println("Temperature is above baseline.");
    }
    else
    {
        Serial.println("Temperature is below baseline.");
    }

    delay(2000);
}