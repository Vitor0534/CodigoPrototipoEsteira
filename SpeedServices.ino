
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

  double start_rotateTime;
  double end_RotateTime;
  
  if(pulse == 1 && getRotateTime){
    
    start_rotateTime = millis(); 
    //Serial.println("start_rotateTime:" + String(start_rotateTime));
    can_increment = true;
    getRotateTime = false;
    
  }else{
    if(pulse == 2){
      
      end_RotateTime = millis();
     // Serial.println("end_RotateTime:" + String(end_RotateTime));
      rotateTime = abs(end_RotateTime - start_rotateTime);
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
  return round(6000/rotateTime);
}


void speed_RPM_controller(int RPM_Target){
  
  int RPM_Atual = get_rpm_motor();
  //Serial.println("RMP_Atual:" + String(RPM_Atual));
  if(RPM_Atual >= 0){
  if(RPM_Atual < RPM_Target){
    Serial.println("RMP_Target: " + String(RPM_Target) + " | " + "RMP_Atual: " + String(RPM_Atual));
    controleDeVelocidade("+", razao_alteracao_velocidade, sentido_0H_1A);
  }else{
    if(RPM_Atual > RPM_Target){
      Serial.println("RMP_Target: " + String(RPM_Target) + " | " + "RMP_Atual: " + String(RPM_Atual));
      controleDeVelocidade("-", razao_alteracao_velocidade, sentido_0H_1A);
    }
  }
  }
}
