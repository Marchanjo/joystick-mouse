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

//joy vcc=5v 
const int VERT = 0; //joy analog
const int HORIZ = 1; //joy analog
const int SEL = 8; //joy digital
int vertical, horizontal, select;//joy
int vert;
//const static uint8_t bt_txdPin = 0;
//const static uint8_t bt_rxdPin = 1;
//const static uint8_t bt_dtrPin = 6;//4;
//const static uint8_t bt_rstPin = 5;

//00:11:12:06:03:59 linvor 1234 meu Bluetooth da China (sem trocar firmware não serve como mouse

int x,y;
boolean button1;
boolean mouseRefresh;
void mouseStep(void);
int joystickSteperMouse(int value);

void setup()
  {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
   
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  
  pinMode(SEL,INPUT);//joy
  
  digitalWrite(redLed, HIGH);
  delay(500);
  digitalWrite(greenLed, HIGH);
  delay(500);
  digitalWrite(blueLed, HIGH);   
  delay(500);
  digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);
   
  Serial.begin(115200);//tem que ser a velocidade certa
  
  button1=false;//inicia o botão1 como aberto
  }
 //para clicar e arrastar trate o clique em vários loops 
void loop()
  {
  digitalWrite(redLed, LOW );digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);
  vertical = analogRead(VERT); //joy will be 0-1023 
  horizontal = analogRead(HORIZ); //joy will be 0-1023
  //select = digitalRead(SEL); //joy will be HIGH (1) if not pressed, and LOW (0) if pressed  
    
  //if((digitalRead(bt1)==0)&&(digitalRead(bt2)==0)) {digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);}
  //if((digitalRead(bt1)==0)&&(digitalRead(bt2)==1)) {digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);}
  //if((digitalRead(bt1)==1)&&(digitalRead(bt2)==0)) {digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);}
  //if((digitalRead(bt1)==1)&&(digitalRead(bt2)==1)) {digitalWrite(redLed, LOW);digitalWrite(greenLed, HIGH);digitalWrite(blueLed, LOW);}
  
  //analogWrite(redLed, vertical/4);
  //analogWrite(blueLed, horizontal/4);
  
  mouseRefresh=false;
  x=0x00; 
  y=0x00;
  x=(horizontal-511)/64;
  y=(vertical-511) /64;
  //x=joystickSteperMouse(horizontal);
  //y=joystickSteperMouse(vertical);
     
 /* vert=vertical-511;
  if(vert<=-480) y=-17;
  if((vert>-480)&&(vert<=-416)) y=-12;
  if((vert>-416)&&(vert<=-352)) y=-8;
  if((vert>-352)&&(vert<=-288)) y=-5;
  if((vert>-288)&&(vert<=-224)) y=-3;
  if((vert>-224)&&(vert<=-160)) y=-2;
  if((vert>-160)&&(vert<=-96)) y=-1;
  if((vert>-96)&&(vert<=-32)) if(y==-1) y=0; else y=-1;
  if((vert>=-32)&&(vert<=32)) y=0;//dead zone 
  if((vert>32)&&(vert<=96)) if(y==1) y=0; else y=1;
  if((vert>96)&&(vert<=160)) y=1;
  if((vert>160)&&(vert<=224)) y=2;
  if((vert>224)&&(vert<=288)) y=3;
  if((vert>288)&&(vert<=352)) y=5;
  if((vert>352)&&(vert<=416)) y=8;
  if((vert>416)&&(vert<=480)) y=12;
  if(vert>480) y=17;*/
  
  if((x!=0)||(y!=0)) mouseRefresh=true;
  //botão1 acionado
  if((digitalRead(SEL)==0)&&(button1==false)) {button1=true;mouseRefresh=true;}//manda a informação de botão acionado uma vez
  //botão1 aberto
  if((digitalRead(SEL)==1)&&(button1==true)) {button1=false;mouseRefresh=true;}//manda a informação de botão levantado uma vez
  
  if(mouseRefresh) {mouseStep();digitalWrite(redLed, HIGH );digitalWrite(greenLed, HIGH);digitalWrite(blueLed, HIGH);}


//Page up e page down para simular o scroll up e scroll down
  if(digitalRead(bt1)==0)
    {
    Serial.write(0x82);//Cursor down(0x89);//page down
    delay(20);//delay(300);//para page down
    }
  
  if(digitalRead(bt2)==0) 
    {
    //Serial.write(0x80);//Cursor up//(0x88);//page up
    //delay(20);//delay(300);//para page up
    int value=0x00;
    Serial.write(0x9F);
    Serial.write(0x05);
    Serial.write(0xa1);
    Serial.write(0x03);
    Serial.write(value);
    Serial.write(value);
    Serial.write(0x20);
    delay(20);
    Serial.write(0x9F);
    Serial.write(0x05);
    Serial.write(0xa1);
    Serial.write(0x03);
    Serial.write(value);
    Serial.write(value);
    Serial.write(value);
    }
    
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
  value=value-511;
  if(value<=-480) retorno=-13;
  if((value>-480)&&(value<=-416)) retorno=-9;
  if((value>-416)&&(value<=-352)) retorno=-6;
  if((value>-352)&&(value<=-288)) retorno=-4;
  if((value>-288)&&(value<=-224)) retorno=-3;
  if((value>-224)&&(value<=-160)) retorno=-2;
  if((value>-160)&&(value<=-96)) retorno=-1;
  if((value>-96)&&(value<=-32)) if(retorno==-1) retorno=0; else retorno=-1;//equivale a -0,5
  if((value>=-32)&&(value<=32)) retorno=0;//dead zone 
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
  if(button1) Serial.write(0x01);
  else Serial.write(value);
  Serial.write(x);
  Serial.write(y);
  delay(20);
  }   

