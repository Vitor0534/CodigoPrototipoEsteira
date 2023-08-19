
void controlerComandosViaSerial(int sentidoDeGiro, int ContadorDeVelocidade){
    
  String inputString = SerialReadString();
  char comando = inputString[0];
  
    switch(comando){
      
       case 's': //stop mat
              pararPWM();
              Serial.println(">>(s) stop mat...");
            break;
       case 'r': //run mat
              configuraSentidoDeGiro(sentidoDeGiro, ContadorDeVelocidade);
              Serial.println(">>(r) run mat");
            break;
       case 'v':  //setup speed
              int velocidade;
              velocidade = splitIn2ComandWithNumber(inputString, ",");
              setVelocidadeAlvo(velocidade);
              Serial.println(">>(v) velocidade alvo setada para: " + String(velocidade) + " pwm");
            break;
       case 'h':  //girar no sentido horário
              sentido_0H_1A_Global = 1;
              configuraSentidoDeGiro(sentido_0H_1A_Global, ContadorDeVelocidade);
              Serial.println(">>(h) sentido horario");
            break;
       case 'a':  //girar no sentido antihorário
              sentido_0H_1A_Global = 0;
              configuraSentidoDeGiro(sentido_0H_1A_Global, ContadorDeVelocidade);
              Serial.println(">>(a) sentido antihorario");
            break;
       case 'c':  //altera a razão de decremento/incremento do PWM
       
              int novaRazao;
              novaRazao = splitIn2ComandWithNumber(inputString, ",");
              
              if(!(255%novaRazao)){
                
                razao_alteracao_velocidade = novaRazao;
                
                Serial.println(">>(c) razão de alteração da velocidade setada para: " + String(razao_alteracao_velocidade));
              
              }else{
                Serial.println(">>(c) Erro: a razao de alteraçao da velocidade precisa ser multiplo de 255");
              }
            break;
        case 'm': //altera o rpm máximo da esteira e recalcula o rpm alvo
        
              int newMaxMatRPM;
              newMaxMatRPM = splitIn2ComandWithNumber(inputString, ",");
              matObject.setMaxRPM(newMaxMatRPM);
              configuraVariaveisDeControleDoRPM();

              Serial.println(">>(c) RPM máximo da esteira alterado para: " + String(newMaxMatRPM));
              
            break;
        case 0: //comando vazio ASCII(0 == null)
              return;
            break;
        default:
              Serial.println("opção inesistente");
            break;
            
      }

 }


String SerialReadString(){
  String dado = "";
  String caracter;
  while(Serial.available() > 0){
    caracter = Serial.readString();
    dado += caracter;
  }
  return dado;
}


double SerialReadDouble(){
  double valor = 0;
  while(Serial.available() > 0){
    valor += Serial.parseInt();
  }
  return valor;
}


void SerialPortFluxy(){
  while(Serial.available() > 0)
    Serial.read();
}

//Ex. >> v,Velocidade
int splitIn2ComandWithNumber(String text, String separator){
  int index = text.indexOf(separator);
  String v  = text.substring(index+1, text.length());
  v.trim();
  int valor = v.toInt();
  return valor;
}
