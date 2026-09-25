// Описание строения одного диода WS2812b.
struct ledWS2812b {
    unsigned char green;  // 0-255;
    unsigned char red;    // 0-255;
    unsigned char blue;   // 0-255;
};

// Декларация функций:
void ws2812bCode0();
void ws2812bCode1();
void ws2812bCodeRet();
