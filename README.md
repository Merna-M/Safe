# Safe
a safe that requires password , in embedded C for microcontroller atmega32

if it's the first time for the user to enter the password , it asks to set the password , the size of the password can be modified in the code
the user enters the password and after 0.5sec it turns to '*' like all the passwords
when the user sets the password it will display 'Password saved'

if it's not the first time , it asks the user to enter the password to open the safe (option 1) or to change the password (option 2)

option 1 : if the user entered the correct password it will display 'Right Password' and 'safe Opened'
if the password is wrong you only have 3 trials before the safe is closed 

option 2: asks the user first to enter the password and the same action is done as before
if the password is right it asks user to enter the new passwors and save ir in the EEPROM
