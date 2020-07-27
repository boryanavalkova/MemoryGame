#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();


//states to adjust for range and commands
#define S_HOURS 1
#define S_MINUTES 2

uint8_t state = S_HOURS;

byte upArrow[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte downArrow[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100
};

byte leftArrow[8] = {
  0b00010,
  0b00110,
  0b01110,
  0b11110,
  0b11110,
  0b01110,
  0b00110,
  0b00010
};

byte rightArrow[8] = {
  0b01000,
  0b01100,
  0b01110,
  0b01111,
  0b01111,
  0b01110,
  0b01100,
  0b01000
};

#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7


//function so that display is called before declaration
void display(int, int);

bool disableSelect = false;
int wait = 1;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  display(0, 0);
  state = S_HOURS;
  randomSeed(analogRead(0));
  lcd.setCursor(2, 0);
  lcd.print("Memory Game!");
  lcd.setBacklight(YELLOW);

  lcd.createChar(0, upArrow);
  lcd.createChar(1, downArrow);
  lcd.createChar(2, leftArrow);
  lcd.createChar(3, rightArrow);
}

//memory efficiency
char buffer[12];

//function that sends to display the values of
//range (how many types of commands) M
//commands for start level to choose from N

void display(int range, int commands) {
  lcd.setCursor(2, 1);
  sprintf(buffer, "%d/%d", range, commands);
  lcd.print(buffer);
  lcd.setCursor(6, 1);
  lcd.print((state == S_HOURS ? "range   " : "commands"));
}

int range = 0, commands = 0;
long randomNumber;

//user menu for mode selection
void modeDisplay() {
  lcd.clear();
  lcd.setBacklight(VIOLET);

  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(1, 0);
  lcd.print("Story mode");

  lcd.setCursor(0, 1);
  lcd.write(byte(1));
  lcd.setCursor(1, 1);
  lcd.print("Practice mode");

  bool disableUp = false;
  bool disableDown = false;

  while (wait == 1 & !disableUp & !disableDown) {
    uint8_t buttons = lcd.readButtons();
    if (buttons & BUTTON_UP) {
      disableUp = true;
      disableDown = true;
      storyMode();
    } else if (buttons & BUTTON_DOWN) {
      disableUp = true;
      disableDown = true;
      practiceMode();
    }
  }

}

uint8_t old_buttons2 = 0;
void storyMode() {
  lcd.clear();
  lcd.setBacklight(TEAL);
  randomSeed(analogRead(0));
  int compareCommands[commands];
  //lopp that generates random numbers and stores them to array
  for (int i = 0; i <= commands - 1; i++) {
    randomNumber = random(0, range);
    compareCommands[i] = randomNumber;
    //associates each number to a command
    switch (randomNumber)
    {
      case 0:
        lcd.clear();
        lcd.write(byte(0));
        break;

      case 1:
        lcd.clear();
        lcd.write(byte(1));
        break;

      case 2:
        lcd.clear();
        lcd.write(byte(2));
        break;

      case 3:
        lcd.clear();
        lcd.write(byte(3));
        break;
    }
    delay(2000);
    if (i == commands - 1) {
      lcd.clear();
      lcd.setBacklight(WHITE);
      int win = 0;
      int level = 0;
      unsigned long timer = millis();
      unsigned long inputPeriod = 8000;
      //waits for 8 seconds for the user to input something
      //checks if it matches the button command from the array
      for (int j = 0; j <= commands - 1; j++) {
        while (inputPeriod + timer > millis()) {
          uint8_t buttons, changes;
          buttons = lcd.readButtons();
          //changes will be applied when a button goes from pressed to released
          changes = old_buttons2 & (~buttons);
          if (changes & BUTTON_UP && compareCommands[j] == 0) {
            win++;
          } else if (changes & BUTTON_DOWN && compareCommands[j] == 1) {
            win++;
          } else if (changes & BUTTON_LEFT && compareCommands[j] == 2) {
            win++;
          } else if (changes & BUTTON_RIGHT && compareCommands[j] == 3) {
            win++;
          } old_buttons2 = buttons;
        } if (win != commands) {
          lcd.clear();
          lcd.setBacklight(RED);
          lcd.print("You lose!");
          lcd.setCursor(0, 1);
          lcd.print("Score:");
          lcd.setCursor(6, 1);
          lcd.print(win);
          delay(5000);
          modeDisplay();
        }
      }
      if (win == commands) {
        lcd.clear();
        lcd.setBacklight(GREEN);
        lcd.setCursor(0, 0);
        lcd.print("You win! Next..");
        lcd.setCursor(0, 1);
        lcd.print("Score:");
        lcd.setCursor(6, 1);
        lcd.print(win);
        delay(5000);
        commands++;
        storyMode();
      }

    }
  }

}

