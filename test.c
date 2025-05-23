#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

//Define the maximum number of Students and the number of chairs in the waiting room
#define NUM_STUDENTS 10
#define NUM_CHAIRS 5

// Define the semaphores for the TA, the Students, and the mutex
sem_t ta_sem;
sem_t student_sem;
pthread_mutex_t mutex;

int waiting_students[NUM_CHAIRS]; // Define a list to keep track of the waiting students
int count = 0;
int front = 0, rear = 0;

// Define the TA thread function
void *ta_function(void *arg)
{
        while (1)
        {
                printf("TA is sleeping...\n");
                sem_wait(&ta_sem);

                pthread_mutex_lock(&mutex);
                if (count > 0)
                {
                        int student_id = waiting_students[front];
                        front = (front + 1) % NUM_CHAIRS;
                        count--;
                        printf("TA is helping student %d\n", student_id);
                        pthread_mutex_unlock(&mutex);

                        sleep(rand() % 3 + 1); // Helping Time
                        printf("TA has finished helping student %d\n", student_id);
                        sem_post(&student_sem);
                }
                else
                        pthread_mutex_unlock(&mutex);
        }
        return NULL;
}

// Define the Student thread function
void *student_function(void *arg)
{
        int student_id = *(int *)arg;
        sleep(rand() % 5 + 1); // Random entry

        pthread_mutex_lock(&mutex);
        if (count < NUM_CHAIRS)
        {
                waiting_students[rear] = student_id;
                rear = (rear + 1) % NUM_CHAIRS;
                count++;
                printf("Student %d is waiting. Chairs left: %d\n", student_id, NUM_CHAIRS - count);
                pthread_mutex_unlock(&mutex);

                sem_post(&ta_sem);      // Waking Up TA
                sem_wait(&student_sem); // Waiting for help of TA
                printf("Student %d has received help.\n", student_id);
        }
        else
        {
                printf("Student %d left (no chair available).\n", student_id);
                pthread_mutex_unlock(&mutex);
        }
        return NULL;
}

int main()
{
        srand(time(NULL));
        pthread_t ta_thread;
        pthread_t student_threads[NUM_STUDENTS];
        int student_ids[NUM_STUDENTS];

        sem_init(&ta_sem, 0, 0);
        sem_init(&student_sem, 0, 0);
        pthread_mutex_init(&mutex, NULL);

        pthread_create(&ta_thread, NULL, ta_function, NULL); // Create TA Thread

        for (int i = 0; i < NUM_STUDENTS; i++) // Create  a thread for each Student
        {
                student_ids[i] = i;
                pthread_create(&student_threads[i], NULL, student_function, &student_ids[i]);
        }

        for (int i = 0; i < NUM_STUDENTS; i++)
                pthread_join(student_threads[i], NULL);

        sem_destroy(&ta_sem);
        sem_destroy(&student_sem);
        pthread_mutex_destroy(&mutex);

        printf("Program terminated.\n");

        return 0;
}
