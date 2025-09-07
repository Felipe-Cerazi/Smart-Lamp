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
5. O LED pode ser controlado remotamente pela nuvem, recebendo comandos, via PostMan.

---

## 🔥 Funcionalidades Diferenciais

- Controle remoto do LED via **MQTT** e FIWARE.
- Publicação periódica da luminosidade em **escala de 0 a 100**.
- Reconexão automática ao **Wi-Fi** e ao **Broker MQTT**.
- Simulação no **Wokwi** para prototipagem rápida e validação.
- Código totalmente comentado e modular para fácil manutenção.

---

## 📦 Componentes Utilizados

### 🛠️ Hardware
- 1x ESP32 DEVKIT 1
- 1x Sensor de Luminosidade (LDR)
- 1x LED onboard do ESP32


### 📚 Bibliotecas
- `WiFi.h` → Conexão Wi-Fi do ESP32
- `PubSubClient.h` → Cliente MQTT para envio e recepção de mensagens
---
## 🎬 Demonstração

### 📸 Simulação no Wokwi
🔗Clique <a href="https://wokwi.com/projects/441458700389768193"> aqui </a> para acessar a simulação no Wokwi.


### 📽️ Vídeo da implementação
🔗 Clique <a href="https://youtu.be/uq3vlq9WLEc"> aqui </a> para acessar o vídeo no Youtube.

---

## 🤝 Contribuições

Este projeto foi desenvolvido como parte de estudos em **IoT e Edge Computing**, aplicando conceitos de sensores, atuadores e comunicação entre dispositivos e nuvem.  


### 🌟 Destaques

- Comunicação bidirecional entre ESP32 e FIWARE  
- Controle remoto do LED de forma confiável  
- Registro contínuo de luminosidade  
- Código modular, comentado e pronto para extensão

---

## 📄 Licença

Este projeto é de uso **educacional e acadêmico**. Sinta-se livre para estudar, adaptar e se inspirar! ✨

---

> Desenvolvido com dedicação, criatividade e muitas horas de café por Enzo Ramos, Felipe Cerazi, Gustavo Peaguda e Lorenzo Coque 💻💡
