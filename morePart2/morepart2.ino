const int GREEN_LED = 8; // Replace with the actual pin number for the green LED
const int BLUE_LED = 9;  // Replace with the actual pin number for the blue LED

// Function to encode ASCII text to BCCode
String encodeToBCCode(String input)
{
    String bcCode = "";
    for (char c : input)
    {
        bcCode += "<" + String(c) + ">";
    }
    return bcCode;
}

// Function to decode BCCode to ASCII text
String decodeFromBCCode(String bcCode)
{
    String decodedText = "";

    // Iterate through the characters in BCCode
    for (int i = 0; i < bcCode.length(); i++)
    {
        // Check if the current character is '<'
        if (bcCode[i] == '<')
        {
            // Find the position of '>' after '<'
            int endPos = bcCode.indexOf('>', i);

            // Check if '>' is found
            if (endPos != -1)
            {
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
void flashGreenLED(String bcCode)
{
    // Adjust the BCCode transmission speed based on the potentiometer value
    int potValue = analogRead(A0);
    int bcCodeTimeUnit = map(potValue, 0, 1023, 20, 400);

    // Iterate through the characters in BCCode and flash the green LED
    for (char c : bcCode)
    {
        digitalWrite(GREEN_LED, HIGH);
        delay(bcCodeTimeUnit);
        digitalWrite(GREEN_LED, LOW);
        delay(bcCodeTimeUnit);
    }
}

// Function to flash BCCode on the blue LED
void flashBlueLED(String bcCode)
{
    // Adjust the BCCode transmission speed based on the potentiometer value
    int potValue = analogRead(A0);
    int bcCodeTimeUnit = map(potValue, 0, 1023, 20, 400);

    // Iterate through the characters in BCCode and flash the blue LED
    for (char c : bcCode)
    {
        digitalWrite(BLUE_LED, HIGH);
        delay(bcCodeTimeUnit);
        digitalWrite(BLUE_LED, LOW);
        delay(bcCodeTimeUnit);
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    Serial.println("Ready to receive input...");
}

void loop()
{
    if (Serial.available() > 0)
    {
        // Read a line from the Serial port
        String input = Serial.readStringUntil('\n');
        Serial.println(input);
        char firstChar = input.charAt(0);
        Serial.println(firstChar);
        if (firstChar == '*' || firstChar == '?' || firstChar == '<')
        {
            // BCCode detected, process the message

            // Perform encoding or decoding based on the BCCode type
            if (firstChar == '*')
            {
                String message = input.substring(1); // Remove the first character
                String encodedMessage = encodeToBCCode(message);
                Serial.println("Encoded: " + encodedMessage);
                flashGreenLED(encodedMessage); // Flash green LED with encoded BCCode
            }
            else
            {
                String message = input.substring(0); // Remove the first character
                String decodedMessage = decodeFromBCCode(message);
                Serial.println("Decoded: " + decodedMessage);
                flashBlueLED(message); // Flash blue LED with original BCCode
            }
        }
    }
}
