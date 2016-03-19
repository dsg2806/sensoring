import paho.mqtt.client as mqtt
import sqlite3
import time

oneB3 = sqlite3.connect('1B3.db')

oneB3.execute('''CREATE TABLE DATA
       (TIME INT PRIMARY KEY     NOT NULL,
       LIGHT           INT    NOT NULL,
       SOUND            INT     NOT NULL,
       TEMPERATURE        INT     NOT NULL,
       HUMIDITY         INT     NOT NULL);''')
oneB3.close()
strng = ""
idint = 0

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/sensors")

def on_message(client, userdata, msg):
    oneB3 = sqlite3.connect('1B3.db')
    strng = (msg.payload).split(",")
    oneB3.execute(
	"INSERT INTO 1B3 (ID,LIGHT,SOUND,TEMPERATURE,HUMIDITY) 
	VALUES (?, ?, ?, ?, ?)"
	(int(time.time()), int(strng[0]), int(strng[1]), int(strng[2]), int(strng[3]))
);
        #VALUES (int(time.time()), strng[0], strng[1], strng[2], strng[3] )");
    oneB3.commit()
    oneB3.close()
    print(msg.topic+" "+str(msg.payload))

def on_disconnect(client, userdata, rc):
    oneB3.close()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect 

client.connect('118.139.125.241', 1883, 60)

client.loop_forever()

