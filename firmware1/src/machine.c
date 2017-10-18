#include "machine.h"

/**
 * @brief set error state
 */
inline void set_state_error(void)
{
    usart_send_string("Set error. ");
    state_machine = STATE_ERROR;
}

/**
* @brief set initializing state
*/ 
inline void set_state_initializing(void)
{
    usart_send_string("Set initializing. ");
    state_machine = STATE_INITIALIZING;
}

/**
* @brief set idle state
*/ 
inline void set_state_idle(void)
{                                
    usart_send_string("Set idle. ");
    state_machine = STATE_IDLE;
}

/**
* @brief set running state
*/ 
inline void set_state_running(void)
{
    usart_send_string("Set running. ");
    state_machine = STATE_RUNNING;
}
 

/**
 * @brief Checks if the system is OK to run:
 *  - all ring_buffers needed to be full
 *  - checks the current
 *  - checks the voltage
 *  - checks the temperature
 *
 */
inline void task_initializing(void)
{
    fault_count = 0;

    if(!error_flags.all){
        set_state_idle();
    }
    else{
        set_state_error();
    }
}


/**
 * @brief waits for commands while checking the system:
 *  - checks the deadman's switch state
 *  - checks the on_off_switch state
 *  - checks the potentiometer state
 *  then if its ok, enable the system to operate
 */
inline void task_idle(void)
{
    can_t msg;

    msg.id = 0x123456;
    msg.flags.rtr = 0;
    msg.flags.extended = 1;
    msg.length = 4;
    msg.data[0] = 0xde;
    msg.data[1] = 0xad;
    msg.data[2] = 0xbe;
    msg.data[3] = 0xef;

    can_send_message(&msg);
 
    set_state_running();
}

uint16_t can_msg_err = 0;
/**
 * @brief running task checks the system and apply the control action to pwm.
 */
inline void task_running(void)
{
    if(can_check_message()){
        usart_send_string("f1: New message! ");
        can_t msg;
        if(can_get_message(&msg)){
            msg.id +=10;
            can_send_message(&msg);
            usart_send_string("ID: ");
            usart_send_uint16(msg.id);
            usart_send_string(". DATA: ");
            for(uint8_t i = 0; i < msg.length; i++){
                usart_send_uint16(msg.data[i]);
                usart_send_char(' ');
            }
            usart_send_string(". ERR: ");
            usart_send_uint16(can_msg_err);
            usart_send_char('\n');
        }else{
            can_msg_err++;
        }
    }
}

/**
 * @brief error task checks the system and tries to medicine it.
 */
inline void task_error(void)
{
    if(total_errors++ >= 20){
        for(;;);    // waits the watchdog to reset.
    }
    
    set_state_initializing();
}


/**
 * @brief this is the machine state itself.
 */
inline void machine_run(void)
{
    switch(state_machine){
        case STATE_INITIALIZING:
            task_initializing();

            break;
        case STATE_IDLE:
            task_idle();

            break;
        case STATE_RUNNING:
            task_running();

            break;
        case STATE_ERROR:
            task_error();

        default:
            break;
    }
}

/**
 * @brief some interrupt
 */
ISR(PCINT2_vect)
{    
}

