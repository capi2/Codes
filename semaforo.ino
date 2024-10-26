int led1 = 10;
int led2 = 9;
int led3 = 8;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void piscar(int led){
  for(int i = 0; i < 5; i++){
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);  
  }
}

void loop() {
  digitalWrite(led1, HIGH);
  delay(3000);
  piscar(led1);
  digitalWrite(led2, HIGH);
  delay(3000);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(3000);
  digitalWrite(led3, LOW);
}
