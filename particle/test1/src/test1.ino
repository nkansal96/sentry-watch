#include "InternetButton/InternetButton.h"
#include "math.h"

/*Did you know that the SparkButton can detect if it's moving? It's true!
Specifically it can read when it's being accelerated. Recall that gravity
is a constant acceleration and this becomes very useful- you know the orientation!*/

SYSTEM_MODE(SEMI_AUTOMATIC);

InternetButton b = InternetButton();
int btnCounter = 0;
int arrX[3] = {1};


void setup() {
    //Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
    int arrXCounter = 0;
    while (arrXCounter < 3)
      arrX[arrXCounter++] = b.readX();
}

/*Segmented-Least-Squares(n) Array M[0...n]
Set M[0]=0
For all pairs i≤j
Compute the least squares error ei , j
Endfor
for the segment
pi , . . . , pj
For j=1,2,...,n
Use the recurrence (6.7) to compute M[j]
Endfor Return M[n]*/

void loop(){ // one time is 50 ms
    b.allLedsOff();

    delay(100);
    int i = 0;
    for (i = 1; i < 3; i++) {
        arrX[i - 1] = arrX[i];
    }
    //How much are you moving in the x direction? (look at the white text on the board)
    int xValue = b.readX();

    //How about in the y direction?
    int yValue = b.readY();

    //And the z!
    int zValue = b.readZ();
    arrX[2] = xValue;
    int comp = abs(arrX[1] - arrX[0]);
    for (i = 2; i < 3; i++) {
        int comp2 = abs(arrX[i] - arrX[i-1]);
        if (comp > 0 && comp2 > 0 && comp2 > (comp + (comp << 2))) {
          /*lightsOn = 2;*/
          b.allLedsOn(abs(xValue), abs(yValue), abs(zValue));
          Serial.print(comp);
          Serial.print(", ");
          Serial.println(comp2);
          Serial.println("JOLT");
        }
        comp = comp2;
    }

    Serial.print(xValue);
    Serial.print(", ");
    Serial.print(yValue);
    Serial.print(", ");
    Serial.println(zValue);


    //This will make the color of the Button change with what direction you shake it
    //The abs() part takes the absolute value, because negatives don't work well
    // b.allLedsOn(abs(xValue), abs(yValue), abs(zValue));
    //b.ledOn(6, 0, 0, 255);
    if(b.buttonOn(2)){
        btnCounter = btnCounter + 1;
        if (btnCounter == 60) {
          Serial.println("FOUND");
        }
    }
    // And if the button's not on, then the LED should be off
    else {
        b.ledOff(3);
        btnCounter = 0;
    }

    //Wait a mo'
    delay(50);
}
