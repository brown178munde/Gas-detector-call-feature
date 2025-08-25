#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(3,2); // RX, TX pins for GSM module
const int gasSensorPin = A1; // MQ2 gas sensor pin
int gasLevel;

void setup() {
  // Start communication with GSM module and Serial Monitor
  gsmSerial.begin(9600);  // GSM module baud rate (usually 9600)
  Serial.begin(9600);     // Serial Monitor baud rate

  pinMode(gasSensorPin, INPUT);

  delay(1000);
  
  // Send AT command to test GSM module
  gsmSerial.println("AT");
  delay(1000);
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }

  // Wait for GSM to be ready
  delay(1000);
  
}

void loop() {
  gasLevel = analogRead(gasSensorPin);

  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  if (gasLevel > 500) { // Replace 'threshold' with the desired gas level threshold
    sendSMS("+918290552295", "ALERT: gas leak");
  }

  delay(1000);
}

void sendSMS(String phoneNumber, String message) {
  // Set SMS mode to text mode

  gsmSerial.println("AT+CMGF=1");  
  delay(1000);
  
  
  // Send recipient phone number
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(1000);

  // Send message text
  gsmSerial.println(message);
  delay(100);

  // Send Ctrl+Z to send SMS
  gsmSerial.write(26);  // ASCII code for Ctrl+Z
  delay(1000);
  
  
  // Print confirmation to Serial Monitor 
  Serial.println("SMS sent successfully.");

}

