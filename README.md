# esp-idf-t3
Firmware for ESP32-C6-DevkitC-1 that makes it do 3 things in parallel:
1. Increment a coounter every 5 seconds and sends the result to a queue. 
2. Receive a counter record from the above mentioned queue and logs it as well as add the time between receiving messages to another queue.
3. Blink with the built-in LED every second.

# Build and flash instructions
## Linux
### Install ESP-IDF
_For more details see: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html_
1. Install required packages
```Shell
sudo apt update
```
```Shell
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
```
2. Get ESP-IDF
```Shell
mkdir -p ~/esp
cd ~/esp
git clone -b v5.3.2 --recursive https://github.com/espressif/esp-idf.git
```
3. Set up the Tools
```Shell
cd ~/esp/esp-idf
./install.sh esp32,esp32c6
```
4. Set up the Environment Variables
```Shell
. $HOME/esp/esp-idf/export.sh
```
> **_NOTE:_** If you restart the terminal you'll have to use this command again to set up the environment variables.
### Clone and build the project
1. Clone the repository
```Shell
cd ~
git clone https://github.com/Zhizhoid/esp-idf-t3.git 
```
> **_NOTE:_** Of course, you can clone it to some other folder instead of ~. You will have to adjust the following commands accordingly.
2. Build the project
```Shell
cd ~/esp-idf-t3
idf.py set-target esp32c6
```
```Shell
idf.py build
```
2. Flash and start the serial monitor
- Connect your ESP32-C6-DevkitC-1 to your PC
```Shell
idf.py flash
```
```Shell
idf.py monitor
```
## Windows
### Install ESP-IDF
_For more details see: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html_

1. Download the Windows installer: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/windows-setup.html
2. Launch it and go through all of the installation steps
### Clone and build the project
1. Clone the repository
- In Command Prompt:
```Shell
cd %userprofile%\esp
git clone https://github.com/Zhizhoid/esp-idf-t3.git 
```
> **_NOTE:_** Of course, you can clone it to some other folder instead of %userprofile%\esp. You will have to adjust the following commands accordingly.
2. Build the project
- Open ESP-IDF CMD:\
![image](readme_images/image.png)
- In ESP-IDF CMD;
```Shell
cd %userprofile%\esp\esp-idf-t3
idf.py set-target esp32c6
idf.py build
```
3. Flash and start the serial monitor
- Connect your ESP32-C6-DevkitC-1 to your PC
```Shell
idf.py flash
```
```Shell
idf.py monitor
```