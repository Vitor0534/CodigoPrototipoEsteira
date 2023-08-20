
# Código Protótipo de Esteira

### Autor: Vitor de Almeida Silva, UFG/PPGEP - 2022

### Breve explicação

O presente repositório contem o código em Arduíno que realiza o controle de uma esteira. O equipamento é usado no experimento de medida de bagagens aeroportuárias com sensor kinect. 

O sistema completo consiste em duas partes, a esteira que movimenta a bagagens abaixo do sensor e o software que coleta os dados da bagagem e realiza as medidas, este, implementado em Matlab 2020.


### Funcionalidades
* **Controle PID:** foi implementado um controlador PID utilizando interrupção e encoder para controle mais preciso do RPM da esteira. É possível configurar o RPM alvo e o PID adequa a velocidade alterando o PWM nos pinos devidos;
* **Painel de Controle:** painel físico com quatro botões para configuração da velocidade, sentido de giro e parada da esteira;
* **Serial Controller:** modulo que recebe comandos vindos da porta serial para controle/configuração da esteira em tempo de execução. Utilizado na integração da esteira com o software central de medida de bagagens, permitindo configurações com os seguintes comandos:
	* Comando 's': para a esteira;
	* Comando 'r': retorna o movimento da esteira;
	* Comando 'v,pwm': altera a velocidade alvo da esteira para a indicada;
		* Ex. >> 'v,150';
	* Comando 'h': altera o sentido de giro para horário;
	* Comando 'a': altera o sentido de giro para anti horário;
	* Comando 'c,razao': altera a razão de decremento/incremento do PWM. Quanto mais alto, maior a reação do PID as alterações e menor a precisão para velocidade alvo. A razão precisa ser multiplo de 255 com conta dos limites do pwm:
		* Ex. >>"C,15"
	* Comando 'm,RPMmaximo': altera o rpm máximo da esteira e recalcula o rpm alvo.


**Quanto aos cálculos para controle do RPM:**

* Calculo do RPM atual:
	* RPM = 60k/Rt
	  * Rt = tempo de rotação, é o tempo que o motor leva para fazer uma rotação completa em milissegundos
* Calculo RPM alvo:
	* RPM_Alvo = (RPM_Max * PWM_Alvo)/255
* Calculo do RPM atual:
	* RPM_Atual = ( 60000 / (TempoEntreDoisPulsos * QuantidadeDePulsosPara360°DoEncoder ) )


**Quanto a equivalência das 5 opções de velocidade e seus valores de RPM**
Ainda que seja possível configurar qualquer RPM, são mais utilizados 5 opções, a seguir as velocidades e seus respectivos valores de RPM:
- Velocidade 1 = 51  pwm  | 64  RPM
- Velocidade 2 = 102 pwm  | 127 RPM
- Velocidade 3 = 153 pwm  | 163 RPM
- Velocidade 4 = 204 pwm  | 254 RPM
- Velocidade 5 = 255 pwm  | 318 RPM



//TODO:


