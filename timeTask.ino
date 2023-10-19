// Constants for array indices
const int SWIM_INDEX = 0;
const int BIKE_INDEX = 1;
const int RUN_INDEX = 2;
const int TOTAL_INDEX = 3;

// Array to store event times in seconds
unsigned long long eventTimes[4] = {0, 0, 0, 0};
// Array to store event times in seconds

String names[] = {"Swim", "Bike", "Run", "Total"};
String readSerialInput() {
  String input = "";
  while (true) {
    while (Serial.available()) {
      char c = Serial.read();
      if (c == '\n') {
        return input;
      }
      input += c;
    }
  }
}
void setup() {
  Serial.begin(9600);
}

void loop() {
  // Task 2: Read times from the serial port and convert to seconds
  for (int i = 0; i < 3; i++) {
    int hours, minutes, seconds;
    Serial.print("Enter hours for " + names[i] + ": ");
    String input = readSerialInput();
    hours = input.toInt();
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
    //Serial.println(eventTimes[i]);
  }


  // Calculate the total time and store it in the array
  eventTimes[TOTAL_INDEX] = eventTimes[SWIM_INDEX] + eventTimes[BIKE_INDEX] + eventTimes[RUN_INDEX];

  // Task 3: Output the event times in the specified format
  for (int i = 0; i < 4; i++) {
    unsigned long long totalSeconds = eventTimes[i];
    int hours = totalSeconds / 3600;
    int minutes = 0;
    int seconds = 0;

    totalSeconds = eventTimes[i];;
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
  // Wait for a demonstrator to test your program
  while (true) {}
}
