
#include "DHT.h"

#define DHTPIN 7     // what digital pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);


#define soil_pin A0 //Declare a variable for the soil moisture sensor
#define water_pin A1 //Declare a variable for the water level sensor  
#define pump 4//relay pin

//definitions for MQ135. FOr caliberation please follow https://www.youtube.com/watch?v=V1uOHOcVZrE

#define CO2_sensor  A2                     //analog feed from MQ135

#define co2Zero     52                        //calibrated CO2 0 level

void setup()
{


  Serial.begin(9600);
  pinMode(CO2_sensor, INPUT);                    //MQ135 analog feed set for input
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);
  dht.begin();
}

void loop()
{
  int temp = 0, hum = 0, moist = 0, level = 0, co2_ppm = 0;
  moist = read_soil_moisture(soil_pin);
  temp = read_temp();
  hum = read_humidity();
  level = read_water_level(water_pin);//reads water level

  co2_ppm = CO2_PPM();
  //print_sensor(hum, temp, moist, level,co2_ppm);

  temp = read_temp();
  if (temp >= 4)
  {
    temp -= 4;
  }
  else
  {
    temp = 0;
  }

  log_sensor(hum, temp, moist, level, co2_ppm); //prints values of sensors to UART
  if (moist > 52)
  {

    digitalWrite(pump, LOW);//Setting relay pin high
    delay(2000);//keeps relay pin high for 2 seconds
    digitalWrite(pump, HIGH);//Setting relay pin low
  }
  else
  {

    digitalWrite(pump, HIGH);//keep relay pin low

  }
  delay(300000);//take a reading every 180 seconds
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



void print_sensor(int h, int t, int m, int l, int co2)
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
  Serial.print("    CO2 = ");
  Serial.print(co2);
  Serial.println(" ppm ");
}
void log_sensor(int h, int t, int m, int l, int co2)
{
  String logg = String(h) + "," + String(t) + "," + String(m) + "," + String(l) + "," + String(co2) + ",";
  Serial.println(logg);
}


int CO2_PPM()
{
  int co2now[10];                               //int array for co2 readings
  int co2raw = 0;                               //int for raw value of co2
  int co2comp = 0;                              //int for compensated co2
  int co2ppm = 0;                               //int for calculated ppm
  int zzz = 0;                                  //int for averaging
  int grafX = 0;                                //int for x value of graph




  for (int x = 0; x < 10; x++) {              //samplpe co2 10x over 2 seconds
    co2now[x] = analogRead(CO2_sensor);
    delay(200);
  }

  for (int x = 0; x < 10; x++) {                //add samples together
    zzz = zzz + co2now[x];

  }
  co2raw = zzz / 10;                          //divide samples by 10
  co2comp = co2raw - co2Zero;                 //get compensated value
  co2ppm = map(co2comp, 0, 1023, 400, 5000);  //map value for atmospheric levels
  return co2ppm;
}
