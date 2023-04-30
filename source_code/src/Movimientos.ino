///////////////////////////////////
// LISTA DE POSICIONES ESTÁTICAS //
///////////////////////////////////

void posicion_estandar() {
  // if (POSICION == POSICION_ESTANDAR)
  //   return;
  int tiempo = (POSICION == POSICION_ESTANDAR || POSICION == POSICION_AGACHADO) ? 1000 : 4000;
  POSICION = POSICION_ESTANDAR;
  POSICION_CADERA = POSICION_CADERA_CENTRADA;

  nipple_lights = false;
  const byte numServos = NUM_SERVOS_PIERNA_IZQUIERDA + NUM_SERVOS_PIERNA_DERECHA + NUM_SERVOS_CADERA /* + NUM_SERVOS_BRAZO_IZQUIERDO + NUM_SERVOS_BRAZO_DERECHO */;
  byte countServo = 0;
  short ajustesPosicionInicial[numServos][5];
  short servosPosicionInicial[numServos];

  for (int servo = 0; servo < NUM_SERVOS_PIERNA_IZQUIERDA; servo++) {
    int desfase = posicionesActuales[pinsServosPiernaIzquierda[servo]] - posicionesEstandarPiernaIzquierda[servo];

    servosPosicionInicial[countServo] = pinsServosPiernaIzquierda[servo];
    ajustesPosicionInicial[countServo][OFFSET] = posicionesActuales[pinsServosPiernaIzquierda[servo]];
    ajustesPosicionInicial[countServo][PERIODO] = tiempo;
    ajustesPosicionInicial[countServo][AMPLITUD] = abs(desfase);
    ajustesPosicionInicial[countServo][FASE] = desfase > 0 ? 180 : 0;
    ajustesPosicionInicial[countServo][DEFAULT] = 0;

    countServo++;
  }
  for (int servo = 0; servo < NUM_SERVOS_PIERNA_DERECHA; servo++) {
    int desfase = posicionesActuales[pinsServosPiernaDerecha[servo]] - posicionesEstandarPiernaDerecha[servo];

    servosPosicionInicial[countServo] = pinsServosPiernaDerecha[servo];
    ajustesPosicionInicial[countServo][OFFSET] = posicionesActuales[pinsServosPiernaDerecha[servo]];
    ajustesPosicionInicial[countServo][PERIODO] = tiempo;
    ajustesPosicionInicial[countServo][AMPLITUD] = abs(desfase);
    ajustesPosicionInicial[countServo][FASE] = desfase > 0 ? 180 : 0;
    ajustesPosicionInicial[countServo][DEFAULT] = 0;

    countServo++;
  }
  for (int servo = 0; servo < NUM_SERVOS_CADERA; servo++) {
    // if (servo != 1) {
      int desfase = posicionesActuales[pinsServosCadera[servo]] - posicionesEstandarCadera[servo];

      if (servo == 1) {
        int posicionCadera;
        switch (POSICION_CADERA) {
        case POSICION_CADERA_CENTRADA:
          posicionCadera = posicionesEstandarCadera[1];
          break;
        case POSICION_CADERA_DERECHA:
          posicionCadera = 180;
          break;
        case POSICION_CADERA_IZQUIERDA:
          posicionCadera = 0;
          break;
        }
        desfase = posicionesActuales[pinsServosCadera[servo]] - posicionCadera;
      }

      servosPosicionInicial[countServo] = pinsServosCadera[servo];
      ajustesPosicionInicial[countServo][OFFSET] = posicionesActuales[pinsServosCadera[servo]];
      ajustesPosicionInicial[countServo][PERIODO] = tiempo;
      ajustesPosicionInicial[countServo][AMPLITUD] = abs(desfase);
      ajustesPosicionInicial[countServo][FASE] = desfase > 0 ? 180 : 0;
      ajustesPosicionInicial[countServo][DEFAULT] = 0;

      countServo++;
    // }
  }
  /* for (int servo = 0; servo < NUM_SERVOS_BRAZO_IZQUIERDO; servo++) {
    int desfase = posicionesActuales[pinsServosBrazoIzquierdo[servo]] - posicionesEstandarBrazoIzquierdo[servo];

    servosPosicionInicial[countServo] = pinsServosBrazoIzquierdo[servo];
    ajustesPosicionInicial[countServo][OFFSET] = posicionesActuales[pinsServosBrazoIzquierdo[servo]];
    ajustesPosicionInicial[countServo][PERIODO] = tiempo;
    ajustesPosicionInicial[countServo][AMPLITUD] = abs(desfase);
    ajustesPosicionInicial[countServo][FASE] = desfase > 0 ? 180 : 0;
    ajustesPosicionInicial[countServo][DEFAULT] = 0;

    countServo++;
  }
  for (int servo = 0; servo < NUM_SERVOS_BRAZO_DERECHO; servo++) {
    int desfase = posicionesActuales[pinsServosBrazoDerecho[servo]] - posicionesEstandarBrazoDerecho[servo];

    servosPosicionInicial[countServo] = pinsServosBrazoDerecho[servo];
    ajustesPosicionInicial[countServo][OFFSET] = posicionesActuales[pinsServosBrazoDerecho[servo]];
    ajustesPosicionInicial[countServo][PERIODO] = tiempo;
    ajustesPosicionInicial[countServo][AMPLITUD] = abs(desfase);
    ajustesPosicionInicial[countServo][FASE] = desfase > 0 ? 180 : 0;
    ajustesPosicionInicial[countServo][DEFAULT] = 0;

    countServo++;
  } */

  ejecutar_movimiento(servosPosicionInicial, ajustesPosicionInicial, numServos, 0.25f);
}

