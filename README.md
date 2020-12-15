# Módulos de de controle de luzes e sinalização


A Van é um veículo fabricado há 10 anos com um sistema de controle de luzes e sinalização convencional baseado em relés e interruptores simples. A conversão da Van para elétrico, também teve que fazer o *redesing* das instalações elétricas do veículo, incorporando toda sinalização e comando de luzes à barramento de comunicação do novo veículo.

Usou-se como base o módulo desenvolvido para o BR800. Este novo módulo foi desenhado para centralizar todos os comandos de luzes e sinalização, aproveitando as teclas e interruptores já existentes no *dashboard* do veículo, mas permitido a sua expansão com elementos não convencionais que podem ser facilmente incorporado na nova configuração tecnológica. O diagrama de blocos a seguir mostra o esquema funcional do novo módulo.

![](figuras/Diagrama_blocos_Mod_luz.jpg)   

Este módulo tem como elemento central o Arduino Nano. Escolheu-se esta placa microcontroladora por sua popularidade, grande acervo técnico de suporte e relação custo benefício. 
O módulo monitora as teclas no painel para ligar a sinalização (setas direita e esquera), farois (baixo e alto), lanterna, luz de freio, pisca alerta, freio de mão, e luz de ré no total de 9 comandos.

Estes comandos são processados pelo módulo e apresentado de forma gráfico no display do módulo e por meio de 7 comandos os sinais luminosos farol alto, farol baixa, lanterna, luz de freio, luz de ré e as setas para direita e esquerda são acionados. 
A sinalização de freio de mão acionada é somente encaminhada para o display. 
O módulo também emite o sinal sonoro de alarme ou setas, por meio de um buzzer. 
As figuras a seguir mostram o esquema elétrica do módulo e a placa de circuito impresso. 

![](figuras/Esquema_Mod_luz.jpg)

