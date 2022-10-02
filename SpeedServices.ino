
volatile int pulse = 0;
boolean can_increment = false;


void callback_GetPulse(){
  if((can_increment || pulse == 0) && pulse < 2){
    Serial.println("pulse Lançado:" + String(pulse));
    pulse++;
  }
}


double rotateTime = 0;
boolean getRotateTime = true;
int  get_rpm_motor(){
  
  if(pulse == 1 && getRotateTime){
    rotateTime = millis(); 
    Serial.println("rotateTime:" + String(rotateTime));
    can_increment = true;
    getRotateTime = false;
  }else{
    if(pulse == 2){
      rotateTime = abs((millis() - rotateTime));
      Serial.println("rotateTime:" + String(rotateTime));
      pulse = 0;
      can_increment = false;
      getRotateTime = true;
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
  Serial.println("RMP_Atual:" + String(RPM_Atual));
  if(RPM_Atual >= 0){
  if(RPM_Atual < RPM_Target){
    controleDeVelocidade("+", razao_alteracao_velocidade, sentido_0H_1A);
  }else{
    if(RPM_Atual > RPM_Target){
      controleDeVelocidade("-", razao_alteracao_velocidade, sentido_0H_1A);
    }
  }
  }
}
