// *** 키보드 버튼 1~8까지 사운드 재생 


// SPI, MP3, SD 라이브러리 
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// 라이브러리 핀설정
#define BREAKOUT_RESET  9      
#define BREAKOUT_CS     10     
#define BREAKOUT_DCS    8     
#define SHIELD_RESET  -1      
#define SHIELD_CS     7      
#define SHIELD_DCS    6      
#define CARDCS 4     
#define DREQ 3      

// music player shield
Adafruit_VS1053_FilePlayer musicPlayer =
Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);


void setup() {
  // initialize serial communication:
  Serial.begin(9600);

   Serial.println("Adafruit VS1053 Simple Test");
  if (! musicPlayer.begin()) { 
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
   Serial.println(F("VS1053 found"));
   SD.begin(CARDCS);  
   musicPlayer.setVolume(20, 20);  
   musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
}

void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    // do something different depending on the character received.
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.  For
    // example 'a' = 97, 'b' = 98, and so forth:

    switch (inByte) {
      case '1':
        musicPlayer.stopPlaying();
        Serial.println(F("Playing track 001"));
        musicPlayer.startPlayingFile("track001.mp3");
        break;
      
      case '2':
        musicPlayer.stopPlaying();
        Serial.println(F("Playing track 002"));
        musicPlayer.startPlayingFile("track002.mp3");
        break;
      
      case '3':
       musicPlayer.stopPlaying();
       Serial.println(F("Playing track 003"));
       musicPlayer.startPlayingFile("track003.mp3"); 
        break;
      
      case '4':
       musicPlayer.stopPlaying();
       Serial.println(F("Playing track 004"));
       musicPlayer.startPlayingFile("track004.mp3");      
        break;
      
      case '5':
       musicPlayer.stopPlaying();
       Serial.println(F("Playing track 005"));
       musicPlayer.startPlayingFile("track005.mp4");   
        break;
        
      case '6':
       musicPlayer.stopPlaying();
       Serial.println(F("Playing track 006"));
       musicPlayer.startPlayingFile("track006.mp3");   
        break;
       
      case '7':
       musicPlayer.stopPlaying();
       Serial.println(F("Playing track 007"));
       musicPlayer.startPlayingFile("track007.mp3");   
        break;    

      case '8':
       musicPlayer.stopPlaying();
       Serial.println(F("Playing track 008"));
       musicPlayer.startPlayingFile("track008.mp3");   
        break;   
  
    }

  }
}

