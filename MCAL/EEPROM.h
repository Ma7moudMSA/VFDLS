/*
 * EEPROM.h
 *
 *  Created on: Dec 13, 2024

 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_types.h"

void writeDTC(const char *DTCmessage, unsigned long block,
              unsigned long offset);
void readDTC(unsigned char *DTCCode, unsigned long block, unsigned long offset);
void deleteDTC(unsigned long block, unsigned long offset);
void writeSentenceToEEPROM(unsigned long block, unsigned long offset, int index,
                           const char *sentence);
void readBufferFromEEPROM(unsigned long block, unsigned long offset);
void writeBufferToEEPROM(unsigned long block, unsigned long offset);
void READ_DTC(unsigned char *DTCCode);
void WriteDTC_2(const char *DTCCode);
void EEPROM_Read(uint32 address, char *buffer, uint32 length);

#define MAX_SENTENCE_LENGTH 25
#define MAX_SENTENCES 2

#define  EESUP_REG    0x400AF000+0x01C

#endif /* EEPROM_H_ */