void posicion_agachado() {
  // if (POSICION == POSICION_AGACHADO)
  //   return;
  POSICION = POSICION_AGACHADO;

  const byte numServos = 9;
  short ajustesAgacharse[numServos][5];
  short servosAgacharse[numServos];
  short posicionesObjetivo[numServos];

  servosAgacharse[0] = pinsServosPiernaDerecha[1];
  servosAgacharse[1] = pinsServosPiernaDerecha[2];
  servosAgacharse[2] = pinsServosPiernaIzquierda[1];
  servosAgacharse[3] = pinsServosPiernaIzquierda[2];
  servosAgacharse[4] = pinsServosCadera[0];
  servosAgacharse[5] = pinsServosCadera[2];
  servosAgacharse[6] = pinsServosPiernaIzquierda[0];
  servosAgacharse[7] = pinsServosPiernaDerecha[0];
  servosAgacharse[8] = pinsServosCadera[1];

  posicionesObjetivo[0] = 100;
  posicionesObjetivo[1] = 90;
  posicionesObjetivo[2] = 180;
  posicionesObjetivo[3] = 68;
  posicionesObjetivo[4] = 45;
  posicionesObjetivo[5] = 173;
  posicionesObjetivo[6] = 170;
  posicionesObjetivo[7] = 38;
  switch (POSICION_CADERA) {
  case POSICION_CADERA_CENTRADA:
    posicionesObjetivo[8] = posicionesEstandarCadera[1];
    break;
  case POSICION_CADERA_DERECHA:
    posicionesObjetivo[8] = 180;
    break;
  case POSICION_CADERA_IZQUIERDA:
    posicionesObjetivo[8] = 0;
    break;
  }

  for (int servo = 0; servo < numServos; servo++) {
    int desfase = posicionesActuales[servosAgacharse[servo]] - posicionesObjetivo[servo];

    ajustesAgacharse[servo][OFFSET] = posicionesActuales[servosAgacharse[servo]];
    ajustesAgacharse[servo][PERIODO] = 1000;
    ajustesAgacharse[servo][AMPLITUD] = abs(desfase);
    ajustesAgacharse[servo][FASE] = desfase > 0 ? 180 : 0;
    ajustesAgacharse[servo][DEFAULT] = 0;
  }
  ejecutar_movimiento(servosAgacharse, ajustesAgacharse, numServos, 0.25f);
}

