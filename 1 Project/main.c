#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include "headers/heap.h"
#include "headers/median.h"
#include "headers/quick.h"
#include "headers/utils.h"

#define increases 50

//increase stack size: gcc -Wl,--stack,4194304 -o namefile namefile.c

//definition of clock variables, of the arrays for execution time
//and the standard deviation of each algorithm and of the file pointer
double execTime[increases];
int size = 100;
int repetitions = 100;
int input[1000000];
FILE *fp;

void quickTimes(double *execTime, int *input, int size, int k, int repetitions, int pos);
void heapTimes(double *execTime, int *input, int size, int k, int repetitions, int pos);
void medianTimes(double *execTime, int *input, int size, int k, int repetitions, int pos);

int main(){

    //initialization of size, repetitions and pos
    srand((unsigned)time(NULL));
    int pos=0; //position for execution time and std in their array
   

    //make the intestation for the file where are stored the times of the algorithms
    fp = fopen("times/times.txt", "w");
    fprintf(fp, "\nsize\t\treps");
    //fprintf(fp, "\t\tquick execution\tquick std");
    fprintf(fp, "\t\theap execution\theap std");
    //fprintf(fp, "\t\tmedian execution\tmedian std");
    fprintf(fp, "\n\n");
    fclose(fp);

    while(size!=-1)
    {
        //calculate a random k and fill the input array with rand ints
        int k = randomInt(1, size);
        randomArray(input, size);

        //each method takes the times for their respective algorithm
        //quickTimes(execTime, input, size, k, repetitions, pos);
        heapTimes(execTime, input, size, k, repetitions, pos);
        //medianTimes(execTime, input, size, k, repetitions, pos);

        //save the time values of the array in the file
        fp = fopen("times/times.txt", "a");
        fprintf(fp, "%d\t\t%d", size, repetitions);
        //fprintf(fp, "\t\t%2.8f\t%2.8f",execTime[pos], execTime[pos+1]);
        fprintf(fp, "\t\t%2.8f\t%2.8f", execTime[pos+2], execTime[pos+3]);
        //fprintf(fp, "\t\t%2.8f\t\t%2.8f", execTime[pos+4], execTime[pos+5]);
        fprintf(fp, "\n");
        fclose(fp);

        //update of size, repetitions and position
        size = increaseSize(size);
        repetitions = decreaseRep(repetitions);
        pos=pos+6;
    }

    return 0;
}


void quickTimes(double *execTime, int *input, int size, int k, int repetitions, int pos)
{
    double elapsed = 0;
    double totalTime = 0;
    int i=0;
    clock_t time_evaluation=0;
    double execs[repetitions+1];

    while(i<repetitions)
    {
        time_evaluation = quickSelect(input, k, size);

        elapsed = (((double) time_evaluation) / CLOCKS_PER_SEC);
        execs[i] = elapsed;
        totalTime = totalTime + elapsed;

        i++;
    }

    execs[i] = (totalTime/repetitions);
    *(execTime + pos) = execs[i];
    *(execTime + pos +1) = std(execs, repetitions);
}

void heapTimes(double *execTime, int *input, int size, int k, int repetitions, int pos)
{
    double elapsed = 0;
    double totalTime = 0;
    int i=0;
    clock_t time_evaluation=0;
    double execs[repetitions+1];

    while(i<repetitions)
    {
        time_evaluation = heapSelect(input, k, size);

        elapsed = (((double) time_evaluation) / CLOCKS_PER_SEC);
        execs[i] = elapsed;
        totalTime = totalTime + elapsed;

        i++;
    }

    execs[i] = (totalTime/repetitions);
    *(execTime +pos +2) = execs[i];
    *(execTime +pos +3) = std(execs, repetitions);
}

void medianTimes(double *execTime, int *input, int size, int k, int repetitions, int pos)
{
    double elapsed = 0;
    double totalTime = 0;
    int i=0;
    clock_t time_evaluation=0;
    double execs[repetitions+1];

    while(i<repetitions)
    {
        time_evaluation = medianSelect(input, k, size);

        elapsed = (((double) time_evaluation) / CLOCKS_PER_SEC);
        execs[i] = elapsed;
        totalTime = totalTime + elapsed;

        i++;
    }

    execs[i] = (totalTime/repetitions);
    *(execTime +pos +4) = execs[i];
    *(execTime +pos +5) = std(execs, repetitions);
}