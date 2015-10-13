
#define TB_DIR_LEFT 3
#define TB_DIR_RIGHT 5
#define TB_DIR_UP 7
#define TB_DIR_DOWN 8

#define TB_CMD 11

int led = 13;
//int bt1 = 9;
bool active=true;

/* TrackBall */
struct TBState
{
	/* current state */
	int up, down, left, right;
	
	/* cumulated state */
	int c_up, c_down, c_left, c_right;
} tbState;

void initTB()
{
	pinMode(TB_DIR_UP, INPUT);
	pinMode(TB_DIR_DOWN, INPUT);
	pinMode(TB_DIR_LEFT, INPUT);
	pinMode(TB_DIR_RIGHT, INPUT);
        pinMode(TB_CMD, INPUT);
	
	//pinMode(TB_LED_BLUE, OUTPUT);
	//pinMode(TB_LED_RED, OUTPUT);
	//pinMode(TB_LED_GREEN, OUTPUT);
	//pinMode(TB_LED_WHITE, OUTPUT);
	
	tbState.up = digitalRead(TB_DIR_UP);
	tbState.down = digitalRead(TB_DIR_DOWN);
	tbState.left = digitalRead(TB_DIR_LEFT);
	tbState.right = digitalRead(TB_DIR_RIGHT);
	
	//digitalWrite(TB_LED_WHITE, HIGH);
}

void pollTB(bool sendEvents=true)
{
	struct TBState newState = tbState;
	const int threshold = 1;//3
	bool reset = false;
	
	newState.up = digitalRead(TB_DIR_UP);
	newState.down = digitalRead(TB_DIR_DOWN);
	newState.left = digitalRead(TB_DIR_LEFT);
	newState.right = digitalRead(TB_DIR_RIGHT);
        
	
	//struct event tb_event;
	//tb_event.type = TRACKBALL_MOVED;
	if (newState.up != tbState.up) {
                newState.c_up++;
		if (newState.c_up > threshold)
		{        
                        Serial.print("UP ");
                        reset = true;
		}
	}
	if (newState.down != tbState.down) {
		newState.c_down++;
		if (newState.c_down > threshold)
		{
			Serial.print("DOWN ");
                        reset = true;
		}
	}
	if (newState.left != tbState.left) {
		newState.c_left++;
		if (newState.c_left > threshold)
		{
			Serial.print("LEFT ");
                        reset = true;
		}
	}
	if (newState.right != tbState.right) {
		newState.c_right++;
		if (newState.c_right > threshold)
		{
  			Serial.print("RIGHT ");
                        reset = true;
		}
	}
	
	if (reset)
	{
		newState.c_up = 0;
		newState.c_down = 0;
		newState.c_left = 0;
		newState.c_right = 0;
                Serial.print(".\n");
	}
		
	tbState = newState;
}


void setup() {        
  Serial.begin(9600);	  
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    
  initTB(); 
  
}


void loop() {
  /* the track ball */
  pollTB();
  
  if(digitalRead(TB_CMD)==0)
    {
    Serial.print("BUTTON\n");
    if(active) active=false;
    else active=true;
    delay(300);
    }
    
  if(active)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
   
}
