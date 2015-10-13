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

//const static uint8_t bt_txdPin = 0;
//const static uint8_t bt_rxdPin = 1;
//const static uint8_t bt_dtrPin = 6;//4;
//const static uint8_t bt_rstPin = 5;

//00:11:12:06:03:59 linvor 1234 meu Bluetooth da China

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
   
  Serial.begin(115200);//tem que ser a velocidade certa
  }
 //para clicar e arrastar trate o clique em vários loops 
void loop()
  {
  vertical = analogRead(VERT); //joy will be 0-1023 
  horizontal = analogRead(HORIZ); //joy will be 0-1023
  //select = digitalRead(SEL); //joy will be HIGH (1) if not pressed, and LOW (0) if pressed  
    
  if((digitalRead(bt1)==0)&&(digitalRead(bt2)==0)) {digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);}
  //if((digitalRead(bt1)==0)&&(digitalRead(bt2)==1)) {digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);}
  //if((digitalRead(bt1)==1)&&(digitalRead(bt2)==0)) {digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);}
  if((digitalRead(bt1)==1)&&(digitalRead(bt2)==1)) {digitalWrite(redLed, LOW);digitalWrite(greenLed, HIGH);digitalWrite(blueLed, LOW);}
  
  //analogWrite(redLed, vertical/4);
  //analogWrite(blueLed, horizontal/4);
  
  if(vertical>600){Serial.write(0x8D);delay(30);}
  if(vertical<400){Serial.write(0x8B);delay(30);}
  if(horizontal>600){Serial.write(0x8C);delay(30);}
  if(horizontal<400){Serial.write(0x8E);delay(30);}
  if(digitalRead(SEL)==0){Serial.write(0x8A);delay(20);Serial.write(0x8F);delay(200);Serial.write(0x8A);delay(20);}
  
  //Teste com dados brutos
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
    }


  
 /* if(digitalRead(bt1)==0)
    {
    digitalWrite(redLed, LOW);digitalWrite(greenLed, LOW);digitalWrite(blueLed, HIGH);
    
    Serial.write(0x8B);//, 8); up
    delay(30);
    }*/
    
  if(digitalRead(bt2)==0)
    {
    digitalWrite(redLed, HIGH);digitalWrite(greenLed, LOW);digitalWrite(blueLed, LOW);
  
    Serial.write(0x8D);//, 8); down
    delay(30);
    }
    
  }
  

 

