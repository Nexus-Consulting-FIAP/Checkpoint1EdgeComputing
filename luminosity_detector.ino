#include <LiquidCrystal.h>
//Pino analógico conectado ao divisor de tensão
const int photoresistorPin = A0;

//Pinos de I/O
const int buzzer = 6, red = 5, yellow = 4, green = 3;

//Conexões do LCD
const int rs = 11, rw = 12, en = 13, d4 = 10, d5 = 9, d6 = 8, d7 = 7;

//Porcentagem da luminosidade
const int lowValue = 30, mediumValue = 50;

//Inicializa o objeto lcd.
LiquidCrystal  lcd(rs, rw, en, d4, d5, d6, d7);

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

//Função que muda o valor da luminosidade no LCD
void percentageLuminosity(int y, int value){
    lcd.setCursor(0, y);
  	lcd.print("Luz% ");
    lcd.setCursor(4, y);
  	lcd.print(value);
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

    //Fala quantos X e Y disponiveis tem no LCD, nosso caso é 16x2
    lcd.begin(16, 2);
	
  	//TODO-> LOGO (Animação)
    lcd.print("Agnello xD");
    //lcd.setCursor(0,1); X e Y, sendo y = 0 primeira linha e y = 1 segunda
	
  	//Aviso sobre a tolerância da luminosidade
    lcd.setCursor(9, 1);
  	lcd.print("RED>");
    lcd.setCursor(13, 1);
  	lcd.print(mediumValue);
  	lcd.setCursor(15, 1);
  	lcd.print("%");
}

void loop()
{	
  	//Lê o valor puro do fotoresistor em A0
  	int rawPhotoresistorValue = analogRead(photoresistorPin);
   	//Converte o valor puro do pino A0 com map -> (0 a 100%)
  	int photoresistorValue = map(rawPhotoresistorValue, 0, 1023, 0, 100);
  	
  	//Console + LCD
  	Serial.print(photoresistorValue);
  	Serial.print("% de Luz\n");
  	percentageLuminosity(1, photoresistorValue);
	delay(1000);
    
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
