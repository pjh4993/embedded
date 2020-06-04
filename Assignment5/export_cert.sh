#!/bin/bash

cp cert/ca.crt /etc/mosquitto/ca_certificates/
cp cert/server.crt /etc/mosquitto/certs/server.crt
cp cert/server.key /etc/mosquitto/certs/server.key
