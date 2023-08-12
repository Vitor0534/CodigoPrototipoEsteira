
void controlerComandosViaSerial(int sentidoDeGiro, int ContadorDeVelocidade){
  String comando;
  
  comando = SerialReadString();
  
  if(comando.indexOf("s") != -1){
     pararPWM();
     Serial.println(">>(s) stop mat...");
     
  }else{
    if(comando.indexOf("r") != -1){
     configuraSentidoDeGiro(sentidoDeGiro, ContadorDeVelocidade);
     Serial.println(">>(r) run mat");
     
    }else{
      if(comando.indexOf("v") != -1){
        int velocidade = splitIn2Velocidade(comando, ",");
        set_Velocidade(velocidade, sentidoDeGiro);
      }else{
        if(comando.indexOf("h") != -1){
          sentido_0H_1A_Global = 1;
          configuraSentidoDeGiro(sentido_0H_1A_Global, ContadorDeVelocidade);
          Serial.println(">>(h) sentido horario");
        }else{
          if(comando.indexOf("a") != -1){
            sentido_0H_1A_Global = 0;
            configuraSentidoDeGiro(sentido_0H_1A_Global, ContadorDeVelocidade);
            Serial.println(">>(a) sentido antihorario");
          }
          }
        }
        }
    }
 }


String SerialReadString(){
  String dado = "";
  String aux;
  while(Serial.available() > 0){
    aux = Serial.readString();
    dado += aux;
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

//v,Velocidade
int splitIn2Velocidade(String text, String separator){
  int index = text.indexOf(separator);
  String v  = text.substring(index+1, text.length());
  v.trim();
  int velocidade = v.toInt();
  return velocidade;
}
