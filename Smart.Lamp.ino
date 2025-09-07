//Autores: Enzo Fernandes Ramos RM:563705, Felipe Cerazi RM:562746, Gustavo Peaguda RM:562923, Lorenzo Coque RM:563385
//Resumo: Esse programa possibilita ligar e desligar o led onboard, além de mandar o status para o Broker MQTT possibilitando o Helix saber
//se o led está ligado ou desligado.
#include <WiFi.h>                // Biblioteca para conexão Wi-Fi no ESP32
#include <PubSubClient.h>        // Biblioteca para conexão e uso do protocolo MQTT

// Configurações - variáveis editáveis
const char* default_SSID = "Wokwi-GUEST"; // Nome da rede Wi-Fi
const char* default_PASSWORD = ""; // Senha da rede Wi-Fi
const char* default_BROKER_MQTT = "102.37.18.193"; // IP do Broker MQTT
const int default_BROKER_PORT = 1883; // Porta do Broker MQTT
const char* default_TOPICO_SUBSCRIBE = "/TEF/lamp001/cmd"; // Tópico MQTT de escuta
const char* default_TOPICO_PUBLISH_1 = "/TEF/lamp001/attrs"; // Tópico MQTT de envio de informações para Broker
const char* default_TOPICO_PUBLISH_2 = "/TEF/lamp001/attrs/l"; // Tópico MQTT de envio de informações para Broker
const char* default_ID_MQTT = "fiware_001"; // ID MQTT
const int default_D4 = 2; // Pino do LED onboard
// Declaração da variável para o prefixo do tópico
const char* topicPrefix = "lamp001";

// Variáveis para configurações editáveis
char* SSID = const_cast<char*>(default_SSID); // SSID configurável
char* PASSWORD = const_cast<char*>(default_PASSWORD); // Senha configurável
char* BROKER_MQTT = const_cast<char*>(default_BROKER_MQTT); // Broker configurável
int BROKER_PORT = default_BROKER_PORT; // Porta do broker configurável
char* TOPICO_SUBSCRIBE = const_cast<char*>(default_TOPICO_SUBSCRIBE); // Tópico de escuta configurável
char* TOPICO_PUBLISH_1 = const_cast<char*>(default_TOPICO_PUBLISH_1); // Tópico de publicação 1
char* TOPICO_PUBLISH_2 = const_cast<char*>(default_TOPICO_PUBLISH_2); // Tópico de publicação 2
char* ID_MQTT = const_cast<char*>(default_ID_MQTT); // ID do cliente MQTT configurável
int D4 = default_D4; // Pino configurável para LED

WiFiClient espClient; // Objeto cliente Wi-Fi
PubSubClient MQTT(espClient); // Cliente MQTT baseado na conexão Wi-Fi
char EstadoSaida = '0'; // Estado inicial do LED (desligado)

// Inicializa comunicação serial
void initSerial() {
    Serial.begin(115200); // Define baud rate em 115200
}

// Inicializa Wi-Fi
void initWiFi() {
    delay(10); // Pequeno atraso antes de iniciar
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID); // Mostra SSID
    Serial.println("Aguarde");
    reconectWiFi(); // Chama função de reconexão Wi-Fi
}

// Inicializa configuração do MQTT
void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT); // Define servidor e porta do broker
    MQTT.setCallback(mqtt_callback); // Define função de callback quando recebe mensagem
}

// Função principal de configuração
void setup() {
    InitOutput(); // Inicializa LED
    initSerial(); // Inicializa comunicação serial
    initWiFi();   // Conecta ao Wi-Fi
    initMQTT();   // Configura cliente MQTT
    delay(5000);  // Espera 5 segundos
    MQTT.publish(TOPICO_PUBLISH_1, "s|on"); // Publica estado inicial no broker
}

// Loop principal do programa
void loop() {
    VerificaConexoesWiFIEMQTT(); // Verifica Wi-Fi e MQTT
    EnviaEstadoOutputMQTT();     // Envia estado do LED
    handleLuminosity();          // Lê e envia luminosidade
    MQTT.loop();                 // Mantém conexão MQTT ativa
}

// Reconecta ao Wi-Fi caso desconecte
void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED) // Se já estiver conectado, retorna
        return;
    WiFi.begin(SSID, PASSWORD); // Inicia conexão
    while (WiFi.status() != WL_CONNECTED) { // Aguarda conexão
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP()); // Mostra IP atribuído

    // Garantir que o LED inicie desligado
    digitalWrite(D4, LOW);
}

// Função callback chamada quando chega mensagem MQTT
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String msg; // Mensagem recebida
    for (int i = 0; i < length; i++) {
        char c = (char)payload[i]; // Converte byte em char
        msg += c; // Adiciona caractere à mensagem
    }
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);

    // Forma padrão para ligar/desligar LED
    String onTopic = String(topicPrefix) + "@on|";
    String offTopic = String(topicPrefix) + "@off|";

    // Liga LED se mensagem corresponder
    if (msg.equals(onTopic)) {
        digitalWrite(D4, HIGH);
        EstadoSaida = '1';
    }

    // Desliga LED se mensagem corresponder
    if (msg.equals(offTopic)) {
        digitalWrite(D4, LOW);
        EstadoSaida = '0';
    }
}

// Verifica conexões Wi-Fi e MQTT
void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected()) // Se MQTT desconectado
        reconnectMQTT();   // Reconecta MQTT
    reconectWiFi();        // Garante Wi-Fi conectado
}

// Publica estado do LED no broker
void EnviaEstadoOutputMQTT() {
    if (EstadoSaida == '1') {
        MQTT.publish(TOPICO_PUBLISH_1, "s|on"); // Publica ligado
        Serial.println("- Led Ligado");
    }

    if (EstadoSaida == '0') {
        MQTT.publish(TOPICO_PUBLISH_1, "s|off"); // Publica desligado
        Serial.println("- Led Desligado");
    }
    Serial.println("- Estado do LED onboard enviado ao broker!");
    delay(1000); // Espera 1s
}

// Inicializa pino do LED com piscada
void InitOutput() {
    pinMode(D4, OUTPUT); // Define pino como saída
    digitalWrite(D4, HIGH); // Acende LED
    boolean toggle = false; // Variável para alternância

    for (int i = 0; i <= 10; i++) { // Pisca LED 10 vezes
        toggle = !toggle;
        digitalWrite(D4, toggle);
        delay(200);
    }
}

// Reconecta ao broker MQTT
void reconnectMQTT() {
    while (!MQTT.connected()) { // Enquanto não conectado
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) { // Se conectar
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); // Inscreve no tópico
        } else {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Haverá nova tentativa de conexão em 2s");
            delay(2000); // Espera antes de tentar de novo
        }
    }
}

// Lê luminosidade e envia para broker
void handleLuminosity() {
    const int potPin = 34; // Pino analógico do sensor
    int sensorValue = analogRead(potPin); // Lê valor (0-4095)
    int luminosity = map(sensorValue, 0, 4095, 0, 100); // Converte para 0-100%
    String mensagem = String(luminosity); // Converte em string
    Serial.print("Valor da luminosidade: ");
    Serial.println(mensagem.c_str()); // Mostra no serial
    MQTT.publish(TOPICO_PUBLISH_2, mensagem.c_str()); // Publica no broker
}
