# Self-watering-plant-system
An over engineered Arduino and RasPi project for watering our office plant

This project is a hobby project to learn more about Arduino, RaspberryPi, Python, API's and sensors.

I have connected a Soil moisture sensor, a water level sensor, a submersible pump and temperature & Humidity sensor to a Arduino Nano. The Nano reads the soil moisure sensor and water the plant when the soil is too dry.

The pump runs for 2 seconds and wits 30 seconds to read the moisture again.

The nano sends the measurements to the RasPi and the RasPi sends the data to ThingSpeaks API so we can display th readings. See: https://thingspeak.com/channels/828568


