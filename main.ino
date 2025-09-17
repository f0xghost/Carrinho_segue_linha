// Robô Segue Linha - ESP32-C3 + TB6612FNG + QTR-8A (digital, linha branca)

// Definições dos motores
#define AIN1 6
#define AIN2 7
#define PWMA 8
#define BIN1 4
#define BIN2 5
#define PWMB 9
#define STBY 10

// Sensores QTR-8A (digitais, 5 centrais)
int sensores[5] = {1, 2, 3, 18, 19};
int valores[5];

// Velocidade base
int velocidadeBase = 180; // 0-255

void setup() {
  Serial.begin(115200);

  // Configura motores
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // Ativa o driver

  // Configura sensores
  for (int i = 0; i < 5; i++) {
    pinMode(sensores[i], INPUT);
  }
}

void loop() {
  // Ler sensores
  for (int i = 0; i < 5; i++) {
    valores[i] = digitalRead(sensores[i]);
    Serial.print(valores[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Lógica para seguir linha branca (HIGH = linha, LOW = fundo preto)
  if (valores[2] == 1 && valores[1] == 0 && valores[3] == 0) {
    // Linha centralizada → frente
    moverMotor(velocidadeBase, velocidadeBase);
  } 
  else if (valores[0] == 1 || valores[1] == 1) {
    // Linha à esquerda
    moverMotor(velocidadeBase - 60, velocidadeBase + 60);
  } 
  else if (valores[3] == 1 || valores[4] == 1) {
    // Linha à direita
    moverMotor(velocidadeBase + 60, velocidadeBase - 60);
  } 
  else {
    // Linha perdida → parar
    moverMotor(0, 0);
  }

  delay(10);
}

// Controle dos motores
void moverMotor(int velEsq, int velDir) {
  // Motor esquerdo
  if (velEsq >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    velEsq = -velEsq;
  }
  analogWrite(PWMA, velEsq);

  // Motor direito
  if (velDir >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    velDir = -velDir;
  }
  analogWrite(PWMB, velDir);
}
