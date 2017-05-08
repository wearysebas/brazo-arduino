#include <Servo.h>
#include <SoftwareSerial.h>

// Pines de transmisión (TX) y recepción (RX) del módulo de Bluetooth
const byte PIN_BT_TX = 11;
const byte PIN_BT_RX = 10;


// Iniciales servo
const char BASE   = 'b';
const char CODO   = 'c';
const char MUNECA = 'm';
const char PINZA  = 'p';

// nombres y pins de los servos
const byte PIN_BASE   = 13;
const byte PIN_CODO   = 11;
const byte PIN_MUNECA = 10;
const byte PIN_PINZA  = 9;

const byte CERO  = 48;
const byte NUEVE = 57;




// Bluetooth
SoftwareSerial bt(PIN_BT_RX, PIN_BT_TX);
// servos del brazo
Servo base, codo, muneca, pinza;


void setup() {

  pinMode(PIN_BT_RX, INPUT);
  pinMode(PIN_BT_TX, OUTPUT);
  
  // inicializar Bluetooth
  bt.begin(9600);

  // inicializar servos
  base.attach(PIN_BASE);
  // codo.attach(PIN_CODO);
  // muneca.attach(PIN_MUNECA);
  // pinza.attach(PIN_PINZA);

}

void loop() {
  servidorBT();
  delay(500);
}

/*
* El mensaje debe de tener el formato 'ax', donde a es un caracter que corresponde a la inicial del servo y  
* x es un entero de 0 a 180.
*/
void servidorBT() {
  char inicialServo;
  int angulo;
  
  inicialServo = leerInicial();
  if(inicialServo == 0){
    // no leyó la inicial, bye.
    return;
  } else {
    angulo = leerAngulo();
    if(angulo >= 0){
      moverServo(inicialServo, angulo);
    } else {
      // error con el ángulo, bye.
      return;
    }
  }
}

/*
* Lee un caracter del serial (Bluetooth).
* 
* Regresa el caracter leído si es una incial correspondiente a un servo. De lo contrario,
* regresa el carcter nulo (0).
*/
char leerInicial() {
  char charLeido = bt.read();
  switch(charLeido){
    case BASE:
    case CODO:
    case MUNECA:
    case PINZA:
      return charLeido;
  }
  return 0;
}

/*
* Lee caracteres del serial buscando el ángulo.
*
* Regresa un entero entre 0 y 180 si leyó del sereal el ángulo, de lo contrario regresa -1.
*
*/
int leerAngulo() {
  int angulo;
  String strAngulo = "";
  char charLeido;
  for(int c = 0; c <= 4; c++) {
    charLeido = bt.read();
    if(charLeido >= CERO || charLeido <= NUEVE ) {
      strAngulo += charLeido;
    } else if (charLeido == 0){
      break;
    } else {
      break;
    }
  }
  if(strAngulo.length() == 0){
    return -1;
  } else {
    angulo = strAngulo.toInt();
    if(angulo >= 0 && angulo <= 180) {
      return angulo;
    } else {
      return -1;
    }
  }
}


void moverServo(char inicialServo, int angulo) {
  Servo servo = escogerServo(inicialServo);
  servo.write(angulo);
}

Servo escogerServo(char inicialServo) {
  Servo servo;
  switch(inicialServo){
    case BASE:
      servo = base;
      break;
    case CODO:
      servo = codo;
      break;
    case MUNECA:
      servo = muneca;
      break;
    case PINZA:
      servo = pinza;
      break;    
  }
  return servo;
}

