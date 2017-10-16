/**
 * 
 */

#include "main.h"
#include "can_filters.h"

uint8_t CTRL_CLK = 0;       // CLOCK of controle (frequency defined by timer2)
uint16_t D = 0;             // DUTY CYCLE of PWM
uint8_t led_div = 0;        // CLOCK division for led control

/**
 * @brief Timer TC2 configs  --> Period for control actions
 */
void ctrl_init()
{
	TCCR2A  =   (1 << WGM21) | (0 << WGM20)			// Timer 2 in Mode 2 = CTC (clear on compare)
			| (0 << COM2A1) | (0 << COM2A0)			// do nothing with OC2A
			| (0 << COM2B1) | (0 << COM2B0);		// do nothing with OC2B
	TCCR2B  =   (0 << WGM22)                        // Timer 0 in Mode 2 = CTC (clear on compare)
            | (0 << FOC0A) | (0 << FOC0B)           // dont force outputs
            | (1 << CS02)			                // clock enabled, prescaller = 1024
			| (1 << CS01) 
            | (1 << CS00);			                 
	OCR2A   =   222;			                    // Set frequency to 35Hz
	TIMSK2 |=   (1 << OCIE2A);                      // Set interrupt when compare to OCR2A
}    
 
/**
 * @brief Peripherals configuration
 */
inline static void setup(void)
{

#ifdef DEBUG_ON
    set_bit(DDRB, PB5);
    set_bit(DDRB, PB4);
#endif 

#ifdef ADC_ON
    adc_init();
#endif

#ifdef PWM_ON
    pwm_init();
#endif

#ifdef CTRL_ON
	ctrl_init();
#endif

#ifdef USART_ON
    usart_init(MYUBRR,1,1);                         // inicializa a usart
#endif

#ifdef WATCHDOG_ON
    wdt_init();
#endif

#ifdef SLEEP_ON 
    set_sleep_mode(SLEEP_MODE_IDLE);                // configura sleep com o modo IDLE
#endif
    
#ifdef CAN_ON
    can_init(BITRATE_125_KBPS);
    can_static_filter(can_filter);
#endif

	sei();				                            // liga a chave geral das interrupcoes

}


/**
 * @brief main
 */
int main(void)
{
    system_flags.all = error_flags.all = 0;
    state_machine = STATE_INITIALIZING;

    setup();

    for(;;){

        wdt_reset();                                // checkpoint: reset watchdog timer

        // Main Task runs at CTRL_CLK frequency (defined by TIMER2)
		if(CTRL_CLK) {
            machine_run();
            CTRL_CLK = 0;
        }
   
#ifdef SLEEP_ON 
        sleep_mode();           // sleeps until next interrupt
#endif

    }
}

/**
 * @brief ISR for control actions
 */
ISR(TIMER2_COMPA_vect)
{
    CTRL_CLK = 1;
}

/**
 * @brief waits until watchdog reset. If DEBUG_ON, then sinature it using DEBUG0 and DEBUG1 pins
 */
ISR(BADISR_vect)
{   
    for(;;){
#ifdef DEBUG_ON
        DEBUG0;
        DEBUG1;
        _delay_ms(100);
#endif
    }
}

 /*
EMPTY_INTERRUPT(TIMER0_COMPB_vect);
EMPTY_INTERRUPT(TIMER0_OVF_vect);
*/
/*
EMPTY_INTERRUPT(TIMER1_CAPT_vect);
EMPTY_INTERRUPT(TIMER1_COMPA_vect);
EMPTY_INTERRUPT(TIMER1_COMPB_vect);
EMPTY_INTERRUPT(TIMER1_OVF_vect);
*/
/*
EMPTY_INTERRUPT(TIMER2_COMPB_vect);
EMPTY_INTERRUPT(TIMER2_OVF_vect);
*/
