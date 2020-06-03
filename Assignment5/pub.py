import paho.mqtt.client as mqtt
import time

client = mqtt.client()

#CA
#client.tls_set('ca.crt')
#client.username_pw_set("test", "test")

client.connect("192.168.1.1", 8883)
client.loop_start()

while True:
    time.sleep(5)
    with open("/dev/rpikey", "r") as rpikey:
    result = rpikey.read()
    client.publish("embedded/button", result)
