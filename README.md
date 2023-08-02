Temperature, Humidity and Light Sensing using FreeRTOS and Arduino IDE

In this Arduino sketch we use FreeRTOS to create 3 tasks to run independently

TaskHum: reads the humidity value from the DHT11 sensor and prints it to the Serial monitor every second
TaskTem: reads the temperature value from the DHT11 sensor and prints it to the Serial monitor every second
TaskLight: controls a relay based on the light intensity measured by either a digital light sensor or an analog light sensor (connected to pin A5)

Components used: Arduino UNO, DHT11 Temperature and Humidity sensor, and MH series Light sensor.
