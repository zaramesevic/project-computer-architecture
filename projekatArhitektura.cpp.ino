#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7};    
byte colPins[COLS] = {8, 9, 10, 11};    
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String enteredPIN = ""; String loginPIN = "";
bool prev = false;
int c = 0;
int zelena = 2;
int crvena = 3;
const int buzzer = 12;

void setup() {
  Serial.begin(9600);
  pinMode(zelena, OUTPUT);
  pinMode(crvena, OUTPUT);
  pinMode(buzzer, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(true); // Halt
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Enter PIN:");
  display.display();
  
}
void loop() {
  
  char key = keypad.getKey();
  digitalWrite(zelena, LOW);
  digitalWrite(crvena, LOW);
  
  if(key){
    if(key == '#') {
      if(enteredPIN.length() == 4) { //to znaci da smo spremni preci na Login dio, ne treba ELSE dio
        prev = true;
        if(loginPIN.length() == 4) { //ovo znaci da je korisnik unio 4 karaktera i da mozemo odrediti jel usao u racun ili ne
          if(enteredPIN==loginPIN){ //odavdje pocinje proces provjere
            display.clearDisplay();
            display.setCursor(0,30);
            display.println("WELCOME");
            display.display();
            digitalWrite(zelena, HIGH);
            tone(buzzer, 562, 1000);
            delay(2000);
            noTone(buzzer); 
            enteredPIN = ""; loginPIN = "";
          } 
          else if(c < 2) {
            loginPIN = "";
            display.clearDisplay();
            display.setCursor(0,0);
            display.println("Incorrect");
            display.setCursor(0, 20);
            display.println("Try again");
            display.display();
            digitalWrite(crvena, HIGH);
            tone(buzzer, 1000); // Send 1KHz sound signal...      // ...for 1 sec
            delay(700);
            noTone(buzzer);
            delay(500);
            tone(buzzer, 1000);     // Stop sound...
            delay(700);
            noTone(buzzer);
            display.clearDisplay();
            display.setCursor(0,0);
            display.println("Login:");
            display.display();
            c++;
          }                       //ovdje zavrsava provjera
          else if (c == 2) {
            loginPIN = "";
            display.clearDisplay();
            display.setCursor(0,0);
            display.println("Unable to enter");
            display.setCursor(0,30);
            display.println("into account");
            display.display();
            digitalWrite(crvena, HIGH);
            tone(buzzer, 262, 1000);
            delay(2000);
            tone(buzzer, 262, 1000);
            delay(2000);
            noTone(buzzer);
            c++;
          }
        }
        else{                     //ovdje se ulazi kada pocinjemo login ili ako je login pin manji od 4 (u tom sl. se login pin brise)
          if(c <= 2){
            loginPIN = "";                      
            display.clearDisplay();
            display.setCursor(0,0);
            display.println("Login:");
            display.display();
          }
        }
      }
    }
    if(key == '*'){
      if(enteredPIN.length() == 4 && loginPIN.length() > 0){
        loginPIN = "";
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Login:");
        display.display();
      }
      else{
          enteredPIN = "";
          loginPIN = "";
          c = 0;
          display.clearDisplay();
          display.setCursor(0,0);
          display.println("Enter PIN:");
          display.display();
      }
    }
    if(key >= '0' && key <= '9'){
      if (enteredPIN.length() < 4) { 
        enteredPIN += key;
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Enter PIN:");
        display.setCursor(0,30);
        for (int i = 0; i < enteredPIN.length(); i++) {
          display.print('*');
        }
        display.display();
      }
      else{
        if(loginPIN.length() < 4 && prev){
          loginPIN += key;
          display.clearDisplay();
          display.setCursor(0,0);
          display.println("Login:");
          display.setCursor(0,30);
          for (int i = 0; i < loginPIN.length(); i++) {
            display.print('*');
          }
          display.display();
        }
      }
    }
  }
}