/////////////////////////////////////////////////////////////////////////////////////////
// Este fichero contendrá todas las funciones referentes a la comunicación mediante BT //
// con el mando y a la gestión de comandos.                                            //
/////////////////////////////////////////////////////////////////////////////////////////

/**
* Función que se debería llamar en tiempo de ejecución para comprobar si hay órdenes pendientes
* en el Buffer de comunicación Serial.
* Comprueba si la letra recibida está dentro de la lista de comandos aceptados del fichero Commands.h y
* efectua la operación pertinente.
*
* NOTE: Importante mantener sincronizado el fichero Commands.h en MiniFrankyBot y MiniFrankyBotController para
*       mantener la integridad de los movimientos.
*/
void update_tasks() {
  if (Serial.available()) {
    // Si hay algo pendiente en el Buffer, lo lee y guarda el tiempo en el que lo leyo.
    last_update = millis();
    byte readByte = Serial.read();

    if ((isDigit((char)readByte) || (char)readByte == '.' || (char)readByte == '-')) {
      // Si es un dígito, signo decimal o signo negativo, lo guarda como un valor.
      valor += (char)readByte;
    } else {
      if (letra != ' ') {
        // Si es una letra y ya hay otra letra ya leída, ejecuta la acción correspondiente a esa letra.
        execute_task(letra, (valor != "") ? valor.toInt() : 0);
      }
      // Llega una nueva letra; limpia el valor anterior y lee la nueva letra.
      valor = "";
      letra = (char)readByte;
    }
  } else if ((millis() - last_update) > 5 && letra != ' ') {
    // Si no se ha recibido nada en los últimos 5ms y hay alguna letra pendiente, ejecuta su acción correspondiente.
    execute_task(letra, (valor != "") ? valor.toInt() : 0);
    letra = ' ';
    valor = "";
  }
}

/**
* Ejecuta el comando enviado mediante BT
* @param comando Letra de la lista de comandos del fichero Comandos.h
* @param valor   Valor opcional que se usaría para realizar la acción
*/
void execute_task(char comando, int valor) {
  switch (comando) {
  case STRONG_RIGHT:
    movimiento_StrongRight();
    break;
  case STRONG_LEFT:
    movimiento_StrongLeft();
    break;
  case SUUUUUUPER:
    posicion_SUUUPER();
    break;
  case POS_INICIAL:
    posicion_estandar();
    break;
  case DESPL_IZQUIERDA:
    movimiento_LateralIzq(1);
    break;
  case DESPL_DERECHA:
    movimiento_LateralDer(1);
    break;
  case ROTATE_IZQUIERDA:
    movimiento_RotarIzq();
    break;
  case ROTATE_DERECHA:
    movimiento_RotarDer();
    break;
  case AGACHARSE:
    posicion_agachado();
    break;
  case INVINCIBLE_MOD:
    posicion_invencible();
    break;
  case POS_CADERA_D:
    POSICION_CADERA = POSICION_CADERA_DERECHA;
    posicion_cadera();
    break;
  case POS_CADERA_I:
    POSICION_CADERA = POSICION_CADERA_IZQUIERDA;
    posicion_cadera();
    break;
  case POS_CADERA_C:
    POSICION_CADERA = POSICION_CADERA_CENTRADA;
    posicion_cadera();
    break;
  case PUNOS_MOD:
    MODO_PUNOS = MODO_PUNOS == MODO_PUNOS_ARRIBA ? MODO_PUNOS_ABAJO : MODO_PUNOS_ARRIBA;
    posicion_punos();
    break;
  case BOLAS_MOD:
    MODO_BOLAS = MODO_BOLAS == MODO_BOLAS_ADELANTE ? MODO_BOLAS_ATRAS : MODO_BOLAS_ADELANTE;
    posicion_bolas();
    break;
  }
}
