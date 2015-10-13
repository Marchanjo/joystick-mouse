//Sistema 10 - Joystick somente de movimento - USED During the tests
//mesmo que o 09 com Roving RN-42 HID somente como joystick do movimento do mouse HeadSet05
//comentei as linhas do segundo joystick com //test single joy//
//curva 1 do código (que é a curva 4 da documentação) está com o dead zone maior 45 ao inves de 32.

// 

//Um joystick como mouse
//o outro com botão2(esq) botão1(dir) Wheel up (cima) Wheel down (baixo) diagonal (up-right) com clicklock}
//Botão 2 mais fácil de acionar assimétrico, com limiar em 620 ao invés de 800
//
//Whell
//
//Clicklock no canto superior direito do joystick da esquerda (o joystick que atua como chaves)
//botão 1 e 2 destravam o clicklock
//
//em mouseStep o button1 ficou por último (prioridade em caso de acionamento de dois botões)
//
//btn 1 e 2 mudam a curva do joystick para avaliar a curva mais efetiva nos testes da Fitts Law



//Comandos que configuraram o módulo:
//$$$				(modo de comandos)
//ST,255			(desativa timer para poder enviar comandos por mais de 60s)
//SF,1 				(restaura configurações de fábrica)
//S-,RN42HID-Mouse	(muda o nome para RV42HID-MOUSE-xxxx 4 últimos dígitos do MAC address do módulo )
//SH,0220			(configura como mouse)
//S~,6				(ativa profile HID)
//SM,0				(Modo Slave, quem inicia a comunicação é o computador)
//R,1 				(Reboot)




//0x80 128 Teclado Cursor up
//0x82 130 Teclado Cursor down

//0x88 136  Teclado Page up
//0x89 137  Teclado Page down



//0x8A	138	Mouse buttons up
//0x8B	139	Mouse up (10px)
//0x8C	140	Mouse right (10px)
//0x8D	141	Mouse down (10px)
//0x8E	142	Mouse left (10px)
//0x8F	143	Mouse button 1 (first clear with 138)
//0x90	144	Mouse button 2 (first clear with 138)
//0x91	145	Mouse button 3 (first clear with 138)

int redLed = 11;   
int greenLed = 10;
int blueLed = 9;
int bt1 = 4;
int bt2 = 7;

//joy vcc=5v vml
const int VERT = 0; //joy analog lrj
const int HORIZ = 1; //joy analog amr
const int SEL = 8; //joy digital vrd

//test single joy//const int VERT2 = 3; //joy analog bco
//test single joy//const int HORIZ2 = 4; //joy analog cnz
//test single joy//const int SEL2 = 6; //joy digital mrn
int vertical, horizontal, select;//joy
//test single joy//int vertical2, horizontal2, select2;//joy2

//int vert;
//const static uint8_t bt_txdPin = 0;
//const static uint8_t bt_rxdPin = 1;
//const static uint8_t bt_dtrPin = 6;//4;
//const static uint8_t bt_rstPin = 5;

//00:11:12:06:03:59 linvor 1234 meu Bluetooth da China (sem trocar firmware não serve como mouse

int x,y;
//test single joy//int x2,y2;
int wheel;
boolean button1,button2,button3;
boolean button1ClickLock;
boolean deadZonePass;

boolean mouseRefresh;
void mouseClear(void);
void mouseStep(void);
void mouseStep2(void);
void readData(void);
int joystickSteperMouse0(int value);
int joystickSteperMouse1(int value);
int joystickSteperMouse2(int value);
int curva=1;//Curva 4 a mais lenta e melhor

//bool repairing = true;