void posicion_invencible() {
  // if (POSICION == POSICION_AGACHADO)
  //   return;
  POSICION = POSICION_INVENCIBLE;

  const byte numServos = 8;
  short ajustesAgacharse[numServos][5];
  short servosAgacharse[numServos];
  short posicionesObjetivo[numServos];

  servosAgacharse[0] = pinsServosPiernaDerecha[1];
  servosAgacharse[1] = pinsServosPiernaDerecha[2];
  servosAgacharse[2] = pinsServosPiernaIzquierda[1];
  servosAgacharse[3] = pinsServosPiernaIzquierda[2];
  servosAgacharse[4] = pinsServosCadera[0];
  servosAgacharse[5] = pinsServosCadera[2];
  servosAgacharse[6] = pinsServosPiernaIzquierda[0];
  servosAgacharse[7] = pinsServosPiernaDerecha[0];

  posicionesObjetivo[0] = 100;
  posicionesObjetivo[1] = 90;
  posicionesObjetivo[2] = 180;
  posicionesObjetivo[3] = 68;
  posicionesObjetivo[4] = 85;
  posicionesObjetivo[5] = 133;
  posicionesObjetivo[6] = 130;
  posicionesObjetivo[7] = 78;

  for (int servo = 0; servo < numServos; servo++) {
    int desfase = posicionesActuales[servosAgacharse[servo]] - posicionesObjetivo[servo];

    ajustesAgacharse[servo][OFFSET] = posicionesActuales[servosAgacharse[servo]];
    ajustesAgacharse[servo][PERIODO] = 2000;
    ajustesAgacharse[servo][AMPLITUD] = abs(desfase);
    ajustesAgacharse[servo][FASE] = desfase > 0 ? 180 : 0;
    ajustesAgacharse[servo][DEFAULT] = 0;
  }
  ejecutar_movimiento(servosAgacharse, ajustesAgacharse, numServos, 0.25f);
}

void posicion_SUUUPER() {
  if (POSICION != POSICION_ESTANDAR)
    return;
  posicion_estandar();
  POSICION = POSICION_SUUUPER;
  delay(1000);

  const byte numServos = 10;
  short ajustesSUPER[numServos][5];
  short servosSUPER[numServos];

  servosSUPER[0] = pinsServosPiernaDerecha[1];
  servosSUPER[1] = pinsServosPiernaDerecha[2];
  servosSUPER[2] = pinsServosCadera[0];
  servosSUPER[3] = pinsServosPiernaIzquierda[0];
  servosSUPER[4] = pinsServosBrazoIzquierdo[2];
  servosSUPER[5] = pinsServosBrazoDerecho[2];
  servosSUPER[6] = pinsServosBrazoDerecho[1];
  servosSUPER[7] = pinsServosBrazoIzquierdo[1];
  servosSUPER[8] = pinsServosBrazoIzquierdo[0];
  servosSUPER[9] = pinsServosBrazoDerecho[0];

  ajustesSUPER[0][OFFSET] = posicionesEstandarPiernaDerecha[1];
  ajustesSUPER[0][PERIODO] = 6000;
  ajustesSUPER[0][AMPLITUD] = 40;
  ajustesSUPER[0][FASE] = 180;
  ajustesSUPER[0][DEFAULT] = 0;

  ajustesSUPER[1][OFFSET] = posicionesEstandarPiernaDerecha[2];
  ajustesSUPER[1][PERIODO] = 6000;
  ajustesSUPER[1][AMPLITUD] = 40;
  ajustesSUPER[1][FASE] = 0;
  ajustesSUPER[1][DEFAULT] = 0;

  ajustesSUPER[2][OFFSET] = posicionesEstandarCadera[0];
  ajustesSUPER[2][PERIODO] = 6000;
  ajustesSUPER[2][AMPLITUD] = 60;
  ajustesSUPER[2][FASE] = 0;
  ajustesSUPER[2][DEFAULT] = 0;

  ajustesSUPER[3][OFFSET] = posicionesEstandarPiernaIzquierda[0];
  ajustesSUPER[3][PERIODO] = 6000;
  ajustesSUPER[3][AMPLITUD] = 60;
  ajustesSUPER[3][FASE] = 180;
  ajustesSUPER[3][DEFAULT] = 0;

  ajustesSUPER[4][OFFSET] = posicionesEstandarBrazoIzquierdo[2];
  ajustesSUPER[4][PERIODO] = 6000;
  ajustesSUPER[4][AMPLITUD] = 90;
  ajustesSUPER[4][FASE] = 0;
  ajustesSUPER[4][DEFAULT] = 0;

  ajustesSUPER[5][OFFSET] = posicionesEstandarBrazoDerecho[2];
  ajustesSUPER[5][PERIODO] = 6000;
  ajustesSUPER[5][AMPLITUD] = 93;
  ajustesSUPER[5][FASE] = 180;
  ajustesSUPER[5][DEFAULT] = 0;

  ajustesSUPER[6][OFFSET] = posicionesEstandarBrazoDerecho[1];
  ajustesSUPER[6][PERIODO] = 6000;
  ajustesSUPER[6][AMPLITUD] = 170;
  ajustesSUPER[6][FASE] = 0;
  ajustesSUPER[6][DEFAULT] = 0;

  ajustesSUPER[7][OFFSET] = posicionesEstandarBrazoIzquierdo[1];
  ajustesSUPER[7][PERIODO] = 6000;
  ajustesSUPER[7][AMPLITUD] = 190;
  ajustesSUPER[7][FASE] = 180;
  ajustesSUPER[7][DEFAULT] = 0;

  ajustesSUPER[8][OFFSET] = posicionesEstandarBrazoIzquierdo[0];
  ajustesSUPER[8][PERIODO] = 6000;
  ajustesSUPER[8][AMPLITUD] = 185;
  ajustesSUPER[8][FASE] = 0;
  ajustesSUPER[8][DEFAULT] = 0;

  ajustesSUPER[9][OFFSET] = posicionesEstandarBrazoDerecho[0];
  ajustesSUPER[9][PERIODO] = 6000;
  ajustesSUPER[9][AMPLITUD] = 185;
  ajustesSUPER[9][FASE] = 180;
  ajustesSUPER[9][DEFAULT] = 0;

  ejecutar_movimiento(servosSUPER, ajustesSUPER, numServos, 0.25f);
  wtv020sd16p.playVoice(0);
  delay(4500);
  wtv020sd16p.stopVoice();
  delay(150);
  nipple_lights = true;
}

