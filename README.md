# 💡 Smart Lamp - Monitoramento e Controle via ESP32 e FIWARE

Bem-vindo ao repositório do projeto **Smart Lamp**, desenvolvido com **ESP32** para monitorar luminosidade e permitir o controle remoto do LED onboard, integrando dispositivos IoT à plataforma **FIWARE** para coleta e análise de dados em nuvem.

---

## 📌 Objetivo

Monitorar e controlar em tempo real:
- **Estado do LED onboard** (ligado/desligado).
- **Nível de luminosidade** ambiente via sensor LDR.

Enviar e processar os dados utilizando:
- **FIWARE** como plataforma de nuvem para armazenar e gerenciar os dados.
- **MQTT** para comunicação eficiente entre ESP32 e FIWARE.

Permitir controle remoto:
- **Ligar/desligar o LED onboard** via comandos MQTT.
- Visualizar e registrar o estado do LED e os níveis de luminosidade.

---

## ⚙️ Estrutura do Projeto

O sistema funciona da seguinte forma:

1. O ESP32 conecta-se à **rede Wi-Fi** e ao **Broker MQTT** configurado.
2. O LED onboard inicia desligado e pisca algumas vezes indicando inicialização.
3. O dispositivo lê continuamente o valor de luminosidade do sensor LDR.
4. Os dados de luminosidade são enviados para FIWARE via MQTT.
5. O LED pode ser controlado remotamente pela nuvem, recebendo comandos:
   - `"lamp001@on|"` → Liga o LED.
   - `"lamp001@off|"` → Desliga o LED.
6. Todas as operações são registradas no **Serial Monitor** para acompanhamento.

---

## 🔥 Funcionalidades Diferenciais

- Controle remoto do LED via **MQTT** e FIWARE.
- Publicação periódica da luminosidade em **escala de 0 a 100%**.
- Reconexão automática ao **Wi-Fi** e ao **Broker MQTT**.
- Simulação no **Wokwi** para prototipagem rápida e validação.
- Código totalmente comentado e modular para fácil manutenção.

---

## 📦 Componentes Utilizados

### 🛠️ Hardware:
- 1x ESP32 DEVKIT 1
- 1x Sensor de Luminosidade (LDR)
- 1x LED onboard do ESP32
- Protoboard e jumpers para testes físicos

### 📚 Bibliotecas:
- `WiFi.h` → Conexão Wi-Fi do ESP32
- `PubSubClient.h` → Cliente MQTT para envio e recepção de mensagens

---

## 🚀 Como Executar

1. Clone ou baixe este repositório.
2. Abra o arquivo `smart_lamp.ino` na IDE do Arduino.
3. Configure os parâmetros de Wi-Fi e MQTT/FIWARE no código:

```cpp
const char* SSID = "SeuWiFi";
const char* PASSWORD = "SuaSenha";
const char* BROKER_MQTT = "IP_DO_BROKER";
