/*
original source : player simple
08.21 mina
digital pin 7 6 4 3 are occupied
버튼 누를때마다 음악 바뀐다 
*/


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

// 사운드 플레이 버튼 초기 설정 
int button = 2;
int state = HIGH;
int reading;
int previous = LOW;
long time = 0;
long debounce = 200;

void setup() {

  Serial.begin(9600);
  Serial.println("Adafruit VS1053 Simple Test");

  if (! musicPlayer.begin()) { 
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    while (1);
  }
  Serial.println(F("VS1053 found"));

 // sd카드 설정
  SD.begin(CARDCS);  
 // 볼륨숫자 작을수록 소리커짐 
  musicPlayer.setVolume(20, 20);  

  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

 //사운드버튼설정
  pinMode(button, INPUT);
}

void loop() {

  reading = digitalRead(button);

  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    
    if (state == HIGH) {
      musicPlayer.stopPlaying();
      Serial.println(F("Playing track 001"));
      musicPlayer.startPlayingFile("track001.mp3");
      state = LOW;
    }
    else {
      musicPlayer.stopPlaying();
      Serial.println(F("Playing track 002"));
      musicPlayer.startPlayingFile("track002.mp3");
      state = HIGH;
    }
    time = millis();


    // File is playing in the background
    if (musicPlayer.stopped()) {
      Serial.println("Done playing music");
      while (1);
    }
    if (Serial.available()) {
      char c = Serial.read();
      // if we get an 's' on the serial console, stop!
      if (c == 's') {
        musicPlayer.stopPlaying();
      }
      // if we get an 'p' on the serial console, pause/unpause!
      if (c == 'p') {
        if (! musicPlayer.paused()) {
          Serial.println("Paused");
          musicPlayer.pausePlaying(true);
        } else {
          Serial.println("Resumed");
          musicPlayer.pausePlaying(false);
        }
      }
    }

    delay(100);
  }
  previous = reading;

}
