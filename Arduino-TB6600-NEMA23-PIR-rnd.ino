// definisanje pinova
const int belaLED = 13;
const int zelenaLED = 12;
const int crvenaLED = 11;
const int stepPin = 8; 
const int dirPin = 9; 
const int enPin = 1;
 
// ulaz senzora
int senzorPin = 7; 
 
// Detektovan pokret
int detektovanPokret = 0;
 
// vrednost senzora
int senzorVrednost; 

 
void setup() {

  // Bindovanje dioda na izlaze
  pinMode(belaLED, OUTPUT);
  pinMode(zelenaLED, OUTPUT);
  pinMode(crvenaLED, OUTPUT);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
  
  // Senzor na ulaz
  pinMode(senzorPin, INPUT);

  // 0 pin mora da bude prazan da bi uzimao shum za random
  randomSeed(analogRead(0));
 
  // 1 minut kalibrisanje senzora, ako to ima uopste ikakve veze :))
  digitalWrite(belaLED, LOW);
  digitalWrite(zelenaLED, LOW);
  digitalWrite(crvenaLED, HIGH);
  delay(60000);
  digitalWrite(zelenaLED, HIGH);
  digitalWrite(crvenaLED, LOW);
   
}

void motor(){
  
  int smer = random(2);
  int randomOkretaja = random(1, 9) * 200; // min 1 krug, max 9 kruga
  
  if (smer == 0) {
    digitalWrite(dirPin,HIGH);
  }else{
    digitalWrite(dirPin,LOW);
  }
   
  for(int korak = 0; korak < randomOkretaja; korak++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); // thanks to https://github.com/jumejume1 for MICROseconds, I was lost here using miliseconds :)
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
  delay(3000); 
}
 
void loop() {

  //detektovanje promena na senzoru
  senzorVrednost = digitalRead(senzorPin); 
  
  // test da li je nasao 
  if (senzorVrednost == 1){
    // Upali belu diodu na 3 sekunde
    digitalWrite(belaLED, HIGH);
    detektovanPokret = 1;
    motor();
  //    delay(3000);
  } else {
    digitalWrite(belaLED, LOW);
  }
  
  // Pauza posle aktiviranja senzora da bi se resetovao
  if (detektovanPokret == 1) {
    // Dozvoli ponovo da radi nakon 6 sekundi
    digitalWrite(belaLED, LOW);
    digitalWrite(zelenaLED, LOW);
    digitalWrite(crvenaLED, HIGH);
    delay(6000);
    digitalWrite(zelenaLED, HIGH);
    digitalWrite(crvenaLED, LOW);
    detektovanPokret = 0;
  }
 }
