# project-computer-architecture
This project is a simulation of entering a bank account via Arduino.

The components that were used to build this project were: Adafruit I2C OLED display, Arduino Uno, a numeric keypad, Piezo speaker, 2 LED lights, 3 resistors, and jumpers. First, we connected the keypad to the Arduino, carefully connecting it due to the layout (4 rows and 4 columns; connected to 8 digital pins). The keypad allows the user to enter the 4-digit pin. The three resistors control the flow of electricity to the LED lights. Without them, they would burn out eventually. For this project, two red, and one green LED was used. The LEDs are connected to the first three digital pins. In addition, one of the wires from the speaker needs to be connected to the ground always.

<img width="899" height="412" alt="Screenshot 2026-08-12 165127" src="https://github.com/user-attachments/assets/2288b9bf-07ce-47e5-ac98-302dee25c8cf" />

When turned on, the display will have ”Enter pin” written on it. There, the user must enter his pin in order for it to be compared again in the log in process (this was done to escape hard coding). When the user enters his pin, he has to go through log in, where he has three tries to enter his bank account. The pin must be 4 digits long and only consist of numbers from 0 to 9. During the entering, the digits will be represented as “*” to hide the pin from the sight of others.

<img width="496" height="354" alt="Screenshot 2026-08-12 165134" src="https://github.com/user-attachments/assets/3dba65f8-be7f-4801-ac8a-3fdfe942b347" />

When the pin is entered, the user must click on the ”#” sign to determine that he entered the pin. Then, the comparison between the first pin and the second entered pin will be done. If the pin is correct, a green LED will turn on, and the speaker will create a sound that lasts two seconds (with delays). In addition, on the display will be written ”Welcome”.

<img width="643" height="393" alt="Screenshot 2026-08-12 165141" src="https://github.com/user-attachments/assets/6678aae8-7f71-4145-9614-b302abba3582" />

On the other hand, if the pin is not correct, a red LED will turn on, the speaker will create a sound that lasts three seconds, and the display will output ”Incorrect. Try again”. The program will allow the user to keep entering his pin until it is correct and until he runs out of tries. When the process is done, the user has the ability to press the “*” sign which will restart the program.

<img width="660" height="479" alt="Screenshot 2026-08-12 165149" src="https://github.com/user-attachments/assets/9bb4bbe1-5afe-4f49-87b5-dd811937e3ba" />
