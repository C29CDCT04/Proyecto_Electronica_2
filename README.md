# Proyecto_Electronica_2
#include <stdint.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

//Pines conectados al potenciometro
#define Pot1 A0
#define Pot2 A1

// Variables que guardan el valor de los potenciómetros
int Pot_1; 
int Pot_2;

// Servos
Servo S1; 
Servo S2; 

// Configuración de la pantalla LCD
#define I2C_ADDR    0x27
#define LCD_COLUMNS 16
#define LCD_LINES   2
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_LINES);

void setup() {
// Definición de entradas
  pinMode(Pot1,INPUT); 
  pinMode(Pot2,INPUT); 
// Conexión de pin para cada servo
  S1.attach(9);
  S2.attach(10);
  lcd.init(); 
  lcd.backlight(); 
}

void loop() {
  // Leer el valor de los potenciómetros
  Pot_1 = analogRead(Pot1);
  Pot_2 = analogRead(Pot2);
  // Se indica que los valores del servo sea de 0 a 180
  Pot_1 = map(Pot_1, 0, 1023, 0, 179);
  Pot_2 = map(Pot_2, 0, 1023, 0, 179);
  // Mostrar el valor de los potenciometros en la LCD
  lcd.setCursor(0,0); 
  lcd.print("S1: ")+lcd.print(Pot_1)+lcd.print(" ");
  //lcd.setCursor(8,0);
  lcd.print("S2: ")+lcd.print(Pot_2)+lcd.print("   ");

  S1.write(Pot_1);
  S2.write(Pot_2);
  delay(500);
}

