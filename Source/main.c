#define F_CPU 9600000UL
#include <avr/io.h>
// #include <avr/iotn13a.h>    // Добавлен только для адекватной работы Zed. Компилируется и без него. Закоментировать перед сборкой.

// 9600000UL для частоты 9.6 МГц.
// При частоте 9.6 МГц один такт исполняется за 0.104 микро секунд (10**-6).
// При частоте 1.2 МГц один такт исполняется за 0.833 микро секунд (10**-6).

#define LEDMAX 3   // Кол-во светодиодов в ленте.

// Описание строения диода WS2812b.
struct ledWS2812b {
    unsigned char green;  // 0-255;
    unsigned char red;    // 0-255;
    unsigned char blue;   // 0-255;
};

int current_LED = 0;    // Текущий светодиод.
int programm = 2;       // Программа работы.

void code_0(){
	// Сигнал T0H 0.35 микро секунд +- 150 нано секунд.
	PORTB = 0xff;	// 0.208 мкс.
	asm volatile ("nop");		// 0.312 мкс.
	asm volatile ("nop");		// 0.416 мкс.
	// Сигнал T0L 0.9 микро секунд +- 150 нано секунд.
	//PORTB = 0x00;	// 0.208 мкс.
	asm volatile ("ldi r24, 0x00");
	asm volatile ("nop");		// 0.312 мкс.
	asm volatile ("nop");		// 0.416 мкс.
	asm volatile ("nop");		// 0.520 мкс.
	asm volatile ("nop");		// 0.624 мкс.
	asm volatile ("nop");		// 0.728 мкс.
	asm volatile ("nop");		// 0.832 мкс.
};

void code_1(){
	// Сигнал T1H 0.9 микро секунд +- 150 нано секунд.
	//PORTB = 0x00;	// 0.208 мкс.
	asm volatile ("ldi r24, 0x00");
	asm volatile ("nop");		// 0.312 мкс.
	asm volatile ("nop");		// 0.416 мкс.
	asm volatile ("nop");		// 0.520 мкс.
	asm volatile ("nop");		// 0.624 мкс.
	asm volatile ("nop");		// 0.728 мкс.
	asm volatile ("nop");		// 0.832 мкс.
	// Сигнал T1L 0.35 микро секунд +- 150 нано секунд.
	PORTB = 0xff;	// 0.208 мкс.
	asm volatile ("nop");		// 0.312 мкс.
	asm volatile ("nop");		// 0.416 мкс.
};

void decInBin(int dec){
    // Перевод десятичного числа в двоичное.
    for (int loop = 0; loop < 8; loop++){
        dec & 0x80 ? code_1() : code_0();
        dec = dec << 1;
    };
};

int main(void){
    // Инициализация переменных.
    struct ledWS2812b ribbon[LEDMAX];   // Лента со светодиодами.

	DDRB |= (1 << PB1); // Инициализация порта PB1 на выход.

	while(1){
		// Плавное увеличение и уменьшение свечения всех диодов.
        if (programm == 2){

            int step = 0; // Увеличение или уменьшение яркости.

            // Инициализация светодиода.
            if (ribbon[current_LED].green == ribbon[current_LED].blue){
                if (ribbon[current_LED].green < 254) {
                    // Если яркость диода не максимальная, то будем её постепенно увеличивать...
                    ribbon[current_LED].green++;
                }
                else {
                    // ... в противном случае будем убавлять
                    ribbon[current_LED].blue--;
                };
            };

            // Увеличиваем яркость.
            if ((ribbon[current_LED].green > ribbon[current_LED].blue) & (ribbon[current_LED].green < 255)){
                step = 1;
            }
            // Уменьшение яркости.
            else if ((ribbon[current_LED].green < ribbon[current_LED].blue) & (ribbon[current_LED].blue > 1)){
                step = -1;
            };

            // Проверяем достижение предела.
            if (step == 0){
                if (ribbon[current_LED].green == 255){
                    ribbon[current_LED].green--;
                    ribbon[current_LED].blue++;
                }
                else if (ribbon[current_LED].blue == 1){
                    ribbon[current_LED].green++;
                    ribbon[current_LED].blue--;
                };
            };

            // Изменение яркости.
            ribbon[current_LED].green += step;
            ribbon[current_LED].red += step;
            ribbon[current_LED].blue += step;

            current_LED++; // Берём следующий светодиод.
        };

        // Недопускаем переполнения массива.
        if (current_LED >= (LEDMAX)){
            current_LED = 0;
        }

        // Передаём значение массива в ленту.
        for (int loop = 0; loop < LEDMAX; loop++){
            decInBin(ribbon[loop].green);
            decInBin(ribbon[loop].red);
            decInBin(ribbon[loop].blue);
        };
	};
};
