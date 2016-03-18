import paho.mqtt.client as mqtt
import sqlite3

1B3 = sqlite3.connect('1B3.db')

1B3.execute('''CREATE TABLE DATA
       (ID INT PRIMARY KEY     NOT NULL,
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
    idint += 1
    #if first two letters is whatever, log whatever
    conn.execute("INSERT INTO 1B3 (ID,LIGHT,SOUND,TEMPERATURE,HUMIDITY) \
        VALUES (idint, strng[0], strng[1], strng[2], strng[3] )");
    conn.commit()
    print(msg.topic+" "+str(msg.payload))
    #ON CLOSE DO conn.close()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect('118.139.125.241', 1883, 60)

client.loop_forever()

