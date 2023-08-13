
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
   case 'v':  //configura velocidade
          int velocidade = splitIn2Velocidade(inputString, ",");
          set_Velocidade(velocidade, sentidoDeGiro);
          Serial.println(">>(v) setar velocidade para: " + String(velocidade));
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
    default:
          Serial.println("opção inesistente");
        break;
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
