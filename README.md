## JMSS Sensoring Project 2.0 - MQTT & NodeMCU Edition

###Synopsis

At the top of the file there should be a short introduction and/ or overview that explains what the project is. 

###Motivation

A short description of the motivation behind the creation and maintenance of the project. This should explain why the project exists.

###Technologies
Client Hardware:
- 1 x ESP8266 Based NodeMCU Development Board
- 1 x MCP3008 Analog to Digital Converter
- 1 x HDC1008 I2C Temperature and Humidity Sensor
- 1 x Freetronics Light Sensor
- 1 x Freetronics Microphone Sensor
- 1 x Breadboard
- Many Breadboard Wires

Broker Hardware:
- 1 x Raspberry Pi 2 Model B

Libraries used in Arduino Client:
- ESP8266WiFi - https://github.com/ekstrand/ESP8266wifi
- Wire - https://www.arduino.cc/en/Reference/Wire
- PubSubClient - https://github.com/knolleary/pubsubclient
- Adafruit HDC1000 Library - https://github.com/adafruit/Adafruit_HDC1000_Library
- MCP3008 - https://github.com/nodesign/MCP3008

###Tests


Raspberry Pi MQTT Server Setup Steps:

Boot your Raspberry Pi and connect it to the either Eduroam or Guest Wireless.

Type in the terminal commands in order in terminal:

>$ wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key

>$ sudo apt-key add mosquitto-repo.gpg.key

>$ cd /etc/apt/sources.list.d/

>$ sudo wget http://repo.mosquitto.org/debian/mosquitto-wheezy.list

>$ sudo apt-get update

>$ sudo apt-get install mosquitto


Now the MQTT server will be running on the raspberry pi!

Now do:

>$ sudo apt-get install mosquitto-clients python-mosquitto

4. To test the mqtt server is running, open two terminal windows side by side.

5. In terminal one:

>$ sudo service mosquitto status

>$ sudo mosquitto_sub -t /test

6. If this doesn’t say the server is running (in green text), we have a problem, tell someone loudly. 

7. In terminal 2:

>$ sudo mosquitto_pub -t /test -m “THIS IS A TEST!”


In the first terminal, the message “THIS IS A TEST!” should appear.

This concludes the Mosquitto server setup for the Raspberry Pi.

###TO-DO
1. Computational Averaging
2. Make it work
3. SQL Lite


###Contributors

Let people know how they can dive into the project, include important links to things like issue trackers, irc, twitter accounts if applicable.

###License

All projects are under The MIT License (MIT)
 
Copyright (c) 2016 Dylan Sanusi-Goh & Ethan Payne
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

**Enjoy!**
