/*
 here's how I approached and completed each task:

Task 1: Defining Constants
In Task 1, the goal is to replace numeric literals in the code with named constants to make the code more robust and readable. Here's what I did:

- I identified the numeric literals in the code. These are the values that are used directly in calculations or comparisons, such as 3600 and 60.

- I decided to create named constants for these values to make the code more readable and maintainable. For example, I created const int SECONDS_IN_HOUR = 3600; and const int SECONDS_IN_MINUTE = 60; to represent these values.

- I replaced the numeric literals with the new constants in the code.

Task 2: Updating Software Design to Use Functions
Task 2 involves planning and designing functions that will be useful in the code. Here's how I approached this task:

- I identified parts of the code where common tasks are performed, such as reading an integer from the Serial port and converting hours, minutes, and seconds to total seconds.

- I thought about what parameters these functions would need (if any) and what they should return. For example,
the readIntegerInput function needs a prompt as a parameter and returns an integer.
The convertToSeconds function takes hours, minutes, and seconds as parameters and returns the total seconds.

- I didn't modify the code at this stage but focused on designing the functions and specifying their parameters and return values.

Task 3: Implementing Functions in Code
Task 3 involves actually writing the code for the functions designed in Task 2.
 Here's what I did to implement the functions:

- I created functions with the specified names and parameters. For example, I created the readIntegerInput
 function that takes a prompt as a parameter and returns an integer.

- In the setup function, I replaced the code for reading input from the Serial port with calls to the
 readIntegerInput function. This reduced the duplication of code and made it more modular.

- I also implemented the convertToSeconds function to calculate the total
seconds from hours, minutes, and seconds.

- In the setup function, I replaced the previous calculations and input reading with calls to
these new functions. This made the setup function more concise and easier to read.

- I continued to use a loop to handle multiple events,
and I printed the results using the printEventTime function.

By breaking down the code into functions and using constants, the code becomes more organized,
 easier to read, and less prone to errors. It also makes the code more modular and reusable, which
  is good programming practice.
*/

// Constants for array indices
const int SWIM_INDEX = 0;
const int BIKE_INDEX = 1;
const int RUN_INDEX = 2;
const int TOTAL_INDEX = 3;

// Constants for time conversion
const int SECONDS_IN_HOUR = 3600;
const int SECONDS_IN_MINUTE = 60;

// Array to store event times in seconds
unsigned long long eventTimes[4] = {0, 0, 0, 0};

String names[] = {"Swim", "Bike", "Run", "Total"};

// Function to read an integer input from Serial monitor
int readIntegerInput(String prompt)
{
    Serial.print(prompt);
    String input = "";
    while (true)
    {
        while (Serial.available())
        {
            char c = Serial.read();
            if (c == '\n')
            {
                Serial.print(input.toInt());
                Serial.println(" ");
                return input.toInt();
                // break; // return input;
            }
            input += c;
        }
    }
    // return Serial.parseInt();
}

// Function to convert hours, minutes, and seconds to total seconds
unsigned long long convertToSeconds(int hours, int minutes, int seconds)
{
    return static_cast<unsigned long long>(hours) * SECONDS_IN_HOUR +
           static_cast<unsigned long long>(minutes) * SECONDS_IN_MINUTE +
           static_cast<unsigned long long>(seconds);
}

// Function to print the event time
void printEventTime(String eventName, unsigned long long eventTime)
{
    int hours = eventTime / SECONDS_IN_HOUR;
    eventTime %= SECONDS_IN_HOUR;
    int minutes = eventTime / SECONDS_IN_MINUTE;
    int seconds = eventTime % SECONDS_IN_MINUTE;

    Serial.print(eventName);
    Serial.print(" time: ");
    Serial.print(hours);
    Serial.print(" hr  ");
    Serial.print(minutes);
    Serial.print(" min ");
    Serial.print(seconds);
    Serial.println(" sec");
}

void setup()
{
    Serial.begin(9600);

    // Task 2: Read times from the serial port and convert to seconds
    for (int i = 0; i < 3; i++)
    {
        int hours, minutes, seconds;

        hours = readIntegerInput("Enter hours for " + names[i] + ": ");
        minutes = readIntegerInput("Enter minutes for " + names[i] + ": ");
        seconds = readIntegerInput("Enter seconds for " + names[i] + ": ");

        eventTimes[i] = convertToSeconds(hours, minutes, seconds);
    }

    // Calculate the total time and store it in the array
    eventTimes[TOTAL_INDEX] = eventTimes[SWIM_INDEX] + eventTimes[BIKE_INDEX] + eventTimes[RUN_INDEX];

    // Task 3: Output the event times in the specified format
    for (int i = 0; i < 4; i++)
    {
        printEventTime(names[i], eventTimes[i]);
    }

    // Wait for a demonstrator to test your program
    while (true)
    {
    }
}

void loop()
{
    // The loop function remains empty in this code
}
