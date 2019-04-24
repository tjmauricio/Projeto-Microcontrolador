//Definições de macros utilizadas no projeto
#define setBit(byte, bit) (byte |= 1 << bit)
#define clearBit(byte, bit) (byte &= ~(1<<bit))
#define toggleBit(byte, bit) (byte ^= 1 << bit)
#define isBitSet(byte,bit) ((byte & (1<<bit)) == (1<<bit)? 1 : 0)
