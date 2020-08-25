// Universum | Universum Projects > FlowerPot Monitor | transmit

// Andrei Florian 9/DEC/2017

#include <VirtualWire.h> // include library to communicate with RF
#include <dht.h> // include library for the DHT temperature module

dht DHT; // Create object

uint8_t valueToSend[4]; // create buffer for data being sent
int temperature;
int soilMoisture;
int humidity;

int chk;

void readTempAndHum()
{
  chk = DHT.read11(11);

  temperature = DHT.temperature;
  humidity = DHT.humidity;
}

void readSoilMoisture()
{
  int sensorValue = analogRead(A0); // read the raw value
  soilMoisture = map(sensorValue,550,0,0,100); // map the received value
}



void setup()
{
  vw_set_tx_pin(12); // set transmitting pin to 12
  vw_setup(2000); // start communication
  delay(2000);
}

void loop()
{
  readTempAndHum(); // read the temperature and humidity
  readSoilMoisture(); // read the amount of moisture is the soil

  // Send these values
  valueToSend[1] = temperature; // send temperature
  valueToSend[2] = humidity; // send humidity
  valueToSend[3] = soilMoisture; // send soil moisture
  valueToSend[4] = 0; // this data does not represent anything
  
  vw_send((uint8_t *) valueToSend, 4); // send the message
  vw_wait_tx(); // Wait until the message is sent
  delay(3000);
}

