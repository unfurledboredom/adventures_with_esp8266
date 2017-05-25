**IOT Enabled Color LEDs**
==========================

In today's project, let's make IOT enabled RGB LEDs. Why you ask? As usual, **why not? ** If followed correctly, by the end, you will have a $15 - 20 IOT enabled RGB LEDs. To do this, we will need a few things. 

Item                | Average Value | Recommended Location
------------------- | ------------- | --------------------
ESP8266 (WeMOS)     | $4            | Aliexpress
30 RGB LEDs         | $6            | Amazon 
5v Power Source     | $5            | Amazon
Some Wire           | ??            | The wall? 

>**My Build includes:**
> - WeMOS board. Any other ESP8266 board can be used for this project. Just be sure to modify the pinout in the source code. 
> - The Arduino IDE with the Adafruit NeoPixel library and jsColor library.
> - RGB LEDs with Built-in WS2812B. 
> - ESP8266 in station mode and connecting it to my local wireless router. You can also use it in AP mode. 
> **WARNING:** DO NOT use more than 30 LEDs without an independent power source (see schematic). Most ESP8266 boards can not handle more than that without burning out.

**Step 1**
Connect your ESP8266 to the LEDs. Use the diagrams below as reference. 

**Step 2**
Configure the Arduino IDE to compile and deploy code into your ESP8266. Verify the Model, buffer rate, frequency and serial port. 

> *Note: Double check this part because misconfigurations can lead to a bricked board. *

**Step 3**
Load the ``esp8266_RGB_LED.ino`` file into your Arduino IDE and make the necessary changes. Such as, wifi information, pinout, led count, and so on. Once you have made the necessary adjustments, it is always a good idea to click on the **verify** icon in the IDE to verify your code. This will compile your code and check that all dependencies are resolved. 

**Step 4**
Connect the ESP8266 to your computer if you haven't already. Then compile and upload the code. Once the code is uploaded, you are good to go. At this point, you can turn on the serial monitor and should see some outputs in your console. You can keep it connected to the computer or connect it with an external USB (5V) power source. 
>**Sample Output:**
>Connecting to (*your ssid*) ...... connected
>Web server started, open (*device ip*) in a web browser

**Step 5**
Open up a browser on your favorite device and go to the IP mentioned in the console. You should see the web interface for your LEDs. Click on the **Color Picker** text box and you should now get a color picker for your LEDs. You can use the picker or if you are 1337, you can manually type in RGB values in the respected text boxes. 

Congratulations, you have just completed the IOT enabled RGB LED lights project. Feel free to make modifications to the source code and try out new things. 

**Refrences**
-----------------

**Schematic**
![Schematic](https://lh3.googleusercontent.com/OyReZvfoz0j85FNXozh8pnZW-nMLkYwvSIp0fcu69PZRm-zuG4E-U4OGAGGMuqUdbC5ASQZAQKApCZ0sLAgOlGDSvY7pvHFzn-fdmiOtTG7zt8o49XpkwV8mQmIg3P8Z9bwDAg=w1830-h684-no)

**Breadboard**
![Breadboard](https://lh3.googleusercontent.com/MyzbifeHpPf8mBQvqoG1fPZdtNjCedadoGpoTHgNoS-VaUeLdw_mDQArUFtlJ6Tx96qkY2NXH99W0cWYx-amfTqLEBy3ATyMWi0FUuBIi7hcowchMzQeAFyywHeNpxBnf_57cg=w1263-h630-no)