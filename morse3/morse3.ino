const int GREEN_LED = 8; // Replace with the actual pin number for the green LED
const int BLUE_LED = 9;  // Replace with the actual pin number for the blue LED
const int RED_LED = 10;   // Replace 10 with the actual pin number
const int ORANGE_LED = 11; // Replace 11 with the actual pin number
const int YELLOW_LED = 12; // Replace 12 with the actual pin number

// Function to encode ASCII text to BCCode
String encodeToBCCode(String input) {
  String bcCode = "";
  for (char c : input) {
    bcCode += "<" + String(c) + ">";
  }
  return bcCode;
}

// Function to decode BCCode to ASCII text
String decodeFromBCCode(String bcCode) {
  String decodedText = "";

  // Iterate through the characters in BCCode
  for (int i = 0; i < bcCode.length(); i++) {
    // Check if the current character is '<'
    if (bcCode[i] == '<') {
      // Find the position of '>' after '<'
      int endPos = bcCode.indexOf('>', i);

      // Check if '>' is found
      if (endPos != -1) {
        // Extract the substring between '<' and '>'
        String encodedChar = bcCode.substring(i + 1, endPos);

        // Append the decoded character to the result
        decodedText += encodedChar;

        // Move the index to the position after '>'
        i = endPos;
      }
    }
  }

  return decodedText;
}

// Function to flash BCCode on the green LED
void flashGreenLED(String bcCode) {
  // Adjust the BCCode transmission speed based on the potentiometer value
  int potValue = analogRead(A0);
  int bcCodeTimeUnit = map(potValue, 0, 1023, 20, 400);

  // Iterate through the characters in BCCode and flash the green LED
  for (char c : bcCode) {
    digitalWrite(GREEN_LED, HIGH);
    delay(bcCodeTimeUnit);
    digitalWrite(GREEN_LED, LOW);
    delay(bcCodeTimeUnit);
  }
}

// Function to flash BCCode on the blue LED
void flashBlueLED(String bcCode) {
  // Adjust the BCCode transmission speed based on the potentiometer value
  int potValue = analogRead(A0);
  int bcCodeTimeUnit = map(potValue, 0, 1023, 20, 400);

  // Iterate through the characters in BCCode and flash the blue LED
  for (char c : bcCode) {
    digitalWrite(BLUE_LED, HIGH);
    delay(bcCodeTimeUnit);
    digitalWrite(BLUE_LED, LOW);
    delay(bcCodeTimeUnit);
  }
}

// Function to respond to command messages
void processCommand(String command) {
  char cmdType = command.charAt(0);
  Serial.print("command ");
  Serial.println(cmdType);

  if (cmdType == 'B') {
    int xValue = command.charAt(1) - '0';
    if (xValue >= 1 && xValue <= 9 && xValue % 2 == 0) {
      // Read analog value from the potentiometer and transmit as 4 decimal digits in BCCode
      int potValue = analogRead(A0);
      String potBCCode = encodeToBCCode(String(potValue, DEC));
      Serial.println(potBCCode);
    }
    if (command.charAt(1) == 'C') {
      int redBrightness = (command.charAt(2) - '0') * 100 + (command.charAt(3) - '0') * 10 + (command.charAt(4) - '0');
      if (redBrightness <= 255) {
        analogWrite(RED_LED, redBrightness);
        delay(250);
        analogWrite(RED_LED, 0); // Set brightness to zero after 250ms
      }
    } else if (command.charAt(1) == 'B') {
      int bbValue = command.substring(2).toInt();
      flashLEDs(bbValue);
    }

  } else if (cmdType == 'P') {
    int sum = 0;
    Serial.print("sum ");
    Serial.println(sum);
    for (int i = 2; i < 5; i++) {
      sum += (command.charAt(i) - '0');
    }
    Serial.print("sum ");
    Serial.println(sum);
    if (sum < 10) {
      // Read value from IR receiver and transmit as "HIGH" or "LOW"
      // Replace the next line with your actual logic for IR receiver input
      String irValue = "HIGH"; // Change this line
      Serial.println(irValue);
    } else {
      Serial.println("UNKNOWN");
    }
  }
}

// Function to flash LEDs based on BB command value
void flashLEDs(int bbValue) {
  for (int i = 0; i < 4; i++) {
    int divisor = pow(10, 3 - i);
    int digitValue = bbValue / divisor;
    bbValue %= divisor;

    flashSingleLED(i, digitValue);
  }
}

// Function to flash a single LED based on BB command value
void flashSingleLED(int ledIndex, int digitValue) {
  int ledPin;
  switch (ledIndex) {
    case 0: // Orange
      ledPin = ORANGE_LED;
      break;
    case 1: // Green
      ledPin = GREEN_LED;
      break;
    case 2: // Red
      ledPin = RED_LED;
      break;
    case 3: // Yellow
      ledPin = YELLOW_LED;
      break;
    default:
      return;
  }

  int flashDuration = digitValue * 100;
  digitalWrite(ledPin, HIGH);
  delay(flashDuration);
  digitalWrite(ledPin, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(ORANGE_LED, OUTPUT);
  Serial.println("Ready to receive input...");
}

void loop() {
  if (Serial.available() > 0) {
    // Read a line from the Serial port
    String input = Serial.readStringUntil('\n');
    Serial.println(input);
    char firstChar = input.charAt(0);
    Serial.println(firstChar);

    if (firstChar == '*' || firstChar == '?' || firstChar == '<' || firstChar == 'B' || firstChar == 'P' || firstChar == 'C' || firstChar == 'B') {
      // BCCode or command detected, process the message

      if (firstChar == '*' || firstChar == '?' || firstChar == '<') {
        // BCCode detected, process as in Part 1 and Part 2
        if (firstChar == '*') {
          String message = input.substring(1); // Remove the first character
          String encodedMessage = encodeToBCCode(message);
          Serial.println("Encoded: " + encodedMessage);
          flashGreenLED(encodedMessage); // Flash green LED with encoded BCCode
        } else {
          String message = input.substring(0); // Remove the first character
          String decodedMessage = decodeFromBCCode(message);
          Serial.println("Decoded: " + decodedMessage);
          flashBlueLED(message); // Flash blue LED with original BCCode
        }
      } else {
        // Command detected, process as in Part 3
        String command = input.substring(0); // Remove the first character
        processCommand(command);
      }
    }
  }
}
