

BD_ADDR laptop
F8:59:71:3E:FE:3A
BD_ADDR hc-05 module
20:19:09:26:03:28


connecting hc-05 via softserial
https://roboindia.com/tutorials/arduino-hc-05-at-mode/

usefull info on how to interact with hc-05
https://arduino.stackexchange.com/questions/16954/problems-connecting-reliably-using-hc-05-as-bluetooth-masterAT

AT commands to setup mastermode and pairing

AT+RESET
AT+ORGL (Set to original)
AT+NAME=ODBRDR
AT+ROLE=1 (Set to Master)
AT+CMODE=0 (Set connect to a specific address)
AT+PSWD=0000
AT+BIND=f859,71,3efe3a
AT+INIT (Need to connect)
AT+PAIR=f859,71,3efe3a,20 (,20 means 20 second timeout)
AT+LINK=f859,71,3efe3a


Useful info on how to setup serial port on linux for bluetooth SPP profile
http://www.userk.co.uk/arduino-bluetooth-linux/


as root run following commands

rfcomm bind 0 20:19:09:26:03:28 1

if busy then run (rfcomm release 0)
configure minicom with /dev/rfcomm0
sudo minicom -s -c on



connection the emulator to the bluetooth interface requires socat
run following command to relay bluetooth arduino stuff to elm emulator
socat /dev/rfcomm0,raw,echo=0 /dev/pts/1,raw,echo=0

Running the emulator so we have something to connect to.
https://github.com/Ircama/ELM327-emulator

PIDS for connecting
https://github.com/brendan-w/python-OBD/blob/master/obd/commands.py

ELM manual
https://www.elmelectronics.com/wp-content/uploads/2017/01/ELM327DS.pdf


0902 (get VIN number)
010C (get engine RPM)
0105 (get coolant temp)
