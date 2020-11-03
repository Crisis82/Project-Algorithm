
int max(int first, int second);
int randomInt(int from, int to);
void randomArray(int *input, int size);
void printArray(int *input, int size);
int increaseSize(int n);
int decreaseRep(int n);
double std(double *exec, int size);

//return the max between two ints
int max(int first, int second)
{
    if(first>second)
    {
        return first;
    }
    else
    {
        return second;
    }
}

//calculate a random int between a range of ints
int randomInt(int from, int to)
{
    srand((unsigned)time(NULL));
    int num = (rand()%(to-from+1) + from);
    return num;
}

//fill an array with random int
void randomArray(int *input, int size)
{
    srand((unsigned)time(NULL));

    for(int i=0; i<size; i++)
    {
        *(input +i)=rand();
    }
}

//print the array
void printArray(int *input, int size)
{
    for(int i=0; i<size; i++)
    {
        printf("%d ", input[i]);
    }
    printf("\n");
}

//update the size of the array: tot=37 increases
int increaseSize(int n)
{
    int increase = 100;

    if(n < pow(10, 3)) //n < 1k
    {
        increase = pow(10, 2); //100
    }
    else if(n < pow(10, 4)) //n < 10k
    {
        increase = pow(10, 3); //1k
    }
    else if(n < pow(10, 5)) //n < 100k
    {
        increase = (5*pow(10, 3)); //5k
    }
    else if(n < pow(10, 6)) //n < 1mln
    {
        increase = (5*pow(10, 4)); //50k
    }
    else if(n < (5*pow(10, 6))) //n < 5mln
    {
        increase = (5*pow(10, 5)); //500k
    }
    else
    {
        n = -1;
        increase = 0;
    }

    return n += increase;
}

//update the number of repetitions
int decreaseRep(int n)
{ 
    return max(10, n - 10);
}

//calculate standard deviation
double std(double *exec, int size)
{
    double dev = 0;

    for(int i=0; i<size; i++)
    {
        dev = dev + (exec[size] - exec[i])*(exec[size] - exec[i]);
    }

    dev = sqrt(dev/size);

    return dev;
}