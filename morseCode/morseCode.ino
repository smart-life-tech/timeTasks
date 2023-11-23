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


void setup() {
  Serial.begin(9600);
  Serial.println("Ready to receive input...");
}

void loop() {
  if (Serial.available() > 0) {
    // Read a line from the Serial port
    String input = Serial.readStringUntil('\n');
    Serial.println(input);
    char firstChar = input.charAt(0);
    Serial.println(firstChar);
    if (firstChar == '*' || firstChar == '?' || firstChar == '<') {
      // BCCode detected, process the message


      // Perform encoding or decoding based on the BCCode type
      if (firstChar == '*') {
        String message = input.substring(1); // Remove the first character
        String encodedMessage = encodeToBCCode(message);
        Serial.println("Encoded: " + encodedMessage);
      } else {
        String message = input.substring(0); // Remove the first character
        String decodedMessage = decodeFromBCCode(message);
        Serial.println("Decoded: " + decodedMessage);
      }
    }
  }
}
