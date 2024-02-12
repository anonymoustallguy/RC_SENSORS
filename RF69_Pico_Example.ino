/*
  RadioLib Non-Arduino Raspberry Pi Pico library example

  Licensed under the MIT License

  Copyright (c) 2024 Cameron Goddard

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

// define pins to be used
#define SPI_PORT spi0
#define SPI_MISO 4
#define SPI_MOSI 3
#define SPI_SCK 2

#define RFM_NSS 26
#define RFM_RST 22
#define RFM_DIO0 14
#define RFM_DIO1 15

#include <pico/stdlib.h>

// include the library
#include <RadioLib.h>

// include the hardware abstraction layer
#include "D:\Documents\Arduino\libraries\RadioLib\examples\NonArduino\Pico\PicoHal.h"

// create a new instance of the HAL class
PicoHal* hal = new PicoHal(SPI_PORT, SPI_MISO, SPI_MOSI, SPI_SCK);

// now we can create the radio module
#define G0    15  //G0 pin?
#define RST   16  //RST pin
#define DIO0  28  //NOT USED
#define DIO1  28  //NOT USED
RF69 radio = new Module(hal, G0, DIO0, RST, DIO1);
int state;

void setup(){
  Serial.begin(115200);
  // initialize just like with Arduino
  Serial.println("[RF69] Initializing ... ");
  state = radio.begin();
  if (state != RADIOLIB_ERR_NONE) {
    Serial.print("failed, code ");Serial.println(state);
  }
  else {
    Serial.println("success!");
  }
}


void loop(){
  // send a packet
  Serial.print("[SX1276] Transmitting packet ... ");
  state = radio.transmit("Hello World!");
  if(state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println("success!");

    // wait for a second before transmitting again
    hal->delay(1000);

  } else {
    Serial.print("failed, code ");Serial.println(state);
  }

}