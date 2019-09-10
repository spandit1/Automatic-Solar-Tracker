#include <Servo.h>
Servo horizontal;
int servoh = 270;   // 90;     // stand horizontal servo

int servohLimitHigh = 270;
int servohLimitLow = 10;

Servo vertical;   // vertical servo 
int servov = 10;    //   90;     // stand vertical servo

int servovLimitHigh = 180;
int servovLimitLow = 10;


//  name  = analogpin;
int ldrlt = 0; //LDR top left - BOTTOM LEFT
int ldrrt = 1; //LDR top rigt - BOTTOM RIGHT 
int ldrld = 2; //LDR down left - TOP LEFT
int ldrrd = 3; //ldr down rigt - TOP RIGHT

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  horizontal.attach(12); 
  vertical.attach(9);
  horizontal.write(270);
  vertical.write(10);
  delay(1000);
}

void loop() 
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  // int dtime = analogRead(4)/20; // read potentiometers  
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt
  
  
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");
  
    
  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
   delay(dtime);

}
 
