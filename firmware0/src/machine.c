#include "machine.h"

/**
 * @brief set error state
 */
inline void set_state_error(void)
{
    state_machine = STATE_ERROR;
}

/**
* @brief set initializing state
*/ 
inline void set_state_initializing(void)
{
    state_machine = STATE_INITIALIZING;
}

/**
* @brief set idle state
*/ 
inline void set_state_idle(void)
{
    state_machine = STATE_IDLE;
}

/**
* @brief set running state
*/ 
inline void set_state_running(void)
{
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
    set_state_running();
}


/**
 * @brief running task checks the system and apply the control action to pwm.
 */
inline void task_running(void)
{

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

