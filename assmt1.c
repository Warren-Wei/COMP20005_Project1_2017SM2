/* Assignment 1 of COMP20005
 * written by Dongwei Wei(728580)
 * C Programming is fun!
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define REFERENCE_POINT_LONGITUDE 144.963123
                                  /* The longitude of reference point */
#define REFERENCE_POINT_LATITUDE  -37.810592
                                  /* The latitude of reference point */
#define PI 3.14159 /* The value of PI used for toRadian function */
#define NUMBER_OF_DAYS_PER_WEEK 7 /* The number of days each week */
#define MAX_NUMBER_OF_CHARACTERS_OF_DAY_OF_WEEK 10 /* The max number of
                charcters of day of a week (Wednesday) plus a null byte space */
#define KM_PER_RADIAN 6371 /* Value used for transfer from radian to km */
#define DEGREE_OF_STRAIGHT_ANGLE 180 /* The degree of the straight angle */
#define TRUE 1 /* Just the value of true */
#define FALSE 0 /* Just the value of false */
#define NUMBER_OF_VARAIBLES_EACH_LINE 8 /* The number of variables of each line
                                          in test file */


/* Function prototype */
void printStage1(int id, double lon, double lat, int day, int month, int year,
                 int times, double dist);
void printStage2(int id, double dist, int havePrintedStage2Head);
void printStage3(int totalAccidentsNumber, char * mostAccidentsDay,
                 int numberOfAccidents);
int indexOfTheMostAccidentDay(int accidentNumberPerDay[]);
double angleDistance(double lon, double lat);
double chordLength(double lon1, double lat1);
double toRadian(double x);


/* The main function to execute the entire program */
int main(int argc, char* argv[]){
   int id, day, month, year, times, i, index;
   double lon, lat, dist;
   char * daysOfWeek[NUMBER_OF_DAYS_PER_WEEK] = {"Monday", "Tuesday",
                                                "Wednesday", "Thursday",
                                                "Friday", "Saturday", "Sunday"};
   int accidentNumberPerDay[NUMBER_OF_DAYS_PER_WEEK] = { 0 };
                          /* Initilise the number of accident per day to zero */
   char currentDayOfWeek[MAX_NUMBER_OF_CHARACTERS_OF_DAY_OF_WEEK];
   int havePrintedStage1 = FALSE, havePrintedStage2Head = FALSE;
   int totalAccidentNumberCounter = 0;

   /* This loop scan one line of the file each time*/
   while ((scanf("%d %lf %lf %d/%d/%d %d %s", &id, &lon, &lat, &day, &month,
          &year, &times, currentDayOfWeek)) == NUMBER_OF_VARAIBLES_EACH_LINE){

          dist = KM_PER_RADIAN * angleDistance(lon, lat);
          totalAccidentNumberCounter ++;

          if (!havePrintedStage1){
            printStage1(id, lon, lat, day, month, year, times, dist);
            printStage2(id, dist, havePrintedStage2Head);
            havePrintedStage1 = TRUE;
            havePrintedStage2Head = TRUE;
          } else {
            printStage2(id, dist, havePrintedStage2Head);
          }

          for (i = 0; i < NUMBER_OF_DAYS_PER_WEEK; i++){
            if (strcmp(currentDayOfWeek, daysOfWeek[i]) == 0){
              accidentNumberPerDay[i] ++;
            }
          }
          getchar(); /* To get rid of the new line character of each line */
   }

   index = indexOfTheMostAccidentDay(accidentNumberPerDay);
   printStage3(totalAccidentNumberCounter, daysOfWeek[index],
               accidentNumberPerDay[index]);
   return 0;
}


/* print out the stage 1 to standard output */
void printStage1(int id, double lon, double lat, int day, int month, int year,
                 int times, double dist){
  printf("Stage 1\n");
  printf("==========\n");
  printf("Accident: #%d\n", id);
  printf("Location: <%.6f, %.6f>\n", lon, lat);
  printf("Date: %d/%d/%d\n", day, month, year);
  printf("Time: %02d\n", times);
  printf("Distance to reference: %05.2f\n", dist);
}


/* print out the stage 2 to standard output */
void printStage2(int id, double dist, int havePrintedStage2Head){
  int i;
  if (!havePrintedStage2Head){
    printf("\nStage 2\n");
    printf("==========\n");
  }
  printf("Accident: #%d, ", id);
  printf("distance to reference: %05.2f |", dist);
  for (i = 1; i < dist+1; i++){
    if (i % 10 == 0){
      printf("+");
    } else {
      printf("-");
    }
  }
  printf("\n");
}


/* print out the stage 2 to standard output */
void printStage3(int totalAccidentsNumber, char * mostAccidentsDay,
                 int numberOfAccidents) {
  printf("\nStage 3\n");
  printf("==========\n");
  printf("Number of accidents: %d\n", totalAccidentsNumber);
  printf("Day of week with the most accidents: %s ", mostAccidentsDay);
  printf("(%d accident(s))\n", numberOfAccidents);
}


/* Calculate and return the angle distance which is used to calculate the
   distance between the accident location and the reference point */
double angleDistance(double lon, double lat) {
  return 2 * atan2(sqrt(chordLength(lon, lat)),sqrt(1 - chordLength(lon, lat)));
}


/* Calculate and return the chord length */
double chordLength(double lon1, double lat1) {
  double lon2 = REFERENCE_POINT_LONGITUDE;
  double lat2 = REFERENCE_POINT_LATITUDE;
  return pow((sin(toRadian(lat2 - lat1) / 2)), 2) + cos(toRadian(lat1))
        * cos(toRadian(lat2)) * pow((sin(toRadian(lon2 - lon1) / 2)), 2);
}


/* Converts a longitude or latitude coordinate x to its radian value */
double toRadian(double x) {
  return x * (PI / DEGREE_OF_STRAIGHT_ANGLE);
}


/* To find the maximum number of the accident of the day in a week and return
   this index */
int indexOfTheMostAccidentDay(int accidentNumberPerDay[]) {
  int i = 0;
  int maxAccidentsNumber = accidentNumberPerDay[i];
  int maxIndex = 0; /* Index of the most numbers of the accident day */
  for (i = 1; i < NUMBER_OF_DAYS_PER_WEEK; i++){
    if (accidentNumberPerDay[i] > maxAccidentsNumber) {
      maxAccidentsNumber = accidentNumberPerDay[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}
