import paho.mqtt.client as mqtt

cnt0 = 0
cnt1 = 0

def on_connect (client, userdata, flags, rc) :
    print("Connected!!")
    client.subscribe("embedded/button")

def on_message (clinet, userdata, msg):
    data = str(msg.payload)
    print("Recieved : " + data)

    for ch in data :
        if ch == '0' :
            cnt0 += 1
        elif ch == '1' :
            cnt1 += 1

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

#CA
#client.tls_set('ca.crt')
#client.username_pw_set("test","test)

client.connect("192.168.1.1", 8883, 60)
client.loop_forever()


