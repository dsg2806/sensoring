import paho.mqtt.client as mqtt
import sqlite3
import time

oneBthree = sqlite3.connect('1B3.db')
oneBthree.execute('''CREATE TABLE DATA (Time INTEGER PRIMARY KEY NOT
NULL, Light INTEGER NOT NULL, Sound INTEGER NOT NULL, Temperature
FLOAT NOT NULL,
Humidity FLOAT NOT NULL);''')
oneBthree.close()
strng = ""
idint = 0

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/sensors/1B3")

def on_message(client, userdata, msg):
    oneBthree = sqlite3.connect('1B3.db')
    strng = (str(msg.payload)).split(" ")
    dontRun = False
    print(str(msg.payload))

#    for i in strng:
 #      if (i.isdigit() == False):
  #             dontRun = True
    #VALUES (int(time.time()), strng[0], strng[1], strng[2], strng[3] )");
    if dontRun == False:
#        oneBthree.execute("INSERT INTO DATA
(Time,Light,Sound,Temperature,Humidity) VALUES (?,?,?,?,?)",
(str(time.time()), strng[0] , strng[1] , strng[2], strng[3])
        oneBthree.execute("insert into data (Time, Light, Sound, Temperature,
Humidity) values (?, ?, ?, ?, ?)", (int(time.time()), int(strng[0]),
int(strng[1]), float(strng[2]),float(strng[3])))
    oneBthree.commit()
    oneBthree.close()
    print(msg.topic+" "+str(msg.payload))

def on_disconnect(client, userdata, rc):
    oneBthree.close()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect

client.connect('localhost', 1883, 60)

client.loop_forever()
