
volatile int pulse = 0;
boolean can_increment = false;



void callback_GetPulse(){
  if((can_increment || pulse == 0) && pulse < 2){
    //Serial.println("pulse Lançado: " + String(pulse));
    pulse++;
  }
  speed_RPM_controller(RPM_Target, encoderWheelPulseCount360Degrees);
  podePrintarRPM = true;
}


double start_rotateTime = 0;
double end_RotateTime = 0;
double rotateTime = 0;
boolean canGetStartRotateTime = true;
int  get_rpm_motor(int encoderWheelPulseCount360Degrees){

  if(pulse == 1 && canGetStartRotateTime){
    
    start_rotateTime = millis(); 
    //Serial.println("start_rotateTime:" + String(start_rotateTime));
    can_increment = true;
    canGetStartRotateTime = false;
    
  }else{
    if(pulse == 2){
      
      end_RotateTime = millis();
      //Serial.println("end_RotateTime:" + String(end_RotateTime));
      rotateTime = abs(end_RotateTime - start_rotateTime);
      //Serial.println("rotateTime: " + String(rotateTime));
      pulse = 0;
      can_increment = false;
      canGetStartRotateTime = true;
      
      return calculaRPM(rotateTime*encoderWheelPulseCount360Degrees);
      
    }
  }
  return -1;
}

int calculaRPM(double rotateTime){
  return round(60000/rotateTime);
}


void speed_RPM_controller(int RPM_Target, int encoderWheelPulseCount360Degrees){
  
  RPM_Atual_Global = get_rpm_motor(encoderWheelPulseCount360Degrees);

  if(RPM_Atual_Global >= 0){
  if(RPM_Atual_Global < RPM_Target){
    controleDeVelocidade("+", razao_alteracao_velocidade, sentido_0H_1A_Global);
    
  }else{
    if(RPM_Atual_Global > RPM_Target){
      controleDeVelocidade("-", razao_alteracao_velocidade, sentido_0H_1A_Global);
      
    }
  }
  }
}

void printRPMInformation(int RPM_Target, int RPM_Atual){
    Serial.println("RMP_Target: " + String(RPM_Target) + " | " + "RMP_Atual: " + String(RPM_Atual));
}

int get_RPM_Target(double maximo_RPM, double pwm_Atual){
 return round((maximo_RPM * pwm_Atual)/255);
}
