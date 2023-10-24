// Constants for array indices
const int SWIM_INDEX = 0;
const int BIKE_INDEX = 1;
const int RUN_INDEX = 2;
const int TOTAL_INDEX = 3;

// Array to store event times in seconds
unsigned long long eventTimes[4] = {0, 0, 0, 0};
// Array to store event times in seconds

String names[] = {"Swim", "Bike", "Run", "Total"};

// Function to read input from Serial monitor until a newline character is encountered
String readSerialInput()
{
  String input = "";
  while (true)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (c == '\n')
      {
        return input;
      }
      input += c;
    }
  }
}
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Task 2: Read times from the serial port and convert to seconds
  for (int i = 0; i < 3; i++)
  {
    int hours, minutes, seconds;
    Serial.print("Enter hours for " + names[i] + ": ");
    String input = readSerialInput();
    hours = input.toInt(); // convert the string to inegers
    Serial.println(hours);
    Serial.print("Enter minutes for " + names[i] + ": ");
    input = readSerialInput();
    minutes = input.toInt();
    Serial.println(minutes);
    Serial.print("Enter seconds for " + names[i] + ": ");
    input = readSerialInput();
    seconds = input.toInt();
    Serial.println(seconds);
    eventTimes[i] = hours * 3600ULL + minutes * 60ULL + seconds;
    // Serial.println(eventTimes[i]);
  }

  /*
  The ULL (unsigned long long) suffix is used to explicitly specify
  the data type of a numeric literal in the code.
  3600ULL and 60ULL are numeric literals with the ULL
  suffix, which tells the compiler to treat these numbers as 64-bit unsigned integers.
  The reason for using ULL is to ensure that the numeric
  literals are treated as 64-bit unsigned integers, which
  is important when performing calculations with variables
   of that data type. This is particularly useful when dealing
   with large numbers, and it can help prevent potential overflow or type-related issues in the code.
  In the context of the code, it ensures that the result of
   the calculations is also treated as an unsigned long long, which matches the data type of the eventTimes array, allowing for safe and correct storage of the calculated values.
  */
  // Calculate the total time and store it in the array
  eventTimes[TOTAL_INDEX] = eventTimes[SWIM_INDEX] + eventTimes[BIKE_INDEX] + eventTimes[RUN_INDEX];

  // Task 3: Output the event times in the specified format
  for (int i = 0; i < 4; i++)
  {
    unsigned long long totalSeconds = eventTimes[i]; // read from the total timing calculations array
    int hours = totalSeconds / 3600;
    int minutes = 0;
    int seconds = 0;

    totalSeconds = eventTimes[i];
    /*
    The code you provided is used to convert the total time in seconds back
     into hours, minutes, and seconds. This is typically done when you want to display
    the total time in a human-readable format. Here's how the code works step by step:

1. `minutes = totalSeconds / 60;`: This line divides the `totalSeconds`
 by 60 to calculate the total number of minutes. The result is stored in
  the `minutes` variable. For example, if `totalSeconds` is 3665, this
   operation will result in `minutes` being set to 61 (3665 / 60).

2. `seconds = totalSeconds % 60;`: This line uses the modulo operator
(%) to find the remaining seconds after calculating the minutes. It
calculates the remainder when `totalSeconds` is divided by 60, which
represents the seconds part of the time. For example, if `totalSeconds`
is 3665, this operation will result in `seconds` being set to 5 (3665 % 60).

3. `hours = minutes / 60;`: This line calculates the hours by dividing
the `minutes` by 60. It accounts for any full hours in the `minutes` value.
For example, if `minutes` is 61, this operation will set `hours` to 1 (61 / 60).

4. `minutes = minutes % 60;`: Similar to the previous step, this line
uses the modulo operator to calculate the remaining minutes after extracting full hours.
 It calculates the remainder when `minutes` is divided by 60. This ensures that `minutes`
 doesn't exceed 59. In the example where `minutes` is 61, this operation will set `minutes` to 1 (61 % 60).

This sequence of operations is used to break down the `totalSeconds`
 value into hours, minutes, and seconds, ensuring that each component is within its respective valid range.
  The result is a human-readable representation of time.
    */
    minutes = totalSeconds / 60;
    seconds = totalSeconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;

    Serial.print(names[i]);
    Serial.print(" time: ");
    Serial.print(hours);
    Serial.print(" hr  ");
    Serial.print(minutes);
    Serial.print(" min ");
    Serial.print(seconds);
    Serial.println("sec");
  }
  // Wait for a demonstrator to test your program, code only runs once
  while (true)
  {
  }
}
