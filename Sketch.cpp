/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Ticker.h>
#define F_CPU 16000000UL
#include "TM1640.h"
#include "StringArray.h"
asm ("#include <WS2812.S>");
#include "Serial.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Beginning of Auto generated function prototypes by Atmel Studio
//End of Auto generated function prototypes by Atmel Studio


#define SW_Tx 10     //Arduino Digital signals (10)  PB1
#define SW_RX 9      //Arduino Digital signals  (9)  PB2


enum Color {NONE,RED,BLUE,GREEN,ORANGE};
Color RGB_Color;
	
static char *Mensaje = "BATMAN";
char buffer[30]={0x0D};
char Memoria[150]={0x0D};
SoftwareSerial mySerial(SW_RX, SW_Tx); // RX, TX

void Sound(void);
void Move(void);
void RGBazul(void);
void RGBverde(void);
void RGBrojo(void);
void RGBnaranja(void);
void OFF(void);
void RGBrojo2(void);
void Tira(void);
void Distancia(void);
void Follow2(void);
//void Follow3(void);
void Infla(void);
void RGB(void);

volatile char F120ms, Counter,a=0,b=0,d=0,Counter2,F2s,TD,TD2,TD3,right, left, front, incre=1, Color=0, Flag1, var=0,i=0,p=0,c=0, temp,B2=0,Alm,ct=0,st=0,at=0;
char temp2,j=0,Datos=0;
char *Mensaje1="ESTACION A",*Mensaje2="ESTACION B",*Mensaje3="AMARILLO",*Mensaje4="VERDE",*Mensaje5="AZUL",*Mensaje6="STAND BY";
unsigned int i_rgb=0;
float s=0;
int t=0;

extern "C" void RGB_BYTE(unsigned char);
const char tono[]={0, 53, 64, 71, 80, 0, 0, 60, 0, 53, 0, 71, 80, 0, 0, 80, 0, 80, 71, 64, 53, 0, 0, 53, 0, 53, 64, 71, 64, 0, 0, 0, 0, 60, 64, 60, 64, 60, 64, 0, 80, 80, 71, 64, 71, 64, 71, 64, 71, 0, 80, 80, 71, 64, 71, 64, 71, 0, 0, 71, 71, 71, 71, 71, 71, 107, 80, 0, 60, 64, 60, 64, 60, 64, 0, 80, 80, 71, 64, 71, 64, 71, 0, 80, 80, 71, 64, 71, 64, 71, 0, 0, 71, 71, 71, 71, 71, 71, 95, 80, 0, 0, 71, 71, 71, 71, 71, 71, 95};

const int tiempo[]={62500, 125000, 125000, 125000, 62500, 62500, 62500, 62500, 62500, 125000, 125000, 125000, 62500, 62500, 62500, 62500, 62500, 125000, 125000, 125000, 62500, 62500, 62500, 62500, 62500, 125000, 125000, 125000, 62500, 62500, 125000, 500000, 125000, 125000, 125000, 125000, 125000, 125000, 125000, 93750, 31250, 125000, 125000, 125000, 125000, 125000, 125000, 125000, 125000, 62500, 125000, 125000, 125000, 125000, 125000, 125000, 125000, 125000, 31250, 31250, 31250, 31250, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 93750, 31250, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 62500, 125000, 31250, 31250, 31250, 31250, 62500, 62500, 62500, 62500, 62500, 62500, 31250, 31250, 31250, 31250, 62500, 62500, 62500, 62500};

HW_Serial HW_SerialA;

//Ticker
Ticker Buzzer(Sound,10,0,MILLIS);
Ticker Line(Follow2, 80,0,MILLIS);
//Ticker Line2(Follow3, 80,0,MILLIS);
Ticker Lights(RGB,10,0,MILLIS);
Ticker Ultrasonico(Distancia, 500,0,MILLIS);
Ticker Matriz(Tira,100,0,MILLIS);
Ticker SensorIn(Infla,500,0,MILLIS);
TM1640 TM1640A; //display

