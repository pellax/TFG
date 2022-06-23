#include <Arduino.h>
#include "LoraMesher.h"
#include "network.h"

#define BOARD_LED 4

LoraMesher& radio = LoraMesher::getInstance() ;
uint32_t dataCounter2 = 0;
uint32_t dataCounter1 = 0;
uint32_t dataCounter3 = 0;
uint32_t dataCounter4 = 0;
uint32_t dataCounter = 0;
struct dataPacket {
    uint32_t counter = 0;
};

dataPacket* helloPacket = new dataPacket;

//Led flash
void led_Flash(uint16_t flashes, uint16_t delaymS) {
    uint16_t index;
    for (index = 1; index <= flashes; index++) {
        digitalWrite(BOARD_LED, HIGH);
        delay(delaymS);
        digitalWrite(BOARD_LED, LOW);
        delay(delaymS);
    }
}

/**
 * @brief Print the counter of the packet
 *
 * @param data
 */
void printPacket(dataPacket data) {
    Log.verboseln(F("Hello Counter received nº %X" CR), data.counter);
}

/**
 * @brief Iterate through the payload of the packet and print the counter of the packet
 *
 * @param packet
 */
void printDataPacket(AppPacket<dataPacket>* packet) {
    Log.traceln(F("Packet arrived from %X with size %d" CR), packet->src, packet->payloadSize);

    //Get the payload to iterate through it
    dataPacket* dPacket = packet->payload;
    size_t payloadLength = packet->getPayloadLength();

    for (size_t i = 0; i < payloadLength; i++) {
        //Print the packet
        printPacket(dPacket[i]);
    }
}

/**
 * @brief Function that process the received packets
 *
 */
void processReceivedPackets(void*) {
    for (;;) {
        /* Wait for the notification of processReceivedPackets and enter blocking */
        ulTaskNotifyTake(pdPASS, portMAX_DELAY);
        led_Flash(1, 100); //one quick LED flashes to indicate a packet has arrived

        //Iterate through all the packets inside the Received User Packets FiFo
        while (radio.getReceivedQueueSize() > 0) {
            Log.traceln(F("ReceivedUserData_TaskHandle notify received" CR));
            Log.traceln(F("Fifo receiveUserData size: %d" CR), radio.getReceivedQueueSize() > 0);

            //Get the first element inside the Received User Packets FiFo
            AppPacket<dataPacket>* packet = radio.getNextAppPacket<dataPacket>();

            //Print the data packet
            printDataPacket(packet);

            //Delete the packet when used. It is very important to call this function to release the memory of the packet.
            radio.deletePacket(packet);
        }
    }
}

/**
 * @brief Initialize LoRaMesher
 *
 */
void setupLoraMesher() {
    //Init the loramesher with a processReceivedPackets function
    radio.init(processReceivedPackets);

    Serial.println("Lora initialized");
}

void setupMonitoring() {
    Network* myNetwork = new Network();

    Serial.println("Network initialized");
}





    



void setup() {
    Serial.begin(115200);

    Serial.println("initBoard");
    pinMode(BOARD_LED, OUTPUT); //setup pin as output for indicator LED
    led_Flash(2, 125);          //two quick LED flashes to indicate program start
    setupLoraMesher();
    setupMonitoring();

}


void loop() {


/* 
    Log.trace(F("Send packet %d" CR), dataCounter);
    helloPacket->counter = dataCounter++;

    //Create packet and send it.
    //radio->createPacketAndSend(BROADCAST_ADDR, helloPacket, 1);

    //Wait 30 seconds to send the next packet
    vTaskDelay(30000 / portTICK_PERIOD_MS);


  */
    if (radio.getLocalAddress() == 0xC4F0&& dataCounter1 <=60) {
        Log.trace(F("Send packet %d" CR), dataCounter1);
        helloPacket->counter = dataCounter1++;

        //Create packet and send it.
        radio.createPacketAndSend(0xD39C, helloPacket, 1);
    }
    if(radio.getLocalAddress() == 0xD39C&& dataCounter2 <= 60){
        Log.trace(F("Send packet %d"CR),dataCounter2);
        helloPacket->counter = dataCounter2++;
        radio.createPacketAndSend(0x3A0C,helloPacket,1);
    }
    if(radio.getLocalAddress() == 0x3A0C&& dataCounter3 <= 60){
        Log.trace(F("Send packet %d"CR),dataCounter3);
        helloPacket->counter = dataCounter3++;
        radio.createPacketAndSend(0x4E64,helloPacket,1);
        }

        if(radio.getLocalAddress() == 0x4E64 && dataCounter4 <= 60){
        Log.trace(F("Send packet %d"CR),dataCounter4);
        helloPacket->counter = dataCounter4++;
        radio.createPacketAndSend(0xC4F0,helloPacket,1);
    }

    //Wait 30 seconds to send the next packet
    vTaskDelay(30000 / portTICK_PERIOD_MS);
    Log.trace(F("Another while loop"CR));



}