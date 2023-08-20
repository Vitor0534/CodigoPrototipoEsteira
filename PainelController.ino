
void veirficaBotoesControlPanel(){

  if(digitalRead(button_5_Sentido) == LOW)
     controleDeSentido();
  else
     if(digitalRead(button_3) == LOW)
         controleDeVelocidade("+",razao_alteracao_velocidade, sentido_0H_1A_Global);
     else
        if(digitalRead(button_4) == LOW)
             controleDeVelocidade("-", razao_alteracao_velocidade, sentido_0H_1A_Global);
}

void callbackPararMotor(){
   pararPWM();
}
