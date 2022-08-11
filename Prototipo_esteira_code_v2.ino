// Autor: Vitor de Almeida Silva, UFG/PPGEP - 2022


#define B1                  9                 // pino que controla a base 1
#define B2                  10                // pino que controla a base 2
#define button_3            2                 // pino que aumenta velocidade
#define button_4            5                 // pino que reduz a velocidade
#define button_5_Sentido    4                 // pino que configura a direção sentido horário/anti horario
#define button_6_stop       3                 // pino que interrompe o funcionaento da esteira

void setup()
{

  Serial.begin(9600);    // configura a comunicação serial com 9600 bps
  configuraPinModes();

  attachInterrupt(digitalPinToInterrupt(button_6_stop),callbackPararMotor, CHANGE);

}

void configuraPinModes(){
  pinMode(B1, OUTPUT);   // configura pino da B1 como saída
  pinMode(B2, OUTPUT);   // configura pino da B2 como saída

  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  
  pinMode(button_5_Sentido, INPUT_PULLUP);
  pinMode(button_6_stop, INPUT_PULLUP);
  
  digitalWrite(B1, LOW); //configura o pino B1 como 0
  digitalWrite(B2, LOW); //configura o pino B2 como 0
}


int ContadorDeVelocidade = 0;
int sentido_0H_1A = 0;   // 0 = horário ; 1 = antihorario


void pararPWM(){
  digitalWrite(B1, LOW); //configura o pino B1 como 0
  digitalWrite(B2, LOW); //configura o pino B2 como 0
}

boolean start_ =true;
void callbackPararMotor(){
  if(!start_){
    Serial.println("Parando movimento");
    pararPWM();
  }else{
    start_=false;
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


void set_Velocidade(int velocidade, int sentido){
   switch(sentido){
    case 0: //horario
        analogWrite(B2, 0); //zera B2
        analogWrite(B1,velocidade); //atualiza a saída PWM do pino B1 com valor recebido
    break;
    case 1: //AntHorario
        analogWrite(B2, ContadorDeVelocidade); //atualiza a saída PWM do pino B2 com valor recebido
        analogWrite(B1, 0); //zera B1
    break;
   }
}


void controleDeVelocidade(String opcao){

  if(opcao.equals("+")){
    if(ContadorDeVelocidade<255){
      ContadorDeVelocidade+=51;
      configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidade);

      Serial.println("+Velocida = " + String(ContadorDeVelocidade));
    }
  }else{
    if(opcao.equals("-")){
      if(ContadorDeVelocidade>0){
        ContadorDeVelocidade-=51;
        configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidade);
        Serial.println("-Velocida = " + String(ContadorDeVelocidade));
      }
    }
  }
}

void controleDeSentido(){

    if(sentido_0H_1A == 0){
      sentido_0H_1A  = 1;
      configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidade);
      Serial.println("motor girando no sentido antihorario");
    }
    else{
      sentido_0H_1A  = 0;
      configuraSentidoDeGiro(sentido_0H_1A, ContadorDeVelocidade);
      Serial.println("Motor girando no sentido horario");
    }
  
}


void botoesDeComando(){

  if(digitalRead(button_5_Sentido) == LOW)
     controleDeSentido();
  else
     if(digitalRead(button_3) == LOW)
         controleDeVelocidade("+");
     else
        if(digitalRead(button_4) == LOW)
             controleDeVelocidade("-");
}

void loop(){
      controlerComandosViaSerial(sentido_0H_1A, ContadorDeVelocidade);
      delay(40);
      botoesDeComando();
}
