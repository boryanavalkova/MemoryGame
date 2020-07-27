# MemoryGame

Requires: Arduino Uno board with 16x2 display.

When the file is uploaded to the Arduino it starts up with yellow screen and awaits the user to choose range of commands (M) to work with and how many commands to be displayed at the start (N).
From this position the user should click the button up to choose from the available ranges (M) (UP, DOWN, LEFT, RIGHT), overall 4 with values from (1-4). If the user wishes to downgrade - arrow down reduces the number by one. 
To switch to commands per start round (N) the user should click button right and set how many commands the round should have. If the user wishes to change any of those after moving the other option pressing left/right will move to the desired area.
By clicking select the user sends to the program the desired parameters and enters the mode menu. By clicking the corresponding arrow story or practice mode shall be started and the game will begin.
If practice mode is selected only one example level will be played with the set range (M) and commands per round (N). On the display will appear the commands on a blue backlight and when it’s the user’s turn to input them the screen will change to white colour. The user has 8 seconds to do so. After the commands are entered the display will change to red/green and print the corresponding message (Red for fail, Green for win). Then the user will be returned to the mode menu (Violet screen).
If story mode is selected a level will be played with the set range (M) and commands per round (N). On the display the commands will appear on a teal backlight and when it’s the user’s turn to input them the screen will change to white colour. The user has 8 seconds to do so. After the commands are entered the display will change to red/green and print the corresponding message (Red for fail, Green for win). If the user wins the round next level will be loaded where N is increased by 1, and this will continue until the user loses the game – the score of the user will be shown at both screens (1 point per correct command). 

* Sequences are displayed on the screen as specified.
* Backlight flashes (only when correct).
* Incorrect answer leads to game over.
* Game supports *N* up to 10.
* Game supports *M* of size 4.
* A menu is present.
* Size of *M* can be changed.
* *N* can be changed.
* Message when wrong printed.
* A menu to switch from practice mode to story mode.
* A time limit T for inputting the next character (8 seconds). If a typing in takes longer than T, the user fails.
* A story mode to build up through increasing N.
* Own graphical representation of characters.
* Suitable displays for winning and losing.
* Score count – shows how many correct commands you have entered each round.

Test plan

1. Observe Menu
2. Click button up to set a value for M.
3. Click button right to change to set value for N.
4. Click select.
5. Observe Mode Menu. 
6. Click button down to play practice mode.
7. Observe commands on screen.
8. Enter commands.
9. Win/Lose message automatically return to Mode Menu. 
10. Click button up to play story mode.
11. Observe commands on screen. 
12. Enter commands. 
13. Win/Lose.
14. If win message – next level.
15. If lose message – automatically return Mode Menu.
