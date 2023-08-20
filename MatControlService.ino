

void controleDeVelocidade(String opcao, int razao, int sentido_0H_1A){

  if(opcao.equals("+")){
    if(ContadorDeVelocidade<255){
      ContadorDeVelocidade += razao;
      configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidade);

      Serial.println("+Velocida = " + String(ContadorDeVelocidade));
    }
  }else{
    if(opcao.equals("-")){
      if(ContadorDeVelocidade>0){
        ContadorDeVelocidade -= razao;
        configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidade);
        Serial.println("-Velocida = " + String(ContadorDeVelocidade));
      }
    }
  }
}


void controleDeSentido(){

    if(sentido_0H_1A_Global == 0){
      sentido_0H_1A_Global  = 1;
      configuraSentidoDeGiro(sentido_0H_1A_Global, ContadorDeVelocidade);
      Serial.println("motor girando no sentido antihorario");
    }
    else{
      sentido_0H_1A_Global  = 0;
      configuraSentidoDeGiro(sentido_0H_1A_Global, ContadorDeVelocidade);
      Serial.println("Motor girando no sentido horario");
    }
  
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
