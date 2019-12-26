#!/usr/bin/python3
import serial
import os
import time
from serial import SerialException

bluetooth_command_file = '/tmp/bluetooth_comms'
ELM_PROMPT = b'>'
ELM_LP_ACTIVE = b'OK'



def write_to_elm(elm_command):
    buffer = bytearray()
    elm = serial.Serial('/dev/pts/1')
    #print(bytearray(elm_command))
    elm_command = elm_command + '\r'
    elm.write(elm_command.encode())
    #elm.write(b'ATI\r')
    while True:
        data = elm.read(elm.in_waiting or 1)
        if data:
            buffer.extend(data)
        if ELM_PROMPT in buffer or ELM_LP_ACTIVE in buffer:
                break

    return buffer


def write_serial_command(cmd):
    odbrdr = serial.Serial('/dev/rfcomm0')
    odbrdr.write(cmd)
# requires tio -l /tmp/bluetooth_comms /dev/rfcomm0 to run so Arduino will connect to the PC :)

def read_serial_command():
    with open(bluetooth_command_file, 'r') as f:
        lines = f.read().splitlines()
        return lines[-1]


def run():
    cached_stamp = os.stat(bluetooth_command_file).st_mtime
    print(cached_stamp)
    while True:
        timestamp = os.stat(bluetooth_command_file).st_mtime
        #print(timestamp)
        time.sleep(0.05)
        if timestamp != cached_stamp:
            # small delay, otherwise we end reading to early
            time.sleep(1)
            cached_stamp = timestamp
            print(cached_stamp)
            serial_cmd = read_serial_command()
            response = write_to_elm(serial_cmd)
            write_serial_command(response)

run()
