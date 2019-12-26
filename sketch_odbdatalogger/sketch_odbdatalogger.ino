#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>


const int chipSelect = 4;
File fh;
Sd2Card card;
char sqfilename[] = "sq";
unsigned int log_sequence = 0;
// Enable HC-05 communication
SoftwareSerial BTSerial(5, 6);


void setup() {
  pinMode(8, OUTPUT);
 // digitalWrite(8, HIGH); 
  delay(1000);
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  BTSerial.begin(38400); 

  
  if (self_test() == 0) {
    Serial.println("OK");

    //Serial.println("Sequence Number");
    //Serial.println(log_sequence);
  }
  else {
    Serial.println("FAIL");
    while(1);
  }

  
}

int write_data_seq(int seq) {
  fh = SD.open(sqfilename, FILE_WRITE);
  
  if(fh) {
    fh.println(String(seq));
    fh.close();
    return 0;
  }
  return -1;
}

int read_data_seq() {
   fh = SD.open(sqfilename);
   String seq;
   int result = 0;
   if(fh) {
    // read until last line 
    char buffer[5];
    int i = 0;
    while(fh.available() && fh.peek() != '\n') {
      buffer[i] = fh.read();
      i++;
    }
    result = atoi(buffer);
    fh.close();
    return result;  
   }
   else {
      return -1;
   }
}

int bluetooth_elm_test() {

  return -1;
}

int sd_card_test() {
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    return -2;
  }
  if(!SD.begin(chipSelect)) {
    return -3;
  }

 

  // To test if the SD card is usable, we are going to do a read/write test. 

  // first try to see if there is a sequence file to read, 
  log_sequence = read_data_seq();

  if(log_sequence < 0) {
    // could be fresh SD card, try to write new logsequence
    if(write_data_seq(0) < 0) {
      return -4;
    } 
  }
  else {
    // Existing file found, delete it and write the sequence to the file.
    SD.remove(sqfilename);
    log_sequence = log_sequence + 1;
    write_data_seq(log_sequence);
  }
  // We can now assume there is a file to read, try to read it and if it fails, something is wrong with SD card

  log_sequence = read_data_seq();

  if(log_sequence == -1) {
    return -5;    
  }
  return 0;
}

int self_test() {
  // Test if the SD card module is connected and working as intended
  int sd_card_test_result = sd_card_test();
  int bluetooth_elm_test_result = bluetooth_elm_test();
  int result = 0;
  if(bluetooth_elm_test_result == 0) {
    Serial.println("BLT_ELMCONN_OK");
  }
  else {
    Serial.println("BLT_ELMCONN_FAIL(" + String(bluetooth_elm_test_result) + ")");
    result = -1;
  }
  if(sd_card_test_result == 0) {
    Serial.println("SD_OK");
  }
  else {
    Serial.println("SD_FAIL(" + String(sd_card_test_result) + ")");
    result = -1;
  }

  return result;
}

void loop() {

  // put your main code here, to run repeatedly:
}
