const int pinEntrada = 2;
volatile unsigned long codigo = 0;
volatile bool recibido = false;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pinEntrada), recibir, CHANGE);
}

void loop() {
  if (recibido) {
    switch(codigo) {
      case 4278238976:
      Serial.println("Presionaste el boton: Prendido/Apagado");
      break;
      case 4261527296:
      Serial.println("Presionaste el boton: Vol+");
      break;
      case 4244815616:
      Serial.println("Presionaste el boton: Func/Stop");
      break;
      case 4211392256:
      Serial.println("Presionaste el boton: |<<");
      break;
      case 4194680576:
      Serial.println("Presionaste el boton: >||");
      break;
      case 4177968896:
      Serial.println("Presionaste el boton: >>|");
      break;
      case 4144545536:
      Serial.println("Presionaste el boton: Abajo");
      break;
      case 4127833856:
      Serial.println("Presionaste el boton: Vol-");
      break;
      case 4111122176:
      Serial.println("Presionaste el boton: Arriba");
      break;
      case 4060987136:
      Serial.println("Presionaste el boton: EQ");
      break;      
      case 4044275456:
      Serial.println("Presionaste el boton: ST/REPT");
      break;     
      case 4077698816:
      Serial.println("Presionaste el boton: 0");
      break;      
      case 4010852096:
      Serial.println("Presionaste el boton: 1");
      break;       
      case 3994140416:
      Serial.println("Presionaste el boton: 2");
      break;       
	    case 3977428736:
      Serial.println("Presionaste el boton: 3");
      break;      
      case 3944005376:
      Serial.println("Presionaste el boton: 4");
      break;
      case 3927293696:
      Serial.println("Presionaste el boton: 5");
      break;
	  case 3910582016:
      Serial.println("Presionaste el boton: 6");
      break;
      case 3877158656:
      Serial.println("Presionaste el boton: 7");
      break;
      case 3860446976:
      Serial.println("Presionaste el boton: 8");
      break;
      case 3843735296:
      Serial.println("Presionaste el boton: 9");
      break;
      
      default:
      Serial.println("No se pudo detectar correctamente el boton");
      break;
    }
    recibido = false;
  }
}

void recibir() {
  static unsigned long startTime = 0;
  static unsigned int contarBits = 0;

  if (digitalRead(pinEntrada) == HIGH) {
    startTime = micros();
  } else {
    unsigned long elapsedTime = micros() - startTime;
    if (elapsedTime > 2000) {
      contarBits = 0;
      codigo = 0;
    } else if (elapsedTime > 1000) {
      codigo |= (1UL << contarBits);
      contarBits++;
    } else {
      contarBits++;
    }

    if (contarBits == 32) {
      recibido = true;
    }
  }
}