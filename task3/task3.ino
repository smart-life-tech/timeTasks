/*
In this code, the while loop allows you to input data for multiple athletes,
 and the program will stop when a negative swim hours input is encountered.
 It also tracks the fastest athlete and their total time.
 The DEBUG_ENABLED macro controls whether debugging output
  is displayed or not.

You can test the code in both DEBUG and RELEASE modes by changing
the value of DEBUG_ENABLED. When set to 1, it will enable debugging,
 and when set to 0, it will disable debugging. This allows you to test the
 code with and without debug statements.
*/

// for task 2 and 3
// Enable or disable debugging output
#define DEBUG_ENABLED 1  // Change this to 0 to disable debugging

#if DEBUG_ENABLED
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif


// Constants for array indices
const int SWIM_INDEX = 0;
const int BIKE_INDEX = 1;
const int RUN_INDEX = 2;
const int TOTAL_INDEX = 3;
// Array to store event times in seconds
unsigned long long eventTimes[4] = {0, 0, 0, 0};
unsigned long long eventTime [4] = {0, 0, 0, 0};// for the fastest record
// Constants for time conversion
const int SECONDS_IN_HOUR = 3600;
const int SECONDS_IN_MINUTE = 60;

// Function to read an integer input from Serial monitor

int readIntegerInput(String prompt)
{
  DEBUG_PRINT(prompt);
  String input = "";
  while (true)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (c == '\n')
      {
        DEBUG_PRINT(input.toInt());
        DEBUG_PRINTLN(" ");
        return input.toInt();
        // break; // return input;
      }
      input += c;
    }
  }
  // return Serial.parseInt();
}


// Function to convert hours, minutes, and seconds to total seconds
unsigned long long convertToSeconds(int hours, int minutes, int seconds) {
  return static_cast<unsigned long long>(hours) * SECONDS_IN_HOUR +
         static_cast<unsigned long long>(minutes) * SECONDS_IN_MINUTE +
         static_cast<unsigned long long>(seconds);
}

// Function to print the event time
void printEventTime(String eventName, unsigned long long eventTime) {
  int hours = eventTime / SECONDS_IN_HOUR;
  eventTime %= SECONDS_IN_HOUR;
  int minutes = eventTime / SECONDS_IN_MINUTE;
  int seconds = eventTime % SECONDS_IN_MINUTE;

  DEBUG_PRINT(eventName);
  DEBUG_PRINT(" time: ");
  DEBUG_PRINT(hours);
  DEBUG_PRINT(" hr  ");
  DEBUG_PRINT(minutes);
  DEBUG_PRINT(" min ");
  DEBUG_PRINT(seconds);
  DEBUG_PRINTLN(" sec");
}

void setup() {
  Serial.begin(9600);

  // Initialize variables for the fastest athlete
  int fastestAthlete = 1; // Initialize with the first athlete
  unsigned long long fastestTime = -1; // Initialize with a large value

  // Start an athlete index at 1
  int athleteIndex = 1;

  while (true) {
    int swimHours = readIntegerInput("Enter swim hours for Athlete " + String(athleteIndex) + ": ");

    // Check for a negative swim hours input to stop the program
    if (swimHours < 0) {
      DEBUG_PRINTLN("The fastest athlete was no. " + String(fastestAthlete) + " with a total time of:");
      printEventTime("Swim", eventTime[SWIM_INDEX]);
      printEventTime("Bike", eventTime[BIKE_INDEX]);
      printEventTime("Run", eventTime[RUN_INDEX]);
      printEventTime("Total", eventTime[TOTAL_INDEX]);
      break;
    }

    int bikeHours = readIntegerInput("Enter bike hours for Athlete " + String(athleteIndex) + ": ");
    int runHours = readIntegerInput("Enter run hours for Athlete " + String(athleteIndex) + ": ");

    // Calculate the event times for the current athlete
    eventTimes[SWIM_INDEX] = convertToSeconds(swimHours, readIntegerInput("Enter swim minutes: "), readIntegerInput("Enter swim seconds: "));
    eventTimes[BIKE_INDEX] = convertToSeconds(bikeHours, readIntegerInput("Enter bike minutes: "), readIntegerInput("Enter bike seconds: "));
    eventTimes[RUN_INDEX] = convertToSeconds(runHours, readIntegerInput("Enter run minutes: "), readIntegerInput("Enter run seconds: "));
    eventTimes[TOTAL_INDEX] = eventTimes[SWIM_INDEX] + eventTimes[BIKE_INDEX] + eventTimes[RUN_INDEX];

    // Display the athlete's times
    DEBUG_PRINTLN("Athlete " + String(athleteIndex) + " times:");
    printEventTime("Swim", eventTimes[SWIM_INDEX]);
    printEventTime("Bike", eventTimes[BIKE_INDEX]);
    printEventTime("Run", eventTimes[RUN_INDEX]);
    printEventTime("Total", eventTimes[TOTAL_INDEX]);

    // Check if this athlete is the fastest so far
    if (eventTimes[TOTAL_INDEX] < fastestTime) {
      fastestTime = eventTimes[TOTAL_INDEX];
      eventTime[SWIM_INDEX] = eventTimes[SWIM_INDEX];
      eventTime[BIKE_INDEX] = eventTimes[BIKE_INDEX];
      eventTime[RUN_INDEX] = eventTimes[RUN_INDEX];
      eventTime[TOTAL_INDEX] = eventTimes[TOTAL_INDEX];

      fastestAthlete = athleteIndex;
    }

    // Increment the athlete index
    athleteIndex++;
  }
}

void loop() {
  // The loop function remains empty in this code
}
