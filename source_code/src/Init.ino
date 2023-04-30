//////////////////////////////////////////////////////////////////////
// Este fichero contendrá todos los procesos iniciales del programa //
// que se deberán ejecutar una sola vez al inicio del mismo.        //
//////////////////////////////////////////////////////////////////////

/**
* Función principal de inicialización de componentes.
*/
void init_all(){
  init_serial();
  delay(100);
  init_posiciones_actuales();
  init_posiciones_iniciales();
  delay(100);
  init_PCA9685_servos();
  delay(100);
  init_leds();
  delay(100);
  MPU9250_init();
  delay(100);
  init_WTV020SD16P();
  delay(100);
  pinMode(BATTERY_PIN, INPUT);
}

/**
* Inicialización del puerto Serial.
*/
void init_serial(){
  Serial.begin(9600);
  while (!Serial){}
}

/**
* Inicizaliza los servos conectados a la PCA9685
*/
void init_PCA9685_servos(){
  // Iniciar de la PCA9685 y establecer la frecuencia de funcionamiento.
  servoController.begin();
  servoController.setPWMFreq(330);
}

/**
* Inicialización de leds
*/
void init_leds(){
  pinMode(LED_DERECHO[0], OUTPUT);
  pinMode(LED_DERECHO[1], OUTPUT);
  pinMode(LED_DERECHO[2], OUTPUT);
  pinMode(LED_IZQUIERDO[0], OUTPUT);
  pinMode(LED_IZQUIERDO[1], OUTPUT);
  pinMode(LED_IZQUIERDO[2], OUTPUT);
}

/**
* Establece los valores para las posiciones iniciales de cada grupo de servos
*/
void init_posiciones_iniciales(){
  ///////////////////////////////////////////
  // Posiciones iniciales PIERNA IZQUIERDA //
  ///////////////////////////////////////////
  posicionesEstandarPiernaIzquierda[0] = 170;
  posicionesEstandarPiernaIzquierda[1] = 140;
  posicionesEstandarPiernaIzquierda[2] = 98;

  /////////////////////////////////////////
  // Posiciones iniciales PIERNA DERECHA //
  /////////////////////////////////////////
  posicionesEstandarPiernaDerecha[0] = 38;
  posicionesEstandarPiernaDerecha[1] = 130;
  posicionesEstandarPiernaDerecha[2] = 58;

  /////////////////////////////////
  // Posiciones iniciales CADERA //
  /////////////////////////////////
  posicionesEstandarCadera[0] = 45;
  posicionesEstandarCadera[1] = 93;
  posicionesEstandarCadera[2] = 173;

  //////////////////////////////////////////
  // Posiciones iniciales BRAZO IZQUIERDO //
  //////////////////////////////////////////
  posicionesEstandarBrazoIzquierdo[0] = 0;
  posicionesEstandarBrazoIzquierdo[1] = 180;
  posicionesEstandarBrazoIzquierdo[2] = 50;

  ////////////////////////////////////////
  // Posiciones iniciales BRAZO DERECHO //
  ////////////////////////////////////////
  posicionesEstandarBrazoDerecho[0] = 170;
  posicionesEstandarBrazoDerecho[1] = 10;
  posicionesEstandarBrazoDerecho[2] = 130;
}

void init_posiciones_actuales() {
  ///////////////////////////////////////////
  // Posiciones actuales PIERNA IZQUIERDA //
  ///////////////////////////////////////////
  posicionesActuales[pinsServosPiernaIzquierda[0]] = 180;
  posicionesActuales[pinsServosPiernaIzquierda[1]] = 80;
  posicionesActuales[pinsServosPiernaIzquierda[2]] = 115;

  /////////////////////////////////////////
  // Posiciones actuales PIERNA DERECHA //
  /////////////////////////////////////////
  posicionesActuales[pinsServosPiernaDerecha[0]] = 25;
  posicionesActuales[pinsServosPiernaDerecha[1]] = 190;
  posicionesActuales[pinsServosPiernaDerecha[2]] = 40;

  /////////////////////////////////
  // Posiciones actuales CADERA //
  /////////////////////////////////
  posicionesActuales[pinsServosCadera[0]] = 38;
  posicionesActuales[pinsServosCadera[1]] = 100;
  posicionesActuales[pinsServosCadera[2]] = 179;

  //////////////////////////////////////////
  // Posiciones actuales BRAZO IZQUIERDO //
  //////////////////////////////////////////
  posicionesActuales[pinsServosBrazoIzquierdo[0]] = 180;
  posicionesActuales[pinsServosBrazoIzquierdo[1]] = 180;
  posicionesActuales[pinsServosBrazoIzquierdo[2]] = 140;

  ////////////////////////////////////////
  // Posiciones actuales BRAZO DERECHO //
  ////////////////////////////////////////
  posicionesActuales[pinsServosBrazoDerecho[0]] = 0;
  posicionesActuales[pinsServosBrazoDerecho[1]] = 0;
  posicionesActuales[pinsServosBrazoDerecho[2]] = 35;
}


void init_WTV020SD16P(){
  wtv020sd16p.reset();
}
