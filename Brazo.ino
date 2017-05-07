#include <Servo.h>
// incluir BT

// Iniciales servo
const char BASE   = 'b';
const char CODO   = 'c';
const char MUNECA = 'm';
const char PINZA  = 'p';

// nombres y pins de los servos
const short PIN_BASE   = 13;
const short PIN_CODO   = 11;
const short PIN_MUNECA = 10;
const short PIN_PINZA  = 9;

// servos del brazo
Servo base, codo, muneca, pinza;


void setup() {
  // inicializar Bluetooth
  
  // inicializar servos
  base.attach(PIN_BASE);
  // codo.attach(PIN_CODO);
  // muneca.attach(PIN_MUNECA);
  // pinza.attach(PIN_PINZA);

}

void loop() {
  
  // - servidor de Bluetooth que procesa mensajes

}

/*
* El mensaje debe de tener el formato 'a:x', donde a es un caracter que corresponde a la inicial del servo y  
* x es un entero de 0 a 180.
*/
void procesarMensaje(String msg){
  char inicialServo = msg.charAt(0);
  int angulo = msg.substring(2).toInt();
  moverServo(inicialServo, angulo);
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
