/**
* Halloween Cat Eyes 
*/
#include <SimpleTimer.h>

// OUTPUT Alias
int ledPins[] = {2,3,4,5,6,7,8};
int ledPinsNum = sizeof( ledPins) / sizeof( int );

int runtimes = 0;
int motion_check_time = 100;
int time_visible = 1000 * 10;
int triggered = 0;

// INPUT Alias
int motion = 13;

SimpleTimer motion_timer;

void setup() {
  
  int i = 0; 
  
  // Set digital inputs as outputs
  for(i = 0; i < ledPinsNum; i++){
    pinMode( ledPins[i], OUTPUT );
  }
  
  // Set digital input as input
  pinMode( motion, INPUT );
  
  Serial.begin(9600);
  
  motion_timer.setInterval( motion_check_time, check_motion );
}

// Main Program
void loop() {
  
   motion_timer.run();
   
}


void check_motion(){
  int val;
  val = digitalRead( motion );
  
  if( val == 1 && triggered == 0 ){
    
    Serial.print("Motion!: ");
    Serial.println( val );
    triggered = 1;
    start_eyes();
  }
  
}


// Turn on then off LEDS 
void start_eyes(){
  
  runtimes = runtimes + 1;
  Serial.print("RunTime: ");
  Serial.println( runtimes );
  
  
  // Turn on leds randomly
  randomLEDon();

  // We'll leave it on for a while
  delay( time_visible );
  
  Serial.println("---------Bye Kitty---------");

  // Then we'll turn it off...
  all_leds_off();
  triggered = 0;
  
}

// LED on by id
void led_on( int led_id ){
    
    digitalWrite(led_id, HIGH);
    
};

// tuen off led by id 
void led_off( int led_id ){

    digitalWrite(led_id, LOW);
    
};

// Turn off all LEDs
void all_leds_off(){
   for (int i=0; i<ledPinsNum; ++i)
  {
    digitalWrite(ledPins[i], LOW);
  }
}

void randomLEDon()
{
  int i = 0;
  int led;
 
  Serial.println( "Start Random ON" );
  for (int i=0; i<ledPinsNum; ++i)
  {
    int led = random(0, ledPinsNum-i);    // select from a decreasing set
    led_on( ledPins[led] );
    delay(500);
    Serial.print("LED: ");
    Serial.println( ledPins[led] );
    
    
    swap(led, (ledPinsNum-1)-i);             // switch the chosen one with the last of the selection set.
  }  
  //print_array();
  
}

void swap(int a, int b)
{
  int t = ledPins[a];
  ledPins[a] = ledPins[b];
  ledPins[b] = t;
}

void print_array(){
  int i = 0;
  
  Serial.print( "Print Array: " );
  for(i = 0; i<ledPinsNum; i++){
    Serial.print( ledPins[i] );
    Serial.print( "," );
  }
  Serial.println( "" );
  Serial.println( "END array" );
}
