
// Recebe o byte de entrada

int byte_entrada = 0; 

// Usando na verificação do sinal recebido

int valor; 

// Configuração dos pinos dos leds 

const int led_mizinho = 2;
const int led_si = 3;
const int led_sol = 4;
const int led_re = 5;
const int led_la = 6;
const int led_mizao = 7;

// Interruptor de depuração 

int opc_debug = false; 

// Caso verdadeiro para testar os leds antes de usá-los

int cond_led = true; 

// Armazena o valor recebido do código em Python

int sinal = 0; 

void setup(){
  
  // Usa a mesma taxa de transmissão do Python
  Serial.begin(115200); 

  if (cond_led == true) {
    
    // Testa os leds
    teste_leds();

  }
}

void loop() {
  
  if(opc_debug == true){
    debug();
  }else{
    Serial.println("Erro no debug!");
  }

  if(Serial.available() > 0) {
    byte_entrada = Serial.read(); 
    sinal = byte_entrada ;
    Serial.print("Eu recebi: ");
    Serial.println(byte_entrada);
  }

  // Realiza a animação dos leds
  
  classificador();
  
}

void debug() {
  
  Serial.print("Valor do Som: ");
  
  if (sinal >= valor) {
    Serial.print(sinal);
    Serial.println(" Led Ligado!");
    
  }else{
    Serial.println(sinal);
  }
}

void teste_leds(){
  
  digitalWrite(led_mizinho, HIGH);
  delay(1000);
  digitalWrite(led_si, HIGH);
  delay(1000); 
  digitalWrite(led_sol, HIGH);
  delay(1000);
  digitalWrite(led_re, HIGH);
  delay(1000);
  digitalWrite(led_la, HIGH);
  delay(1000);
  digitalWrite(led_mizao, HIGH);
  delay(1000);
  
}

void classificador(){
  
  if(sinal == 0){
    digitalWrite(led_mizinho, LOW);
    digitalWrite(led_si, LOW);
    digitalWrite(led_sol, LOW);
    digitalWrite(led_re, LOW);
    digitalWrite(led_la, LOW);
    digitalWrite(led_mizao, LOW);

  }else if(sinal == 1){
    digitalWrite(led_mizinho, HIGH);
    delay(300); 
    digitalWrite(led_si, LOW);
    digitalWrite(led_sol, LOW);
    digitalWrite(led_re, LOW);
    digitalWrite(led_la, LOW);
    digitalWrite(led_mizao, LOW);
    
  }else if(sinal == 2){
    
    digitalWrite(led_mizinho, LOW);
    digitalWrite(led_si, HIGH);
    delay(300); 
    digitalWrite(led_sol, LOW);
    digitalWrite(led_re, LOW);
    digitalWrite(led_la, LOW);
    digitalWrite(led_mizao, LOW);
    
  }else if(sinal == 3){
    
    digitalWrite(led_mizinho, LOW);
    digitalWrite(led_si, LOW);
    digitalWrite(led_sol, HIGH);
    delay(300); 
    digitalWrite(led_re, LOW);
    digitalWrite(led_la, LOW);
    digitalWrite(led_mizao, LOW);
    
  }else if(sinal == 4){
    
    digitalWrite(led_mizinho, LOW);
    digitalWrite(led_si, LOW);
    digitalWrite(led_sol, LOW);
    digitalWrite(led_re, HIGH);
    delay(300); 
    digitalWrite(led_la, LOW);
    digitalWrite(led_mizao, LOW);
  
  }else if(sinal == 5){
    
    digitalWrite(led_mizinho, LOW);
    digitalWrite(led_si, LOW);
    digitalWrite(led_sol, LOW);
    digitalWrite(led_re, LOW);
    digitalWrite(led_la, HIGH);
    delay(300); 
    digitalWrite(led_mizao, LOW);
   
  }else if(sinal == 6){
      
    digitalWrite(led_mizinho, LOW);
    digitalWrite(led_si, LOW);
    digitalWrite(led_sol, LOW);
    digitalWrite(led_re, LOW);
    digitalWrite(led_la, LOW);
    digitalWrite(led_mizao, HIGH);
    delay(300); 
    
    }
}
