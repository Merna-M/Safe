#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_

/* EEPROM Address Register */
#define EEARL *((volatile uint8*)(0x3E))
#define EEARH *((volatile uint8*)(0x3F))
#define EEAR  *((volatile uint16*)(0x3E))

/* EEPROM data Register */
#define EEDR *((volatile uint8*)(0x3D))

/* EEPROM control Register */
#define EECR *((volatile uint8*)(0x3C))

#endif 