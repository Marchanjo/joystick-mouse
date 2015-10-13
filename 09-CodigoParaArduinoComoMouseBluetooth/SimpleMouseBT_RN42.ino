
int led = 13;

int bt1 = 4;
int bt2 = 5;
int bt3 = 6;
int bt4 = 7;
int bt5 = 8;
int bt6 = 9;
int bt7 = 10;
int bt8 = 11;

void readData(void);
void mouseSend(void);
void mouseClear(void);


void setup() {                
  pinMode(led, OUTPUT); 
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(bt3, INPUT);
  pinMode(bt4, INPUT);
  pinMode(bt5, INPUT);
  pinMode(bt6, INPUT);
  pinMode(bt7, INPUT);
  pinMode(bt8, INPUT);  
  
  digitalWrite(led, HIGH);
  Serial.begin(115200);//tem que ser a velocidade certa
 
  delay(500);
  Serial.print("$$$");//<<<<<<<<<< command mode
  readData();

  Serial.println("C");//<<<<<<<<<<< Connect immediate to stored remote address
  readData();
  digitalWrite(led, LOW);
}


void loop() {
   
  if(digitalRead(bt1)==0)
    {
    digitalWrite(led, HIGH);
    mouseClear();//necessary for button activation  
    mouseSend(1,0,0,0);
    delay(200);
    mouseClear();
    }
  if(digitalRead(bt2)==0)
    {
    digitalWrite(led, LOW);
    mouseClear();//necessary for button activation
    mouseSend(2,0,0,0);
    delay(200);
    mouseClear();
    }
  if(digitalRead(bt3)==0)
    {
    digitalWrite(led, HIGH);
    mouseSend(0,0,0,-1);   
    }
  if(digitalRead(bt4)==0)
    {
    digitalWrite(led, LOW);
    mouseSend(0,0,0,1);    
    }
  if(digitalRead(bt5)==0)
    {
    digitalWrite(led, HIGH);
    mouseSend(0,0,-10,0);    
    }
  if(digitalRead(bt6)==0)
    {
    digitalWrite(led, LOW);
    mouseSend(0,0,10,0);   
    }
  if(digitalRead(bt7)==0)
    {
    digitalWrite(led, HIGH);
    mouseSend(0,-10,0,0);   
    }
  if(digitalRead(bt8)==0)
    {
    digitalWrite(led, LOW); 
    mouseSend(0,10,0,0);  
    }
}


 void readData(void) 
   {
   while(!Serial.available());
   delay(200);
   while(Serial.available()) Serial.read();
   delay(200);
   }
   
void mouseSend(int button,int x, int y,int wheel)
  {
  int value=0x00;
 
  Serial.write(0xFD);
  Serial.write(0x05);
  Serial.write(0x02);
  Serial.write(button);//botão
  Serial.write(x);//(x);
  Serial.write(y);//(y);
  Serial.write(wheel);//(wheel);
  
  delay(20);
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
