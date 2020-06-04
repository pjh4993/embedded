#!/bin/bash
sudo mount /dev/$1 sdcard
mkdir sdcard/root/.ssh
chmod 700 sdcard/root/.ssh
cp authorized_keys sdcard/root/.ssh/
cp interfaces sdcard/etc/network/
cp sshd_config sdcard/etc/ssh/
cp wpa_supplicant.conf /etc/
sync
sudo umount sdcard
