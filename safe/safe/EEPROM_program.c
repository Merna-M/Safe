#include "EEPROM_interface.h"

void EEPROM_vWrite(uint16 Copy_u16Address , uint8 Copy_u8Data)
{
	/* set up address register*/
	EEAR = Copy_u16Address;
	/* set up data register*/
	EEDR = Copy_u8Data;
	/*setting EEMWE*/
	SET_BIT(EECR,EEMWE);
	/*start writing by setting EEWE*/
	SET_BIT(EECR,EEWE);
	/*wait till the processor finishes writing*/
	while(READ_BIT(EECR,EEWE)==1);
}


uint8 EEPROM_vREAD(uint16 Copy_u16Address)
{
	/* set up address register*/
	EEAR = Copy_u16Address;
	/* start reading by setting EERE */
	SET_BIT(EECR,EERE);
	/*wait till the processor finishes reading */
	while(READ_BIT(EECR,EERE)==1);
	/*return the data in the data register*/
	return EEDR;
}