#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
File fh;
Sd2Card card;
unsigned int log_sequence = 0;


void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (self_test() == 0) {
    Serial.println("Self test OK");
  }
  else {
    Serial.println("Self test failed, refusing to do anything");
    while(1);
  }

  
}

int write_data_seq(int seq) {
  fh = SD.open("sq", FILE_WRITE);

  if(fh) {
    Serial.println("Komt hij hier niet?");
    fh.println(String(seq));
    fh.close();
    return 0;
  }
  return -1;
}

int read_data_seq() {
   fh = SD.open("sq");
   String seq;
   int result = 0;
   if(fh) {
    // read until last line 
    do {
      seq = fh.read();
      result = seq.toInt();
    } while(fh.available());
    fh.close();
    return result;  
   }
   else {
      return -1;
   }
}

int sd_card_test() {
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("SD card initialisation failed");
    return -1;
  }
  if(!SD.begin(chipSelect)) {
    Serial.println("SD card probing failed");
    return -1;
  }

  // To test if the SD card is usable, we are going to do a read/write test. 

  // first try to see if there is a sequence file to read, 
  log_sequence = read_data_seq();

  if(log_sequence == -1) {
    // could be fresh SD card, try to write new logsequence
    if(write_data_seq(0) == -1) {
      Serial.println("SD Card write test failed");  
      return -1;
    } 
  }
  else {
    
    log_sequence += 1;
    Serial.println(log_sequence);
    write_data_seq(log_sequence);
  }
  // We can now assume there is a file to read, try to read it and if it fails, something is wrong with SD card

  log_sequence = read_data_seq();

  if(log_sequence == -1) {
    Serial.print("SD Card read test failed");
    return -1;    
  }
  return 0;
}

int self_test() {
  Serial.println("Starting self test....");
  // Test if the SD card module is connected and working as intended 
  if(sd_card_test() == 0) {
    Serial.println("SD Card OK");
  }
  else {
    Serial.println("SD Card test failed");
    return -1;
  }
  return 0;
}

void loop() {

  //Serial.println(log_sequence);
  // put your main code here, to run repeatedly:

}
