#include <SPI.h>
#include <SD.h>

volatile int s1pin=31;
volatile int s2pin=33;
volatile int stoppin=35;
volatile byte state1 = LOW;
volatile byte state2 = LOW;
volatile int cnt1=0;
volatile int cnt2=0;
volatile int lickdata1[5000][2];
volatile int lickdata2[5000][2];
const int chipSelect = 4;
volatile int maxcnt=5000;

void setup() 
{
  pinMode(s1pin,INPUT);
  pinMode(s2pin,INPUT);
  pinMode(stoppin,INPUT);
  attachInterrupt(digitalPinToInterrupt(s1pin), s1func, CHANGE);
  attachInterrupt(digitalPinToInterrupt(s2pin), s2func, CHANGE);
  attachInterrupt(digitalPinToInterrupt(stoppin), stopfunc, RISING);
  Serial.begin(115200);
  if (SD.begin(chipSelect)) 
  {
    Serial.println("Card initialized!");
  }
}

void loop() 
{
  if (cnt1>=maxcnt)
  {
    detachInterrupt(digitalPinToInterrupt(s1pin));
    if (SD.begin(chipSelect))
      {
        File myFile1 = SD.open("data1.txt", FILE_WRITE);
        for (int i = 0; i<maxcnt; i++) 
        {        
          myFile1.println(String(lickdata1[i][0]) + "  " + String(lickdata1[i][1]));
        }         
        myFile1.close();     
      }     
    cnt1=0;
    attachInterrupt(digitalPinToInterrupt(s1pin), s1func, CHANGE);
  }

  if (cnt2>=maxcnt)
  {
    detachInterrupt(digitalPinToInterrupt(s2pin));
    if (SD.begin(chipSelect))
      {
        File myFile2 = SD.open("data2.txt", FILE_WRITE);
        for (int i = 0; i<maxcnt; i++) 
        {        
          myFile2.println(String(lickdata2[i][0]) + "  " + String(lickdata2[i][1]));
        }   
        myFile2.close();  
      }
    cnt2=0;
    attachInterrupt(digitalPinToInterrupt(s2pin), s2func, CHANGE);
  }
 
}

void s1func() 
{
  if (!!(g_APinDescription[s1pin].pPort -> PIO_PDSR & g_APinDescription[s1pin].ulPin)==HIGH){lickdata1[cnt1][0]=millis();}
  if (!!(g_APinDescription[s1pin].pPort -> PIO_PDSR & g_APinDescription[s1pin].ulPin)==LOW){lickdata1[cnt1][1]=millis();cnt1=cnt1+1;}
}

void s2func() 
{
  if (!!(g_APinDescription[s2pin].pPort -> PIO_PDSR & g_APinDescription[s2pin].ulPin)==HIGH){lickdata2[cnt2][0]=millis();}
  if (!!(g_APinDescription[s2pin].pPort -> PIO_PDSR & g_APinDescription[s2pin].ulPin)==LOW){lickdata2[cnt2][1]=millis();cnt2=cnt2+1;}
}

void stopfunc() 
{
  cnt1=maxcnt;
  cnt2=maxcnt;
}