void posicion_cadera() {
  const byte numServos = 1;
  short ajustesCadera[numServos][5];
  short servosCadera[numServos];
  short posicionesObjetivo[numServos];

  servosCadera[0] = pinsServosCadera[1];

  switch (POSICION_CADERA) {
  case POSICION_CADERA_CENTRADA:
    posicionesObjetivo[0] = posicionesEstandarCadera[1];
    break;
  case POSICION_CADERA_DERECHA:
    posicionesObjetivo[0] = 180;
    break;
  case POSICION_CADERA_IZQUIERDA:
    posicionesObjetivo[0] = 0;
    break;
  }

  int desfase = posicionesActuales[servosCadera[0]] - posicionesObjetivo[0];

  ajustesCadera[0][OFFSET] = posicionesActuales[servosCadera[0]];
  ajustesCadera[0][PERIODO] = 1000;
  ajustesCadera[0][AMPLITUD] = abs(desfase);
  ajustesCadera[0][FASE] = desfase > 0 ? 180 : 0;
  ajustesCadera[0][DEFAULT] = 0;

  ejecutar_movimiento(servosCadera, ajustesCadera, numServos, 0.25f);
}

void posicion_punos() {

  const byte numServos = 2;
  short ajustesPunos[numServos][5];
  short servosPunos[numServos];
  short posicionesObjetivo[numServos];

  servosPunos[0] = pinsServosBrazoIzquierdo[0];
  servosPunos[1] = pinsServosBrazoDerecho[0];

  switch (MODO_PUNOS) {
  case MODO_PUNOS_ARRIBA:
    posicionesEstandarBrazoIzquierdo[0] = 0;
    posicionesEstandarBrazoDerecho[0] = 170;
    break;
  case MODO_PUNOS_ABAJO:
    posicionesEstandarBrazoIzquierdo[0] = 170;
    posicionesEstandarBrazoDerecho[0] = 0;
    break;
  }

  posicionesObjetivo[0] = posicionesEstandarBrazoIzquierdo[0];
  posicionesObjetivo[1] = posicionesEstandarBrazoDerecho[0];

  for (int servo = 0; servo < numServos; servo++) {
    int desfase = posicionesActuales[servosPunos[servo]] - posicionesObjetivo[servo];

    ajustesPunos[servo][OFFSET] = posicionesActuales[servosPunos[servo]];
    ajustesPunos[servo][PERIODO] = 1000;
    ajustesPunos[servo][AMPLITUD] = abs(desfase);
    ajustesPunos[servo][FASE] = desfase > 0 ? 180 : 0;
    ajustesPunos[servo][DEFAULT] = 0;
  }

  ejecutar_movimiento(servosPunos, ajustesPunos, numServos, 0.25f);
}

