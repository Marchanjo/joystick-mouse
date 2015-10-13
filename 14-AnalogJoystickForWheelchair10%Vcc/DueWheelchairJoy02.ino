//In (joystick) (0 a 1023) e out (1638 a 2457) metade de 4095 = 2047 sendo que 1638(-10% de vcc) e 2457(+10% vcc) padrão para joystick de cadeira de rodas


int led = 13;
int ana00,ana01,ana02;

int convertionADtoDA(int joy);

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 
  pinMode(DAC0, OUTPUT);
  pinMode(DAC1, OUTPUT);  
  analogWriteResolution(12);//0-4095 limite da arduino due (12 bits) //(10);//0-1023
  
  Serial.begin(115200);//tem que ser a velocidade certa
}

// the loop routine runs over and over again forever:
void loop() {
  ana00 = analogRead(0); //joy will be 0-1023 
  ana00 = 1023 - ana00;//invertendo um dos sinais
  ana01 = analogRead(1); //joy will be 0-1023
  ana02 = analogRead(2); //joy will be 0-1023
  
  Serial.print(" Analogico 00=");
  Serial.print(ana00);
  Serial.print(" - ");
  Serial.print(convertionADtoDA(ana00));
  Serial.print(" Analogico 01=");
  Serial.print(ana01);
  Serial.print(" - ");
  Serial.print(convertionADtoDA(ana01));
  Serial.print(" Analogico 02=");
  Serial.print(ana02);
  Serial.print("\n");
  
  

  analogWrite(DAC0,convertionADtoDA(ana00));
  analogWrite(DAC1,convertionADtoDA(ana01));
  /*
  if((ana00>600)||(ana01>600))
    {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    analogWrite(DAC0,4096);//vertical);2048
    analogWrite(DAC1,4096);//horizontal);
    }
  else
    {
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    analogWrite(DAC0,0);//vertical);2048
    analogWrite(DAC1,0);//horizontal);
    }*/
  delay(100);
}

int convertionADtoDA(int joy)
  {
   float in;
   float out;
   in=joy;
   //out=1843+(in*0.4);//joy (0 a 1023) e out (1843 a 2252) metade de 4095 = 2047 sendo que 1843(-10% da metade) e 2252(+10% da metade) padrão para joystick de cadeira de rodas
   out=1638+(in*0.8);//joy (0 a 1023) e out (1638 a 2457) metade de 4095 = 2047 sendo que 1638(-10% de vcc) e 2457(+10% vcc) padrão para joystick de cadeira de rodas
   return (int) out;    
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