void setup()
  {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
   
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  
  pinMode(SEL,INPUT);//joy
  //test single joy//pinMode(SEL2,INPUT);//joy
  
  
  Serial.begin(115200);//tem que ser a velocidade certa
  
  digitalWrite(redLed, HIGH);
  delay(500);
  digitalWrite(greenLed, HIGH);
  delay(500);
  digitalWrite(blueLed, HIGH);   
  delay(500);
  
     
  digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);
   
  
  delay(500);
  
  
  digitalWrite(greenLed, HIGH);
  Serial.print("$$$");//<<<<<<<<<< Modo de comandos
  readData();

  Serial.println("C");//<<<<<<<<<<< Connect immediate to stored remote address
  readData();
  digitalWrite(greenLed, LOW);  
  
  
  wheel=0;  
  button1=false;//inicia o botão1 como aberto
  button2=false;//inicia o botão2 como aberto
  button3=false;//inicia o botão3 como aberto
  button1ClickLock=false;
  deadZonePass=false;
  }
 
 void readData(void) 
   {
   while(!Serial.available());
   delay(200);
   while(Serial.available()) Serial.read();
   delay(200);
   } 
 
void loop()
  {
  vertical = analogRead(VERT); //joy will be 0-1023 
  horizontal = analogRead(HORIZ); //joy will be 0-1023
  //test single joy// vertical2 = analogRead(VERT2); //joy will be 0-1023 
  //test single joy//horizontal2 = analogRead(HORIZ2); //joy will be 0-1023
  
  if(digitalRead(bt1)==0)
    {
    curva++;
    if(curva>2) curva=0; 
    delay(500);
    }
  
  //test single joy//if(digitalRead(bt2)==0) 
  //test single joy//  {
  //test single joy//  curva--;
  //test single joy//  if(curva<0) curva=2;
  //test single joy//  delay(500);
  //test single joy//  }
    
  if(curva==0) {x=joystickSteperMouse0(horizontal); y=joystickSteperMouse0(vertical);digitalWrite(redLed, HIGH );digitalWrite(greenLed, LOW);}
  if(curva==1) {x=joystickSteperMouse1(horizontal); y=joystickSteperMouse1(vertical);digitalWrite(redLed, LOW );digitalWrite(greenLed, HIGH);}//Curva4 
  if(curva==2) {x=joystickSteperMouse2(horizontal); y=joystickSteperMouse2(vertical);digitalWrite(redLed, HIGH );digitalWrite(greenLed, HIGH);}
   

  mouseRefresh=false;
  if((x!=0)||(y!=0)) mouseRefresh=true;
  
  /* //test single joy//
  
   // Wheel Up
  if((horizontal2>424)&&(horizontal2<600)&&(vertical2>800)) 
    {wheel=1;
    mouseRefresh=true;
    delay(100);}//up //digitalWrite(greenLed, HIGH );digitalWrite(redLed, LOW);digitalWrite(blueLed, LOW);
  
  // Wheel Down
  if((horizontal2>424)&&(horizontal2<600)&&(vertical2<224)) 
    {wheel=-1;
    mouseRefresh=true;
    delay(100);}//down //digitalWrite(redLed, HIGH);digitalWrite(blueLed, HIGH );digitalWrite(greenLed, LOW);
  
  
    
  //Click Botão 1 - destrava o Click Lock do botão 1
  if((horizontal2<224)&&(vertical2>424)&&(vertical2<600)&&((button1==false)||(button1ClickLock==true)) )
    {
    if(button1ClickLock==true)//destrava Click Lock do botão 1
        {button1=false;
         button1ClickLock=false;
         deadZonePass=false;
         mouseRefresh=true;
         digitalWrite(blueLed, LOW);}
    
    button1=true;
    button2=false;//Importante <<<<<<<<<<<<<
    button3=false;//Importante <<<<<<<<<<<<<
    mouseRefresh=true;
    }//right //digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW );digitalWrite(blueLed, LOW);
 
  //Click Botão 2  -  destrava o Click Lock do botão 1
  if((horizontal2>600)&&(vertical2>424)&&(vertical2<600)&&(button2==false)) 
      {
      if(button1ClickLock==true)//destrava Click Lock do botão 1
        {mouseClear();//desativa tudo, pois o Modulo trava se transitar do botão 1 para o 2 sem antes desativá-lo
         button1=false;
         button1ClickLock=false;
         deadZonePass=false;
         mouseRefresh=true;
         digitalWrite(blueLed, LOW);}
         
      button2=true; 
      button1=false;//Importante <<<<<<<<<<<<<
      button3=false;//Importante <<<<<<<<<<<<<
      mouseRefresh=true;
      }//left //digitalWrite(blueLed, HIGH);digitalWrite(redLed, LOW );digitalWrite(greenLed, LOW);
  
  //ClickLock
   if((horizontal2<424)&&(vertical2>600)) 
     {
     if((deadZonePass==true)&&(button1ClickLock==false))//entra somente na primeira vez 
       {button1=true;
       button2=false;//Importante <<<<<<<<<<<<<
       button3=false;//Importante <<<<<<<<<<<<<
       button1ClickLock=true;
       deadZonePass=false;
       mouseRefresh=true;
       digitalWrite(blueLed, HIGH);}//up  right - Ativa ButtonClickLock //digitalWrite(greenLed, HIGH);digitalWrite(redLed, HIGH);digitalWrite(blueLed, LOW);
     
     if((deadZonePass==true)&&(button1ClickLock==true))//entra somente depois de passar pela deadZone
       {button1=false;
       button1ClickLock=false;
       deadZonePass=false;
       mouseRefresh=true;
       digitalWrite(blueLed, LOW);}//up  right - desativa ButtonClickLock //digitalWrite(greenLed, HIGH);digitalWrite(redLed, HIGH);digitalWrite(blueLed, LOW);
     }
  
  //if((horizontal2>=424)&&(horizontal2<=600)&&(button1==true)&&(vertical2>=424)&&(vertical2<=600)&&(button1ClickLock==true)) {deadZonePass=true;}//indica que passou pela dead zone após Button1ClickLock
  //if((horizontal2>=424)&&(horizontal2<=600)&&(vertical2>=424)&&(vertical2<=600) ) {deadZonePass=true;}//indica que passou pela dead zone após Button1ClickLock sem histerese
  
  //Dead Zone geral (limiar não pode ser o mesmo o usado para definir o click, sempre deve haver um gap para ocorrer a histerese)
  if((horizontal2>=428)&&(horizontal2<=596)&&(vertical2>=428)&&(vertical2<=598) ) 
      {
      deadZonePass=true;//indica que passou pela dead zone
      wheel=0;
      
      if ((button1==true)&&(button1ClickLock==false)) {button1=false;mouseRefresh=true;}//manda a informação de botão levantado uma vez
      
      if (button2==true) {button2=false;mouseRefresh=true;}//manda a informação de botão levantado uma vez
      
      if (button3==true) {button3=false;mouseRefresh=true;}//manda a informação de botão levantado uma vez
      }
  //test single joy//
  */
  
  if(mouseRefresh) {mouseStep();}//digitalWrite(redLed, HIGH );digitalWrite(greenLed, HIGH);}//digitalWrite(blueLed, HIGH);}
  }
  

