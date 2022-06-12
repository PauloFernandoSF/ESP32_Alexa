# ESP32_Alexa
- Description: MCU(Esp32 in this case) that connects with Alexa(Amazon's home assistant), using "fauxmoESP" library. This example turnon/turnoff two LEDs and dims another LED.

- Connections:
	
  VCC    			           -> 	Powered by USB 
	LED Output(3V3 Logic)  -> 	GPIO 12,GPIO 14
  LED Output(PWM)   	   ->   GPIO 15 

- This example uses fauxmoESP library to connect ESP32 WROVER module with Amazon's Echo Dot gen3. The library creates a TCP server in port 80 and exchanges UDP packages with Echo Dot. 

- Dependencies:
     - Installing ESP32 board in Arduino IDE   : https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
     - fauxmoESP library : https://github.com/vintlabs/fauxmoESP
