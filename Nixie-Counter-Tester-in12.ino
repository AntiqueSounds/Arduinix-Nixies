#define COUNTVERSION
#define IN12
// #define IN2
// Arduinix 4 tube board
//
// Set COUNTVERSION to change the code to deliver a 0-9999 counter instead of a clock.  
// If the COUNTVERSION is not set, the display will be a default clock display with blinking colons.
// 
// Set the tube type to either "IN2" for an IN-2 tube/board or to "IN12" for and IN-12 tube/board
//
//
//
// This code runs a 4 bulb tube board setup and displays a prototype clock-like setup.
//
// NOTE: the delay is setup for IN-12/IN-2 nixie bulbs.
//
// by Jeremy Howa mods by M. Keith Moore for IN-2/IN-12 4 digit and blinking colon
// www.robotpirate.com
// www.arduinix.com
// 2009/2016(MKM)
//
// Note: Anod pin 3 and 2 are used for colons
// 
// Anod to number diagram for IN-2/IN-12 boards
//
//          num array position
//            0   1   2   3
// Anod 0     #           #
// Anod 1         #   #
//
// Anod 2  Array #2 Colon=0
// Anod 3  Array #1 Colon=0

#ifdef COUNTVERSION
int cnt3, cnt2, cnt1 = 0;
int cnt4 = -1;
#endif

// SN74141 : Truth Table
//D C B A #
//L,L,L,L 0
//L,L,L,H 1
//L,L,H,L 2
//L,L,H,H 3
//L,H,L,L 4
//L,H,L,H 5
//L,H,H,L 6
//L,H,H,H 7
//H,L,L,L 8
//H,L,L,H 9

// SN74141 (1)
int ledPin_0_a = 2;                
int ledPin_0_b = 3;
int ledPin_0_c = 4;
int ledPin_0_d = 5;
// SN74141 (2)
int ledPin_1_a = 6;                
int ledPin_1_b = 7;
int ledPin_1_c = 8;
int ledPin_1_d = 9;

// anod pins
int ledPin_a_1 = 10;
int ledPin_a_2 = 11;
int ledPin_a_3 = 12;
int ledPin_a_4 = 13;


