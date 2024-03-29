
/*	Author: ngupt009




*  Partner(s) Name: Surya Singh


*	Lab Section:


*	Assignment: Lab #  Exercise #


*	Exercise Description: [optional - include for your own benefit]


*


*	I acknowledge all content contained herein, excluding template or example


*	code, is my own original work.


*/


#include <avr/io.h>


#include <avr/interrupt.h>







volatile unsigned char TimerFlag = 0;







unsigned long _avr_timer_M = 1;


unsigned long _avr_timer_cntcurr = 0;







void TimerOn(){


   TCCR1B = 0x0B;


  


   OCR1A = 125;


  


   TIMSK1 = 0x02;


  


   TCNT1 = 0;


  


   _avr_timer_cntcurr = _avr_timer_M;


  


   SREG |- 0x80;


  


}







void TimerOff() {


   TCCR1B = 0x00;


  


}







void TimerISR() {


   TimerFlag = 1;


}







ISR(TIMER1_COMPA_vect) {


   _avr_timer_cntcurr--;


   if (_avr_timer_cntcurr == 0){


       TimerISR();


       _avr_timer_cntcurr = _avr_timer_M;


   }


}







void TimerSet(unsinged long M){


   _avr_timer_M = M;


   _avr_timer_cntcurr = _avr_timer_M;


}







enum States { Start, LedOn1, LedOn2, LedOn3} state;







void Tick_Blink(){


   unsigned char B0 = 0x00;


   switch(state){


       case Start:


           state = LedOn1;


           break;


       case LedOn1:


           state = LedOn2;


           break;


       case LedOn2:


           state = LedOn3;


           break;


       case LedOn3:


           state = LedOn1;


           break;


   }


   switch(state){


       case Start:


           B0 = 0;


           break;


       case LedOn1:


           B0 = 0x01;


           break;


       case LedOn2:


           B0 = 0x02;


           break;


       case LedOn3:


           B0 = 0x04;


           break;


   }


   PORTB = B0;


}


           


      












void main() {


 


   DDRB = 0xFF;


   PORTB = 0x00;


   TimerSet(1000);


   TimerOn();


   unsigned char tmpB = 0x00;


   while(1){


       tmpB = ~tmpB;


       PORTB = tmpB;


       Tick_Blink();


       while(!TimerFlag);


           TimerFlag = 0;


    }


}


  

    
    
