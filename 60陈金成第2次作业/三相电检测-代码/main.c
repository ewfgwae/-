#include <REGX52.H>
#include <INTRINS.H>

sbit Relay_A = P2^0; 
sbit Relay_B = P2^2; 
sbit Relay_C = P2^4; 


sbit LED_A = P2^1;   
sbit LED_B = P2^3;   
sbit LED_C = P2^5;  

void Delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = ms; i > 0; i--)
        for (j = 110; j > 0; j--);
}

void main() {
    LED_A = 1;
    LED_B = 1;
    LED_C = 1;

    while (1) {
        if (Relay_A == 1) {  
            LED_A = 0;       
        } else {             
            LED_A = 1;      
        }


        if (Relay_B == 1) {  
            LED_B = 0;       
        } else {
            LED_B = 1;       
        }


        if (Relay_C == 1) { 
            LED_C = 0;       
        } else {
            LED_C = 1;       
        }

        Delay_ms(10); 
    }
}