void setup() 
{
  pinMode(ledPin_0_a, OUTPUT);      
  pinMode(ledPin_0_b, OUTPUT);      
  pinMode(ledPin_0_c, OUTPUT);      
  pinMode(ledPin_0_d, OUTPUT);    
  
  pinMode(ledPin_1_a, OUTPUT);      
  pinMode(ledPin_1_b, OUTPUT);      
  pinMode(ledPin_1_c, OUTPUT);      
  pinMode(ledPin_1_d, OUTPUT);      
  
  pinMode(ledPin_a_1, OUTPUT);      
  pinMode(ledPin_a_2, OUTPUT);      
  pinMode(ledPin_a_3, OUTPUT);
  pinMode(ledPin_a_4, OUTPUT);     
  
  // NOTE:
  // Grounding on pints 14 and 15 will set the Hour and Mins.
  pinMode( 14, INPUT ); // set the vertual pin 14 (pin 0 on the analog inputs ) 
  digitalWrite(14, HIGH); // set pin 14 as a pull up resistor.

  pinMode( 15, INPUT ); // set the vertual pin 15 (pin 1 on the analog inputs ) 
  digitalWrite(15, HIGH); // set pin 15 as a pull up resistor.

  Serial.begin(9600);
  
}
////////////////////////////////////////////////////////////////////////
//
// DisplayNumberSet
// Use: Passing anod number, and number for Tube 1 and Tube 2, this function
//      looks up the truth table and opens the correct outputs from the arduino
//      to light the numbers given to this funciton (num1,num2).
//      On a 4 nixie bulb setup.
//
////////////////////////////////////////////////////////////////////////
void DisplayNumberSet( int anod, int num1, int num2 )
{
  int anodPin;
  int a,b,c,d;
  
  // set defaults.
  a=0;b=0;c=0;d=0; // will display a zero.
  anodPin =  ledPin_a_1;     // default on first anod.
  //
  // Note: Anodes are marked one-relative on the PCB board instead of zero-relative here.
  // 
  // Select what anod to fire.
  switch( anod )  
  {
    case 0:    anodPin =  ledPin_a_1;    break; // Anode marked "1" on the PCB 
    case 1:    anodPin =  ledPin_a_2;    break; // Anode marked "2" on the PCB
    case 2:    anodPin =  ledPin_a_3;    break; // Anode marked "3" on the PCB
    case 3:    anodPin =  ledPin_a_4;    break; // Anode marked "4" on the PCB
  }  
  
  // Load the a,b,c,d.. to send to the SN74141 IC (1)
 #ifdef IN2
 switch( num1 )
  {
    case 0: a=0;b=0;c=0;d=0;break; // pin 10
    case 1: a=1;b=0;c=0;d=0;break; // pin 1
    case 2: a=0;b=1;c=0;d=0;break; // pin 2
    case 3: a=1;b=1;c=0;d=0;break; // pin 3
    case 4: a=0;b=0;c=1;d=0;break; // pin 4
    case 5: a=1;b=0;c=1;d=0;break; // pin 5
    case 6: a=0;b=1;c=1;d=0;break; // pin 6
    case 7: a=1;b=1;c=1;d=0;break; // pin 7
    case 8: a=0;b=0;c=0;d=1;break; // pin 8
    case 9: a=1;b=0;c=0;d=1;break; // pin 9
    default: break;  // used to no-op the number in the array
  }  
 #else
// IN12 or other
 switch( num1 )
  {
    case 0: a=0;b=0;c=0;d=0;break; // pin 2
    case 1: a=1;b=0;c=0;d=0;break; // pin 11
    case 2: a=0;b=1;c=0;d=0;break; // pin 10 
    case 3: a=1;b=1;c=0;d=0;break; // pin 9
    case 4: a=0;b=0;c=1;d=0;break; // pin 8
    case 5: a=1;b=0;c=1;d=0;break; // pin 7
    case 6: a=0;b=1;c=1;d=0;break; // pin 6
    case 7: a=1;b=1;c=1;d=0;break; // pin 5
    case 8: a=0;b=0;c=0;d=1;break; // pin 4
    case 9: a=1;b=0;c=0;d=1;break; // pin 3
    default: break;  // used to no-op the number in the array
  }  
 #endif 
  // Write to output pins.
  digitalWrite(ledPin_0_d, d);
  digitalWrite(ledPin_0_c, c);
  digitalWrite(ledPin_0_b, b);
  digitalWrite(ledPin_0_a, a);

  // Load the a,b,c,d.. to send to the SN74141 IC (2)
#ifdef IN2
  switch( num2 )
  {
    case 0: a=0;b=0;c=0;d=0;break;
    case 1: a=1;b=0;c=0;d=0;break;
    case 2: a=0;b=1;c=0;d=0;break;
    case 3: a=1;b=1;c=0;d=0;break;
    case 4: a=0;b=0;c=1;d=0;break;
    case 5: a=1;b=0;c=1;d=0;break;
    case 6: a=0;b=1;c=1;d=0;break;
    case 7: a=1;b=1;c=1;d=0;break;
    case 8: a=0;b=0;c=0;d=1;break;
    case 9: a=1;b=0;c=0;d=1;break;
    default: break;
  }
   #else
// IN12 or other
 switch( num2 )
  {
    case 0: a=0;b=0;c=0;d=0;break;
    case 1: a=1;b=0;c=0;d=0;break; // *
    case 2: a=0;b=1;c=0;d=0;break; // *
    case 3: a=1;b=1;c=0;d=0;break; // *
    case 4: a=0;b=0;c=1;d=0;break; // *
    case 5: a=1;b=0;c=1;d=0;break; // *
    case 6: a=0;b=1;c=1;d=0;break; //*
    case 7: a=1;b=1;c=1;d=0;break; // *
    case 8: a=0;b=0;c=0;d=1;break; // *
    case 9: a=1;b=0;c=0;d=1;break;
    default: break;  // used to no-op the number in the array
  }  
 #endif 
  // Write to output pins
  digitalWrite(ledPin_1_d, d);
  digitalWrite(ledPin_1_c, c);
  digitalWrite(ledPin_1_b, b);
  digitalWrite(ledPin_1_a, a);

  // Turn on this anod.
  digitalWrite(anodPin, HIGH);   

  // Delay
  // NOTE: With the differnce in Nixie bulbs you may have to change
  //       this delay to set the update speed of the bulbs. If you 
  //       dont wait long enough the bulb will be dim or not light at all
  //       you want to set this delay just right so that you have 
  //       nice bright output yet quick enough so that you can multiplex with
  //       more bulbs.
  delay (4);
  
  // Shut off this anod.
  digitalWrite(anodPin, LOW);
}
////////////////////////////////////////////////////////////////////////
//
// DisplayNumberString
// Use: passing an array that is 8 elements long will display numbers
//      on a 6 nixie bulb setup.
//
////////////////////////////////////////////////////////////////////////
void DisplayNumberString( int* array )
{
  // bank 1 (bulb 0,3)
  DisplayNumberSet(0,array[0],array[3]);   
  // bank 2 (bulb 1,2)
  DisplayNumberSet(1,array[1],array[2]);

 
#ifdef IN2
  if (array[4]<1) DisplayNumberSet(3,array[4],11);  // 11 is a dummy value to ignore in the code (fall-thru case/switch value)
  if (array[5]<1) DisplayNumberSet(2,11,array[5]); // this colon is turned on if 0  
#else //* IN12
  if (array[4]<1) DisplayNumberSet(3,array[4],11);  // 11 is a dummy value to ignore in the code (fall-thru case/switch value)
  if (array[5]<1) DisplayNumberSet(2,11,array[5]); // this colon is turned on if 0   nfg 
#endif
}

