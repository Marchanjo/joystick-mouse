//Sistema 05
//Um joystick como mouse
//o outro com botão2(esq) botão1(dir) Cursor up (cima) Cursor down (baixo)


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

const int VERT2 = 3; //joy analog bco
const int HORIZ2 = 4; //joy analog cnz
const int SEL2 = 6; //joy digital mrn
int vertical, horizontal, select;//joy
int vertical2, horizontal2, select2;//joy
//int vert;
//const static uint8_t bt_txdPin = 0;
//const static uint8_t bt_rxdPin = 1;
//const static uint8_t bt_dtrPin = 6;//4;
//const static uint8_t bt_rstPin = 5;

//00:11:12:06:03:59 linvor 1234 meu Bluetooth da China (sem trocar firmware não serve como mouse

int x,y;
int x2,y2;
boolean button1,button2,button3;

boolean mouseRefresh;
void mouseStep(void);
void mouseStep2(void);
int joystickSteperMouse(int value);

void setup()
  {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
   
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  
  pinMode(SEL,INPUT);//joy
  pinMode(SEL2,INPUT);//joy
  
  digitalWrite(redLed, HIGH);
  delay(500);
  digitalWrite(greenLed, HIGH);
  delay(500);
  digitalWrite(blueLed, HIGH);   
  delay(500);
  digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);
   
  Serial.begin(115200);//tem que ser a velocidade certa
  
  button1=false;//inicia o botão1 como aberto
  button2=false;//inicia o botão2 como aberto
  button3=false;//inicia o botão3 como aberto
  }
 //para clicar e arrastar trate o clique em vários loops 
void loop()
  {
  digitalWrite(redLed, LOW );digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);
  vertical = analogRead(VERT); //joy will be 0-1023 
  horizontal = analogRead(HORIZ); //joy will be 0-1023
  vertical2 = analogRead(VERT2); //joy will be 0-1023 
  horizontal2 = analogRead(HORIZ2); //joy will be 0-1023
  
  //select = digitalRead(SEL); //joy will be HIGH (1) if not pressed, and LOW (0) if pressed  
    
  //if((digitalRead(bt1)==0)&&(digitalRead(bt2)==0)) {digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);}
  //if((digitalRead(bt1)==0)&&(digitalRead(bt2)==1)) {digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);}
  //if((digitalRead(bt1)==1)&&(digitalRead(bt2)==0)) {digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);}
  //if((digitalRead(bt1)==1)&&(digitalRead(bt2)==1)) {digitalWrite(redLed, LOW);digitalWrite(greenLed, HIGH);digitalWrite(blueLed, LOW);}
  
  //analogWrite(redLed, vertical/4);
  //analogWrite(blueLed, horizontal/4);
  
  mouseRefresh=false;
  x=joystickSteperMouse(horizontal);
  y=joystickSteperMouse(vertical);
  //vertical2=-vertical2;
//horizontal2=-horizontal2;   
 
  if((x!=0)||(y!=0)) mouseRefresh=true;
  //botão acionado
  //if((digitalRead(SEL)==0)&&(button1==false)) {button1=true;mouseRefresh=true;}//manda a informação de botão acionado uma vez
  if((horizontal2>800)&&(button2==false)) {button2=true;mouseRefresh=true;}//manda a informação de botão acionado uma vez
  if((horizontal2<200)&&(button1==false)) {button1=true;mouseRefresh=true;}//manda a informação de botão acionado uma vez
  //botão aberto
  //if((digitalRead(SEL)==1)&&(button1==true)) {button1=false;mouseRefresh=true;}//manda a informação de botão levantado uma vez
  if((horizontal2<=800)&&(button2==true)) {button2=false;mouseRefresh=true;}//manda a informação de botão levantado uma vez
  if((horizontal2>=200)&&(button1==true)) {button1=false;mouseRefresh=true;}//manda a informação de botão levantado uma vez
  
  
  if(mouseRefresh) {mouseStep();digitalWrite(redLed, HIGH );digitalWrite(greenLed, HIGH);digitalWrite(blueLed, HIGH);}

  //estava sendo acionado de maneira errada, por isso aumentei a zona
  if(vertical2>800){Serial.write(0x80);delay(40);}
  if(vertical2<200){Serial.write(0x82);delay(40);}

