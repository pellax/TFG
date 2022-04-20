### Introduction
Main project for testing the LoRaMesher with the network module

### Description
Project with four boards sending data packets in round 
### Set up
Open the directory ExampleSergi with the PlatformIO IDE
### Compilation
You have to delete HTTPClient from the library dependences, concretely from the RadioLib library because it's duplicated and has conflict with Arduino HttpClient. You have to comment all the references as well. 