void posicion_bolas() {
  const byte numServos = 2;
  short ajustesPunos[numServos][5];
  short servosPunos[numServos];
  short posicionesObjetivo[numServos];

  servosPunos[0] = pinsServosBrazoIzquierdo[2];
  servosPunos[1] = pinsServosBrazoDerecho[2];

  switch (MODO_BOLAS) {
  case MODO_BOLAS_ADELANTE:
    posicionesEstandarBrazoIzquierdo[2] = 50;
    posicionesEstandarBrazoDerecho[2] = 130;
    break;
  case MODO_BOLAS_ATRAS:
    posicionesEstandarBrazoIzquierdo[2] = 130;
    posicionesEstandarBrazoDerecho[2] = 50;
    break;
  }

  posicionesObjetivo[0] = posicionesEstandarBrazoIzquierdo[2];
  posicionesObjetivo[1] = posicionesEstandarBrazoDerecho[2];

  for (int servo = 0; servo < numServos; servo++) {
    int desfase = posicionesActuales[servosPunos[servo]] - posicionesObjetivo[servo];

    ajustesPunos[servo][OFFSET] = posicionesActuales[servosPunos[servo]];
    ajustesPunos[servo][PERIODO] = 1000;
    ajustesPunos[servo][AMPLITUD] = abs(desfase);
    ajustesPunos[servo][FASE] = desfase > 0 ? 180 : 0;
    ajustesPunos[servo][DEFAULT] = 0;
  }

  ejecutar_movimiento(servosPunos, ajustesPunos, numServos, 0.25f);
}

//////////////////////////
// LISTA DE MOVIMIENTOS //
//////////////////////////

void movimiento_StrongLeft() {
  const byte numServos = 2;
  short ajustesStrongLeft[numServos][5];
  short servosStrongLeft[numServos];
  servosStrongLeft[0] = pinsServosBrazoIzquierdo[0];
  servosStrongLeft[1] = pinsServosBrazoIzquierdo[1];

  ajustesStrongLeft[0][OFFSET] = posicionesEstandarBrazoIzquierdo[0];
  ajustesStrongLeft[0][PERIODO] = 800;
  ajustesStrongLeft[0][AMPLITUD] = 95;
  ajustesStrongLeft[0][FASE] = MODO_PUNOS == MODO_PUNOS_ARRIBA ? 0 : 180;
  ajustesStrongLeft[0][DEFAULT] = 0;

  ajustesStrongLeft[1][OFFSET] = posicionesEstandarBrazoIzquierdo[1];
  ajustesStrongLeft[1][PERIODO] = 800;
  ajustesStrongLeft[1][AMPLITUD] = 50;
  ajustesStrongLeft[1][FASE] = 180;
  ajustesStrongLeft[1][DEFAULT] = 0;

  ejecutar_movimiento(servosStrongLeft, ajustesStrongLeft, numServos, 0.5f);
}

void movimiento_StrongRight() {

  const byte numServos = 2;
  short ajustesStrongRight[numServos][5];
  short servosStrongRight[numServos];
  servosStrongRight[0] = pinsServosBrazoDerecho[0];
  servosStrongRight[1] = pinsServosBrazoDerecho[1];

  ajustesStrongRight[0][OFFSET] = posicionesEstandarBrazoDerecho[0];
  ajustesStrongRight[0][PERIODO] = 800;
  ajustesStrongRight[0][AMPLITUD] = 95;
  ajustesStrongRight[0][FASE] = MODO_PUNOS == MODO_PUNOS_ARRIBA ? 180 : 0;
  ajustesStrongRight[0][DEFAULT] = 0;

  ajustesStrongRight[1][OFFSET] = posicionesEstandarBrazoDerecho[1];
  ajustesStrongRight[1][PERIODO] = 800;
  ajustesStrongRight[1][AMPLITUD] = 50;
  ajustesStrongRight[1][FASE] = 0;
  ajustesStrongRight[1][DEFAULT] = 0;

  ejecutar_movimiento(servosStrongRight, ajustesStrongRight, numServos, 0.5f);
}

