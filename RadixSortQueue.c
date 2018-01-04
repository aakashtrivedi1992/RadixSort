#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct queue
{
   int queueMaxSize;
   int queueFront;
   int queueRear;
   int queueSize;
   int queueArray[];
} queue;

typedef struct queue* QUEUE;


QUEUE createQueue(int maxSize)
{
   QUEUE Q = (QUEUE) malloc(sizeof(queue));

   if (Q == NULL)
   {
      printf("Out of space!!!");
   }

   Q->queueArray[maxSize];
   Q->queueMaxSize = 25;
   Q->queueSize = 0;
   Q->queueFront = 0;
   Q->queueRear = 0;

   return Q;
}

int isEmpty( QUEUE Q )
{
   return( Q->queueSize == 0 );
}

void makeNull ( QUEUE Q )
{
   Q->queueSize = 0;
   Q->queueFront = 1;
   Q->queueRear = 0;
}

void checkFront(QUEUE Q)
{
   printf("Front of Queue: %d", Q->queueFront);
}

void checkRear (QUEUE Q)
{
   printf("Front of Queue: %d", Q->queueRear);
}

int succ( int value, QUEUE Q )
{
   if( ++value == Q->queueMaxSize )
   {
      value = 0;
   }

   return value;
}

void enqueue(int x, QUEUE Q )
{
   if(Q->queueSize == Q->queueMaxSize)
   {
      printf("Full queue");
   }
   
   else
   {
      Q->queueSize++;
      Q->queueArray[ Q->queueRear ] = x;
      Q->queueRear = succ( Q->queueRear, Q );
   }
}

int dequeue(int d, QUEUE Q)
{
   int tempElement = Q->queueFront;

   Q->queueSize--;
   Q->queueFront = succ(Q->queueFront, Q);

   return tempElement;
}

void printQueue(QUEUE Q)
{
   int i = 0;

   printf("\nSorted Queue:\t");

   for (i = 0; i < Q->queueSize; i++)
   {
      printf("%d\t", Q->queueArray[i]);
   }
}

void sort(int* unsortedArray, int size, int* sortedArray, int m, int exp)
{
   int i = 0;
   int bucketArray[10] = {0};

   for (i = 0; i < size; i++)
   {
      bucketArray[unsortedArray[i] / exp % m]++;
   }

   bucketArray[1] += bucketArray[0];
   bucketArray[2] += bucketArray[1];
   bucketArray[3] += bucketArray[2];
   bucketArray[4] += bucketArray[3];
   bucketArray[5] += bucketArray[4];
   bucketArray[6] += bucketArray[5];
   bucketArray[7] += bucketArray[6];
   bucketArray[8] += bucketArray[7];
   bucketArray[9] += bucketArray[8];
	
   for (i = size - 1; i >= 0; i--)
   {
      sortedArray[--bucketArray[unsortedArray[i] / exp % 10]] = unsortedArray[i];
   }
}


int main(int argc, char *argv[])
{
   int sortArraySize = 0;
   int a = 0, i=0;
   int inputValue = 0;
   int exp = 1;

   printf("Please Type in how many numbers you want to sort < 25: ");
   scanf("%d", &sortArraySize);

   QUEUE theQueue = createQueue(sortArraySize);

   int sortedArray[sortArraySize], tempArray[sortArraySize], newTempArray[sortArraySize], unsortedArray[sortArraySize];

   printf("\n\nPlease type in each number you want to sort.\n");

   for (a = 0; a < sortArraySize; a++)
   {
      scanf("%d", &inputValue);
      enqueue(inputValue, theQueue);
   }

   int highestNumber = theQueue->queueArray[0];
	
   for (i = 0; i < theQueue->queueSize; i++)
   {
      if (highestNumber < theQueue->queueArray[i])
      {
         highestNumber = theQueue->queueArray[i];
      }
   }

   for (a = 0; a < sortArraySize; a++)
   {
      unsortedArray[a] = theQueue->queueArray[a];
   }

   i = 0;

   while ((highestNumber / exp) > 0)
   {
      sort(unsortedArray, theQueue->queueSize, sortedArray, 10, pow(10, i));
      exp = exp * 10;
   
      for (a = 0; a < sortArraySize; a++)
      {
         unsortedArray[a] = sortedArray[a];
      }
   
      i++;
   }

   for (a = 0; a <sortArraySize; a++)
   {
      theQueue->queueArray[a] = unsortedArray[a];
   }

   printQueue(theQueue);
   printf("\n\n");

   return 0;
}
