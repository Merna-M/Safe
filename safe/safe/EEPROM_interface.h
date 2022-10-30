
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/* ############################# Macros #############################*/

/* EEPROM control bits */
#define EERE   0
#define EEWE   1
#define EEMWE  2
#define EERIE  3

/* ################################## Include ###################################*/
#include "STD_types.h"
#include "BIT_math.h"
#include "EEPROM_private.h"

/*####################################### prototypes ########################################*/

/*
FUNCTION NAME        : EEPROM_vWrite
FUNCTION DESCRIPTION : writes a data in a certain address in the EEPROM
FUNCTION INPUTS      : Copy_u16Address: address of the location , Copy_u8Data: the data to be written
FUNCTION RETURN      : void
*/
void EEPROM_vWrite(uint16 Copy_u16Address , uint8 Copy_u8Data);

/*
FUNCTION NAME        : EEPROM_vREAD
FUNCTION DESCRIPTION : reads a data from a certain address in the EEPROM
FUNCTION INPUTS      : Copy_u16Address: address of the location
FUNCTION RETURN      : returns the data in the address
*/
uint8 EEPROM_vREAD(uint16 Copy_u16Address);

#endif 