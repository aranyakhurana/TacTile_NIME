/*
  Matrix: Kapton + Copper
  A simple pressure sensor matrix made from two Kapton film sheets with
  7x7 copper tape traces and a piece of Velostat or Eeonyx piezoresistive
  material in between.
  Parsing through this grid by switching individual rows/columns to be
  HIGH, LOW, or INPUT (high impedance) to detect location and pressure.
  >> http://howtogetwhatyouwant.at/
*/

#define numRows 10
#define numCols 10
#define sensorPoints numRows * numCols


// the comments below are based on the processing sketch matrix visualisation:
int rows[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9}; // (add ... at the end for 10 strips) these can be thought of as up and down sliders; A0 is the left-most UD slider, A6 is the right-most
int cols[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; // (add ... at the beginning for 10 strips) these can be thought of as left and right sliders; 11 is the top-most LR slider, 5 is the lowest
int incomingValues[sensorPoints] = {};

void setup() {
  // Set all rows and columns to INPUT (high impedance):
  for (int i = 0; i < numRows; i++) {
    pinMode(rows[i], INPUT_PULLUP); // previously INPUT_PULLUP
  }
  for (int i = 0; i < numCols; i++) {
    pinMode(cols[i], INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for (int colCount = 0; colCount < numCols; colCount++) {
    pinMode(cols[colCount], OUTPUT); // Set as OUTPUT
    digitalWrite(cols[colCount], LOW); // Set LOW
    for (int rowCount = 0; rowCount < numRows; rowCount++) {
      incomingValues[colCount * numRows + rowCount] = analogRead(rows[rowCount]); // Read INPUT
    } // End rowCount
    pinMode(cols[colCount], INPUT); // Set back to INPUT
  } // End colCount

  // Print the incoming values of the grid:
  for (int i = 0; i < sensorPoints; i++) {
    Serial.print(incomingValues[i]);
    if (i < sensorPoints - 1)
      Serial.print("\t");
  }
  Serial.println();
  delay(10);
}
