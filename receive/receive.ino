// Universum | Universum Projects > FlowerPot Monitor | receive

// Andrei Florian 9/DEC/2017

#include <VirtualWire.h> // include library to communicate with RF
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // include library to communicate with the LCD

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD

uint8_t data[4]; // create buffer for received data
int temperature;
int humidity;
int soilMoisture;

int state = 0;
int LEDPin = 11;

void readValues()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN]; // create buffer where the data is received
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // if we receive a message
  {
    for(int i = 0; i < buflen; i++) 
    {
      data[i] = buf[i]; // store message
    }

    if(buflen == 4)
    {
      temperature = data[1]; // store temperature
      humidity = data[2]; // store humidity
      soilMoisture = data[3]; // store soil moisture
    }
  }
}

void displayTempAndHum()
{
  lcd.setCursor(0,1);
  lcd.print("Temp ");
  lcd.setCursor(5,1);
  lcd.print(temperature);
  lcd.setCursor(7,1);
  lcd.print("C");
  lcd.setCursor(9,1);
  lcd.print("Hum ");
  lcd.setCursor(13,1);
  lcd.print(humidity);
  lcd.setCursor(15,1);
  lcd.print("%");
}

void displaySoilMoisture()
{
  lcd.setCursor(1,0);
  lcd.print("Soil Moist ");
  lcd.setCursor(12,0);
  lcd.print(soilMoisture);
  lcd.setCursor(14,0);
  lcd.print("%");
}



void setup()
{
  pinMode(LEDPin, OUTPUT);
  vw_set_ptt_inverted(true); // set to true
  vw_set_rx_pin(12); // set the receiving pin
  vw_setup(2000); // set the communication speed
  vw_rx_start(); // start communication
  
  lcd.init(); // initialise the lcd
  lcd.backlight(); // turn on the backlight

  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("FlowerPotMonitor");
  lcd.setCursor(0,1);
  lcd.print(" Awaiting Data! ");
  delay(2000);
  lcd.clear();
  digitalWrite(LEDPin, HIGH);
}

void loop()
{
  readValues(); // read the incoming data
  
  displaySoilMoisture();
  displayTempAndHum();
  delay(1000);
}





