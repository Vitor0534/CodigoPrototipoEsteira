// Autor: Vitor de Almeida Silva, UFG/PPGEP - 2022

#include "Mat.h"

#define B1                  9                 // pino que controla a base 1
#define B2                  10                // pino que controla a base 2
#define button_3            7                 // pino que aumenta velocidade
#define button_4            5                 // pino que reduz a velocidade
#define button_5_Sentido    4                 // pino que configura a direção sentido horário/anti horario
#define button_6_stop       3                 // pino que interrompe o funcionamento da esteira
#define pulse_cont_interupt 2                 // pino que recebe o pulso do encoder para calculo do RPM


int ContadorDeVelocidade       = 0;
int velocidadeAlvo             = 153;         // valor está no formado de pwm (0 - 255)
int razao_alteracao_velocidade = 5;           // razão na qual a velocidade é incrementada ou decrementada default 51
int sentido_0H_1A_Global       = 0;           // 0 = horário ; 1 = antihorario

Mat matObject                  = Mat(318);
int RPM_Target = 0;
int RPM_Atual_Global  = 0;
volatile bool podePrintarRPM = false;

int encoderWheelPulseCount360Degrees = 8;     // indica quantos furos tem a roda do enconder para um giro de 360°, para calcular RPM 

void setup()
{

  Serial.begin(9600);    // configura a comunicação serial com 9600 bps
  configuraPinModes();
  configuraVariaveisDeControleDoRPM();
  
  attachInterrupt(digitalPinToInterrupt(button_6_stop),callbackPararMotor, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pulse_cont_interupt),callback_GetPulse, FALLING);

}

void configuraPinModes(){
  pinMode(B1, OUTPUT);   // configura pino da B1 como saída
  pinMode(B2, OUTPUT);   // configura pino da B2 como saída

  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);
  
  pinMode(button_5_Sentido, INPUT_PULLUP);
  pinMode(button_6_stop,    INPUT_PULLUP);

  pinMode(pulse_cont_interupt, INPUT_PULLUP);
  
  digitalWrite(B1, LOW); //configura o pino B1 como 0
  digitalWrite(B2, LOW); //configura o pino B2 como 0
}


void configuraVariaveisDeControleDoRPM(){
  RPM_Target = get_RPM_Target(matObject.get_maximo_RPM(), velocidadeAlvo);
  Serial.println("RPM motor " + String(matObject.get_maximo_RPM()) + " | " + "RPM_Target = " + String(RPM_Target));
}

int get_RPM_Target(double maximo_RPM, double pwm_Atual){
 return round((maximo_RPM * pwm_Atual)/255);
}

void callbackPararMotor(){
   pararPWM();
}

void pararPWM(){
  digitalWrite(B1, LOW); //configura o pino B1 como 0
  digitalWrite(B2, LOW); //configura o pino B2 como 0
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

void botoesDeComando(){

  if(digitalRead(button_5_Sentido) == LOW)
     controleDeSentido();
  else
     if(digitalRead(button_3) == LOW)
         controleDeVelocidade("+",razao_alteracao_velocidade, sentido_0H_1A_Global);
     else
        if(digitalRead(button_4) == LOW)
             controleDeVelocidade("-", razao_alteracao_velocidade, sentido_0H_1A_Global);
}

void loop(){


     controlerComandosViaSerial(sentido_0H_1A_Global, ContadorDeVelocidade);
     
     delay(40);
     
     botoesDeComando();
  
     if(podePrintarRPM && RPM_Atual_Global > 0){
         printRPMInformation(RPM_Target, RPM_Atual_Global);
         podePrintarRPM = false;
     }

}