uint8_t old_buttons1 = 0;

void practiceMode() {
  lcd.clear();
  lcd.setBacklight(BLUE);
  randomSeed(analogRead(0));
  int compareCommands[commands];

  //lopp that generates random numbers and stores them to array
  for (int i = 0; i <= commands - 1; i++) {
    randomNumber = random(0, range);
    compareCommands[i] = randomNumber;
    //associates each number to a command
    switch (randomNumber)
    {
      case 0:
        lcd.clear();
        lcd.print("UP");
        break;

      case 1:
        lcd.clear();
        lcd.print("DOWN");
        break;

      case 2:
        lcd.clear();
        lcd.print("LEFT");
        break;

      case 3:
        lcd.clear();
        lcd.print("RIGHT");
        break;
    }
    delay(2000);
    if (i == commands - 1) {
      lcd.clear();
      lcd.setBacklight(WHITE);
      int win = 0;
      unsigned long timer = millis();
      unsigned long inputPeriod = 5000;
      //waits for 8 seconds for the user to input something
      //checks if it matches the button command from the array
      for (int j = 0; j <= commands - 1; j++) {
        while (inputPeriod + timer > millis()) {
          uint8_t buttons, changes;
          buttons = lcd.readButtons();
          //changes will be applied when a button goes from pressed to released
          changes = old_buttons1 & (~buttons);
          if (changes & BUTTON_UP && compareCommands[j] == 0) {
            win++;
          } else if (changes & BUTTON_DOWN && compareCommands[j] == 1) {
            win++;
          } else if (changes & BUTTON_LEFT && compareCommands[j] == 2) {
            win++;
          } else if (changes & BUTTON_RIGHT && compareCommands[j] == 3) {
            win++;
          } old_buttons1 = buttons;
        } if (win != commands) {
          lcd.clear();
          lcd.setBacklight(RED);
          lcd.print("You lose!");
          delay(5000);
          modeDisplay();
        }
      }
      if (win == commands) {
        lcd.clear();
        lcd.setBacklight(GREEN);
        lcd.print("You win!");
        delay(5000);
        modeDisplay();
      }

    }
  }
}

uint8_t old_buttons = 0;

void loop() {
  uint8_t buttons, changes;
  buttons = lcd.readButtons();

  //changes will be applied when a button goes from pressed to released
  changes = old_buttons & (~buttons);
  if (!disableSelect) {
    display(range, commands);
    //controls range and command values on button click
    switch (state) {
      case S_HOURS:
        if (changes & BUTTON_UP) {
          range = (range == 4 ? 1 : range + 1);
        } else if (changes & BUTTON_DOWN) {
          range = (range == 1 ? 4 : range - 1);
        } else if (changes & BUTTON_RIGHT) {
          state = S_MINUTES;
        } else if (changes & BUTTON_SELECT) {
          modeDisplay();
          disableSelect = true;
        }
        break;

      case S_MINUTES:
        if (changes & BUTTON_UP) {
          commands = (commands == 5 ? 1 : commands + 1);
        } else if (changes & BUTTON_DOWN) {
          commands = (commands == 1 ? 5 : commands - 1);
        } else if (changes & BUTTON_LEFT) {
          state = S_HOURS;
        } else if (changes & BUTTON_SELECT) {
          modeDisplay();
          disableSelect = true;
        }
        break;
    }
    old_buttons = buttons;
  }
}
