# Robô Seguidor de Linha (ESP32-C3 + TB6612FNG + QTR-8A)

## 📌 Descrição
Este projeto implementa um **robô seguidor de linha branca** usando:
- ESP32-C3 Mini (microcontrolador)  
- TB6612FNG (driver de motores)  
- QTR-8A (sensor de refletância digital)  
- Dois motores DC com rodas  
- Power Bank 5V 5000mAh (alimentação)  

O robô segue uma **linha branca sobre fundo preto**.

---

## 🛠️ Componentes
- 1x ESP32-C3 Mini  
- 1x TB6612FNG (driver motor)  
- 1x QTR-8A (sensor digital de 8 canais)  
- 2x motores DC com rodas  
- 1x Power Bank 5V (5000mAh recomendado)  
- Jumpers e chassi para montagem  

---

## ⚡ Ligações Elétricas

### 🔋 Alimentação
- Power Bank (5V) → ESP32-C3 via USB  
- Power Bank (5V) → TB6612FNG (VM + VCC)  
- Power Bank (5V) → QTR-8A (VCC)  
- GND comum → ESP32-C3, TB6612FNG e QTR-8A  

### 🎛️ TB6612FNG ↔ ESP32-C3 Mini
| TB6612FNG | ESP32-C3 |
|-----------|----------|
| VM (motor VCC) | 5V (Power Bank) |
| VCC (lógica) | 3.3V |
| GND | GND |
| STBY | GPIO 10 |
| AIN1 | GPIO 6 |
| AIN2 | GPIO 7 |
| PWMA | GPIO 8 |
| BIN1 | GPIO 4 |
| BIN2 | GPIO 5 |
| PWMB | GPIO 9 |
| AO1, AO2 | Motor Esquerdo |
| BO1, BO2 | Motor Direito |

### 📡 QTR-8A (modo digital)
- VCC → 5V  
- GND → GND  
- IR → 5V (mantém LEDs infravermelhos sempre ligados)  
- D3 → GPIO 1  
- D4 → GPIO 2  
- D5 → GPIO 3  
- D6 → GPIO 18  
- D7 → GPIO 19  

*(usando 5 sensores centrais para leitura da linha)*

---

## 🖥️ Código
O código lê os sensores digitais (D3–D7).  
- Se a linha estiver centralizada, o robô anda para frente.  
- Se a linha estiver deslocada à esquerda/direita, o robô corrige ajustando a velocidade dos motores.  
- Se perder a linha, para.  

### Upload
1. Abra o **Arduino IDE**.  
2. Instale o **ESP32 Core** (caso não tenha).  
3. Selecione a placa **ESP32C3 Dev Module**.  
4. Carregue o código `main.ino` para o ESP32-C3.  

---

## 🚀 Como Usar
1. Monte o chassi do robô com o ESP32-C3, TB6612FNG, motores e sensor QTR-8A.  
2. Conecte o Power Bank ao ESP32-C3.  
3. Coloque o robô sobre uma pista com **linha branca sobre fundo preto**.  
4. Ligue o sistema e observe o robô seguir a linha.  

---

## 🔧 Ajustes
- `velocidadeBase` → controla a velocidade padrão (0–255).  
- Correção de curva → altere os valores de diferença entre as rodas (ex.: `+60`, `-60`).  
- Ordem dos sensores → se o robô inverter lados, troque os fios dos sensores (ex.: inverter D3↔D7).  

---

## 📷 Esquema Simplificado
```
Power Bank 5V → ESP32-C3 (USB)  
Power Bank 5V → TB6612FNG (VM, VCC)  
Power Bank 5V → QTR-8A (VCC, IR)  
GND comum em todos os módulos  

ESP32-C3 GPIO → TB6612FNG (controle motores)  
ESP32-C3 GPIO → QTR-8A D3..D7 (sensores digitais)  
```

---

## ✅ Resultado Esperado
O robô deve se mover para frente seguindo a **linha branca**.  
Se a linha curva para esquerda/direita, o robô ajusta os motores para se manter sobre a linha.  
Se perder a linha, ele para até reencontrá-la.