void movimiento_LateralDer(int repeticiones) {
  for (byte loops = 0; loops < repeticiones; loops++) {
    const byte numServosMovLatDer = 7;
    short ajustesMovLatDer[numServosMovLatDer][5];
    short servosMovLatDer[numServosMovLatDer];
    int periodo = 500;

    servosMovLatDer[0] = pinsServosPiernaIzquierda[1];
    servosMovLatDer[1] = pinsServosPiernaIzquierda[2];
    servosMovLatDer[2] = pinsServosCadera[2];
    servosMovLatDer[3] = pinsServosPiernaIzquierda[0];
    servosMovLatDer[4] = pinsServosPiernaDerecha[1];
    servosMovLatDer[5] = pinsServosPiernaDerecha[2];
    servosMovLatDer[6] = pinsServosCadera[0];

    ajustesMovLatDer[0][OFFSET] = posicionesActuales[servosMovLatDer[0]];
    ajustesMovLatDer[0][PERIODO] = periodo;
    ajustesMovLatDer[0][AMPLITUD] = 20;
    ajustesMovLatDer[0][FASE] = 180;
    ajustesMovLatDer[0][DEFAULT] = 1;

    ajustesMovLatDer[1][OFFSET] = posicionesActuales[servosMovLatDer[1]];
    ajustesMovLatDer[1][PERIODO] = periodo;
    ajustesMovLatDer[1][AMPLITUD] = 20;
    ajustesMovLatDer[1][FASE] = 0;
    ajustesMovLatDer[1][DEFAULT] = 1;

    ajustesMovLatDer[2][OFFSET] = posicionesActuales[servosMovLatDer[2]];
    ajustesMovLatDer[2][PERIODO] = periodo;
    ajustesMovLatDer[2][AMPLITUD] = 5;
    ajustesMovLatDer[2][FASE] = 180;
    ajustesMovLatDer[2][DEFAULT] = 1;

    ajustesMovLatDer[3][OFFSET] = posicionesActuales[servosMovLatDer[3]];
    ajustesMovLatDer[3][PERIODO] = periodo;
    ajustesMovLatDer[3][AMPLITUD] = 9;
    ajustesMovLatDer[3][FASE] = 180;
    ajustesMovLatDer[3][DEFAULT] = 1;

    ajustesMovLatDer[4][OFFSET] = posicionesActuales[servosMovLatDer[4]];
    ajustesMovLatDer[4][PERIODO] = periodo;
    ajustesMovLatDer[4][AMPLITUD] = 10;
    ajustesMovLatDer[4][FASE] = 180;
    ajustesMovLatDer[4][DEFAULT] = 1;

    ajustesMovLatDer[5][OFFSET] = posicionesActuales[servosMovLatDer[5]];
    ajustesMovLatDer[5][PERIODO] = periodo;
    ajustesMovLatDer[5][AMPLITUD] = 10;
    ajustesMovLatDer[5][FASE] = 0;
    ajustesMovLatDer[5][DEFAULT] = 1;

    ajustesMovLatDer[6][OFFSET] = posicionesActuales[servosMovLatDer[6]];
    ajustesMovLatDer[6][PERIODO] = periodo;
    ajustesMovLatDer[6][AMPLITUD] = 15;
    ajustesMovLatDer[6][FASE] = 0;
    ajustesMovLatDer[6][DEFAULT] = 1;

    ejecutar_movimiento(servosMovLatDer, ajustesMovLatDer, numServosMovLatDer, 0.5f);
    delay(50);
  }
}

void movimiento_LateralIzq(int repeticiones) {
  for (byte loops = 0; loops < repeticiones; loops++) {
    const byte numServosMovLatDer = 7;
    short ajustesMovLatDer[numServosMovLatDer][5];
    short servosMovLatDer[numServosMovLatDer];
    int periodo = 500;

    servosMovLatDer[0] = pinsServosPiernaDerecha[1];
    servosMovLatDer[1] = pinsServosPiernaDerecha[2];
    servosMovLatDer[2] = pinsServosCadera[0];
    servosMovLatDer[3] = pinsServosPiernaDerecha[0];
    servosMovLatDer[4] = pinsServosPiernaIzquierda[1];
    servosMovLatDer[5] = pinsServosPiernaIzquierda[2];
    servosMovLatDer[6] = pinsServosCadera[2];

    ajustesMovLatDer[0][OFFSET] = posicionesActuales[servosMovLatDer[0]];
    ajustesMovLatDer[0][PERIODO] = periodo;
    ajustesMovLatDer[0][AMPLITUD] = 20;
    ajustesMovLatDer[0][FASE] = 0;
    ajustesMovLatDer[0][DEFAULT] = 1;

    ajustesMovLatDer[1][OFFSET] = posicionesActuales[servosMovLatDer[1]];
    ajustesMovLatDer[1][PERIODO] = periodo;
    ajustesMovLatDer[1][AMPLITUD] = 20;
    ajustesMovLatDer[1][FASE] = 180;
    ajustesMovLatDer[1][DEFAULT] = 1;

    ajustesMovLatDer[2][OFFSET] = posicionesActuales[servosMovLatDer[2]];
    ajustesMovLatDer[2][PERIODO] = periodo;
    ajustesMovLatDer[2][AMPLITUD] = 5;
    ajustesMovLatDer[2][FASE] = 0;
    ajustesMovLatDer[2][DEFAULT] = 1;

    ajustesMovLatDer[3][OFFSET] = posicionesActuales[servosMovLatDer[3]];
    ajustesMovLatDer[3][PERIODO] = periodo;
    ajustesMovLatDer[3][AMPLITUD] = 9;
    ajustesMovLatDer[3][FASE] = 0;
    ajustesMovLatDer[3][DEFAULT] = 1;

    ajustesMovLatDer[4][OFFSET] = posicionesActuales[servosMovLatDer[4]];
    ajustesMovLatDer[4][PERIODO] = periodo;
    ajustesMovLatDer[4][AMPLITUD] = 10;
    ajustesMovLatDer[4][FASE] = 0;
    ajustesMovLatDer[4][DEFAULT] = 1;

    ajustesMovLatDer[5][OFFSET] = posicionesActuales[servosMovLatDer[5]];
    ajustesMovLatDer[5][PERIODO] = periodo;
    ajustesMovLatDer[5][AMPLITUD] = 10;
    ajustesMovLatDer[5][FASE] = 180;
    ajustesMovLatDer[5][DEFAULT] = 1;

    ajustesMovLatDer[6][OFFSET] = posicionesActuales[servosMovLatDer[6]];
    ajustesMovLatDer[6][PERIODO] = periodo;
    ajustesMovLatDer[6][AMPLITUD] = 15;
    ajustesMovLatDer[6][FASE] = 180;
    ajustesMovLatDer[6][DEFAULT] = 1;

    ejecutar_movimiento(servosMovLatDer, ajustesMovLatDer, numServosMovLatDer, 0.5f);
    delay(50);
  }
}

