//Inicialização do conversor ADC - por padrão, vem configurado para o canal 0
void initAdc(void){
  ADMUX |= (1 << REFS0);  //Ajuste da tensão de referência
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //Ajusta o pre-scaler para 1/8
  ADCSRA |= (1 << ADEN); //Habilita o hardware do conversor para funcionar
}

void escolheCanal(uint8_t canal){
  switch(canal){
    case 0:
      clearBit(ADMUX, MUX0);
      clearBit(ADMUX, MUX1);
      clearBit(ADMUX, MUX2);
      clearBit(ADMUX, MUX3);
      break;
    case 1:
      setBit(ADMUX, MUX0);
      clearBit(ADMUX, MUX1);
      clearBit(ADMUX, MUX2);
      clearBit(ADMUX, MUX3);
      break;
    case 2:
      clearBit(ADMUX, MUX0);
      setBit(ADMUX, MUX1);
      clearBit(ADMUX, MUX2);
      clearBit(ADMUX, MUX3);
      break;
    case 3:
      setBit(ADMUX, MUX0);
      setBit(ADMUX, MUX1);
      clearBit(ADMUX, MUX2);
      clearBit(ADMUX, MUX3);
      break;
    case 4:
      clearBit(ADMUX, MUX0);
      clearBit(ADMUX, MUX1);
      setBit(ADMUX, MUX2);
      clearBit(ADMUX, MUX3);
      break;
    case 5:
      setBit(ADMUX, MUX0);
      clearBit(ADMUX, MUX1);
      setBit(ADMUX, MUX2);
      clearBit(ADMUX, MUX3);
      break;
    default:
      clearBit(ADMUX, MUX0);
      clearBit(ADMUX, MUX1);
      clearBit(ADMUX, MUX2);
      clearBit(ADMUX, MUX3);
      break;
  }
}

int fazerLeitura(uint8_t canal){
  escolheCanal(canal);
  ADCSRA |= (1 << ADSC);  //Liga o ADC no canal atual
  loop_until_bit_is_clear(ADCSRA, ADSC);  //Espera até a conversão terminar
  return  ADC;
}