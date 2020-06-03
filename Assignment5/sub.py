import paho.mqtt.client as mqtt
import threading

cnt0 = 0
cnt1 = 0

def on_connect (client, userdata, flags, rc) :
    print("Connected!!")
    client.subscribe("embedded/button")

def on_message (clinet, userdata, msg) :
    global cnt0
    global cnt1
    data = str(msg.payload)
    #print("Recieved : " + msg.payload)
    for ch in data :
        if ch == '0' :
            cnt0 = cnt0 + 1
        elif ch == '1' :
            cnt1 = cnt1 + 1

def loopclient(c) :
    c.loop_forever()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

#CA
#client.tls_set('ca.crt')
#client.username_pw_set("test","test)

client.connect("127.0.0.1", 8888, 60)
thread = threading.Thread(target=loopclient, args=(client,))
thread.start()

