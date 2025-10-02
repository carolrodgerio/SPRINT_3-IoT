# 🏍️🚦 Challenge FIAP - Sprint 3
## Disruptive Architectures: IoT, IOB & Generative IA

---

## 📖 Descrição

Projeto de IoT que permite monitorar o **status e a localização de motocicletas nos pátios da Mottu** _(empresa de locação de motos)_, utilizando um microcontrolador **ESP32** com sensores e comunicação via **HTTP**. Os dados são enviados para o **Node-RED**, que processa e exibe as informações em um **dashboard interativo**.

---

## 🎯 Funcionalidades

- 🔍 Identificação de motocicletas por checkpoint
- 📡 Envio de dados via **HTTP POST**
- 🖥️ Visualização em tempo real no dashboard:
  - ✔️ ID da moto
  - ✔️ Status
  - ✔️ Localização
  - ✔️ Horário da última detecção
- 🌧️ Detecção de condições climáticas adversas
- 🔔 Notificações visuais no painel (Dashboard Node-RED)

---

## 🛠️ Tecnologias e Ferramentas

- ESP32 (microcontrolador)
- Simulador Wokwi
- Node-RED
- Node-RED Dashboard
- Protocolo HTTP (REST)
- JSON (formato dos dados)

---

## 🏗️ Arquitetura da Solução

```plaintext
+------------+       HTTP POST       +------------+       Visualização
|   ESP32    |  ------------------>  |  Node-RED  |  ------------------>
| (Sensor)   |                       |  Dashboard |       (Web UI)
+------------+                        +------------+
```
---

## 🔌 Requisitos

✅ Node-RED instalado na máquina (https://nodered.org/docs/getting-started/)

✅ Paleta node-red-dashboard instalada no Node-RED (http://xxx.xxx.xx.x:1880/ui | atualizar com IP da máquina)

✅ Rede Wi-Fi local (ESP32 físico precisa estar na mesma rede que o Node-RED)

✅ Acesso ao Wokwi (https://wokwi.com) para simulação do ESP32 (somente para testes locais, sem integração real com Node-RED)

---

## 🎥 Pitch - Demonstração

[https://youtu.be/qU4wdBXmzxE](https://youtu.be/ODlGk797dhA)
