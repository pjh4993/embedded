import paho.mqtt.client as mqtt
import time

client = mqtt.Client()

#CA
#client.tls_set('ca.crt')
#client.username_pw_set("test", "test")

client.connect("127.0.0.1", 8888)
client.loop_start()

while True:
    time.sleep(5)
    with open("/dev/rpikey", "r") as rpikey :
        result = rpikey.readline()
        client.publish("embedded/button", result)