void movimiento_Sentadillas(int repeticiones) {
  if (!(POSICION == POSICION_ESTANDAR || POSICION == POSICION_AGACHADO))
    return;
  const byte numServos = 4;
  short ajustesAgacharse[numServos][5];
  short servosAgacharse[numServos];

  servosAgacharse[0] = pinsServosPiernaDerecha[1];
  servosAgacharse[1] = pinsServosPiernaDerecha[2];
  servosAgacharse[2] = pinsServosPiernaIzquierda[1];
  servosAgacharse[3] = pinsServosPiernaIzquierda[2];

  ajustesAgacharse[0][OFFSET] = posicionesActuales[servosAgacharse[0]];
  ajustesAgacharse[0][PERIODO] = 1000;
  ajustesAgacharse[0][AMPLITUD] = 35;
  ajustesAgacharse[0][FASE] = POSICION == POSICION_AGACHADO ? 270 : 180;
  ajustesAgacharse[0][DEFAULT] = 0;

  ajustesAgacharse[1][OFFSET] = posicionesActuales[servosAgacharse[1]];
  ajustesAgacharse[1][PERIODO] = 1000;
  ajustesAgacharse[1][AMPLITUD] = 35;
  ajustesAgacharse[1][FASE] = POSICION == POSICION_AGACHADO ? 90 : 0;
  ajustesAgacharse[1][DEFAULT] = 0;

  ajustesAgacharse[2][OFFSET] = posicionesActuales[servosAgacharse[2]];
  ajustesAgacharse[2][PERIODO] = 1000;
  ajustesAgacharse[2][AMPLITUD] = 35;
  ajustesAgacharse[2][FASE] = POSICION == POSICION_AGACHADO ? 90 : 0;
  ajustesAgacharse[2][DEFAULT] = 0;

  ajustesAgacharse[3][OFFSET] = posicionesActuales[servosAgacharse[3]];
  ajustesAgacharse[3][PERIODO] = 1000;
  ajustesAgacharse[3][AMPLITUD] = 35;
  ajustesAgacharse[3][FASE] = POSICION == POSICION_AGACHADO ? 270 : 180;
  ajustesAgacharse[3][DEFAULT] = 0;

  ejecutar_movimiento(servosAgacharse, ajustesAgacharse, numServos, repeticiones);
}

