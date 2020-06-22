/*
  Programa para executar os comandos da sinalizacao do BREletrico
  Placa Arduino Mega instalada em baixo do painel do veiculo

  A sinalizacao dos comandos no LCD sao:
  - setaDireitaOn();
  - setaDireitaOff();
  - setaEsquerdaOn();
  - setaEsquerdaOff();
  - farolBaixo();
  - farolAlto();
  - freioDeMao();
  - bateria();

  This example code is in the public domain.
  
  2018/09/15 - Transferido para Servidor Raspberry no carro
               Tela de inicializacao
               Ainda fala implementar o CAN e o Audio beep

*/


#include "U8glib.h"
#include "MsTimer2.h"

char versao[10]="15set18";

U8GLIB_ST7920_128X64_4X u8g(13, 12, 11);
// enable = white = 13
// r/w = gray = 12
// rs - blue = 11

const int PinFarolBaixa = 34;   // fio preto
const int PinFarolAlta = 32;    // fio marron 
const int PinLanterna = 30;     // fio amarela
const int PinLuzDeFreio = 28;   // fio laranja 
const int PinLuzRe = 26;        // fio verde 
const int PinSetaDireita = 24;  // fio azul  
const int PinSetaEquerda = 22;  // fio vermelho

const int InLanterna = 53;
const int InFarolBaixo = 51;
const int InFarolAlto = 49;

const int InSetaEsquerda = 47;
const int InSetaDireita = 45;
const int InPiscaAlerta = 43; 
const int InFreioDeMao = 41;
const int InLuzDeFreio = 39;
const int InLuzRe = 37;

boolean BpiscaAlerta = 0;
boolean BsetaEsquerda = 0;
boolean BsetaDireita = 0;
boolean BfarolBaixo = 0;
boolean BfarolAlto = 0;
boolean Blanterna = 0;
boolean BfreioDeMao = 0;
boolean BluzDeFreio = 0;
boolean BluzRe = 0;

boolean pisca_on;