int joystickSteperMouse0(int value)
  {
  int retorno;
  value=-(value-511);
  if(value<=-480) retorno=-13;
  if((value>-480)&&(value<=-416)) retorno=-9;
  if((value>-416)&&(value<=-352)) retorno=-6;
  if((value>-352)&&(value<=-288)) retorno=-4;
  if((value>-288)&&(value<=-224)) retorno=-3;
  if((value>-224)&&(value<=-160)) retorno=-2;
  if((value>-160)&&(value<=-96)) retorno=-1;
  if((value>-96)&&(value<=-32)) if(retorno==-1) retorno=0; else retorno=-1;//equivale a -0,5
  if((value>-32)&&(value<=32)) retorno=0;//dead zone 
  if((value>32)&&(value<=96)) if(retorno==1) retorno=0; else retorno=1;//equivale a 0,5
  if((value>96)&&(value<=160)) retorno=1;
  if((value>160)&&(value<=224)) retorno=2;
  if((value>224)&&(value<=288)) retorno=3;
  if((value>288)&&(value<=352)) retorno=4;
  if((value>352)&&(value<=416)) retorno=6;
  if((value>416)&&(value<=480)) retorno=9;
  if(value>480) retorno=13;
  return retorno;
  }
  
int joystickSteperMouse1(int value)//curva 4 mais suave e lenta que a 3
  {
  int retorno;
  int deadzone=45;
  value=-(value-511);
  if(value<=-480) retorno=-5;
  if((value>-480)&&(value<=-416)) retorno=-4;
  if((value>-416)&&(value<=-352)) retorno=-3;
  if((value>-352)&&(value<=-288)) retorno=-2;
  if((value>-288)&&(value<=-224)) retorno=-2;
  if((value>-224)&&(value<=-160)) retorno=-1;
  if((value>-160)&&(value<=-96)) retorno=-1;
  if((value>-96)&&(value<=-deadzone)) if(retorno==-1) retorno=0; else retorno=-1;//equivale a -0,5
  if((value>-deadzone)&&(value<=deadzone)) retorno=0;//dead zone maior que nas outras curvas aqui é 38 e nas outras é 32
  if((value>deadzone)&&(value<=96)) if(retorno==1) retorno=0; else retorno=1;//equivale a 0,5
  if((value>96)&&(value<=160)) retorno=1;
  if((value>160)&&(value<=224)) retorno=1;
  if((value>224)&&(value<=288)) retorno=2;
  if((value>288)&&(value<=352)) retorno=2;
  if((value>352)&&(value<=416)) retorno=3;
  if((value>416)&&(value<=480)) retorno=4;
  if(value>480) retorno=5;
  return retorno;
  }
  
