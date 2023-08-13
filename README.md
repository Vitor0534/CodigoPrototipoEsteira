# CodigoPrototipoEsteira



- Foi iniciada a implementação do controle PID para velocidade do motor, alguns itens faltantes são:
  - Realizar testes com motor físico, para ajustar o método



**Quanto aos cálculo para controle do RPM:**

Calculo do RPM atual:

* RPM = 60k/Rt
  * Rt = tempo de rotação, é o tempo que o motor leva para fazer uma rotação completa em milisegundos

Calculo RPM alvo:

* RPM_Alvo = (RPM_Max * PWM_Alvo)/255



**Quanto a equivalência das 5 opções de velocidade e seus valores de RPM**

- Velocidade 1 = 51  pwm  | 38  RPM
- Velocidade 2 = 102 pwm  | 76  RPM
- Velocidade 3 = 153 pwm  | 113 RPM
- Velocidade 4 = 204 pwm  | 152 RPM
- Velocidade 5 = 255 pwm  | 190 RPM



//TODO:
revisar comportamento do controle de rpm que está impreciso. verifique se tem relação com o código ou o disco do encoder

- Velocidade 1 = 51  pwm  | xx  RPM
- Velocidade 2 = 102 pwm  | xx  RPM
- Velocidade 3 = 153 pwm  | 163 RPM
- Velocidade 4 = 204 pwm  | xx RPM
- Velocidade 5 = 255 pwm  | xx RPM