void LigaFarolBaixo() {
  boolean farol[][20] {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
  // farol baixo
  int baixo = 2;
  int dX = 50;
  int dY = 40;
  for ( int x = 0; x < 13; x++)
    for ( int y = 0; y < 20; y++)
      if (farol[y][x] == 1)
        u8g.drawPixel(x + dX + 10, y + dY);
  u8g.drawLine(1 + dX, 1 + dY + baixo, 9 + dX, 1 + dY);
  u8g.drawLine(1 + dX, 5 + dY + baixo, 8 + dX, 5 + dY);
  u8g.drawLine(1 + dX, 10 + dY + baixo, 7 + dX, 10 + dY);
  u8g.drawLine(1 + dX, 15 + dY + baixo, 8 + dX, 15 + dY);
  u8g.drawLine(1 + dX, 19 + dY + baixo, 9 + dX, 19 + dY);
}

void LigaFarolAlto() {
  boolean farol[][20] {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  }; 
  // farol alto
  int dX = 50;
  int dY = 40;
  for ( int x = 0; x < 13; x++)
    for ( int y = 0; y < 20; y++)
      if (farol[y][x] == 1)
        u8g.drawPixel(x + dX + 10, y + dY);
  u8g.drawLine(1 + dX, 1 + dY, 9 + dX, 1 + dY);
  u8g.drawLine(1 + dX, 5 + dY, 8 + dX, 5 + dY);
  u8g.drawLine(1 + dX, 10 + dY, 7 + dX, 10 + dY);
  u8g.drawLine(1 + dX, 15 + dY, 8 + dX, 15 + dY);
  u8g.drawLine(1 + dX, 19 + dY, 9 + dX, 19 + dY);
}


void SetaDireitaOn()
{
  int dX = 112;
  int dY = 20;
  u8g.drawTriangle(0 + dX, 0 + dY, 0 + dX, 20 + dY, 15 + dX, 10 + dY);
}

void SetaDireitaOff()
{
  int dX = 113;
  int dY = 20;
  u8g.drawLine(0 + dX, 0 + dY, 0 + dX, 20 + dY);
  u8g.drawLine(0 + dX, 0 + dY, 15 + dX, 10 + dY);
  u8g.drawLine(15 + dX, 10 + dY, 0 + dX, 20 + dY);
}

void SetaEsquerdaOn()
{
  int dX = 0;
  int dY = 20;
  u8g.drawTriangle(15 + dX, 0 + dY, 15 + dX, 20 + dY, 0 + dX, 10 + dY); // seta esquerda
}

void SetaEsquerdaOff()
{
  int dX = 0;
  int dY = 20;
  u8g.drawLine(15 + dX, 0 + dY, 15 + dX, 20 + dY);
  u8g.drawLine(15 + dX, 0 + dY, 0 + dX, 10 + dY);
  u8g.drawLine(0 + dX, 10 + dY, 15 + dX, 20 + dY);
}

void BaseDeTempo(void)
{
 pisca_on =! pisca_on;
}

void setup() {
  pinMode(PinSetaDireita, OUTPUT);
  pinMode(PinSetaEquerda, OUTPUT);
  pinMode(PinFarolBaixa, OUTPUT);
  pinMode(PinFarolAlta, OUTPUT);
  pinMode(PinLanterna, OUTPUT);
  pinMode(PinLuzDeFreio, OUTPUT);
  pinMode(PinLuzRe, OUTPUT);
  pinMode(InPiscaAlerta, INPUT); // pisca alerta
  pinMode(InSetaEsquerda, INPUT);// seta esquerda
  pinMode(InSetaDireita, INPUT); //seta direita 
  pinMode(InFarolBaixo, INPUT); // farol baixo
  pinMode(InFarolAlto, INPUT); // farol alto
  pinMode(InLanterna, INPUT); 
  pinMode(InFreioDeMao, INPUT);
  pinMode(InLuzRe,INPUT);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }  
  MsTimer2::set(500, BaseDeTempo);
  MsTimer2::start();
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("BREletrica CAN Luzes ");
  /*
  Essa parte foi incluido e ainda não foi testado..  15/09/2018 
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(20, 20, "BREletrico");      
    u8g.drawStr(30, 54, versao);
  } while (u8g.nextPage());
  delay(3000);
  
  */
  
}

void SequencialLuzes(void) {
  digitalWrite(PinSetaDireita, HIGH);  delay(1000); digitalWrite(PinSetaDireita, LOW);  delay(1000);
  digitalWrite(PinSetaEquerda, HIGH);  delay(1000); digitalWrite(PinSetaEquerda, LOW);  delay(1000);
  digitalWrite(PinFarolBaixa, HIGH);  delay(1000); digitalWrite(PinFarolBaixa, LOW); delay(1000);
  digitalWrite(PinFarolAlta, HIGH);  delay(1000); digitalWrite(PinFarolAlta, LOW); delay(1000);
  digitalWrite(PinLanterna, HIGH);  delay(1000); digitalWrite(PinLanterna, LOW); delay(1000);
  digitalWrite(PinLuzDeFreio, HIGH);  delay(1000); digitalWrite(PinLuzDeFreio, LOW);  delay(1000);
  digitalWrite(PinLuzRe, HIGH);  delay(1000);  digitalWrite(PinLuzRe, LOW);  delay(1000);
}

