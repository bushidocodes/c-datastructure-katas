// NOTE: This is my overengineering solution where I overthought problem 3 and attempted to modify the constraints
// to enable constant time operations. Please see problem3.c for my strict solution

// Implement the deleteMin operation for priority queue with only a single(normal, non-priority) queue in
// which to store data. You are allowed to declare int variables, but not arrays, vectors or any other data
// structures. You can assume the Queue class provides the following methods: void enqueue(int), int
// dequeue(), int size().
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 100

/* These are all my base Queue components. The function signatures differ only in the fact that I always pass a 
pointer to my Queue struct as the first argument, because I'm not using C++ or a native OOP langauge. Additionally,
I have implemented an abstract Node type that includes a priority value. The queue methods ignore this. Ideally, I'd
want to be able to support any nodes that has a value attribute */

typedef struct QueueNode
{
    int value;
} QueueNode;

typedef struct Queue
{
    void *data[MAX_ELEMENTS];
    int front;
    int rear;
    int size;
} Queue;

void initializeQueue(Queue *this)
{
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        this->data[i] = NULL;
    }
    this->front = 0;
    this->rear = -1;
    this->size = 0;
}

// Frees all elements and then the queue itself
void destroyQueue(Queue *this)
{
    for (int i = 0; i < MAX_ELEMENTS; i++)
    {
        if (this->data[i] = NULL)
        {
            free(this->data[i]);
        };
    }
    free(this);
}

void printQueue(Queue *this)
{
    printf("front: %d\nrear: %d\n", this->front, this->rear);
    for (int i = this->front, s = this->size; s > 0; i = (i + 1 == MAX_ELEMENTS ? 0 : i + 1), s--)
    {
        printf("%d: %d\n", i, ((QueueNode *)(this->data[i]))->value);
    }
}

int enqueue(Queue *this, void *newElement)
{
    if (this->size == MAX_ELEMENTS)
    {
        printf("ERR: Queue is full\n");
    }
    else
    {
        printf("Setting rear from %d to %d\n", this->rear, this->rear + 1 == MAX_ELEMENTS ? 0 : this->rear + 1);
        this->rear = this->rear + 1 == MAX_ELEMENTS ? 0 : this->rear + 1;
        this->data[this->rear] = newElement;
        this->size++;
        return this->rear;
    }
};

void *dequeue(Queue *this)
{
    if (this->size == 0)
    {
        printf("ERR: Queue is Empty");
    }
    else
    {
        void *result = this->data[this->front];
        this->front = this->front + 1 == MAX_ELEMENTS ? 0 : this->front + 1;
        this->size--;
        return result;
    }
};

int size(Queue *this)
{
    return this->size;
};

/* These are my PriorityQueue components. */
typedef struct PriorityQueueNode
{
    int priority;
    int value;
} PriorityQueueNode;

typedef struct PriorityQueue
{
    Queue *queue;
    int idxOfMin;
    int minPriority;
} PriorityQueue;

void initializePriorityQueue(PriorityQueue *this)
{
    this->queue = malloc(sizeof(Queue));
    initializeQueue(this->queue);
    this->minPriority = INFINITY;
    this->idxOfMin = -1;
}

void destroyPriorityQueue(PriorityQueue *this)
{
    destroyQueue(this->queue);
    free(this);
}

void insert(PriorityQueue *this, PriorityQueueNode *new)
{
    int idx = enqueue(this->queue, new);
    if (new->priority < this->minPriority)
    {
        this->minPriority = new->priority;
        this->idxOfMin = idx;
    }
}

void *deleteMin(PriorityQueue *this)
{
    // I bypass the Queue methods, pluck out the result, and then set the value to NULL;
    PriorityQueueNode *result = this->queue->data[this->idxOfMin];
    // The issue is that I now have holes in the array behind my Queue.
    this->queue->data[this->idxOfMin] = NULL;
    return result;
}

main(int argc, char *argv[])
{
    Queue *testQueue = malloc(sizeof(Queue));
    initializeQueue(testQueue);

    printf("stage 1: Fill the queue\n");
    for (int i = 0; i < 75; i++)
    {
        QueueNode *newNode = malloc(sizeof(QueueNode));
        newNode->value = i;
        enqueue(testQueue, newNode);
    }
    printQueue(testQueue);

    printf("stage 2: Empty half the queue\n");
    for (int i = 0; i < 25; i++)
    {
        QueueNode *returnedNode = dequeue(testQueue);
        printf("Dequeued %d\n", returnedNode->value);
        free(returnedNode);
    }
    printQueue(testQueue);

    printf("stage 3: Refill queue\n");
    for (int i = 0; i < 50; i++)
    {
        QueueNode *newNode = malloc(sizeof(QueueNode));
        newNode->value = i;
        enqueue(testQueue, newNode);
    }
    printQueue(testQueue);

    destroyQueue(testQueue);
}
