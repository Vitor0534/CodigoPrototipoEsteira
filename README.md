# CodigoPrototipoEsteira



- Foi iniciada a implementação do controle PID para velocidade do motor, alguns itens faltantes são:
  - Realizar testes com motor físico, para ajustar o método



**Quanto aos cálculo para controle do RPM:**

Calculo do RPM atual:

* RPM = 60k/Rt
  * Rt = tempo de rotação, é o tempo que o motor leva para fazer uma rotação completa em milisegundos

Calculo RPM alvo:

* RPM_Alvo = (RPM_Max * PWM_Alvo)/255

