
#include <SPI.h>
#include <RH_RF95.h>
#include <dht.h>

#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2
#define DHT11_PIN 7

#define RF95_FREQ 863.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);

dht DHT;
void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  while (!Serial);
  Serial.begin(9600);
  delay(100);

  Serial.println("Arduino LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);
}

int16_t packetnum = 0;  // packet counter, we increment per xmission

void loop()
{


  int chk = DHT.read11(DHT11_PIN);

  
  int tem = DHT.temperature;
  int hum = DHT.humidity;

  
  Serial.print("Temperature = ");
  Serial.println(tem);
  Serial.print("Humidity = ");
  Serial.println(hum);


  Serial.println("Sending to rf95_server");
   
  String msg = String(tem) + String (hum);
  Serial.println(msg);
  byte buf[8];
  msg.toCharArray(buf,8);

  for (int i = 0; i<8; i++){
  Serial.print(buf[i]);
  }

  Serial.println("Sending..."); delay(10);
  rf95.send((uint8_t *)buf, 8);

  Serial.println("Waiting for packet to complete..."); delay(10);
  rf95.waitPacketSent();
  // Now wait for a reply



  delay(1000);
}