ISR(TIMER2_COMPA_vect){
	Follow2();
}

//////Timer bluetooth
ISR(USART_RX_vect)
{
	HW_SerialA.ISR_RX_vect();
}
ISR(USART_TX_vect)
{
	HW_SerialA.ISR_TX_vect();
}
void setup() {
  // put your setup code here, to run once:
    mySerial.begin(9600);
    mySerial.listen();
	
	//Inicializar funciones Ticker
	Matriz.start();
	Ultrasonico.start();
	Buzzer.start();
	Lights.start();
	SensorIn.start();
	
	//Display Init
	TM1640A.clearDisplay();
	Matrix(Memoria, Mensaje);
	
	//CONFIGURACIÓN DE LOS MOTORES
	
	pinMode(8, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(6, OUTPUT);//Motor derecho
	pinMode(5, OUTPUT);//Motor izquierdo
	
	//CONFIGURACION DE EL SENSOR ULTRASONICO
	pinMode(3, OUTPUT); //trigger
	pinMode(4, INPUT); //ECHO SIGNAL
	pinMode(2, OUTPUT);
	
	
	//Seguidor de linea
	pinMode(2,OUTPUT);
	pinMode(11,INPUT);
	pinMode(12,INPUT);
	pinMode(11,LOW);
	pinMode(12,LOW);
	
	//Display
	pinMode(0,OUTPUT);
	

	//CONFIGURACIÓN SENSORES LATERALES
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(A2, LOW);
	pinMode(A3, LOW);
	
	//Inflarrojo 
	
	pinMode(13,INPUT);
	pinMode(13,LOW);
	
	//Cte timer prescalador
	pinMode(SW_RX, INPUT);
	pinMode(SW_Tx, OUTPUT);
	
	//Configurar timer2
	TCCR2A = (1<<WGM21);
	TCCR2B = (1<<CS22)|(1<<CS21)|(1<<CS20);
	OCR2A = 120;
	TIMSK2 = (1<<OCIE2A);
	
	//USART
	HW_SerialA.starUpSerial();
	
	sei();
	
	
}

void loop() {
  // put your main code here, to run repeatedly:
	 
	 Ultrasonico.update();
	 Matriz.update();
	 Line.update();
	 //Line2.update();
	 Lights.update();
	 SensorIn.update();
	 Buzzer.update();
	
	while(mySerial.available()>0) 
	{
		temp =  mySerial.read();
		buffer[i++] = temp;
		if(temp==0x0D){
			//Matrix(Memoria,buffer);
			i=0;
			Datos=1;
			break;			
		}
	}
		if(Datos)
		{
			mySerial.write(buffer[1]);
			if (buffer[1]=='0')
			{
				Matrix(Memoria,Mensaje6);
				mySerial.write(buffer[1]);
				RGB_Color=GREEN;
				TD3=1;
			}
			if (buffer[1]=='1')
			{
				mySerial.write(buffer[1]);
				TD3=0;
				
			}
			
			//Estacion A
			if (buffer[1]=='2')
			{
				Matrix(Memoria,Mensaje1);
				mySerial.write(buffer[1]);
				
			}
			//Estacion B
			if (buffer[1]=='3')
			{
				Matrix(Memoria,Mensaje2);
				mySerial.write(buffer[1]);
			}
			
			//Amarillo
			if (buffer[1]=='4')
			{
				Matrix(Memoria,Mensaje3);
				mySerial.write(buffer[1]);
			}
			//Azul
			if (buffer[1]=='5')
			{
				Matrix(Memoria,Mensaje4);
				mySerial.write(buffer[1]);
			}
			//Verde
			if (buffer[1]=='6')
			{
				Matrix(Memoria,Mensaje5);
				mySerial.write(buffer[1]);
			}
			Datos=0;
		}
}

//Funcion para el sensor ultrasonico y el calculo de la distancia
void Distancia(void){
	if(TD2||TD3) return;
	
	float duration, distance;
	digitalWrite(3,LOW);
	delayMicroseconds(100);
	digitalWrite(3,HIGH);
	delayMicroseconds(100);
	digitalWrite(3,LOW);
	
	//Calculo de la distancia
	duration = (float)(pulseIn(4,HIGH,12212));
	distance= duration*0.034/2;
	
	if (distance<30.0 &&distance>1.0)
	{
		sprintf(buffer,"D=%.3f\n",distance);
		Matrix(Memoria,buffer);
	}
	if(distance<10.0 && distance>1.0){
		analogWrite(6,0);
		analogWrite(5,0);
		TD=1;
		RGB_Color=RED;
	}
	
	else{
		
		TD=0;
		RGB_Color=BLUE;
		temp;
	}
	
}

//Funcion para la bocina del Qbot
void Sound(void){
	
	if (TD||TD2)
	{
	if ((PORTD&(1<<PIND2)))
	{
		digitalWrite(PIND2,LOW);
	}
	else{
		digitalWrite(PIND2,HIGH);
	
	}
	}
	else digitalWrite(PIND2,LOW);
	
	
}

//RGB
void Move(void){
	if (TD==0)
	{	
		DDRD |= (1<<PIND0);
		PORTD &=~(1<<PIND0);
		UCSR0B &=~((1<<RXEN0));
		if (incre)
		{
			RGB_BYTE(0);
			RGB_BYTE(0);
			RGB_BYTE(i_rgb);
			RGB_BYTE(0);
			RGB_BYTE(0);
			RGB_BYTE(i_rgb);
			i_rgb++;
			if (i_rgb==200)
			{
				incre =0;
			}
		}
		else{
			RGB_BYTE(0);
			RGB_BYTE(0);
			RGB_BYTE(i_rgb);
			RGB_BYTE(0);
			RGB_BYTE(0);
			RGB_BYTE(i_rgb);
			i_rgb--;
			
			if (i_rgb)
			{
				incre =1;
			}
		}
			DDRD &= ~(1<<PIND0);
			UCSR0B |=( (1 << RXEN0));// 
	}
	else{
		RGBrojo;
		}

}

//RGB rojo
void RGBrojo(void){
	DDRD |= (1<<PIND0);
	PORTD &=~(1<<PIND0);
	UCSR0B &=~( (1 << RXEN0));
	if (incre)
	{
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		i_rgb++;
		
		if (i_rgb==200)
		{
			incre=0;
		}
	}
	else{
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		i_rgb--;
		
		if (i_rgb==0)
		{
			incre=1;
		}
	}
	DDRD &= ~(1<<PIND0);
	UCSR0B |=( (1 << RXEN0));// | (1 << TXEN0));
}

//RGB verde
void RGBverde (void){
	DDRD |= (1<<PIND0);
	PORTD &=~(1<<PIND0);
	UCSR0B &=~( (1 << RXEN0));
	if (incre)
	{
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		i_rgb++;
		if (i_rgb==200)
		{
			incre=0;
		}
	}
	else{
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		i_rgb--;
		if (i_rgb==0)
		{
			incre=1;
		}
	}
	DDRD &= ~(1<<PIND0);
	UCSR0B |=( (1 << RXEN0));// | (1 << TXEN0));
	
}

//RGB azul
void RGBazul (void){
	DDRD |= (1<<PIND0);
	PORTD &=~(1<<PIND0);
	UCSR0B &=~( (1 << RXEN0));
	if (incre)
	{
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		i_rgb++;
		if (i_rgb==200)
		{
			incre=0;
		}
	}
	else{
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		i_rgb--;
		if (i_rgb==0)
		{
			incre=1;
		}
	}
	DDRD &= ~(1<<PIND0);
	UCSR0B |=( (1 << RXEN0));// | (1 << TXEN0));
	
}

//RGB naranja
void RGBnaranja(void){
	DDRD |= (1<<PIND0);
	PORTD &=~(1<<PIND0);
	UCSR0B &=~( (1 << RXEN0));
	if (incre)
	{
		RGB_BYTE(i_rgb);
		RGB_BYTE(128);
		RGB_BYTE(0);
		RGB_BYTE(i_rgb);
		RGB_BYTE(128);
		RGB_BYTE(0);
		i_rgb++;
		if (i_rgb==200)
		{
			incre=0;
		}
	}
	else{
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(0);
		RGB_BYTE(0);
		i_rgb--;
		if (i_rgb==0)
		{
			incre=1;
		}
	}
	DDRD &= ~(1<<PIND0);
	UCSR0B |=( (1 << RXEN0));// | (1 << TXEN0));
}

//Matriz de leds
void Tira(void){
	for (unsigned char a=0;a<16;a++)// NUMERO DE COLUMNAS EN LA MATRIZ Y DESPLAZAMIENTO
	{
		if(Memoria[b+a]==0x0D){
			b=0;
			d=0;
			break;
		}
		TM1640A.sendData(a, Memoria[b+a]);
	}
	b+=1;
}

//Seguidor de linea
void Follow2(void){
	if(TD||TD2||TD3) 
	{
		analogWrite (6, 0);
		analogWrite (5,0);
		return;
	}
	Infla();
	//Delante
	if(digitalRead(12)==1 && digitalRead(11)==1)
	{
		analogWrite(6,200);
		analogWrite(5,200);
		digitalWrite(7,LOW);
		digitalWrite(8,LOW);
		st++;
	}
	//Izquierda
	if (digitalRead(12)==0 && digitalRead(11)==1)
	{
		analogWrite(6,0);
		analogWrite(5,200);
		digitalWrite(7,LOW);
		digitalWrite(8,LOW);
		st++;
		
	}
	//Derecha
	if (digitalRead(12)==1 && digitalRead(11)==0)
	{
		analogWrite(6,200);
		analogWrite(5,0);
		digitalWrite(7,LOW);
		digitalWrite(8,LOW);
		st--;
	}
	//Excepcion
	if (digitalRead(12)==0 && digitalRead(11)==0)
	{
		analogWrite(6,200);
		analogWrite(5,30);
		digitalWrite(7,LOW);
		digitalWrite(8,LOW);
		st--;
		/*
		if (st==5)
		{
			analogWrite(6,100);
			analogWrite(5,100);
			digitalWrite(7,LOW);
			digitalWrite(8,LOW);
			st++;
		}
		*/
	}
	
	if (st==1)
	{
		analogWrite(6,0);
		analogWrite(5,200);
		digitalWrite(7,LOW);
		digitalWrite(8,LOW);
		st--;
	}
	
	if (st==3)
	{
		analogWrite(6,200);
		analogWrite(5,200);
		digitalWrite(7,LOW);
		digitalWrite(8,LOW);
		st--;
	}
	
	st=0;
}

//Sensores inflarrojos de los costados
void Infla(void){
	if(TD) return;
	if(TD3)return;
	
	if (digitalRead(A2)==0 || digitalRead(A3)==0)
	{
		analogWrite(6,0);
		analogWrite(5,0);
		TD2=1;
		RGB_Color=ORANGE;
		at++;
		
		if (at==1)
		{
			Matrix(Memoria,Mensaje1);
			mySerial.write(buffer[1]);
		}
		if (at==2)
		{
			Matrix(Memoria,Mensaje2);
			mySerial.write(buffer[1]);
			at=0;
		}
		return;
	}
	
	if (digitalRead(A2)==1 && digitalRead(A3)==1)
	{
		TD2=0;
		RGB_Color=BLUE;
		return;
	}
	at=0;
}

//Funcion para el RGB
void RGB(void)
{
	if (RGB_Color==NONE) return;
	DDRD |= (1<<PIND0);
	PORTD &=~(1<<PIND0);
	UCSR0B &=~( (1 << RXEN0));
	if(RGB_Color==GREEN) RGBverde();
	else if(RGB_Color==RED) RGBrojo();
	else if(RGB_Color==BLUE) RGBazul();
	else if(RGB_Color==ORANGE) RGBnaranja();
	DDRD &= ~(1<<PIND0);
	UCSR0B |=( (1 << RXEN0));// | (1 << TXEN0));
}

