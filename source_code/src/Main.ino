///////////////
// LIBRERÍAS //
///////////////
#include <Adafruit_PWMServoDriver.h>
#include <Comandos.h>
#include <MadgwickAHRS.h>
#include <Octosnake.h>
#include <Wire.h>
#include <Wtv020sd16p.h>
#include <Servo.h>

//////////////////
// PINES DE LEDS //
//////////////////
int LED_IZQUIERDO[] = {3, 5, 6};
int LED_DERECHO[] = {11, 10, 9};

/////////////////////////
// DEFINICIÓN DE SERVOS //
/////////////////////////
#define NUM_SERVOS_PIERNA_IZQUIERDA 3
#define NUM_SERVOS_PIERNA_DERECHA 3
#define NUM_SERVOS_CADERA 3
#define NUM_SERVOS_BRAZO_IZQUIERDO 3
#define NUM_SERVOS_BRAZO_DERECHO 3
// #define SERVOMIN 1011 // Ancho de pulso mínimo
// #define SERVOMAX 2820 // Ancho de pulso máximo
#define SERVOMIN 1100 // Ancho de pulso mínimo
#define SERVOMAX 2700 // Ancho de pulso máximo

////////////////////
// PINES DE SERVOS //
////////////////////
short pinsServosPiernaIzquierda[] = {11, 10, 9};
short pinsServosPiernaDerecha[] = {4,5,6};
short pinsServosCadera[] = {12, 7, 3};
short pinsServosBrazoIzquierdo[] = {13, 14, 15};
short pinsServosBrazoDerecho[] = {2, 1, 0};

////////////////////////
// INICIO DE LIBRERÍAS //
////////////////////////
Adafruit_PWMServoDriver servoController = Adafruit_PWMServoDriver();
Oscillator oscillatorPiernaIzquierda[NUM_SERVOS_PIERNA_IZQUIERDA];
Oscillator oscillatorPiernaDerecha[NUM_SERVOS_PIERNA_DERECHA];
Oscillator oscillatorCadera[NUM_SERVOS_CADERA];
Oscillator oscillatorBrazoIzquierdo[NUM_SERVOS_BRAZO_IZQUIERDO];
Oscillator oscillatorBrazoDerecho[NUM_SERVOS_BRAZO_DERECHO];

///////////////////////////////////
// ARRAYS DE POSICIONES INICIALES //
///////////////////////////////////
byte posicionesEstandarPiernaIzquierda[NUM_SERVOS_PIERNA_IZQUIERDA];
byte posicionesEstandarPiernaDerecha[NUM_SERVOS_PIERNA_DERECHA];
byte posicionesEstandarCadera[NUM_SERVOS_CADERA];
byte posicionesEstandarBrazoIzquierdo[NUM_SERVOS_BRAZO_IZQUIERDO];
byte posicionesEstandarBrazoDerecho[NUM_SERVOS_BRAZO_DERECHO];

///////////////////////////////////
// ARRAYS DE POSICIONES ACTUALES //
///////////////////////////////////
int posicionesActuales[16];

//////////////////////////////
// POSICIONES DE ARRAYS      //
// POSICIONES DE MOVIMIENTOS //
//////////////////////////////
#define OFFSET 0
#define PERIODO 1
#define AMPLITUD 2
#define FASE 3
#define DEFAULT 4


/////////////////////////
// LISTA DE POSICIONES //
/////////////////////////
#define POSICION_ESTANDAR 0
#define POSICION_AGACHADO 1
#define POSICION_INVENCIBLE 2
#define POSICION_SUUUPER 3
int POSICION = -1;

#define POSICION_CADERA_CENTRADA 0
#define POSICION_CADERA_DERECHA 1
#define POSICION_CADERA_IZQUIERDA 2
int POSICION_CADERA = 0;

#define MODO_PUNOS_ARRIBA 1
#define MODO_PUNOS_ABAJO 2
int MODO_PUNOS = 1;

#define MODO_BOLAS_ADELANTE 1
#define MODO_BOLAS_ATRAS 2
int MODO_BOLAS = 1;

/////////////////////
// VARIABLES PARA  //
// COMUNICACIÓN BT //
/////////////////////
long last_update;
char letra = ' ';
char letraAnterior = ' ';
String valor = "";
int repeticionesLetra = 1;

bool nipple_lights = false;
bool invencible = false;

#define BATTERY_PIN A0

int resetPin = 2; // The pin number of the reset pin.
int clockPin = 7; // The pin number of the clock pin.
int dataPin = 8;  // The pin number of the data pin.
int busyPin = 12; // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin, clockPin, dataPin, busyPin);

void setup() {
  Serial.begin(9600);
  init_all();
  setBatteryColor();
  // posicion_estandar();
  // delay(5000);
  // mov_SUUUUUPER();
  posicion_estandar();
  
}

void loop() {
  // setRainbowColor();
  update_tasks();
  // movimiento_LateralDer(1);
  // delay(1000);

  if(nipple_lights){
    setRGBColor(255,255,0);
    delay(85);
    setRGBColor(0,0,0);
    delay(85);
  }else{
    setRGBColor(0,0,0);
  }
}