// Defines
long MINS = 60;         // 60 Seconds in a Min.
long HOURS = 60 * MINS; // 60 Mins in an hour.
long DAYS = 24 * HOURS; // 24 Hours in a day. > Note: change the 24 to a 12 for non military time.

long runTime = 0;       // Time from when we started.
long previous = 0;
long interval = 1000;
#ifdef COUNTVERSION
long cntInterval = 100; // tenth of a second increment timer
long cntPrevious = 0;
#endif
int colon = 1;

// default time sets. clock will start at 12:59:00
// NOTE: We start seconds at 0 so we dont need a clock set
//       The values you see here would be what you change 
//       if you added a set clock inputs to the board.
long clockHourSet = 12;
long clockMinSet  = 59;

int HourButtonPressed = false;
int MinButtonPressed = false;

////////////////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////////////////
void loop()     
{
   // Get milliseconds.
  runTime = millis();
  
  int hourInput = digitalRead(14);  
  int minInput  = digitalRead(15);

  if( hourInput == 0 )
    HourButtonPressed = true;
//    Serial.println("button down");
  if( minInput == 0 )
    MinButtonPressed = true;
  
  if( HourButtonPressed == true && hourInput == 1 )
  {
    clockHourSet++;
    HourButtonPressed = false;
  }
  
  if( MinButtonPressed == true && minInput == 1 )
  {
    clockMinSet++;
    MinButtonPressed = false;
  }

  // Get time in seconds.
  long time = (runTime) / 1000;
  
  // Set time based on offset..
  long hbump = 60*60*clockHourSet;
  long mbump = 60*clockMinSet;
  time += mbump + hbump;

  // Convert time to days,hours,mins,seconds
  long days  = time / DAYS;    time -= days  * DAYS; 
  long hours = time / HOURS;   time -= hours * HOURS; 
  long minutes  = time / MINS;    time -= minutes  * MINS; 
  long seconds  = time; 

  //*****************************
  unsigned long current = millis();
//
// For countversion set the cntInterval to represent the frequency of the bump of the counter for the display in milliseconds
//  
 #ifdef COUNTVERSION
// This mechanical way of displaying the digits allows for rolling quickly or slowly.   
  if ( (current - cntPrevious) > cntInterval){ // every cntInterval, this code is executed. 
    cntPrevious = current;
    if (++cnt4 > 9) {
      cnt4=0;
      if (++cnt3 > 9) {
        cnt3=0;
        if (++cnt2 > 9) {
          cnt2=0;
          if (++cnt1 > 9) {
            cnt1=0;
          }
        }
      }
   }
  }
#endif   
// Interval is one second for the colons to blink 
// This is executed in both clock and counter versions
//
  if( (current - previous) > interval){
    previous = current;
    if (colon == 0) {
      colon = 1;
 //       Serial.println("Colon off");
    } 
    else {
      colon = 0;
 //       Serial.println("Colon on")
    }
  }
  if( hours > 12 )
      time-= 60*60*12;
// For counter, just place each digit into the display
#ifdef COUNTVERSION
  int lowerMins = cnt4;
  int upperMins = cnt3;
  int lowerHours = cnt2;
  int upperHours = cnt1;
  int upperSeconds = upperMins;
  int lowerSeconds = lowerMins;
//  Serial.print(upperHours);Serial.print(lowerHours);Serial.print(upperMins);Serial.println(lowerMins);

// For clock version, cut up the digits and place into the digits  
#else
  // Get the high and low order values for hours,min,seconds. 
  int lowerHours = hours % 10;
  int upperHours = hours - lowerHours;
  int lowerMins = minutes % 10;
  int upperMins = minutes - lowerMins;
  int lowerSeconds = seconds % 10;
  int upperSeconds = seconds - lowerSeconds;
  if( upperSeconds >= 10 )   upperSeconds = upperSeconds / 10;
  if( upperMins >= 10 )      upperMins = upperMins / 10;
  if( upperHours >= 10 )     upperHours = upperHours / 10;
#endif
  // Fill in the Number array used to display on the tubes.
  int NumberArray[6]={0,0,0,0,0,0};
  NumberArray[0] = upperHours;
  NumberArray[1] = lowerHours;
  NumberArray[2] = upperMins;
  NumberArray[3] = lowerMins;
  NumberArray[4] = colon;
  NumberArray[5] = colon;
  // Display.
  DisplayNumberString( NumberArray ); 
}
