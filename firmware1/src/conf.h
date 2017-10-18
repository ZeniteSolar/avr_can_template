/**
 * @file conf.h
 *
 * @defgroup CONF Configurations 
 *
 * @brief General configuration of the system.
 *
 */

#ifndef _CONF_H_
#define _CONF_H_

// CONFIGURACOES DE COMPILACAO
//#define DEBUG_ON
//#define VERBOSE_ON

// ATIVACAO DOS MODULOS
#define ADC_ON
#define USART_ON
//#define PWM_ON
#define CTRL_ON
#define MACHINE_ON
//#define SLEEP_ON
#define WATCHDOG_ON
#define CAN_ON

// DEFINICOES DOS PINOS DE ENTRADA

// DEFINICOES DOS PINOS DE SAIDA
#define     LED_PORT                PORTC
#define     LED_PIN                 PINC
#define     LED_DDR                 DDRC
#define     LED                     PC5

#define     cpl_led()               cpl_bit(LED_PORT, LED);
#define     set_led()               set_bit(LED_PORT, LED);
#define     clr_led()               clr_bit(LED_PORT, LED);

// DEFINICOES DOS ADCS
//#define     avg_pot                 avg_adc0

// -----------------------------------------------------------------------------
/* Global settings for building the can-lib and application program.
 *
 * The following two #defines must be set identically for the can-lib and
 * your application program. They control the underlying CAN struct. If the
 * settings disagree, the underlying CAN struct will be broken, with
 * unpredictable results.
 * If can.h detects that any of the #defines is not defined, it will set them
 * to the default values shown here, so it is in your own interest to have a
 * consistent setting. Ommiting the #defines in both can-lib and application
 * program will apply the defaults in a consistent way too.
 *
 * Select if you want to use 29 bit identifiers.
 */
#define SUPPORT_EXTENDED_CANID  1

/* Select if you want to use timestamps.
 * Timestamps are sourced from a register internal to the AT90CAN.
 * Selecting them on any other controller will have no effect, they will
 * be 0 all the time.
 */
#define SUPPORT_TIMESTAMPS      0

#define SUPPORT_MCP2515         1

// MCP2515 PINS
#define MCP2515_CS              B,2     // PB2, PCINT2, OC1B, PCINT1, PWM
#define MCP2515_INT             D,2     // PD2, INT0, PCINT18

#endif /* ifndef _CONF_H_ */
