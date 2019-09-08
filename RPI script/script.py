from serial import Serial
import sys
import urllib2
from time import sleep


# Enter Your API key here
myAPI = '1YJZRBLZ5BV9A4CM' 
# URL where we will send the data, Don't change it
baseURL = 'https://api.thingspeak.com/update?api_key=%s' % myAPI 
#serial object to read from arduino serial port
ser = Serial(port='/dev/ttyACM1',baudrate = 9600)

while 1:
    try:
        if ser.is_open:
            if ser.in_waiting>0:
                x=ser.readline()
                y=x.split(",")
                temp=y[1]
                humidity=y[0]
                soil_moisture=y[2]
                water_level=y[3]
                print humidity,temp,soil_moisture,water_level
                # Sending the data to thingspeak
                conn = urllib2.urlopen(baseURL + '&field1=%s&field2=%s&field3=%s&field4=%s' % (water_level, soil_moisture,temp,humidity))
                print conn.read()
                # Closing the connection
                conn.close()
                sleep(10)
    except:
          print("Error")
          
                