/*
  if(vertical2>600){Serial.write(0x8D);delay(20);}
  if(vertical2<400){Serial.write(0x8B);delay(20);}
  if(horizontal2>600){Serial.write(0x8C);delay(20);}
  if(horizontal2<400){Serial.write(0x8E);delay(20);}
 */ 


//Page up e page down para simular o scroll up e scroll down
  if(digitalRead(bt1)==0)
    {
    int value=0x00;
    Serial.write(0x9F);
    Serial.write(0x0a);
    Serial.write(0xa1);
    Serial.write(0x01);
    Serial.write(value);//(0x01);//Modifier 0x01 parece ser o Control
    Serial.write(value);
    Serial.write(0x51);//(0x04);//a
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
       
    delay(20);
    
    Serial.write(0x9F);
    Serial.write(0x0a);
    Serial.write(0xa1);
    Serial.write(0x01);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    }
  
  if(digitalRead(bt2)==0) 
    {
    int value=0x00;
    Serial.write(0x9F);
    Serial.write(0x0a);
    Serial.write(0xa1);
    Serial.write(0x01);
    Serial.write(value);//(0x01);//Modifier 0x01 parece ser o Control
    Serial.write(value);
    Serial.write(0x52);//(0x04);//a
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
       
    delay(20);
    
    Serial.write(0x9F);
    Serial.write(0x0a);
    Serial.write(0xa1);
    Serial.write(0x01);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    }
    
  /*vertical2=-vertical2;
  horizontal2=-horizontal2;
  if(vertical2>600){Serial.write(0x8D);delay(30);}
  if(vertical2<400){Serial.write(0x8B);delay(30);}
  if(horizontal2>600){Serial.write(0x8C);delay(30);}
  if(horizontal2<400){Serial.write(0x8E);delay(30);}*/
  
  //if(digitalRead(SEL)==0){Serial.write(0x8A);delay(20);Serial.write(0x8F);delay(200);Serial.write(0x8A);delay(20);}
  
 /* //Teste com dados brutos
  if(digitalRead(bt1)==0)//Raw data 159  9F  
    {
    int value=0x00;
    Serial.write(0x9F);
    Serial.write(0x05);
    Serial.write(0xa1);
    Serial.write(0x02);
    Serial.write(value);
    Serial.write(0x01);
    Serial.write(value);
    delay(20);
    }]*/


  
 /* if(digitalRead(bt1)==0)
    {
    digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);
    
    Serial.write(0x8B);//, 8); up
    delay(30);
    }*/
    
  
    
  }
  

int joystickSteperMouse(int value)
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




void mouseStep(void)
  {
  int value=0x00;
  Serial.write(0x9F);
  Serial.write(0x05);
  Serial.write(0xa1);
  Serial.write(0x02);
  
  if((!button1)&&(!button2)&&(!button3)) Serial.write(value);
  if(button1) Serial.write(0x01);
  if(button2) Serial.write(0x02);
  if(button3) Serial.write(0x03);
  
  Serial.write(x);
  Serial.write(y);
  delay(20);
  }   

void mouseStep2(void)
  {
  int value=0x00;
  Serial.write(0x9F);
  Serial.write(0x05);
  Serial.write(0xa1);
  Serial.write(0x02);
  
  if((!button1)&&(!button2)&&(!button3)) Serial.write(value);
  if(button1) Serial.write(0x01);
  if(button2) Serial.write(0x02);
  if(button3) Serial.write(0x03);
  
  Serial.write(x2);
  Serial.write(y2);
  delay(20);
  }  
