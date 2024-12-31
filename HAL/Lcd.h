/*
 * Lcd.h
 *
 */

#ifndef LCD_H_
#define LCD_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//port A
#define LCD_DB4_PIN                2
#define LCD_DB5_PIN                3
#define LCD_DB6_PIN                4
#define LCD_DB7_PIN                5
#define RS_PIN                     6
#define E_PIN                      7


/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


void LCD_init(void);
void LCD_Welcome_Screen();
void LCD_Display();
void LCD_Delay_Three_seconds();


/*
 * Description :
 * Send the required command to the screen
 */
void LCD_sendCommand(char command);



/*
 * Description :
 * Display the required character on the screen
 */
void LCD_displayCharacter(char data);




/*
 * Description :
 * Display the required string on the screen
 */
void LCD_displayString(const char *Str);




/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(char row,char col);



/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(char row,char col,const char *Str);



/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_intgerToString(int data);



/*
 * Description :
 * Send the clear screen command
 */
void LCD_clearScreen(void);


void static Delay_MS(unsigned long long n);
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND        364
#define NUMBER_OF_ITERATIONS_PER_ONE_MICRO_SECOND       3.64

#endif /* LCD_H_ */
