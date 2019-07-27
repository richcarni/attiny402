#define F_CPU 3333333

//#include <atmel_start.h>
// #include "include/atmel_start_pins.h"
#include <util/delay.h>
#include <port.h>

/**
 * \brief Set LED0 data direction
 *
 * Select if the pin data direction is input, output or disabled.
 * If disabled state is not possible, this function throws an assert.
 *
 * \param[in] direction PORT_DIR_IN  = Data direction in
 *                      PORT_DIR_OUT = Data direction out
 *                      PORT_DIR_OFF = Disables the pin
 *                      (low power state)
 */
static inline void LED0_set_dir(const enum port_dir dir)
{
	PORTA_set_pin_dir(3, dir);
}

/**
 * \brief Set LED0 level
 *
 * Sets output level on a pin
 *
 * \param[in] level true  = Pin level set to "high" state
 *                  false = Pin level set to "low" state
 */
static inline void LED0_set_level(const bool level)
{
	PORTA_set_pin_level(3, level);
}

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	//atmel_start_init();
	LED0_set_dir(PORT_DIR_OUT);
	PORTA_set_pin_dir(6, PORT_DIR_OUT);

	LED0_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);
	PORTA_set_pin_level(6, false);

	/* Replace with your application code */
	while (1) {
		LED0_set_level(true);
		PORTA_set_pin_level(6, true);
		_delay_ms(330);
		PORTA_set_pin_level(6, false);
		_delay_ms(330);
		PORTA_set_pin_level(6, true);
		_delay_ms(330);
		LED0_set_level(false);
		PORTA_set_pin_level(6, false);
		_delay_ms(330);
	}
}
