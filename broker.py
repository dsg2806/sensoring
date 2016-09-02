import time

strng = ""
idint = 0

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("/sensors/1B3")

#def on_message simply runs when a message is received. it is always constantly searching for messages.
def on_message(client, userdata, msg):
    strng = (str(msg.payload)).split(" ")
    dontRun = False
    print(str(msg.payload))

    if dontRun == False:
        print(msg.topic+" "+str(msg.payload))

def on_disconnect(client, userdata, rc):
    oneBthree.close()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect

client.connect('localhost', 1883, 60)

client.loop_forever()
