#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;
int i;
void setup() 
{
  Serial.begin(115200);
 
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  File myFile = SD.open("test.txt", FILE_WRITE);  
  if (myFile) 
  {
    Serial.print("Writing to test.txt...");
    myFile.println("This is a test file :)");
    myFile.println("testing 1, 2, 3.");
    for (int i = 0; i < 20; i++) 
    {
      myFile.println(i);
    }
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  else 
  {
  // if the file didn't open, print an error:
  Serial.println("error opening test.txt");
  }
}

void loop() 
{
}
