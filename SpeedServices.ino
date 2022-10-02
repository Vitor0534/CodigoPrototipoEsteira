
volatile int pulse = 0;
boolean can_increment = false;
void callback_GetPulse(){
  if(can_increment || pulse == 0){
    pulse++;
  }
}


double rotateTime = 0;
int  get_rpm_motor(){
  
  if(pulse == 1){
    rotateTime = millis();
    can_increment = true;
  }else{
    if(pulse == 2){
      rotateTime = abs((millis() - rotateTime));
      pulse = 0;
      can_increment = false;
      return calculaRPM(rotateTime);
    }
  }
  return -1;
}

int calculaRPM(double rotateTime){
  return round(60/(rotateTime/1000));
}


void speed_RPM_controller(int RPM_Target){
  
  int RPM_Atual = get_rpm_motor();

  if(RPM_Atual >= 0){
  if(RPM_Atual < RPM_Target){
    controleDeVelocidade("+", razao_alteracao_velocidade, sentido_0H_1A);
  }else{
    if(RPM_Atual > RPM_Target){
      controleDeVelocidade("+", razao_alteracao_velocidade, sentido_0H_1A);
    }
  }
  }
}
