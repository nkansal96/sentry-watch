#include "InternetButton/InternetButton.h"
#include "math.h"

/*Did you know that the SparkButton can detect if it's moving? It's true!
Specifically it can read when it's being accelerated. Recall that gravity
is a constant acceleration and this becomes very useful- you know the orientation!*/

SYSTEM_MODE(SEMI_AUTOMATIC);

InternetButton b = InternetButton();
int btnCounter = 0;
int arrXCounter = 0;
double C = 1000;
double INF = 10000000;
double counter = 0;
double total = 0;
double slopeArr[5] = {-1};
int resetTimer = 40;
int leds = 0;

#define MAXN 15
#define N 10

struct Point {
	int x, y;
} points[MAXN + 1];

void setup() {
    //Tell b to get everything ready to go
    // Use b.begin(1); if you have the original SparkButton, which does not have a buzzer or a plastic enclosure
    // to use, just add a '1' between the parentheses in the code below.
    b.begin();
		b.setBrightness(100);
}

void loop(){ // one time is 50 ms
	delay(20);
  if (arrXCounter < (N+5)) {
    points[arrXCounter].x = arrXCounter;
    points[arrXCounter++].y = abs(b.readX());
    Serial.printf("IN LOOP [%d] %d\n", points[arrXCounter - 1].x, points[arrXCounter - 1].y);
    return;
  }
	counter += 1;

    //b.allLedsOff();
		// this shifts stuff
    int i = 0;
    for (i = 1; i < N; i++) {
        points[i - 1].y = points[i].y;
    }
    //How much are you moving in the x direction? (look at the white text on the board)
    int xValue = b.readX();

    //How about in the y direction?
    int yValue = b.readY();

    //And the z!
    int zValue = b.readZ();

		if (counter < 6) {
			total += abs(xValue);
			return;
		}
		else {
			points[N - 1].y = total / 5.0;
			total = 0;
			counter = 0;
		}

    if (arrXCounter >= (N+5)) {
      double cumulative_x[MAXN + 1], cumulative_y[MAXN + 1], cumulative_xy[MAXN + 1], cumulative_xSqr[MAXN + 1];
      double slope[MAXN + 1][MAXN + 1], intercept[MAXN + 1][MAXN + 1], E[MAXN + 1][MAXN + 1];

      double OPT[MAXN + 1];
      double opt_segment[MAXN + 1];

      int i, j, k, interval;
      double x_sum, y_sum, xy_sum, xsqr_sum, num, denom;
      double tmp;
			double temp;
			double teemp;

      cumulative_x[0] = cumulative_y[0] = cumulative_xy[0] = cumulative_xSqr[0] = 0;
      for (j = 1; j <= N; j++)	{
        cumulative_x[j] = cumulative_x[j-1] + points[j].x;
        cumulative_y[j] = cumulative_y[j-1] + points[j].y;
        cumulative_xy[j] = cumulative_xy[j-1] + points[j].x * points[j].y;
        cumulative_xSqr[j] = cumulative_xSqr[j-1] + points[j].x * points[j].x;

        for (i = 1; i <= j; i++)	{
          interval = j - i + 1;
          x_sum = cumulative_x[j] - cumulative_x[i-1];
          y_sum = cumulative_y[j] - cumulative_y[i-1];
          xy_sum = cumulative_xy[j] - cumulative_xy[i-1];
          xsqr_sum = cumulative_xSqr[j] - cumulative_xSqr[i-1];

          num = interval * xy_sum - x_sum * y_sum;

          if (num == 0)
            slope[i][j] = 0.0;
          else {
            denom = interval * xsqr_sum - x_sum * x_sum;
            slope[i][j] = (denom == 0) ? INF : (num / double(denom));
          }

          double ttt = slope[i][j];
          intercept[i][j] = (y_sum - ttt * x_sum) / double(interval);
					teemp = intercept[i][j];

          int q;
          for (q = i, E[i][j] = 0.0; q <= j; q++)	{
            tmp = points[q].y - (ttt * points[q].x) - teemp;
            E[i][j] += tmp * tmp;
            Serial.flush();
          }
        }
      }

      OPT[0] = 0;
      opt_segment[0] = 0;
			double try1;
      for (j = 1; j <= N; j++)	{
				double mn = INF;
				k = 0;
        for (i = 1; i <= j; i++)	{
					temp = E[i][j] + OPT[i-1];
          if (temp < mn)	{
            mn = temp;
            k = i;
          }
        }
				OPT[j] = mn + C;
        opt_segment[j] = k;
      }

      // find the optimal solution
      int segments[N + N];
      k = 0;
      for (i = N, j = opt_segment[N]; i > 0; i = j-1, j = opt_segment[i])	{
        segments[k++] = i;
        segments[k++] = j;
      }
      //Serial.printf("\nAn optimal solution (%d):\n", k);
      while (k > 0)	{
        i = segments[--k];//segments.top(); segments.pop();
        j = segments[--k];//segments.top(); segments.pop();
        /*Serial.printf("Segment (y = %lf * x + %lf) from points %d to %d with square error %lf.\n",
            slope[i][j], teemp, i, j, E[i][j]);*/
				//Serial.printf("%f\n", slope[i][j]);
				int a = 1;
				for (a = 1; a < 5; a++) {
						slopeArr[a - 1] = slopeArr[a];
		    }
				slopeArr[4] = slope[i][j];
      }
    }
		/*Serial.printf("%f, %f, %f\n", slopeArr[0], slopeArr[1], slopeArr[2]);*/

		for (int u = 0; u < 4; u++) {
			double A = max(abs(slopeArr[u]), abs(slopeArr[u+1]));
			double B = min(abs(slopeArr[u]), abs(slopeArr[u+1]));
			double C = abs(slopeArr[1]);
			double D = abs(slopeArr[3]);
			Serial.printf("%f, %f, %f, %f, %f\n", slopeArr[0], slopeArr[1], slopeArr[2], slopeArr[3], slopeArr[4]);
			if (C == 0 || D == 0)
					continue;
			if (A/B > 20.0 && B > 0.5) {
					Serial.printf("Adding an LED: %d\n", leds);
					if (leds < 11)
						b.ledOn(++leds, 0, leds*10, leds*13);
					if (leds >= 11) {
						// send to the server
					}
					resetTimer = 40;
			} else {
				resetTimer -= 1;
				if (resetTimer == 0) {
					resetTimer = 40;
					if (leds > 0) {
						b.ledOff(leds--);
					}
				}
			}
		}



    //This will make the color of the Button change with what direction you shake it
    //The abs() part takes the absolute value, because negatives don't work well
    // b.allLedsOn(abs(xValue), abs(yValue), abs(zValue));
    //b.ledOn(6, 0, 0, 255);
    /*if(b.buttonOn(2)){
        btnCounter = btnCounter + 1;
        if (btnCounter == 60) {
          Serial.println("FOUND");
        }
    }*/
    // And if the button's not on, then the LED should be off
    /*else {
        b.ledOff(3);
        btnCounter = 0;
    }*/
}






