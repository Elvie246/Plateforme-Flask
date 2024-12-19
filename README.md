# Morse MQTT PRoject 
## Groupe H

## This project combines two main functions:

### 1. **Translation of an ASCII message into Morse code.**
### 2. **Communication via MQTT to send and receive messages.**

## Project structure

### Main files
#### . morse.h: Provides functions for converting ASCII text into Morse code.
#### . mqtt.h and mqtt.c: Manage connection and communication with an MQTT broker using the Mosquitto library.
#### . main.c: Program entry point, combines Morse and MQTT functionalities.

## Prerequisites

### Hardware
#### . A Raspberry Pi 4 with a Linux-based operating system (e.g. Raspberry Pi OS).

#### Software
#### 1. **Mosquitto library:**
##### Install the Mosquitto library to use MQTT. On Raspberry Pi OS, run :
```bash
sudo apt update
sudo apt install libmosquitto-dev mosquitto
````
#### 2. **MQTT broker:**
##### An MQTT broker must be running on your Raspberry Pi. Install Mosquitto as an MQTT broker:
```bash
sudo apt install mosquitto
sudo systemctl start mosquitto
sudo systemctl enable mosquitto
````
## Compilation and execution
With the Makefile, in the project directory, simply run :
```bash
make
````
## Features
#### 1. Morse code translation
The program converts ASCII text into Morse code.
```bash
Example: the word Hello will be translated into -... --- -. .--- --- ..- .-..
````
#### 2. MQTT communication
##### The program acts as an MQTT client:
##### Connects to a local MQTT broker.
##### Publishes a message 
##### Listens to incoming messages on all topics.

## References
####  . Official Mosquitto documentation
####  . Raspberry Pi Documentation
