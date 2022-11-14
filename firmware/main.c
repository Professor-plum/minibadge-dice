/*
 * File:   main.c
 * Author: plum
 *
 * Created on May 14, 2022, 8:30 PM
 */


#include <xc.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>



/*
 * 
 *          1   10
 *          2 8 20
 *          4   40
 * 
 */

const uint8_t roll[] = {0x08, 0x41, 0x49, 0x55, 0x5D, 0x77}; //leds from each roll
const uint8_t pattern[] = {0x01, 0x02, 0x04, 0x40, 0x20, 0x10}; 

void rollDice() {
    for (int i=0; i<20; ++i) {
        PORTA = roll[rand()%6];
        _delay_ms(50);
    }
    for (int i=0; i<10; ++i) {
        PORTA = roll[rand()%6];
        _delay_ms(100);
    }
    for (int i=0; i<5; ++i) {
        PORTA = roll[rand()%6];
        _delay_ms(150);
    }
    PINA = roll[rand()%6];
    _delay_ms(150);
    PORTA = roll[rand()%6];
    _delay_ms(150);
    uint8_t final = rand()%6;
    PORTA = roll[final];
    _delay_ms(150);
    for (int i=0; i<5; ++i) {
        _delay_ms(100);
        PORTA =0;
        _delay_ms(100);
        PORTA = roll[final];
    }
}

int main(void) {
    DDRA = 0x7F; //set led pins as output
    PORTA = 0; //lights off
    DDRB &= ~(1<<PINB0); //button input
    PUEB |= (1<<PINB0); // pull up button
    
    uint32_t counter = 200;
    
    while (1) {
        if ((PINB & (1<<PINB0)) == 0 ){ // button press
            counter = 0;
            rollDice();
        } 
        else if (counter > 60) {
            PORTA = pattern[counter%6];
        }
        _delay_ms(60);
        counter++;
        rand();
    }
    
    return 0;
}
