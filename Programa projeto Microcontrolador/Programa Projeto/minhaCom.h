//definição para o setbaud funcionar
#define BAUD 9600

#include <util/setbaud.h>
//funções de configuração da porta serial
void initUSART(void){
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    //Se o multiplicador de clock estiver ligado
    #if USE_2X
        UCSR0A |= (1 << U2X0);
    #else
        UCSR0A &= ~(1 << U2X0);
    #endif

    UCSR0B = (1 << TXEN0) | (1 << RXEN0);   //Habilita a transmissão e recepção de dados
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //Configura a comunicação para 8 bits, 1 stop bit

}

void transmitByte(uint8_t data){
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

uint8_t receiveByte(void){
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void printString(const char myString[]){
    uint8_t i = 0;
    while(myString[i]){
        transmitByte(myString[i]);
        i++;
    }
}
