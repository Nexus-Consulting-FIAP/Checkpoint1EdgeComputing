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

// Criando caracteres customizados
byte fullBlock[8] = {  // █
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte vazio[8] = { //
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte halfBlock[8] = {  // Bloco cheio na esquerda
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};
byte halfBlock2[8] = {  // Bloco cheio na esquerda
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011
};

byte diag[8] = {  // \ (diagonal do "N")
  B11000,
  B01100,
  B01100,
  B00110,
  B00110,
  B00011,
  B00011,
  B00001
};
byte halfDiagRight[8] = {  // Diagonal com bloco cheio na esquerda
  B11000,
  B11100,
  B11100,
  B11110,
  B11110,
  B11011,
  B11011,
  B11001
};
byte halfDiagLeft[8] = {  // Diagonal com bloco cheio na direita
  B11011,
  B01111,
  B01111,
  B00111,
  B00111,
  B00011,
  B00011,
  B00011
};

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
  	mediumValue = (map(analogValue, 0, 1023, 0, 100))*0.9; //Map = Regra de três que eu usei pra fazer de 1 a 100%
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

void drawFrame1() { // Animação -> Encher tela
  lcd.clear();
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 16; x++) {
      lcd.setCursor(x, y);
      lcd.write((uint8_t)0);
      delay(30);
    }
  }
}

void drawFrame2() {
  for (int x = 0; x <= 8; x++) { // Animação -> Desaparecer blocos e formar N
    if (x < 7) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)3);
      lcd.setCursor(x, 1); lcd.write((uint8_t)3);
      lcd.setCursor(15-x, 0); lcd.write((uint8_t)2);
      lcd.setCursor(15-x, 1); lcd.write((uint8_t)2);
      
      lcd.setCursor(x-1, 0); lcd.write((uint8_t)1);
      lcd.setCursor(x-1, 1); lcd.write((uint8_t)1);
      lcd.setCursor(16-x, 0); lcd.write((uint8_t)1);
      lcd.setCursor(16-x, 1); lcd.write((uint8_t)1);
    }
    if (x == 6) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)3);
      lcd.setCursor(x, 1); lcd.write((uint8_t)3);
    }
    if (x == 7) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)6);
      lcd.setCursor(x, 1); lcd.write((uint8_t)3);
      lcd.setCursor(15-x, 1); lcd.write((uint8_t)5);
      lcd.setCursor(15-x, 0); lcd.write((uint8_t)2);
    }
    if (x == 8) {
      lcd.setCursor(x, 0); lcd.write((uint8_t)1);
      lcd.setCursor(x, 1); lcd.write((uint8_t)4);
      lcd.setCursor(15-x, 1); lcd.write((uint8_t)1);
      lcd.setCursor(15-x, 0); lcd.write((uint8_t)4);
    }
    delay(75);
  }
}
void drawFrame3() { // Animação ->  Apagar com /
  for (int x = 0; x < 18; x++) {
    lcd.setCursor(15-x, 0); lcd.write((uint8_t)3);
    lcd.setCursor(15-x, 1); lcd.write((uint8_t)3);
    lcd.setCursor(16-x, 0); lcd.write((uint8_t)2);
    lcd.setCursor(16-x, 1); lcd.write((uint8_t)2);
    lcd.setCursor(17-x, 0); lcd.write((uint8_t)1);
    lcd.setCursor(17-x, 1); lcd.write((uint8_t)1);
    
    if (x == 6) {
      lcd.setCursor(15-x, 0); lcd.write((uint8_t)0);
      lcd.setCursor(15-x, 1); lcd.write((uint8_t)0);
    }
    if (x == 7) {
      lcd.setCursor(15-x, 1); lcd.write((uint8_t)6);
    }
    if (x == 8) {
      lcd.setCursor(15-x, 0); lcd.write((uint8_t)6);
    }
    delay(25);
  }
}


void setup()
{
  	//Inicializa a comunicação serial a.k.a console
    Serial.begin(9600); 

    //buzzer
    pinMode(buzzer, OUTPUT);

    //leds
    pinMode(red, OUTPUT); OUTPUT MANDA ENERGIA -> Arduino, manda energia pro LED pra ele liga
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
  
  	//botão
	pinMode(button, INPUT);  INPUT TE AVISA SOBRE ENERGIA-> Arduino, se o botão corta a energia, me avisa

    //Define X e Y disponiveis no LCD
    lcd.begin(16, 2);
	
  	//LOGO (Animação)
      lcd.begin(16, 2);
  
      lcd.createChar(0, fullBlock);
      lcd.createChar(1, vazio);
      lcd.createChar(2, halfBlock);
      lcd.createChar(3, halfBlock2);
      lcd.createChar(4, diag);
      lcd.createChar(5, halfDiagRight);
      lcd.createChar(6, halfDiagLeft);

      drawFrame1(); delay(500);
      drawFrame2(); delay(500);
      drawFrame3(); delay(500);
      delay(1500);
  	
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
   		percentageShowRedLuminosity(); //Mostra qual valor evitar, no caso, o RED
        percentageShowActualLuminosity(1, photoresistorValue); //Mostra a luz no LCD
        detectingLuminosity(); //Faz o fotorresistor funcionar, no caso, ver qual valor
    }
}
