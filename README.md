# Stroz_SPIN
# Czujnik ruchu PIR z powiadomieniami e-mail

Ten kod Arduino został zaprojektowany dla projektu opartego na ESP32, który wykorzystuje czujnik ruchu pasywnego podczerwieni (PIR) do wykrywania ruchu. Po wykryciu ruchu system wysyła powiadomienie e-mail na wcześniej zdefiniowany adres e-mail. Dodatkowo dostarcza interfejs internetowy umożliwiający dynamiczne ustawienie adresu e-mail do powiadomień.

## Użyte Komponenty
- ESP32 (NodeMCU lub podobny)
- Czujnik Ruchu PIR
- Rezystory i przewody według potrzeb

## Zależności
- [EMailSender](https://github.com/xreef/EMailSender)
- Biblioteka WiFi
- Biblioteka AsyncTCP
- Biblioteka ESPAsyncWebServer

## Instrukcje Konfiguracji

### 1. Połączenie
Upewnij się, że połączenia między komponentami są poprawne, w tym między czujnikiem ruchu PIR a ESP32. Dostosuj konfigurację pinów w kodzie, jeśli to konieczne.

### 2. Konfiguracja WiFi
Zaktualizuj zmienne `ssid` i `password` z odpowiednimi wartościami dla swojej sieci WiFi.

### 3. Konfiguracja E-mail
Zamień wartości zastępcze w poniższych linijkach na swoje dane logowania do e-maila:
```cpp
EMailSender emailSend("twój_email@gmail.com", "twoje_hasło_do_emaila");
```

### 4. Początkowa Konfiguracja E-mail
Dostosuj początkową wiadomość e-mail wysyłaną podczas konfiguracji, modyfikując zawartość `startMessage` w funkcji `setup`.

### 5. Interfejs WWW
Kod zawiera prostą stronę internetową dostępną pod adresem wysyłąnym na podany przez użytkownika mail. Użyj tego interfejsu do dynamicznego ustawiania adresu e-mail do powiadomień.

### 6. Dostosowanie Interfejsu HTML (Opcjonalne)
Jeśli chcesz, możesz dostosować interfejs HTML w stałej `index_html` do swoich preferencji.

### 7. Wgrywanie Kodu
Wgraj kod na swoje ESP32 za pomocą Arduino IDE lub innego preferowanego narzędzia.

## Instrukcje Interfejsu WWW
1. Połącz ESP32 z siecią.
2. Otwórz przeglądarkę internetową i przejdź pod sugerowany adres.
3. Wprowadź żądany adres e-mail w polu tekstowym i kliknij "Ustaw".
4. Ustawiony adres e-mail będzie wyświetlony na stronie internetowej.

## Uwagi
- Czujnik ruchu jest podłączony do pinu 19. Dostosuj zmienną `motion_sensor`, jeśli używasz innego pinu.
- System wprowadza opóźnienie 5 sekund między kolejnymi powiadomieniami o wykryciu ruchu, aby zapobiec nadmiernemu spamowi.

