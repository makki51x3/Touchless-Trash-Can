# Touchless-Trash-Can
a smart touchless trashcan where the user only needs to approach the trashcan to open it, includes safety and usability features. In addition the status for leakage, temperature, capacity, and other information will be displayed on an LCD screen. It also contains an alarm system to notify the user of a possible fire outbreak. 

![image](https://user-images.githubusercontent.com/96151955/170456130-138abbe9-6ded-44ca-bb91-59dfb03df871.png)![image](https://user-images.githubusercontent.com/96151955/170456442-7fe97ed9-1ea8-44dd-93b7-e6ad858ad94a.png)

# Use Case
Initially the green led is ON and the user only needs to approach the trashcan. Once detected by the ultrasonic sensor, the trashcan will activate the servo motor to open automatically and after a few seconds the trashcan will close back to its original state. The user can find real-time information of the current percentage of the trash, measurement of temperature in degree Celsius and percentage of humidity in the air, all displayed on an LCD screen. The trashcan has an inner moisture detector to detect if there’s leakage in the bin. In case of a leakage, the blue led will light up and the LCD will display “Leakage detected Replace bag”, so that the user can get notified to change the bag. It also contains a smoke detector that activates a buzzer, to alarm the user of a possible fire outbreak, all leds will light up and the LCD displays “Danger! Smoke Detected”. Moreover, it has a humidity sensor that activates another alarm with a different tone whenever the humidity is above 85% , the red and blue leds will light up and “Danger! High Humidity” will be displayed. On high temperatures, above 50 C, the buzzer gets activated, green, and red leds will light up and the LCD displays “Danger! High Temp”. Lastly, If the trash is more than 70% full, the red led will light up and the LCD will display “Trash is full! Replace bag”. 


# Flow Chart
![image](https://user-images.githubusercontent.com/96151955/170455905-87da04a9-6409-45cf-a479-f66f2064a81b.png)

# Hardware Components
1)	Arduino UNO 
2)	LCD Screen
3)	Ultrasonic sensor 
4)	Servo motor 
5)	Moisture sensor 
6)	Breadboard and wires 
7)	Temperature sensor
8)	Smoke sensor 

# Datasheets
![image](https://user-images.githubusercontent.com/96151955/170460186-139e6491-6bcc-4384-9fb7-20ac803d3afe.png)

![image](https://user-images.githubusercontent.com/96151955/170460205-b6b48b81-9f38-43f9-87f5-f52f2a097972.png)

![image](https://user-images.githubusercontent.com/96151955/170460233-b9d25f18-d5d4-4509-b72d-b70b49738e7c.png)

![image](https://user-images.githubusercontent.com/96151955/170460264-51538eee-cd27-4405-b961-298949fe61ba.png)

![image](https://user-images.githubusercontent.com/96151955/170460299-55046389-1a73-462a-b8c0-918b3e71fbca.png)

![image](https://user-images.githubusercontent.com/96151955/170460314-d90eeeba-21f2-4d0f-92cb-6b1e2372b928.png)

![image](https://user-images.githubusercontent.com/96151955/170460327-95de038e-585b-4413-96f1-78427a96fbcd.png)

![image](https://user-images.githubusercontent.com/96151955/170460341-7980055d-518c-4f40-b2b0-65ebb9ce4678.png)
