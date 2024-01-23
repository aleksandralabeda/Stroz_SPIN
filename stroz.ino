#include "Arduino.h"
#include <EMailSender.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

int motion_sensor = 19;
const char* ssid = "dlink-C340";
const char* password = "jpfkp94347";

// Replace with your e-mail address
String address = "labeda.ola@gmail.com";

const char* PARAM_INPUT = "value";

EMailSender emailSend("espczujnik@gmail.com", "xxdj ehad nezs ogbb");

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pl">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      margin: 0;
    font-family: "Lucida Console", monospace;
      background: linear-gradient(to right, #09203F, #537895);
    }

    .window {
      width: 300px;
      padding: 20px;
      background-color: #f1f1f1;
      border: 1px solid #ccc;
      border-radius: 8px;
      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
    }
  
  #submitButton {
      width: 300px;
      padding: 10px;
      background: linear-gradient(to right, #e67e22, #d35400);
    margin-bottom: 25px;
      color: white;
      border: none;
      border-radius: 4px;
      cursor: pointer;
    font-family: "Lucida Console", "Courier New", monospace;
    }

    #textInput {
      width: 300px;
      padding: 10px;
      margin-bottom: 10px;
    margin-top: 10px;
      box-sizing: border-box;
    font-family: "Lucida Console", "Courier New", monospace;
    }

    #submitButton:hover {
      background: linear-gradient(to right, #d35400, #803401);
    }
  
  p {
    font-size: 14px;
  }
  </style>
  <title>Ustawianie adresu e-mail</title>
</head>
<body>
  <div class="window">
      <label for="textInput">Wpisz adres e-mail:</label>
      <input type="text" id="textInput" placeholder="Twój adres e-mail">
      <button id="submitButton" onclick="setAddress()">Ustaw</button>
    <label>Ustawiony adres e-mail:</label>
    <p id="displayArea">%ADDRESS%</p>
  </div>
  <script>
        function setAddress() {
            var newAddress = document.getElementById("textInput").value;
            if(newAddress != "") {
        document.getElementById("displayArea").innerText = newAddress;
        console.log(newAddress);
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/set?value=" + newAddress, true);
        xhr.send();
      }
        }
    </script>
</body>
</html>
)rawliteral";

String processor(const String& var){
  //Serial.println(var);
  if (var == "ADDRESS"){
    return address;
  }
  return String();
}

void setup(){
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Łączenie z siecią WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());
  EMailSender::EMailMessage startMessage;
  startMessage.subject = "[Czujnik ESP] Adres do rejestracji";
  startMessage.message = "Lokalny adres do zmiany adresu e-mail to: " + WiFi.localIP().toString();
  emailSend.send(address, startMessage);
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/set?value=<inputMessage>
  server.on("/set", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/set?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      address = inputMessage;
      
      EMailSender::EMailMessage message;
      message.subject = "[Czujnik ESP] Rejestracja";
      message.message = "Zmiana adresu e-mail się powiodła.";
      
      EMailSender::Response resp = emailSend.send(address, message);
    }
    else {
      inputMessage = "Adres nie został przesłany";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}
  
void loop() {
  
    int motionStatus = digitalRead(motion_sensor);
    if (motionStatus == HIGH) {
        EMailSender::EMailMessage message;
        message.subject = "[Czujnik ESP] Wykryto ruch!";
        message.message = "Ruch został wykryty przy wyjściu z mieszkania.";
        EMailSender::Response resp = emailSend.send(address, message);
        Serial.println("Status wysyłania: ");
        Serial.println(resp.status);
        Serial.println(resp.code);
        Serial.println(resp.desc);

        // Wait for some time to avoid continuous notifications for the same motion event
        delay(5000);
    }

    // Add other logic or delay if needed
    delay(100);
}