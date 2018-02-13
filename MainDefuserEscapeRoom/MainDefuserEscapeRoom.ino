/* 
 *  Combined Bomb Defuser Escape Room Code
 *  
 *  Author E. Goyette
 *  
 *  For the matrix keypad
 *  Pins from left to right when key pad is facing you
 *  Col1(1,4,7,*), Col2(2,5,8,0), Col3(3,6,9,#), Row1(1,2,3), Row2(4,5,6) Row3(7,8,9), Row4 (*,0,#)
 */

#include <Key.h>
#include <Keypad.h>

// defines
#define CMDCODE "**#*"
#define DEFUSE "3791"
#define PASS "2580147369"
#define BUFDELAY 50
#define RESET 1

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char buf1[5];

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte colPins[COLS] = {2, 3, 6}; //connect to the column pinouts of the keypad
byte rowPins[ROWS] = {7, 8, 12, 13}; //connect to the row pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int cnt = 0;

void setup(){
  Serial.begin(9600);
  Serial.println("Ready for code");
}
  
void loop(){
  char key = keypad.getKey();
  
  if (key != NO_KEY){
    Serial.print(key);
    buf1[cnt] = key;
    cnt++;
  }
  
  if (cnt == 4){
    buf1[cnt] = '\0';
    
    if (strcmp(buf1, CMDCODE) == 0){
      Serial.println("Command mode!");
      getPass();
    }
    else if (strcmp(buf1, DEFUSE) == 0){
      Serial.println("Defuse code entered");
    }
    else{
      Serial.println("No Code recognized - BOOM!");
    }
    
    cnt = 0;
  }
  
  delay(BUFDELAY);
}

void getPass(){
  char buf2[11];
  char key;
  int cnt = 0;
  bool done = false;
    
  while(!done){
    key = keypad.getKey();
    
    if (key != NO_KEY){
      Serial.print(key);
      buf2[cnt] = key;
      cnt++;
    }
    
    if (cnt == 10){
      buf2[cnt] = '\0';
      
      if (strcmp(buf2, PASS) == 0){
        Serial.println("Password is correct!");
        Serial.println("Ready for Commands");
      }
      else{
        Serial.println("Password not recognized");
        Serial.println(buf1);
      }
      
      cnt = 0;
      done = true;
    }
    
    delay(BUFDELAY);
  }
}