/*int analyzePoints()	{
  Serial.println("A");
  Serial.flush();
	long long cumulative_x[MAXN + 1], cumulative_y[MAXN + 1], cumulative_xy[MAXN + 1], cumulative_xSqr[MAXN + 1];
	double slope[MAXN + 1][MAXN + 1], intercept[MAXN + 1][MAXN + 1], E[MAXN + 1][MAXN + 1];

	double OPT[MAXN + 1];
	int opt_segment[MAXN + 1];

	int i, j, k, interval;
	long long x_sum, y_sum, xy_sum, xsqr_sum, num, denom;
	double tmp, mn;

	// precompute the error terms

    Serial.println("B");
    Serial.flush();
	cumulative_x[0] = cumulative_y[0] = cumulative_xy[0] = cumulative_xSqr[0] = 0;
	for (j = 1; j <= N; j++)	{

      Serial.printf("-- C %d\n", j);
      Serial.flush();
		cumulative_x[j] = cumulative_x[j-1] + points[j].x;
		cumulative_y[j] = cumulative_y[j-1] + points[j].y;
		cumulative_xy[j] = cumulative_xy[j-1] + points[j].x * points[j].y;
		cumulative_xSqr[j] = cumulative_xSqr[j-1] + points[j].x * points[j].x;

		for (i = 1; i <= j; i++)	{

        Serial.printf("-- -- D %d\n", i);
        Serial.flush();
			interval = j - i + 1;
			x_sum = cumulative_x[j] - cumulative_x[i-1];
			y_sum = cumulative_y[j] - cumulative_y[i-1];
			xy_sum = cumulative_xy[j] - cumulative_xy[i-1];
			xsqr_sum = cumulative_xSqr[j] - cumulative_xSqr[i-1];

			num = interval * xy_sum - x_sum * y_sum;
			if (num == 0)
				slope[i][j] = 0.0;
			else {
				denom = interval * xsqr_sum - x_sum * x_sum;
				slope[i][j] = (denom == 0) ? INF : (num / double(denom));
			}

      intercept[i][j] = (y_sum - slope[i][j] * x_sum) / double(interval);

 		  for (k = i, E[i][j] = 0.0; k <= j; k++)	{
  			tmp = points[k].y - slope[i][j] * points[k].x - intercept[i][j];
  			E[i][j] += tmp * tmp;
        Serial.printf("-- -- -- E %d %f\n", k, E[i][j]);
        Serial.flush();
  		}
		}
	}

	// find the cost of the optimal solution

  Serial.println("at optimal cost");
  Serial.flush();
	OPT[0] = 0;
  opt_segment[0] = 0;
	for (j = 1; j <= N; j++)	{
		for (i = 1, mn = INF, k = 0; i <= j; i++)	{
			tmp = E[i][j] + OPT[i-1];
      Serial.printf("--- tmp val %f\n", tmp);
      Serial.flush();
			if (tmp < mn)	{
				mn = tmp;
				k = i;
			}
		}
		OPT[j] = mn + C;
		opt_segment[j] = k;
	}

	Serial.printf("\nCost of the optimal solution : %lf\n", OPT[N]);
  Serial.flush();

	// find the optimal solution
	//vector <int> segments;
	int segments[N + N];
	k = 0;
	for (i = N, j = opt_segment[N]; i > 0; i = j-1, j = opt_segment[i])	{
		segments[k++] = i;
		segments[k++] = j;
		//segments.push(i);
		//segments.push(j);
	}

	Serial.printf("\nAn optimal solution :\n");
	while (k > 0)	{
		i = segments[--k];//segments.top(); segments.pop();
		j = segments[--k];//segments.top(); segments.pop();
		Serial.printf("Segment (y = %lf * x + %lf) from points %d to %d with square error %lf.\n",
				slope[i][j], intercept[i][j], i, j, E[i][j]);
	}

	return 0;
}*/
