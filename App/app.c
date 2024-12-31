#include "app.h"
#include "Windows.h"
#include "Operations.h"

extern volatile int flag_window;
extern char isPassCorrect;
extern char DTClog[MAX_SENTENCES][MAX_SENTENCE_LENGTH + 1];
extern short Global_counter_for_DTC_Messages;

static const int TEN_MICROSECONDS = 10;



/**************************************************************************/
/**************************************************************************/
void InIt()
{
    Clock_Enable();
    EchoPin_init();
    TriggerPin_init();
    LED_Blue_Init();
    LED_Green_Init();
    PB1_Init();
    PB2_Init();
    PB3_Init();
    PB4_Init();
    PortB_Pin0_Init();
    PortB_Pin1_Init();
    PortB_Pin2_Init();
    PortB_Pin3_Init();
    UART0_Init();
    LCD_init(); /* Initialize the LCD */
    ADC_Init(CHANNEL_ZERO);
    Motor_Init();
    SysTick_Init();
    Timer1A_Init();
}

int main(void)
{

    int distance = 0;
    short first_time = TRUE;

    //eeprom variables
    const char accident[] = "P001"; //near accident DTC code
    const char temp[] = "P002";  //temperature DTC code

    //temperature sensor
    int temperature = 0;

    InIt();

    LCD_Welcome_Screen();
    Enable_Exceptions();
    while (1)
    {
        //if we recieved 3 (3+48 in ascii table) from the terminal end the program
        if (operation == END_PROGRAM)
        {
            HandleEndProgram();
            first_time = FALSE;
            break;
        }
        //if we recieved 2 (2+48 in ascii table) from the terminal print the message in EEPROM
        else if (operation == PRINT_MESSAGE)
        {
            HandleEEPROM();
            //HandleDTC();
            operation = RUNNING; //return operation to 49 to complete the program
            first_time = FALSE;
        }

        else if (operation == RUNNING)
        {
            //if (isPassCorrect)

            HandlePassword();

            if (first_time)
            {
                LCD_clearScreen();
                LCD_Display();
                first_time = FALSE;
            }
            //Application Code
            GPIO_PORTF_DATA_REG |= (1 << 1);  // Set Trigger Pin high
            Delay_US(TEN_MICROSECONDS);              // 10 microsecond delay
            GPIO_PORTF_DATA_REG &= ~(1 << 1); // Set Trigger Pin low
            while (GET_BIT(GPIO_PORTF_DATA_REG, 4) == 1);
            HandleUltraSonic(&distance, accident);
            HandleTemperature(temperature, temp);
            HandleWindow(flag_window);

        }
    }
}

