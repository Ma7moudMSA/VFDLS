/*
 * EEPROM.c
 *
 */
#include "tm4c123gh6pm_registers.h"
#include "EEPROM.h"
// Global array to hold multiple sentences
char DTClog[MAX_SENTENCES][MAX_SENTENCE_LENGTH + 1]; // +1 for null terminator
short Global_counter_for_DTC_Messages = 0;

void readDTC(unsigned char *DTCCode, unsigned long block, unsigned long offset)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        EEPROM_EEBLOCK_REG = block;
        EEPROM_EEOFFSET_REG = offset + i;
        DTCCode[i] = (char) EEPROM_EERDWR_REG;
        while (EEPROM_EEDONE_REG & 1)
            ;
    }
    DTCCode[4] = '\0';

}
void writeDTC(const char *DTCCode, unsigned long block, unsigned long offset)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        EEPROM_EEBLOCK_REG = block;
        EEPROM_EEOFFSET_REG = offset + i;
        EEPROM_EERDWR_REG = DTCCode[i];
        while (EEPROM_EEDONE_REG & 1)
            ;
    }
}
void WriteDTC_2(const char *DTCCode)
{
    static unsigned long block = 0;  // Ensure proper initialization
    static unsigned long offset = 0;
    int i;

    // Validate block and offset ranges
    if (block > 31 || offset >= 16)
    {
        block = 0;   // Reset block
        offset = 0;  // Reset offset
    }

    for (i = 0; i < 4; i++)
    {
        EEPROM_EEBLOCK_REG = block;          // Set the block
        EEPROM_EEOFFSET_REG = offset + i;   // Set the offset
        EEPROM_EERDWR_REG = DTCCode[i];      // Write the data

        // Wait for the write operation to complete
        while (EEPROM_EEDONE_REG & 1)
            ;
    }

    // Increment offset and block
    offset += 4;
    if (offset >= 16)
    {
        offset = 0;
        block++;
    }

    // Wrap around block if it exceeds maximum
    if (block > 31)
    {
        block = 0;
    }
}
void EEPROM_Read(uint32 address, char* buffer, uint32 length) {
    uint32 block, offset;
    uint32 i;
    unsigned char message[50]=0;

    for (i = 0; i < length; i++) {
        // Calculate block and offset
        block = (address + i) / 16;  // Divide by 16 to determine the block
        offset = (address + i) % 16; // Modulo to find the offset within the block

        // Set the block and offset
        EEPROM_EEBLOCK_REG = block;
        EEPROM_EEOFFSET_REG = offset;

        // Read the data
        buffer[i] = (char)EEPROM_EERDWR_REG;
        message[i] = buffer[i];

        // Wait for read completion
        while (EEPROM_EEDONE_REG & EEPROM_EEDONE_REG);
    }
    buffer[length] = '\0'; // Null-terminate the string if reading text
}

void READ_DTC(unsigned char *DTCCode)
{
    unsigned long block = 0;
    unsigned long offset = 0;
    int j;
    int i;

    for (j = 0; j < 31; j++)
    {
        for (i = 0; i < 4; i++)
        {
            EEPROM_EEBLOCK_REG = block;
            EEPROM_EEOFFSET_REG = offset + i;
            DTCCode[j] = (char) EEPROM_EERDWR_REG;
            while (EEPROM_EEDONE_REG & 1)
                ;
        }
        //DTCCode[i++] = '\n';
        offset += 4;
        if (offset >= 16)
        {
            offset = 0;
            block++;
        }
    }

}

void writeBufferToEEPROM(unsigned long block, unsigned long offset)
{
    unsigned long i, j, addr = offset;
    for (i = 0; i < MAX_SENTENCES; i++)
    {
        for (j = 0; j < MAX_SENTENCE_LENGTH; j++)
        {
            EEPROM_EEBLOCK_REG = block;              // Set block
            EEPROM_EEOFFSET_REG = addr++;            // Increment address
            EEPROM_EERDWR_REG = DTClog[i][j]; // Write character
            while (EEPROM_EEDONE_REG & 1)
                ;           // Wait for write completion
        }
    }
}

void readBufferFromEEPROM(unsigned long block, unsigned long offset)
{
    unsigned long i, j, addr = offset;
    for (i = 0; i < MAX_SENTENCES; i++)
    {
        for (j = 0; j < MAX_SENTENCE_LENGTH; j++)
        {
            EEPROM_EEBLOCK_REG = block;              // Set block
            EEPROM_EEOFFSET_REG = addr++;            // Increment address
            DTClog[i][j] = (char) EEPROM_EERDWR_REG; // Read character
            while (EEPROM_EEDONE_REG & 1)
                ;           // Wait for read completion
        }
        DTClog[i][MAX_SENTENCE_LENGTH] = '\0'; // Null-terminate each sentence
    }
}

void writeSentenceToEEPROM(unsigned long block, unsigned long offset, int index,
                           const char *sentence)
{
    if (index >= MAX_SENTENCES)
        return; // Out-of-bounds check
    strncpy(DTClog[index], sentence, MAX_SENTENCE_LENGTH); // Update global array
    unsigned long addr = offset + (index * MAX_SENTENCE_LENGTH);
    unsigned long j;
    for (j = 0; j < MAX_SENTENCE_LENGTH; j++)
    {
        EEPROM_EEBLOCK_REG = block;                    // Set block
        EEPROM_EEOFFSET_REG = addr + j;                // Calculate address
        EEPROM_EERDWR_REG = DTClog[index][j];   // Write character
        while (EEPROM_EEDONE_REG & 1)
            ;                 // Wait for write completion
    }
}

void deleteDTC(unsigned long block, unsigned long offset)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        EEPROM_EEBLOCK_REG = block;
        EEPROM_EEOFFSET_REG = offset + i;
        EEPROM_EERDWR_REG = 0;
        while (EEPROM_EEDONE_REG & 1)
            ;
    }
}
