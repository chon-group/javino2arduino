/* Initial beliefs and rules */
serialPort(ttyEmulatedPort0).		// If you are using the simulIDE 
//serialPort(ttyACM0).			// If you are using a Arduino board in /dev/ttyACM0 
//serialPort(ttyUSB0).			// If you are using a Arduino board in /dev/ttyUSB0

/* Initial goals */
!connect.

/* Plans */
+!connect: serialPort(Port) <- 
	.print("Trying connection with the low-end IoT device in ",Port);
	argo.port(Port);
	argo.limit(1000);
	argo.percepts(open).

+ledStatus(Status): Status = on <-
	.print("I perceived that the LED is on. Turning OFF the LED on the low-end IoT device!");
	argo.act(ledOff).

+ledStatus(Status): Status = off <-
	.print("I perceived that the LED is off. Turning ON the LED on the low-end IoT device!");
	argo.act(ledOn).

+port(Port,Status): Status = timeout | Status = off <- 
	argo.percepts(close);
	.print("The serial port ",Port," status is ",Status,"!").