#include "GFButton.h" // Librería para manejar botones
#include <LiquidCrystal.h> // Librería para manejar pantallas LCD

// Definición de pines y variables para los LEDs y potenciómetros
int pot1 = 11;      // LED conectado al pin digital 11
int trans1 = A0;    // Potenciómetro conectado al pin analógico A0
int val1 = 0;       // Variable para almacenar el valor leído del potenciómetro 1
int pot2 = 12;      // LED conectado al pin digital 12
int trans2 = A1;    // Potenciómetro conectado al pin analógico A1
int val2 = 0;       // Variable para almacenar el valor leído del potenciómetro 2

// Inicialización del objeto LiquidCrystal para la pantalla LCD (pines RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Definición de pines para los botones
int pinBotonON = 8;
int pinBotonOFF = 9;

// Variables para manejar la entrada serial
String inputString = "";  // Cadena para almacenar la entrada serial
bool stringComplete = false;  // Bandera para indicar si la cadena de entrada está completa

// Inicialización de objetos GFButton para manejar los botones
GFButton boton1(pinBotonON);
GFButton boton2(pinBotonOFF);

void setup() {
  // Configuración de pines como salida
  pinMode(pot1, OUTPUT);
  pinMode(pot2, OUTPUT);

  // Reserva espacio en la cadena para la entrada serial
  inputString.reserve(200);

  // Configuración de pines de botones como entrada
  pinMode(pinBotonON, INPUT);
  pinMode(pinBotonOFF, INPUT);

  // Asignación de manejadores de pulsaciones a los botones
  boton1.setPressHandler(botonON_pulsado);
  boton2.setPressHandler(botonOFF_pulsado);

  // Inicialización de la comunicación serial
  Serial.begin(9600);

  // Inicialización de la pantalla LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Automatización");
  lcd.setCursor(0, 1);
  lcd.print("para todos");
  delay(2000); // Pausa para mostrar el mensaje inicial
}

void loop() {
  // Leer el valor del potenciómetro 1 y ajustar el LED 1
  val1 = analogRead(trans1);
  analogWrite(pot1, val1 / 4); // Convertir de 0-1023 a 0-255

  // Leer el valor del potenciómetro 2 y ajustar el LED 2
  val2 = analogRead(trans2);
  analogWrite(pot2, val2 / 4); // Convertir de 0-1023 a 0-255

  // Procesar el estado de los botones
  boton1.process();
  boton2.process();

  // Verificar si se ha recibido una cadena completa por el puerto serial
  if (stringComplete) {
    if (inputString == "L1ON_") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LED 1-> ON");
    } else if (inputString == "L1OFF_") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("LED 1-> OFF");
    }

    // Limpiar la cadena de entrada y restablecer la bandera
    inputString = "";
    stringComplete = false;
  }
}

// Función de manejador para el botón ON
void botonON_pulsado(GFButton &btn) {
  Serial.print("LED1ON_");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LED 1-> ON");
}

// Función de manejador para el botón OFF
void botonOFF_pulsado(GFButton &btn) {
  Serial.print("LED1OFF_");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LED 1-> OFF");
}

// Función que se llama cuando hay datos disponibles en el puerto serial
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); // Leer el carácter recibido
    inputString += inChar; // Añadir el carácter a la cadena de entrada
    if (inChar == "_") { // Verificar si la cadena de entrada está completa
      stringComplete = true; // Establecer la bandera a true
    }
  }
}