void Leia_Chaves(void) {
  
   byte x; 
   BpiscaAlerta = digitalRead(InPiscaAlerta);
   BsetaEsquerda = digitalRead(InSetaEsquerda);
   BsetaDireita = digitalRead(InSetaDireita);
   BfarolBaixo = digitalRead(InFarolBaixo);
   BfarolAlto = digitalRead(InFarolAlto);
   Blanterna = digitalRead(InLanterna);
   BfreioDeMao = digitalRead(InFreioDeMao);
   BluzDeFreio = digitalRead(InLuzDeFreio);  

    
   x= BpiscaAlerta*B10000000+BsetaEsquerda*B01000000+BsetaDireita*B00100000+BfarolBaixo*B00010000+BfarolAlto*B00001000+Blanterna*B00000100+BfreioDeMao*B00000010+BluzDeFreio*B00000001;
    
   Serial.print(x,BIN);
   Serial.println(" Entradas ");
  /* char inChar;
  if (Serial.available()) {
   inChar = (char)Serial.read();
   Serial.print(" Valor = ");Serial.print(inChar);
   switch (inChar){
    case '0':  BpiscaAlerta = 0; //digitalRead(InPiscaAlerta);
               BsetaEsquerda = 0; // digitalRead(InSetaEsquerda);
               BsetaDireita = 0; //digitalRead(InSetaDireita);
               BfarolBaixo = 0; // digitalRead(InFarolBaixo);
               BfarolAlto = 0; //digitalRead(InFarolAlto);
               Blanterna = 0;  //digitalRead(InLuzAlta);
               BfreioDeMao = 0; //digitalRead(InFreioDeMao);
               BluzDeFreio = 0; //digitalRead(InLuzDeFreio);
               break;
    case '1':  BpiscaAlerta = 1; break; // Blaterna
    case '2':  BfarolBaixo = 1; break; //setaEsquerda = 1; break;
    case '3':  BsetaDireita = 1; break;
    case '4':  BsetaEsquerda = 1; break; //farolBaixo = 1; break;
    case '5':  BfarolAlto = 1; break;
    case '6':  Blanterna = 1;  break;
    case '7':  BfreioDeMao = 1; break;
    case '8':  BluzDeFreio = 1; break;
    default: break;
    }
  } */
}

void draw() {
  // graphic commands to redraw the complete screen should be placed here  
  // comandos simultaneamento no LCD e na Sinalizacao  
  if (BfarolBaixo) {LigaFarolBaixo(); digitalWrite(PinFarolBaixa, HIGH); } else digitalWrite(PinFarolBaixa, LOW);
  if (BfarolAlto) {LigaFarolAlto(); digitalWrite(PinFarolAlta, HIGH);  } else digitalWrite(PinFarolAlta, LOW);  
  if (Blanterna) { digitalWrite(PinLanterna, HIGH); } else { digitalWrite(PinLanterna, LOW); }
  if (BluzDeFreio) { digitalWrite(PinLuzDeFreio, HIGH); } else { digitalWrite(PinLuzDeFreio, HIGH);}
  if (BluzRe) { digitalWrite(PinLuzRe, HIGH);} else { digitalWrite(PinLuzRe, LOW); }
  
  // comandos somente no LCD
  if (BfreioDeMao) {;}

  // comandos temporizados no LCD e na sinalizacao
  if (BpiscaAlerta) 
  { 
   if (pisca_on) 
   {
    SetaEsquerdaOn();  SetaDireitaOn(); digitalWrite(PinSetaEquerda, HIGH); digitalWrite(PinSetaDireita, HIGH); }
    else 
   { 
    SetaEsquerdaOff(); SetaDireitaOff();digitalWrite(PinSetaEquerda, LOW); digitalWrite(PinSetaDireita, LOW);}
  }
   else {SetaEsquerdaOff(); SetaDireitaOff();digitalWrite(PinSetaEquerda, LOW); digitalWrite(PinSetaDireita, LOW);}
     
  if (BsetaEsquerda) 
  { 
    if (pisca_on) {SetaEsquerdaOn(); digitalWrite(PinSetaEquerda, HIGH); } else { SetaEsquerdaOff(); digitalWrite(PinSetaEquerda, LOW);}
  } 
   else  { SetaEsquerdaOff(); digitalWrite(PinSetaEquerda, LOW);}
  if (BsetaDireita) 
  { 
    if (pisca_on) {SetaDireitaOn();digitalWrite(PinSetaDireita, HIGH); } else { SetaDireitaOff(); digitalWrite(PinSetaDireita, LOW);} 
  } else { SetaDireitaOff(); digitalWrite(PinSetaDireita, LOW);}
}

void loop() {
  // SequencialLuzes();   //
  Leia_Chaves();
  u8g.firstPage();
  do {
    draw();
  } while ( u8g.nextPage() );
}
