
#include "DHT.h"

#define DHTPIN 7     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);


#define soil_pin A0 //Declare a variable for the soil moisture sensor
#define water_pin A1 //Declare a variable for the water level sensor  
#define pump 4//relay pin
void setup()
{
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, LOW);
  dht.begin();

}

void loop()
{
  int temp = 0, hum = 0, moist = 0, level = 0;
  moist = read_soil_moisture(soil_pin);
  temp = read_temp();
  hum = read_humidity();
  level = read_water_level(water_pin);//reads water level
  //print_sensor(hum, temp, moist, level);
  log_sensor(hum, temp, moist, level);//prints values of sesnors to UART


  if (moist < 40)
  {

    digitalWrite(pump, LOW);//Setting relay pin high
    delay(2000);//keeps relay pin high for 2 seconds
    digitalWrite(pump, HIGH);//Setting relay pin low

  }
  else
  {

    digitalWrite(pump, HIGH);//keep relay pin low

  }


  
  
  delay(180000);//take a reading every 30 second
}
//This is a function used to get the soil moisture content

int read_temp()
{
  int t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(t) ){
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }
  return t;

}


int read_humidity()
{
  int h = dht.readHumidity();
  if (isnan(h) ){
    //Serial.println("Failed to read from DHT sensor!");
    return;
  }
  return h;
}
int read_soil_moisture(int pin)
{
  int x = analogRead(pin);
  return map(x, 0, 1023, 0, 100);

}

int read_water_level(int pin)
{

  int x = analogRead(pin);
  return map(x, 0, 1023, 0, 100);
}

void print_sensor(int h, int t, int m, int l)
{
  Serial.print("Soil Moisture = ");
  Serial.print(m);
  Serial.println("%");
  Serial.print("Water level = ");
  Serial.print(l);
  Serial.println("%");


  // Printing the results on the serial monitor
  Serial.print("Temperature = ");
  Serial.print( t);
  Serial.print(" *C "); 
  Serial.print("    Humidity = ");
  Serial.print(h);
  Serial.println(" % ");
}
void log_sensor(int h, int t, int m, int l)
{
  String logg = String(h) + "," + String(t) + "," + String(m) + "," + String(l)+",";
  Serial.println(logg);
}
