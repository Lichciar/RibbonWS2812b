// #include <avr/io.h>
#include "ws2812b.h"  // Подключаем библиотеку с функциями управления диодной лентой WS2812b.

// Передача сигнала логического нуля в шину данных.
void ws2812bCode0(){
	// Сигнал T0H 0.35 микро секунд +- 150 нано секунд.
	//PORTB = 0xff;	// 0.250 мкс.
	asm volatile ("ldi r24, 0xff"); // 1 clocks = 0.125 мкс.
	asm volatile ("out 0x18, r24"); // 1 clocks = 0.250 мкс.
	asm volatile ("nop");		    // 1 clocks = 0.375 мкс.
	// Сигнал T0L 0.9 микро секунд +- 150 нано секунд.
	//PORTB = 0x00;	// 0.250 мкс.
	asm volatile ("ldi r24, 0x00"); // 1 clocks = 0.125 мкс.
	asm volatile ("out 0x18, r24"); // 1 clocks = 0.250 мкс.
	asm volatile ("nop");		    // 1 clocks = 0.375 мкс.
	asm volatile ("nop");		    // 1 clocks = 0.500 мкс.
	asm volatile ("nop");		    // 1 clocks = 0.625 мкс.
	asm volatile ("nop");		    // 1 clocks = 0.750 мкс.
	asm volatile ("nop");		    // 1 clocks = 0.875 мкс.
};

// Передача сигнала логической единицы в шину данных.
void ws2812bCode1(){
	// Сигнал T1H 0.9 микро секунд +- 150 нано секунд.
	//PORTB = 0x00;	// 0.208 мкс.
	asm volatile ("ldi r24, 0x00"); // 1 clocks = 0.125 мкс.
	asm volatile ("out 0x18, r24"); // 1 clocks = 0.250 мкс.
	asm volatile ("nop");           // 1 clocks = 0.375 мкс.
	asm volatile ("nop");           // 1 clocks = 0.500 мкс.
	asm volatile ("nop");           // 1 clocks = 0.625 мкс.
	asm volatile ("nop");           // 1 clocks = 0.750 мкс.
	asm volatile ("nop");           // 1 clocks = 0.875 мкс.
	// Сигнал T1L 0.35 микро секунд +- 150 нано секунд.
	//PORTB = 0xff;	// 0.208 мкс.
	asm volatile ("ldi r24, 0xff"); // 1 clocks = 0.125 мкс.
	asm volatile ("out 0x18, r24"); // 1 clocks = 0.250 мкс.
	asm volatile ("nop");           // 1 clocks = 0.375 мкс.
};

// Передача сигнала окончания передачи данных в шину данных.
void ws2812bCodeRet(){
	// Сигнал Treset 1.25 микро секунд +- 150 нано секунд.
	asm volatile ("ldi r24, 0x00"); // 1 clocks = 0.125 мкс.
	asm volatile ("out 0x18, r24"); // 1 clocks = 0.250 мкс.
	asm volatile ("nop");           // 1 clocks = 0.375 мкс.
	asm volatile ("nop");           // 1 clocks = 0.500 мкс.
	asm volatile ("nop");           // 1 clocks = 0.625 мкс.
	asm volatile ("nop");           // 1 clocks = 0.750 мкс.
	asm volatile ("nop");           // 1 clocks = 0.875 мкс.
	asm volatile ("nop");           // 1 clocks = 1.000 мкс.
	asm volatile ("nop");           // 1 clocks = 1.125 мкс.
	asm volatile ("nop");           // 1 clocks = 1.250 мкс.
};
