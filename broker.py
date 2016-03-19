import paho.mqtt.client as mqtt
import sqlite3
import time

1B3 = sqlite3.connect('1B3.db')

1B3.execute('''CREATE TABLE DATA
       (TIME INT PRIMARY KEY     NOT NULL,
       LIGHT           INT    NOT NULL,
       SOUND            INT     NOT NULL,
       TEMPERATURE        INT,
       HUMIDITY         INT);''')
strng = ""
idint = 0

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/sensors")

def on_message(client, userdata, msg):
    strng = (msg.payload).split(",")
    1B3.execute("INSERT INTO 1B3 (ID,LIGHT,SOUND,TEMPERATURE,HUMIDITY) \
        VALUES (int(time.time()), strng[0], strng[1], strng[2], strng[3] )");
    1B3.commit()
    print(msg.topic+" "+str(msg.payload))

def on_disconnect(client, userdata, rc):
    1B3.close()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect 

client.connect('118.139.125.241', 1883, 60)

client.loop_forever()

