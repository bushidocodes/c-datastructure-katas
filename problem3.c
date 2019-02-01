// Implement the deleteMin operation for priority queue with only a single(normal, non-priority) queue in
// which to store data. You are allowed to declare int variables, but not arrays, vectors or any other data
// structures. You can assume the Queue class provides the following methods: void enqueue(int), int
// dequeue(), int size().
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

/* These are all my base Queue components. The function signatures differ only in the fact that I always pass a 
pointer to my Queue struct as the first argument, because I'm not using C++ or a native OOP langauge. */

typedef struct Queue
{
    int data[MAX_ELEMENTS];
    int front;
    int rear;
    int size;
} Queue;

void enqueue(Queue *, int);
int dequeue(Queue *);
int size(Queue *);

void initializeQueue(Queue *this)
{
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        this->data[i] = 0;
    }
    this->front = 0;
    this->rear = -1;
    this->size = 0;
}

// Frees all elements and then the queue itself
void destroyQueue(Queue *this)
{
    free(this);
}

void printQueue(Queue *this)
{
    for (int i = this->front, s = this->size; s > 0; i = (i + 1 == MAX_ELEMENTS ? 0 : i + 1), s--)
    {
        printf("%d: %d\n", i, this->data[i]);
    }
}

void enqueue(Queue *this, int newElement)
{
    if (this->size == MAX_ELEMENTS)
    {
        printf("ERR: Queue is full\n");
    }
    else
    {
        this->rear = this->rear + 1 == MAX_ELEMENTS ? 0 : this->rear + 1;
        this->data[this->rear] = newElement;
        this->size++;
    }
};

int dequeue(Queue *this)
{
    if (this->size == 0)
    {
        printf("ERR: Queue is Empty");
    }
    else
    {
        int result = this->data[this->front];
        this->front = this->front + 1 == MAX_ELEMENTS ? 0 : this->front + 1;
        this->size--;
        return result;
    }
};

int size(Queue *this)
{
    return this->size;
};

/* Here is my answer for the question following restrictions to the letter. I began this problem by overengineering
a solution using void pointers, structs for nodes containing values and prioirities, etc. This solution attempts to 
follow the prompt strictly and not add any new persistant state beyond the queue above. Because the queue is a queue of
ints and I'm not allowed to modify the queue to a new 


It is O(n) and has to make two passes through the queue to calculate
the min and then filter the min from the queue while respecting the existing FIFO order. I assume the value to be the 
priority since the underlying data type is an int in the instructions. Normally, I would assume that there are distinct
prior priorities and values
in the queue  */

int deleteMin(Queue *q)
{
    int minValue = INT_MAX;
    int buffer;
    int foundLowest = 0; /* I treat this like a bool flag (but I was only allowed to declare ints per instructions) 
    it serves to make sure I only delete the earliest element if there are several with the same priority */
    for (int i = 0, s = size(q); i < s; i++)
    {
        buffer = dequeue(q);
        minValue = buffer < minValue ? buffer : minValue;
        enqueue(q, buffer);
    }
    // My second pass deques all values and requeues all but the first element matching min value
    for (int i = 0, s = size(q); i < s; i++)
    {
        buffer = dequeue(q);
        if (buffer != minValue || foundLowest == 1)
        {
            enqueue(q, buffer);
        }
        else if (buffer == minValue || foundLowest == 0)
        {
            foundLowest = 1;
        }
    }
    // Then I return min value;
    return minValue;
}

int main(int argc, char *argv[])
{
    Queue *testQueue = malloc(sizeof(Queue));
    initializeQueue(testQueue);
    int testValues[] = {917, 1182, 914, 1368, 753, 544, 1094, 910, 1382, 923};
    for (int i = 0; i < 10; i++)
    {
        enqueue(testQueue, testValues[i]);
    }

    printf("Size of 10? %d\n", size(testQueue));
    int result = deleteMin(testQueue);
    printf("Size of 9? %d\n", size(testQueue));
    printf("Result is 544? %d\n", result);
    printf("Does the following match 917, 1182, 914, 1368, 753, 1094, 910, 1382, 923?\n");
    printQueue(testQueue);

    destroyQueue(testQueue);
}