O módulo tem a capacidade de monitorar seu consumo de corrente e a sua tensão e o barramento CAN permitirá a medição e acionamento remoto.
A comunicação CAN é implementado por um controlador dedicada para CAN Bus MCP2515 que está ligado por meio da interface SPI ao microcontrolador Arduino. Veja o datasheet do controlador MCP2515 
[aqui](http://ww1.microchip.com/downloads/en/DeviceDoc/MCP2515-Stand-Alone-CAN-Controller-with-SPI-20001801J.pdf). 

Os demais componentes do módulo são todos circuitos integrados convencionais, com destaque para o sensor de corrente ACS712.
O layout da placa de circuito impresso (PCB) está na figura a seguir. 

![](figuras/placa_mod_luz.jpg)

## Alojamento e conexões

O módulo será alojado numa caixa padrão Patola [PB115](http://www.patola.com.br/index.php?route=product/product&product_id=359) com conectores específicos para cada funcionalidade, com pinagem diferenciados para evitar trocas. Os conectores para display, alimentação 12 volts, CAN também são padronizadas. 
Convencionou-se que entrada dos sensores e saída dos comandos ficarão na parte de traseira da caixa, enquanto a interface CAN, alimentação, saída para display e acesso para reporgramação do arduino ficarão no frente. A interface CAN será implementado por dois conectores DB9, mantendo o padrão industrial.

A foto na figura a seguir mostra a caixa PB115 com a proposta de placa de circuito impresso com na parte de frente os conectores de entrada dos botões e saída para as lámpadas. Na parte de traz, entrada para programar o arduino nano, o conector para o dislay, interface CAN e alimentação de 12Vdc.     

![](fotos/foto_placa_luzes.jpg)


## Conector CAN

Pinagem do conector DB9 macho para ligar o barramento CAN.


# Protótipo V1
Primeiro protótipo montado em setembro 2020.

![](figuras/PCB_ModLuz_v1_esquema.png)

![](figuras/PCB_ModLuz_v1_lado_componentes.png)


![](figuras/PCB_ModLuz_v1_lado_solda.png)

![](figuras/PCB_ModLuz_v1_montado_3d.png)

![](figuras/PCB_ModLuz_v1_montado.png)


![](fotos/foto_placa_luzes_montado.jpg)

# Programa 

O programa de controle está no repositório 
[`https://github.com/rudivels/BREletrica_Luzes_CAN_beep_display`](https://github.com/rudivels/BREletrica_Luzes_CAN_beep_display)


# Comando de Luzes

O conector de comando de luzes é formado por um conector de 2x5 pinos (modelo - tipo) com a seguinte especificação.
Na primeira fileira os pinos:

| pino | função       | cor      | ULN   | 74595 |
|:----:|:------------:|:--------:|:-----:|:-----:|
| 1    | Luz de freio | cinza    | Out 1 |  QG   |
| 2    |  GND         | preto    | GND   |  -    |
| 3    |  12V         | vermelho | 12V   |  -    |
| 4    |  GND         | preto    | GND   |  -    |
| 5    | Luz de ré    | branco   | Out 7 |  QA   |

Na segunda fileira os pinos: 

| pino | função        | cor     |  ULN  | 74595 | 
|:----:|:-------------:|:-------:|:-----:|:-----:|
| 6    | Lanterna      | laranja | Out 2 | QF    |
| 7    | Farol baixa   | amarela | Out 3 | QE    |
| 8    | Farol alta    | verde   | Out 4 | QD    |
| 9    | Seta direita  | azul    | Out 5 | QC    |
| 10   | Seta esquerda | violeta | Out 6 | QB    |

Os pinos D3, D4 e D5 comandam o 74HC595 

| pino | nome  | 74595 |pino função             |
|:----:|:-----:|:-----:|:-----------------------| 
| D3   | RCLK  | 12    | Storage register clock |
| D4   | SRCLK | 11    | Shift register clock   |
| D5   | SER   | 14    | serial data input      | 




# Engenharia reversa do painel UP VW Can bus

Fazendo a engenharia reversa do painel de instrumentos do UP VW.

![](fotos/painel_up_frente.jpg)

![](fotos/painel_up_fundo.jpg)

![](fotos/detalhes_painel_up.jpg)


Já sabemos que pino 20 é GND e pino 32 e 31 alimentação..  32 deve ser alimentação geral e 31 deve ser alimentação do painel depois da chave de partida...


Bom...  com isso resolvido, podemos ver se a gente acha um conector que se encaixa nessas configuração..   Deve ter alguma documentação sobre reparação de paineis, imobilização do motor (immo) chave de segurança que trata sobre este conector...  Também deve ter alguma padronização de cores (conector azul, verde)...

Eu não tinha certeza se este painel tinha uma interface CAN...  mas pesquisando o datasheet do microcontrolador, conferi que o chip tem duas interfaces can..

[https://www.nxp.com/docs/en/data-sheet/MC9S12XHZ512.pdf](https://www.nxp.com/docs/en/data-sheet/MC9S12XHZ512.pdf)

Continuando com a engenharia reversa... pela lógica o microcontrolador deve estar ligado a um transciever,  e este chip deve ser um CI mais robusto pelo fato de estar diretamente ligado ao barramento CAN .. e deve estar posicionado entre o microcontrolador e o conector..


![](fotos/placa_painel_up.jpg)

Achei o chip...    
[https://www.infineon.com/cms/en/product/transceivers/automotive-transceiver/automotive-can-transceivers/tle6251ds/](https://www.infineon.com/cms/en/product/transceivers/automotive-transceiver/automotive-can-transceivers/tle6251ds/)

pino 6 canl  está ligado a pino 29 do conector...
pino 7 canh está no pino 28

| pino | função   | cor     |   
|:----:|:--------:|:-------:| 
| 28   | CAN_H    | cinza   | 
| 29   | CAN_L    | branco  |
| 20   | GND      |
| 32   | +12v     |
| 31   | +12v     |

Com isso resolvido, podemos ver se a gente acha um conector que se encaixa nessas configuração..   Deve ter alguma documentação sobre reparação de paineis, imobilização do motor (immo) chave de segurança que trata sobre este conector...  Também deve ter alguma padronização de cores (conector azul, verde)...

A rigor, podemos rodar um teste, alimentando o painel e medir o osciloscopio o sinal que o microcontrolador manda no barramento CAN...  Pela lógica o painel deve mandar uma informação no barramento avisando que ele está vivo e esperando dados...

Assim podemos medir o baudrate e tentar identificar o ID do painel..

![](fotos/sinal_can_sem_terminador.jpg)

veja o mesmo sinal com resistor..

da para ver que ao inicializar o painel manda uma palavra comprido de 300ms e depois ele manda a cada 0,1s em bloco de informação..

este bloco tem o seguinte formato..

![](fotos/sinal_can_terminador.jpg)

dá para ver que o menor elemento tem 2us...  ou seja a taxa de transmissao é 500khz..

os mais corajosos podem a partir deste sinal decodificar o dado...  ou outra solução é liga-lo com um computador com interface CAN e depurar o codigo..

uma vez ligado, o painel manda um bloco de 150ms e depois para 100ms...

![](fotos/sinal_bloco_1.jpg)

este bloco de 150ms é divido em vários blocos com 200uS

![](fotos/sinal_bloco_2.jpg)

e o detalhe da palavra mandado pelo CAN é o seguinte ..  a partir dessa figura dá para reconstituir o dado que é mandado pela CAN   500bps.

![](fotos/sinal_bloco_3.jpg)




# Dump do CAN

Usando a biblioteca do CAN Read Demo do Sparkfun CAN bus shield conseguimos monitorar o barramento. 
Um programa simples que monitora e imprime.

Segue o dump do que é lido no momento que o painel é ligado.


```
02:41:19.961 -> ID: 322, Data: 0
02:41:20.032 -> ID: 322, Data: 0
02:41:23.771 -> ID: 321, Data: 926 26 92 64 97 48 90 FF C 
02:41:23.843 -> ID: 321, Data: 926 26 92 64 97 48 90 FF C 
02:41:23.916 -> ID: 321, Data: 964 97 4F 92 64 97 4F 92 C 
02:41:23.988 -> ID: 321, Data: 964 97 4F 92 64 97 4F 92 C 
02:41:24.023 -> ID: 321, Data: 997 4F 92 64 97 4F 92 64 C 
02:41:24.096 -> ID: 321, Data: 964 97 4F 92 64 97 4F 92 C 
02:41:24.165 -> ID: 321, Data: 964 97 4F 92 64 97 4F 92 C 
02:41:24.236 -> ID: 321, Data: 964 97 4F 97 4F 92 24 92 C 
02:41:24.307 -> ID: 321, Data: 94F 92 64 97 4F 92 64 97 C 
02:41:24.380 -> ID: 320, Data: 964 97 4F 92 64 97 4F 92 C 
02:41:24.516 -> ID: 321, Data: 992 20 92 64 97 4F C9 4F C 
02:41:24.588 -> ID: 321, Data: 9C9 C9 8 C9 C9 C9 C9 C9 C 
02:41:24.728 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:24.798 -> ID: 322, Data: 0
02:41:24.870 -> ID: 322, Data: 0
02:41:24.938 -> ID: 322, Data: 0
02:41:25.007 -> ID: 322, Data: 0
02:41:25.080 -> ID: 322, Data: 0
02:41:25.191 -> ID: 322, Data: 0
02:41:25.259 -> ID: 322, Data: 0
02:41:25.398 -> ID: 322, Data: 0
02:41:25.465 -> ID: 322, Data: 0
02:41:25.542 -> ID: 322, Data: 0
02:41:25.609 -> ID: 322, Data: 0
02:41:25.676 -> ID: 322, Data: 0
02:41:25.748 -> ID: 322, Data: 0
02:41:25.820 -> ID: 322, Data: 0
02:41:25.892 -> ID: 322, Data: 0
02:41:25.964 -> ID: 322, Data: 0
02:41:26.103 -> ID: 322, Data: 0
02:41:26.137 -> ID: 322, Data: 0
02:41:26.213 -> ID: 322, Data: 0
02:41:26.287 -> ID: 322, Data: 0
02:41:26.355 -> ID: 322, Data: 0
02:41:26.428 -> ID: 322, Data: 0
02:41:26.501 -> ID: 322, Data: 0
02:41:26.568 -> ID: 322, Data: 0
02:41:26.636 -> ID: 322, Data: 0
02:41:26.779 -> ID: 448, Data: 10C9 C9 C9 C8 C9 C9 C9 C9 C 0 
02:41:26.854 -> ID: 322, Data: 0
02:41:26.993 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:27.066 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:27.139 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:27.211 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:27.244 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:27.314 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:27.384 -> ID: 322, Data: 9C9 C9 C9 C8 C9 C9 C9 C9 C 
02:41:27.451 -> ID: 322, Data: 0
02:41:27.522 -> ID: 322, Data: 0
02:41:27.663 -> ID: 322, Data: 0
02:41:27.736 -> ID: 122, Data: 0
02:41:27.807 -> ID: 322, Data: 0
02:41:27.875 -> ID: 322, Data: 0
02:41:27.942 -> ID: 322, Data: 0
02:41:28.015 -> ID: 322, Data: 0
02:41:28.086 -> ID: 764, Data: 0
02:41:28.154 -> ID: 322, Data: 0
02:41:28.226 -> ID: 322, Data: 0
02:41:28.332 -> ID: 322, Data: 0
02:41:28.399 -> ID: 322, Data: 0
02:41:28.538 -> ID: 322, Data: 0
02:41:28.610 -> ID: 64, Data: 0
02:41:28.687 -> ID: 322, Data: 0
02:41:28.758 -> ID: 322, Data: 0
02:41:28.825 -> ID: 322, Data: 0
02:41:28.900 -> ID: 322, Data: 0
02:41:28.973 -> ID: 322, Data: 0
02:41:29.011 -> ID: 322, Data: 0
02:41:29.083 -> ID: 322, Data: 0
02:41:29.224 -> ID: 322, Data: 0
02:41:29.295 -> ID: 322, Data: 0
02:41:29.371 -> ID: 322, Data: 0
02:41:29.440 -> ID: 322, Data: 0
02:41:29.517 -> ID: 322, Data: 0
02:41:29.584 -> ID: 322, Data: 0
02:41:29.620 -> ID: 322, Data: 0
02:41:29.689 -> ID: 322, Data: 0
02:41:29.790 -> ID: 322, Data: 0
02:41:29.896 -> ID: 322, Data: 0
02:41:29.969 -> ID: 322, Data: 0
02:41:30.041 -> ID: 322, Data: 0
02:41:30.113 -> ID: 322, Data: 0
02:41:30.182 -> ID: 322, Data: 0
02:41:30.250 -> ID: 322, Data: 0
02:41:30.317 -> ID: 322, Data: 0
02:41:30.384 -> ID: 322, Data: 0
02:41:30.456 -> ID: 322, Data: 0
02:41:30.597 -> ID: 322, Data: 0
02:41:30.671 -> ID: 322, Data: 0
02:41:30.810 -> ID: C8, Data: 0
02:41:30.880 -> ID: 322, Data: 0
02:41:30.947 -> ID: 322, Data: 0
02:41:31.020 -> ID: 322, Data: 0
02:41:31.054 -> ID: 322, Data: 0
02:41:31.126 -> ID: 248, Data: 0
02:41:31.270 -> ID: 322, Data: 0
02:41:31.343 -> ID: 322, Data: 0
02:41:31.478 -> ID: 322, Data: 0
02:41:31.551 -> ID: 322, Data: 0
02:41:31.626 -> ID: 322, Data: 0
02:41:31.693 -> ID: 322, Data: 0
02:41:31.764 -> ID: 64, Data: 0
02:41:31.832 -> ID: 322, Data: 0
02:41:31.899 -> ID: 322, Data: 0
02:41:31.937 -> ID: 322, Data: 0
02:41:32.039 -> ID: 322, Data: 0
02:41:32.150 -> ID: 322, Data: 0
02:41:32.219 -> ID: 322, Data: 0
02:41:32.287 -> ID: 322, Data: 0
02:41:32.359 -> ID: 322, Data: 0
02:41:32.432 -> ID: 64, Data: 0
02:41:32.500 -> ID: 322, Data: 88 40 C9 C8 C9 C9 C9 C9 
02:41:32.570 -> ID: 322, Data: 0
02:41:32.641 -> ID: 322, Data: 0
02:41:32.710 -> ID: 322, Data: 0
02:41:32.853 -> ID: 264, Data: 0
02:41:32.923 -> ID: 322, Data: 0
02:41:33.060 -> ID: 322, Data: 0
02:41:33.131 -> ID: 322, Data: 0
02:41:33.203 -> ID: 322, Data: 0
02:41:33.241 -> ID: 448, Data: 0
02:41:33.314 -> ID: 322, Data: 0
02:41:33.416 -> ID: 322, Data: 88 40 8 C8 C9 C9 C9 C9 
02:41:33.451 -> ID: 322, Data: 0
02:41:33.523 -> ID: 322, Data: 0
02:41:33.596 -> ID: 322, Data: 0
02:41:33.740 -> ID: 322, Data: 0
02:41:33.813 -> ID: 322, Data: 0
02:41:33.887 -> ID: 322, Data: 0
02:41:33.921 -> ID: 322, Data: 0
02:41:33.991 -> ID: 322, Data: 0
02:41:34.063 -> ID: 322, Data: 0
02:41:34.135 -> ID: 322, Data: 0
02:41:34.202 -> ID: 322, Data: 0
02:41:34.270 -> ID: 322, Data: 0
02:41:34.409 -> ID: 322, Data: 0
02:41:34.477 -> ID: 322, Data: 0
02:41:34.548 -> ID: 322, Data: 0
02:41:34.620 -> ID: 322, Data: 0
02:41:34.690 -> ID: 322, Data: 0
02:41:34.763 -> ID: 322, Data: 0
02:41:34.831 -> ID: 322, Data: 0
02:41:34.899 -> ID: 322, Data: 0
02:41:34.968 -> ID: 120, Data: 0
02:41:35.108 -> ID: 322, Data: 0
02:41:35.181 -> ID: 322, Data: 0
02:41:35.286 -> ID: 322, Data: 0
02:41:35.359 -> ID: 322, Data: 0
02:41:35.431 -> ID: 322, Data: 0
02:41:35.502 -> ID: 448, Data: 0
02:41:35.573 -> ID: 322, Data: 0
02:41:35.644 -> ID: 322, Data: 0
02:41:35.711 -> ID: 322, Data: 0
02:41:35.781 -> ID: 322, Data: 0
02:41:35.848 -> ID: 322, Data: 0
02:41:35.985 -> ID: 322, Data: 0
02:41:36.061 -> ID: 322, Data: 0
02:41:36.128 -> ID: 322, Data: 0
02:41:36.200 -> ID: 322, Data: 0
02:41:36.268 -> ID: 322, Data: 0
02:41:36.336 -> ID: 322, Data: 0
02:41:36.408 -> ID: 322, Data: 0
02:41:36.442 -> ID: 322, Data: 0
02:41:36.514 -> ID: 322, Data: 0
02:41:36.651 -> ID: 448, Data: 0
02:41:36.719 -> ID: 322, Data: 0
02:41:36.789 -> ID: 322, Data: 0
02:41:36.856 -> ID: 322, Data: 0
02:41:36.928 -> ID: 322, Data: 0
02:41:36.995 -> ID: 322, Data: 0
02:41:37.067 -> ID: 322, Data: 0
02:41:37.134 -> ID: 322, Data: 0
02:41:37.211 -> ID: 322, Data: 0
02:41:37.349 -> ID: 322, Data: 0
02:41:37.417 -> ID: 322, Data: 0
02:41:37.557 -> ID: 322, Data: 0
02:41:37.629 -> ID: 322, Data: 0
02:41:37.699 -> ID: 322, Data: 0
02:41:37.767 -> ID: 322, Data: 0
02:41:37.840 -> ID: 322, Data: 0
02:41:37.874 -> ID: 322, Data: 0
02:41:38.014 -> ID: 448, Data: 0
02:41:38.081 -> ID: 322, Data: 0
02:41:38.232 -> ID: 322, Data: 0
02:41:38.303 -> ID: 322, Data: 0
02:41:38.374 -> ID: 322, Data: 0
02:41:38.442 -> ID: 322, Data: 0
02:41:38.511 -> ID: 322, Data: 88 40 8 49 8 C9 C9 C9 
02:41:38.584 -> ID: 322, Data: 0
02:41:38.654 -> ID: 322, Data: 0
02:41:38.722 -> ID: 322, Data: 0
02:41:38.789 -> ID: 322, Data: 0
02:41:38.896 -> ID: 322, Data: 0
02:41:38.964 -> ID: 103, Data: 0
02:41:39.040 -> ID: 322, Data: 0
02:41:39.112 -> ID: 322, Data: 0
02:41:39.184 -> ID: 322, Data: 0
02:41:39.251 -> ID: 322, Data: 0
02:41:39.319 -> ID: 322, Data: 0
02:41:39.392 -> ID: 322, Data: 0
02:41:39.464 -> ID: 322, Data: 0
02:41:39.601 -> ID: 322, Data: 0
02:41:39.667 -> ID: 322, Data: 0
02:41:39.801 -> ID: 448, Data: 0
02:41:39.868 -> ID: 322, Data: 98 40 8 49 8 C9 C9 C9 C 
02:41:39.936 -> ID: 322, Data: 98 40 8 49 8 8 C9 C9 C 
02:41:40.006 -> ID: 322, Data: 0
02:41:40.072 -> ID: 322, Data: 0
02:41:40.139 -> ID: 322, Data: 0
02:41:40.205 -> ID: 322, Data: 0
02:41:40.272 -> ID: 322, Data: 0
02:41:40.338 -> ID: 322, Data: 0
02:41:40.473 -> ID: 322, Data: 0
02:41:40.541 -> ID: 322, Data: 0
02:41:40.612 -> ID: 322, Data: 0
02:41:40.681 -> ID: 322, Data: 0
02:41:40.747 -> ID: 322, Data: 0
02:41:40.817 -> ID: 322, Data: 0
02:41:40.885 -> ID: 322, Data: 0
02:41:40.955 -> ID: 322, Data: 0
02:41:41.023 -> ID: 248, Data: 0
02:41:41.159 -> ID: 322, Data: 0
02:41:41.226 -> ID: 322, Data: 0
02:41:41.292 -> ID: 322, Data: 0
02:41:41.360 -> ID: 322, Data: 0
02:41:41.436 -> ID: 322, Data: 0
02:41:41.504 -> ID: 64, Data: 0
02:41:41.578 -> ID: 322, Data: 0
02:41:41.647 -> ID: 322, Data: 0
02:41:41.715 -> ID: 322, Data: 0
02:41:41.857 -> ID: 322, Data: 0
02:41:41.924 -> ID: 322, Data: 0```


Agora descobir a parir do dicionário de dados quais os comandos que podemos usar neste painel.
