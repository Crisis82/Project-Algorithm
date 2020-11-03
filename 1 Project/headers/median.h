#define true 1

clock_t medianSelect(int *input, int k, int size);
int median(int *array, int k, int first, int last);
int medOfMed(int *array, int from, int to);
int partitionFixed(int *array, int from, int to, int median);
void insertionsort(int *array, int from, int to);
void swapMed(int *array, int i, int j);
int min(int first, int second);


clock_t medianSelect(int *input, int k, int size)
{
    clock_t time_start = clock();
    int min = median(input, k, 0, size);
    clock_t time_end = clock();
    return (time_end -time_start);
    
    //printf("%d\n", min);
}

//ritorna il k-esimo minimo usando median-of-median
int median(int *array, int k, int from, int to)
{
    int median;
    int posMed;

    while(true)
    {
        median = medOfMed(array, from, to);
        posMed = partitionFixed(array, from, (to -1), median);
        int position = posMed -from +1;

        if(k < position)
        {
            to = posMed;
        }
        else if(k > position)
        {
            from = posMed +1;
            k = k -position;
        }
        else
        {
            break;
        }
    }
    
    return array[posMed];
}

int medOfMed(int *array, int from, int to)
{
    int blockSize = 5;

    if(from>=(to-1))
    {
        return array[from];
    }
    else
    {
        int difference = to -from;
        int quantity = (difference/blockSize) + min(1, difference%blockSize);
        int position = 0;
        int block[quantity];

        for(int i=from; i<to; i=i+blockSize)
        {
            int last = min((i +blockSize -1), (to -1));
            insertionsort(array, i, last);
            block[position++] = array[(i + last)/2];
        }
        
        return medOfMed(block, 0, quantity);
    }
}

int partitionFixed(int *array, int from, int to, int median)
{
    int i = from;
    int j = to;
    int val = -1;

    while(i <= j)
    {
        if(array[i] <= median)
        {
            if(array[i] == median)
            {
                val = i;
            }

            i++;
        }
        else
        {
            swapMed(array, j, i);
            j--;
        }
    }

    if(val >= 0)
    {
        swapMed(array, j, val);
    }

    return j;
}

void insertionsort(int *array, int from, int to)
{
    for(int j=(from+1); j<(to+1); j++)
    {
        int key = array[j];
        int i = j -1;

        while((i>=from) && (array[i]>key))
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

void swapMed(int *array, int i, int j)
{
    int temp = *(array +i);
    *(array +i) = *(array +j);
    *(array +j) = temp;
}

int min(int first, int second)
{
    if(first<second)
    {
        return first;
    }
    else
    {
        return second;
    }
}