#include "STD_types.h"
#include "LCD_interface.h"
#include "LED_interface.h"
#include "KYP_interface.h"
#define F_CPU 8000000UL
#include "util/delay.h"

/* ############## Macros ############### */
#define E2PROM_STATUS_LOCATION		0x20
#define E2PROM_START_ADDRESS		0x30
#define PW_DIGIT_NUMBER				4
#define MAX_TRIAL					3


int main(void)
{
	/*Initialization*/
	LCD_vInit();
	KYP_vInit();
	LED_vInit('C',PIN7);
	//remove cursor
	LCD_vSendCmd(DISPLAY_ON_CURSOR_OFF);
	uint8 count,CheckKey,flag=0,option;
	uint8 PW_arr[PW_DIGIT_NUMBER]; // array to hold the PW entered by user
	uint8 current_trial = MAX_TRIAL;//decremented if the user entered a wrong password
	
	//check if there is a password stored before or this is the first time 
	if(EEPROM_vREAD(E2PROM_STATUS_LOCATION) != 0x00)
	{
		LCD_vSendString("Set Pass:");
		for(count=0 ; count<PW_DIGIT_NUMBER ; count++)
		{
			//take a value from the keypad
			do{
				CheckKey = KYP_u8CheckPress();
			}
			while(CheckKey==NOT_PRESSED);
			//write the entered number at the EEPROM
			EEPROM_vWrite(E2PROM_START_ADDRESS+count,CheckKey);
			//displaying the number for 500ms then displaying '*'
			LCD_vSendData(CheckKey);
			_delay_ms(500);
			//a command to shift cursor left
			LCD_vSendCmd(SHIFT_LEFT_ONCE);
			LCD_vSendData('*');
		}
		//after setting password change the status as there a password stored at the EEPROM
		EEPROM_vWrite(E2PROM_STATUS_LOCATION,0x00);
		LCD_vClearScreen();
		LCD_vSendString("Password Saved");
	}
	//there is already password stored
	else
	{
		//displaying the options
		LCD_vSendString("1:Check PW");
		LCD_vMoveCursor(ROW2,COL1);
		LCD_vSendString("2:Change PW");
		//make the user choose only from the 2 options
		do{
			option = KYP_u8CheckPress();
		}
		while((option != '1')&&(option != '2'));
		_delay_ms(200);
		LCD_vClearScreen();
		
		//flag=0 if the password is correct or the user passed the trials tries then the loop breaks
		while(flag==0)
		{	
			LCD_vSendString("Enter PW:");
			//taking the password from the user and storing it into the array
			for(count=0 ; count<PW_DIGIT_NUMBER ; count++)
			{
				do{
					CheckKey = KYP_u8CheckPress();
				}
				while(CheckKey == NOT_PRESSED);
				PW_arr[count]=CheckKey;
				LCD_vSendData(CheckKey);
				_delay_ms(500);
				LCD_vSendCmd(SHIFT_LEFT_ONCE);
				LCD_vSendData('*');
			}
			/* a loop to check if the password entered by the user is right or wrong */
			for(count=0 ; count<PW_DIGIT_NUMBER ; count++)
			{
				if(PW_arr[count] != EEPROM_vREAD(E2PROM_START_ADDRESS+count))
				{
					break;//if the password is wrong , the loop breaks before count = PW_DIGIT_NUMBER
				}
			}
			//count = PW_DIGIT_NUMBER only if the password is correct
			if(count == PW_DIGIT_NUMBER)
			{
				LCD_vClearScreen();
				LCD_vSendString("Right Password");
				_delay_ms(2000);
				LCD_vClearScreen();
				/* check options */
				//1 to check the password and open the safe
				if(option == '1')
				{
					LCD_vSendString("Safe Opened");
					LED_vSwitchON('C',PIN7);
				}
				//2 to change the password
				else if(option == '2')
				{
					LCD_vClearScreen();
					// set a new password and store it into the EEPROM
					LCD_vSendString("Set Pass:");
					for(count=0 ; count<PW_DIGIT_NUMBER ; count++)
					{
						do{
							CheckKey = KYP_u8CheckPress();
						}
						while(CheckKey==NOT_PRESSED);
						EEPROM_vWrite(E2PROM_START_ADDRESS+count,CheckKey);
						LCD_vSendData(CheckKey);
						_delay_ms(500);
						LCD_vSendCmd(SHIFT_LEFT_ONCE);
						LCD_vSendData('*');
					}
					EEPROM_vWrite(E2PROM_STATUS_LOCATION,0x00);
					LCD_vClearScreen();
					LCD_vSendString("Password Saved");
				}
				//flag = 1 to break from the loop as the entered password is correct
				flag=1;
			}
			//the entered password is not right
			else
			{
				//decrement the trials
				current_trial--;
				LCD_vClearScreen();
				LCD_vSendString("Wrong Password");
				_delay_ms(2000);
				LCD_vClearScreen();
				LCD_vSendString("Trials Left:");
				LCD_vSendData(current_trial+48);//convert to ascii
				_delay_ms(2000);
				LCD_vClearScreen();
				//close the safe if the user ran out of trials
				if(current_trial==0)
				{
					LCD_vSendString("Safe Closed");
					//change the flag to break from the loop 
					flag=1;
				}
			}
		}
	}
	
    while(1)
    {
        
    }
}