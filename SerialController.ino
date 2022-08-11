
void controlerComandosViaSerial(int sentido_0H_1A, int ContadorDeVelocidade){
  String comando;
  
  comando = SerialReadString();
  
  if(comando.indexOf("s") != -1){
     pararPWM();
     Serial.print("Comando: " + comando);
     Serial.println(">>(s) stop mat...");
     //SerialPortFluxy();
     
  }else{
    if(comando.indexOf("r") != -1){
     configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidade);
     Serial.print("Comando: " + comando);
     Serial.println(">>(r) run mat");
     //SerialPortFluxy();
     
    }else{
      if(comando.indexOf("v") != -1){
        int velocidade = splitIn2Velocidade(comando, ",");
        set_Velocidade(velocidade, sentido_0H_1A);
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
