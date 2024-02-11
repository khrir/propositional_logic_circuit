byte pin[] = {2, 3, 4, 5, 6, 7, 8}; // Array de pinos do Arduino

int number[10][7] = { // Matriz de numeros impressos no display
  // e, d, c, b, a, b, g 
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 1, 0, 0, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {1, 0, 0, 0, 0, 1, 0}, // 3
  {1, 1, 0, 0, 1, 0, 0}, // 4
  {1, 0, 0, 1, 0, 0, 0}, // 5
  {0, 0, 0, 1, 0, 0, 0}, // 6
  {1, 1, 0, 0, 0, 0, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {1, 1, 0, 0, 0, 0, 0}  // 9
};

#define BUTTON_1 9

const byte BUTTON_2 = 10;
const byte BUTTON_3 = 11;

const byte LED_RED_1 = 12;
const byte LED_RED_2 = 13;
const byte LED_GREEN = A1; 

int current_number = 0;

void setup() {
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_RED_2, OUTPUT);

  for (byte a = 0; a < 7; a++) {
    pinMode(pin[a], OUTPUT); // Define os pinos do display como de saída
  }
}

void loop() {
  int x = current_number;

  // Lê os botões
  bool button_2_state = digitalRead(BUTTON_2);
  bool button_3_state = digitalRead(BUTTON_3);

  digitalWrite(LED_RED_1, button_2_state);
  digitalWrite(LED_RED_2, button_3_state);

  // Incrementa o número atual quando o botão 1 é pressionado
  if (!digitalRead(BUTTON_1)) {
    current_number = (current_number + 1) % 10; // Garante que o número permaneça entre 0 e 9
    delay(200);
  }

  // Exibe o número atual
  for (int j = 0; j < 7; j++) {
    digitalWrite(pin[j], number[current_number][j]);
  }

  // Define o comportamento do LED verde com base no número atual
  switch (x) {
    case 1: // Implica
      digitalWrite(LED_GREEN, !button_2_state || button_3_state);
      break;
    case 2: // Bi-implica
      digitalWrite(LED_GREEN, (button_2_state == button_3_state));
      break;
    case 3: // NOT
      digitalWrite(LED_GREEN, (!button_2_state && !button_3_state));
      break;
    case 4: // AND
      digitalWrite(LED_GREEN, (button_2_state && button_3_state));
      break;
    case 5: // NAND
      digitalWrite(LED_GREEN, !(button_2_state && button_3_state));
      break;
    case 6: // OR
      digitalWrite(LED_GREEN, (button_2_state || button_3_state));
      break;
    case 7: // XOR
      digitalWrite(LED_GREEN, (button_2_state != button_3_state));
      break;
    case 8: // XNOR
      digitalWrite(LED_GREEN, (button_2_state == button_3_state));
      break;
    case 9: // NOR
      digitalWrite(LED_GREEN, !(button_2_state || button_3_state));
      break;
    default: // Caso x seja diferente de 1 a 9
      // Faz o LED piscar
      digitalWrite(LED_GREEN, HIGH);
      delay(200);
      digitalWrite(LED_GREEN, LOW);
      delay(200);
      break;
  }
}