void movimiento_RotarIzq() {
  if (!(POSICION == POSICION_ESTANDAR || POSICION == POSICION_AGACHADO))
    return;
  const byte numServos = 5;
  short ajustesRotarIzq[numServos][5];
  short servosRotarIzq[numServos];

  servosRotarIzq[0] = pinsServosPiernaDerecha[1];
  servosRotarIzq[1] = pinsServosPiernaDerecha[2];
  servosRotarIzq[2] = pinsServosPiernaIzquierda[1];
  servosRotarIzq[3] = pinsServosPiernaIzquierda[2];
  servosRotarIzq[4] = pinsServosCadera[1];

  ajustesRotarIzq[0][OFFSET] = posicionesActuales[servosRotarIzq[0]];
  ajustesRotarIzq[0][PERIODO] = 750;
  ajustesRotarIzq[0][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarIzq[0][FASE] = 0;
  ajustesRotarIzq[0][DEFAULT] = 0;

  ajustesRotarIzq[1][OFFSET] = posicionesActuales[servosRotarIzq[1]];
  ajustesRotarIzq[1][PERIODO] = 750;
  ajustesRotarIzq[1][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarIzq[1][FASE] = 180;
  ajustesRotarIzq[1][DEFAULT] = 0;

  ajustesRotarIzq[2][OFFSET] = posicionesActuales[servosRotarIzq[2]];
  ajustesRotarIzq[2][PERIODO] = 750;
  ajustesRotarIzq[2][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarIzq[2][FASE] = 180;
  ajustesRotarIzq[2][DEFAULT] = 0;

  ajustesRotarIzq[3][OFFSET] = posicionesActuales[servosRotarIzq[3]];
  ajustesRotarIzq[3][PERIODO] = 750;
  ajustesRotarIzq[3][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarIzq[3][FASE] = 0;
  ajustesRotarIzq[3][DEFAULT] = 0;

  ajustesRotarIzq[4][OFFSET] = posicionesActuales[servosRotarIzq[4]];
  ajustesRotarIzq[4][PERIODO] = 750;
  ajustesRotarIzq[4][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 45 : 35;
  ajustesRotarIzq[4][FASE] = 0;
  ajustesRotarIzq[4][DEFAULT] = 0;

  ejecutar_movimiento(servosRotarIzq, ajustesRotarIzq, numServos, 0.25f);
  // delay(100);
  switch (POSICION) {
  case POSICION_ESTANDAR:
    posicion_estandar();
    break;
  case POSICION_AGACHADO:
    posicion_agachado();
    break;
  }
}

void movimiento_RotarDer() {
  if (!(POSICION == POSICION_ESTANDAR || POSICION == POSICION_AGACHADO))
    return;
  const byte numServos = 5;
  short ajustesRotarDer[numServos][5];
  short servosRotarDer[numServos];

  servosRotarDer[0] = pinsServosPiernaDerecha[1];
  servosRotarDer[1] = pinsServosPiernaDerecha[2];
  servosRotarDer[2] = pinsServosPiernaIzquierda[1];
  servosRotarDer[3] = pinsServosPiernaIzquierda[2];
  servosRotarDer[4] = pinsServosCadera[1];

  ajustesRotarDer[0][OFFSET] = posicionesActuales[servosRotarDer[0]];
  ajustesRotarDer[0][PERIODO] = 750;
  ajustesRotarDer[0][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarDer[0][FASE] = 0;
  ajustesRotarDer[0][DEFAULT] = 0;

  ajustesRotarDer[1][OFFSET] = posicionesActuales[servosRotarDer[1]];
  ajustesRotarDer[1][PERIODO] = 750;
  ajustesRotarDer[1][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarDer[1][FASE] = 180;
  ajustesRotarDer[1][DEFAULT] = 0;

  ajustesRotarDer[2][OFFSET] = posicionesActuales[servosRotarDer[2]];
  ajustesRotarDer[2][PERIODO] = 750;
  ajustesRotarDer[2][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarDer[2][FASE] = 180;
  ajustesRotarDer[2][DEFAULT] = 0;

  ajustesRotarDer[3][OFFSET] = posicionesActuales[servosRotarDer[3]];
  ajustesRotarDer[3][PERIODO] = 750;
  ajustesRotarDer[3][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 30 : 20;
  ajustesRotarDer[3][FASE] = 0;
  ajustesRotarDer[3][DEFAULT] = 0;

  ajustesRotarDer[4][OFFSET] = posicionesActuales[servosRotarDer[4]];
  ajustesRotarDer[4][PERIODO] = 750;
  ajustesRotarDer[4][AMPLITUD] = POSICION == POSICION_ESTANDAR ? 45 : 35;
  ajustesRotarDer[4][FASE] = 180;
  ajustesRotarDer[4][DEFAULT] = 0;

  ejecutar_movimiento(servosRotarDer, ajustesRotarDer, numServos, 0.25f);
  // delay(100);
  switch (POSICION) {
  case POSICION_ESTANDAR:
    posicion_estandar();
    break;
  case POSICION_AGACHADO:
    posicion_agachado();
    break;
  }
}