#define F_CPU 8000000UL
#include <avr/io.h>
// #include <avr/iotn13a.h> // Добавлен только для адекватной работы Zed. Компилируется и без него. Закоментировать перед сборкой.
#include "ws2812b.h"  // Подключаем библиотеку с функциями управления диодной лентой WS2812b.

// 9600000UL для частоты 9.6 МГц.
// 8000000UL для частоты 8 МГц.
// При частоте 9.6 МГц один такт исполняется за 0.104 микро секунд (10**-6).
// При частоте 8 МГц один такт исполняется за 0.125 микро секунд (10**-6).
// При частоте 1.2 МГц один такт исполняется за 0.833 микро секунд (10**-6).

#define LEDMAX 3   // Кол-во светодиодов в ленте.

void decInBin(int dec){
    // Перевод десятичного числа в двоичное.
    for (int loop = 0; loop < 8; loop++){
        dec & 0x80 ? ws2812bCode1() : ws2812bCode0();
        dec = dec << 1;
    };
};

int main(void){
    // Инициализация переменных.
    struct ledWS2812b ribbon[LEDMAX];   // Лента со светодиодами.

    // Задаём значения.
    ribbon[0].blue = 255;
    ribbon[0].green = 0;
    ribbon[0].red = 0;

    ribbon[1].blue = 0;
    ribbon[1].green = 255;
    ribbon[1].red = 0;

    ribbon[2].blue = 0;
    ribbon[2].green = 0;
    ribbon[2].red = 255;

	DDRB |= (1 << PB1); // Инициализация порта PB1 на выход.

	while(1){

        // Передаём значение массива в ленту.
        for (int loop = 0; loop < LEDMAX; loop++){
            decInBin(ribbon[loop].green);
            decInBin(ribbon[loop].red);
            decInBin(ribbon[loop].blue);
        };

        // Делаем перерыв в передаче данных.
        ws2812bCodeRet();
	};
};
