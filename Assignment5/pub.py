import paho.mqtt.client as mqtt
import time

client = mqtt.Client()
client.tls_set('/root/Assignment5/cert/ca.crt')
client.username_pw_set("sysadmin", "1234")
client.connect("192.168.2.1", 8888)
client.loop_start()

while True:
    time.sleep(5)
    with open("/dev/rpikey", "r") as rpikey :
        result = rpikey.readline()
        client.publish("embedded/button", result)
