#include <LiquidCrystal.h>
//Pino analógico conectado ao divisor de tensão + valor dele
const int photoresistorPin = A0;
int photoresistorValue = 0;

//Pinos de I/O
const int buzzer = 6, red = 5, yellow = 4, green = 3, button = 2;

//Conexões do LCD
const int rs = 11, rw = 12, en = 13, d4 = 10, d5 = 9, d6 = 8, d7 = 7;

//Porcentagem da luminosidade
int lowValue; 
int mediumValue;

//Inicializa o objeto lcd.
LiquidCrystal  lcd(rs, rw, en, d4, d5, d6, d7);

//Contadores e Variaveis de Ambiente
int setupdone = 0;

//Função pra facilitar a mudança de cores do led
void changeColor(char color){
  switch (color){
  	case 'r':
    	digitalWrite(red, HIGH);
    	digitalWrite(yellow, LOW);
    	digitalWrite(green, LOW);
    	break;
    case 'y':
    	digitalWrite(red, LOW);
    	digitalWrite(yellow, HIGH);
    	digitalWrite(green, LOW);
    	break;
    case 'g':
    	digitalWrite(red, LOW);
    	digitalWrite(yellow, LOW);
    	digitalWrite(green, HIGH);
    	break;
  }
}



//Função que define o valor de brilho do ambiente
void defineValues(int analogValue){
  	mediumValue = (map(analogValue, 0, 1023, 0, 100))*0.9;
	lowValue = mediumValue/2;
}

//Função que faz a detecção da luz + luminosidade atual
void detectingLuminosity(){
	 //Lê o valor puro do fotoresistor em A0
  	int rawPhotoresistorValue = analogRead(photoresistorPin);
   	//Converte o valor puro do pino A0 com map -> (0 a 100%)
  	photoresistorValue = map(rawPhotoresistorValue, 0, 1023, 0, 100);
    
  	if(photoresistorValue < lowValue){
  		changeColor('g');
  	}else if(photoresistorValue >= lowValue && photoresistorValue <= mediumValue){
  		changeColor('y');
  	}else if(photoresistorValue > mediumValue){
    	changeColor('r');
          //pinOutput, Hz, Time
  		tone(buzzer, 440, 3000);
      	delay(3000);
  	}
}

//Função que mostra a % de luminosidade atual no LCD
void percentageShowActualLuminosity(int y, int value){
  	//Console 
  	Serial.print(photoresistorValue);
  	Serial.print("% de Luz\n");
  	//LCD
    lcd.setCursor(0, y);
  	lcd.print("Luz% ");
  	lcd.print("   ");
    lcd.setCursor(4, y);
  	lcd.print(value);
	delay(1000);
}

//Função que mostra a luminosidade que deve evitar no LCD
void percentageShowRedLuminosity(){
	    lcd.setCursor(9, 1);
        lcd.print("RED>");
        lcd.setCursor(13, 1);
        lcd.print(mediumValue);
        lcd.setCursor(15, 1);
        lcd.print("%");
}

void setup()
{
  	//Inicializa a comunicação serial a.k.a console
    Serial.begin(9600); 

    //buzzer
    pinMode(buzzer, OUTPUT);

    //leds
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
  
  	//botão
	pinMode(button, INPUT); 

    //Define X e Y disponiveis no LCD
    lcd.begin(16, 2);
	
  	//TODO-> LOGO (Animação)
    lcd.print("Agnello xD");
  	delay(5000);
    //lcd.setCursor(0,1); X e Y, sendo y = 0 primeira linha e y = 1 segunda
  	
  	//Aviso para definir a luminosidade do ambiente
  	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("LIGHT ON > THEN");
    lcd.setCursor(0,1);
  	lcd.print("PRESS BUTTON");
}

void loop()
{	
  	if(setupdone == 0){
      	if (digitalRead(button) == HIGH) {
            int value = analogRead(photoresistorPin);
			defineValues(value);
          	
          	lcd.clear();
          	lcd.setCursor(0, 0);
          	lcd.print("==--===++===--==");
          
            setupdone = 1;
            // Segurança pra não repetir a leitura
            while (digitalRead(button) == HIGH) {
              	delay(50);
        	}
        }
    }else{
   		percentageShowRedLuminosity();
        percentageShowActualLuminosity(1, photoresistorValue);
        detectingLuminosity();
    }
}
