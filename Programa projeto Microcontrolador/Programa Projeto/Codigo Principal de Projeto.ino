#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "minhasMacros.h"
#include "minhaCom.h"
#include "minhaAdc.h"
#define sensor_Optico_debaixo 
#define sensor_Optico_alto 
#define sensor_indutivo 
#define S0_cor 
#define S1_cor 
#define S2_cor 
#define S3_cor 
#define out_cor 10
#define led_caixa_vazia 
#define led_caixa_cheia 
#define led_defeito_laranja 
#define led_peca_verde 
#define Led_peca_azul 


int AZUL = 0;
int VERDE = 0;

void setup()
{
 initUSART();
 initAdc();

clearBit(DDRD, DDD3);
setBit(PORTD, PD3);//Sensor optico dabaixo como ENTRADA

clearBit(DDRD, DDD4);
setBit(PORTD, PD4);//Sensor optico alto como ENTRADA

clearBit(DDRD, DDD5);
setBit(PORTD, PD5);//Sensor indutivo como ENTRADA

setBit(DDRD, DDD6);//Pino S0 como saída do sensor de cor
setBit(DDRD, DDD7);//Pino S1 como saída do sensor de cor
setBit(DDRB, DDB0);//Pino S2 cmo saída do sensor de cor
setBit(DDRB, DDB1);//PIno S3 como saída do sensor de cor

clearBit(DDRB, DDB2);
setBit(PORTB, PB2);//Pino OUT do sensor como ENTRADA

setBit(DDRB, DDB3);//Configura Led vermelho como saída(Nao tem nada na caixa)
setBit(DDRB, DDB4);//Configura Led AMARELO como saída(Peca na caixa)
setBit(DDRB, DDB5);//Configura Led laranja peca defeito 
setBit(DDRC, DDC0);//Configura peca, led verde
setBit(DDRC, DDC1);//Configura peca, led azul

printString("***Programa Iniciado***");
printString("\n\n");



}

void loop()
{
  //Configurta a frequencia de saida em 20% de acordo com o Datasheet
  setBit(PORTD, PD6);//S0 do sensor ligado
  clearBit(PORTD, PD7);//S1 so sensor desligado
  

 //Funcao Detecta a cor
  cor();
  //Mostra valores no serial monitor
  /*Serial.print(" Verde : ");
  Serial.print(VERDE, DEC);
  delay(500);
  Serial.print(" Azul : ");
  Serial.print(AZUL, DEC);
  delay(500);
  Serial.println();
  */

  byte estado_optico_debaixo = !isBitSet(PIND, PIND3);//Leitura do sensor optico abaixo NPN
  byte estado_optico_acima = !isBitSet(PIND, PIND4);//Leitura do sensor acima NPN
  byte estado_indutivo = !isBitSet(PIND, PIND5);//Leitura do sensor indutivo NPN

//PECA AZUL MAIOR plastico
  if(estado_optico_debaixo == 1 && estado_optico_acima == 1 && estado_indutivo == 0 && AZUL < VERDE && AZUL < 1000)
  {
    clearBit(PORTB, PB3);//Desliga Led Vermelho
    setBit(PORTB, PB4);//Peça na esteira LIGADA AMARELO
    clearBit(PORTB, PB5);//Led peça com defeito desligado LARANJA
    setBit(PORTC, PC1);//LeD AZUL, LIGADO
    clearBit(PORTC, PC0);//LeD VERDE, DESLIGADO
    printString("Peça: plástico,Cor: azul,Peça maior, aprovada,lota A");
    printString("\n");
    delay(1000);
  }
  
  //PECA VERDE MENOR METAL
  else if(estado_optico_debaixo == 1 && estado_optico_acima == 0 && estado_indutivo == 1 && VERDE < AZUL)
  {
    clearBit(PORTB, PB3);//Desliga Led Vermelho
    setBit(PORTB, PB4);//Peça na esteira LIGADA AMARELO
    clearBit(PORTB, PB5);//Led peça com defeito desligado LARANJA
    clearBit(PORTC, PC1);//LeD AZUL, DESLIGADO
    setBit(PORTC, PC0);//LeD VERDE, LIGADO
    printString("Peça: metal,Cor:verde,Peça:menor,aprovada,lote B");
    printString("\n");
    delay(1000);
  }
    //NAO TEM PECA
   else if(estado_optico_debaixo == 0 && estado_optico_acima == 0 && estado_indutivo == 0)
   {
    setBit(PORTB, PB3);//liga Led Vermelho
    clearBit(PORTB, PB4);//Peça na esteira DESLIGADA AMARELO
    clearBit(PORTB, PB5);//Led peça com defeito desligado LARANJA
    clearBit(PORTC, PC1);//LeD AZUL, DESLIGADO
    clearBit(PORTC, PC0);//LeD VERDE, DESLIGADO
    char nao_tem_peca[30]= {"NÃO TEM PEÇA NA PLATAFORMA"};
    printString(nao_tem_peca);
    printString("\n");
    delay(1000);
   }
   
   //Peça Reprovada
   else
   
   {
    char peca_nao_qualificada[30] = {"Peça reprovada"};
    printString(peca_nao_qualificada);
    setBit(PORTB, PB5);
    clearBit(PORTB, PB3);
    clearBit(PORTC, PC0);
    clearBit(PORTC, PC1);
    setBit(PORTB, PB4);
    printString("\n");
    delay(1000);
   }
}
void cor()
{
  //Rotina que le o valor das cores 
  clearBit(PORTB, PB0);//S2 desligado do sensor
  setBit(PORTB, PB1);//S3 ligado so sensor
  
  //Ve o valor led azul
  AZUL = pulseIn(10, digitalRead(10) == 1 ? 0 : 1);//Le o pino out sensor2
  
  setBit(PORTB, PB0);//S2 ligado do sensor
  
  //Ve o valor led verde
  VERDE = pulseIn(10, digitalRead(10) == 1 ? 0 : 1);//Le o pino out sensor
}
