

void controleDeVelocidade(String opcao, int razao, int sentido_0H_1A){

  if(opcao.equals("+")){
    
      ContadorDeVelocidadeGlobal += razao;
    
  }else{
    
      ContadorDeVelocidadeGlobal -= razao;
   }
   
   ContadorDeVelocidadeGlobal = validaContadorDeVelocidade(ContadorDeVelocidadeGlobal);
   
   configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidadeGlobal);
   serialPrintVelocidade(opcao, ContadorDeVelocidadeGlobal);
   
}


int validaContadorDeVelocidade(int ContadorDeVelocidade){
  
  if(ContadorDeVelocidade > 255){
    return 255;
  }else{
    if(ContadorDeVelocidade < 0){
      return 0;
    }
  }
 
  return ContadorDeVelocidade;
}

void controleDeSentido(){


    sentido_0H_1A_Global  = !sentido_0H_1A_Global;
    
    configuraSentidoDeGiro(sentido_0H_1A_Global, ContadorDeVelocidadeGlobal);

    Serial.print("motor girando no sentido");
    Serial.println(sentido_0H_1A_Global ? " horário" : " ante horario");
  
}


void configuraSentidoDeGiro(int sentido, int ContadorDeVelocidade){
  
  switch(sentido){
    case 0: //horario
        analogWrite(B2, 0); //zera B2
        analogWrite(B1, ContadorDeVelocidade); //atualiza a saída PWM do pino B1 com valor recebido
        break;
    case 1: //AntHorario
        analogWrite(B2, ContadorDeVelocidade); //atualiza a saída PWM do pino B2 com valor recebido
        analogWrite(B1, 0); //zera B1
        break;
   case 3:
        pararPWM();
        break;
    default:
        Serial.println("opção inesistente");
        break;
  }
  
}


void setVelocidadeAlvo(int velocidade){
   velocidadeAlvo = velocidade;
   configuraVariaveisDeControleDoRPM();
}


void pararPWM(){
  digitalWrite(B1, LOW); //configura o pino B1 como 0
  digitalWrite(B2, LOW); //configura o pino B2 como 0
}

void serialPrintVelocidade(String operacao, int ContadorDeVelocidade){
  Serial.println(operacao + "Velocida = " + String(ContadorDeVelocidade));
}