int joystickSteperMouse2(int value)//curva 3 mais suave e lenta que a 0
  {
  int retorno;
  value=-(value-511);
  if(value<=-480) retorno=-9;
  if((value>-480)&&(value<=-416)) retorno=-7;
  if((value>-416)&&(value<=-352)) retorno=-5;
  if((value>-352)&&(value<=-288)) retorno=-4;
  if((value>-288)&&(value<=-224)) retorno=-3;
  if((value>-224)&&(value<=-160)) retorno=-2;
  if((value>-160)&&(value<=-96)) retorno=-1;
  if((value>-96)&&(value<=-32)) if(retorno==-1) retorno=0; else retorno=-1;//equivale a -0,5
  if((value>-32)&&(value<=32)) retorno=0;//dead zone 
  if((value>32)&&(value<=96)) if(retorno==1) retorno=0; else retorno=1;//equivale a 0,5
  if((value>96)&&(value<=160)) retorno=1;
  if((value>160)&&(value<=224)) retorno=2;
  if((value>224)&&(value<=288)) retorno=3;
  if((value>288)&&(value<=352)) retorno=4;
  if((value>352)&&(value<=416)) retorno=5;
  if((value>416)&&(value<=480)) retorno=7;
  if(value>480) retorno=9;
  return retorno;
  }


void mouseClear(void)
  {
  int value=0x00;
 
  Serial.write(0xFD);
  Serial.write(0x05);
  Serial.write(0x02);
  Serial.write(value);//botão
  Serial.write(value);//(x);
  Serial.write(value);//(y);
  Serial.write(value);//(wheel);
  
  delay(20);
  }
  

void mouseStep(void)
  {
  int value=0x00;
   
  Serial.write(0xFD);
  Serial.write(0x05);
  Serial.write(0x02);
  
  
  if((!button1)&&(!button2)&&(!button3)) Serial.write(value);
  if(button3) Serial.write(0x3);
  if(button2) Serial.write(0x2); 
  if(button1) Serial.write(0x1);//botão1 é prioritário
 
    
  Serial.write(x);
  Serial.write(y);
  Serial.write(wheel);
  delay(20);
  }   


