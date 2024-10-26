int ledred = 8;
int ledblue = 9;
int ledgreen = 10;

void setup(){
    pinMode(ledred, OUTPUT); //Configuração dos pinos como saída
    pinMode(ledgreen, OUTPUT);
    pinMode(ledblue, OUTPUT);
}

void loop(){
    digitalWrite(ledred, 0);
    digitalWrite(ledgreen, 1);
    digitalWrite(ledblue, 1);
    delay(1000);

    digitalWrite(ledred, 0);
    digitalWrite(ledgreen, 0);
    digitalWrite(ledblue, 1);
    delay(1000);

    digitalWrite(ledred, 1);
    digitalWrite(ledgreen, 0);
    digitalWrite(ledblue, 1);
    delay(1000);

    digitalWrite(ledred, 1);
    digitalWrite(ledgreen, 0);
    digitalWrite(ledblue, 0);
    delay(1000);

    digitalWrite(ledred, 1);
    digitalWrite(ledgreen, 1);
    digitalWrite(ledblue, 0);
    delay(1000);

    digitalWrite(ledred, 0);
    digitalWrite(ledgreen, 1);
    digitalWrite(ledblue, 0);
    delay(1000);
    
}
