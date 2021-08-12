//Define pins for the 3 Pushbuttons
const byte pushon = 2;
const byte pushoff = 3;
const byte pushblink = 4;
//Define pin for the LED
const byte ledpin = 5;
//A Bool variable to indicate if blinking is active
volatile bool blinking = false;

void setup()
{
  //Define push buttons as INPUT
  for(int pin=2;pin<5;pin++)
  {
    pinMode(pin,INPUT);
  }
  //Define led as OUTPUT
  pinMode(ledpin,OUTPUT);
  //Activate the interrupts on pin2 and 3 with RISING edge
  attachInterrupt(digitalPinToInterrupt(2),TurnOn,RISING);
  attachInterrupt(digitalPinToInterrupt(3),TurnOff,RISING);
}

void loop()
{
  //Read the status of the pushbutton on pin 4 (blinking)
  int statuspush = digitalRead(pushblink);
  //If push button is pressed set blinking to true
  if(statuspush==HIGH)
  {
    blinking = true;
  }
  //If blinking is set to true call the blinking function
  while(blinking)
  {
    BlinkLed();
  }
}
//ISR for pushbutton on pin 2 to turn led on
void TurnOn()
{
  digitalWrite(ledpin,HIGH);
  blinking = false;
}
//ISR for pushbutton on pin 3 to turn led off
void TurnOff()
{
  digitalWrite(ledpin,LOW);
  blinking = false;
}
//Function for blinking the led
void BlinkLed()
{
  digitalWrite(ledpin,HIGH);
  delay(1000);
  //Check if the program was interrupted by push button pin 2
  if(blinking==false)
  {
    return;
  }
  digitalWrite(ledpin,LOW);
  delay(1000);
}
