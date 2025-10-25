This project is a Condo flood monitoring system built using the PIC16F18877 microcontroller.
It detects water levels using sensors and provides visual and audible alerts through a 7-segment display, LCD, and buzzer.
The system aims to simulate flood detection in carparks or low-lying areas.

Youtube Video URL: https://youtube.com/shorts/hK0vwFBc_S0?si=l7SeD1ebDUvhcPaS



⚙️ Overview
	•	Microcontroller: PIC16F18877
	•	Language: Embedded C
	•	IDE: MPLAB X IDE
	•	Compiler: XC8
	•	Simulation: Proteus

🧠 Features
	•	Real-time flood level monitoring using sensors
	•	ADC conversion to process analog voltage inputs
	•	LCD and 7-segment display for level indication
	•	Buzzer alerts when water level crosses threshold
	•	Interrupts (IOC & ISR) for responsive event handling
	•	PWM control for dynamic output signals
	•	Tested and verified in Proteus simulation

⸻

🧪 How It Works
	1.	The sensor detects water level and sends an analog voltage to the PIC16F18877.
	2.	The ADC module converts the analog signal to a digital value.
	3.	The main program interprets the digital value and categorizes the flood level.
	4.	The LCD and 7-segment display show the corresponding flood level.
	5.	The buzzer activates when the water level exceeds the danger threshold.
	6.	Interrupts (IOC/ISR) ensure the system responds quickly to sudden changes.

⸻

📚 Learning Outcomes
	•	Understanding ADC, PWM, and interrupt handling on PIC microcontrollers
	•	Interfacing sensors, LCDs, and 7-segment displays
	•	Structuring modular embedded C code
	•	Simulating and debugging embedded systems in Proteus

⸻
🧾 Author

kenkanekiken
Computer Engineering Student @ Temasek Polytechnic
📍 Singapore
💡 Passionate about Embedded Systems | IoT | AI & Data Analytics
