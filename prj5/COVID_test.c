#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t lock_id;
static sem_t connected_lock;
static sem_t operators;
static int NUM_OPERATORS = 4;
static int NUM_LINES = 7;
static int connected = 0;    // Callers that are connected
int next_id = 0;

void *phonecall(void *vargp) {

    sem_wait(&lock_id);
    int caller_id = next_id;
    ++next_id;
    sem_post(&lock_id);

    printf("Thread [%d] is attempting to connect ...\n",caller_id);
    sem_wait(&connected_lock);

    while(connected == NUM_LINES){      
        sem_post(&connected_lock);
        sleep(1);
        sem_wait(&connected_lock);
    }

    ++connected;
    printf("Thread [%d] connects to an available line, call ringing ...\n",caller_id);
    sem_post(&connected_lock);

    sem_wait(&operators);
    printf("Thread [%d] is speaking to an operator in the local health center.\n",caller_id);
    sleep(2);
    printf("Thread [%d] has made an appointment for the test! The operator has left ...\n",caller_id);
    sem_post(&operators);

    sem_wait(&connected_lock);
    printf("Thread [%d] has hung up!\n",caller_id);
    --connected;
    sem_post(&connected_lock);
    return NULL;

}

int main(int argc, char *argv[]) {
    if (argc != 2){
        exit(0);
    } 
    int num_threads = atoi(argv[1]);

    if (num_threads == 0){
        exit(0);
    }
    
    sem_init(&lock_id,0,1);
    sem_init(&operators,0,NUM_OPERATORS);
    sem_init(&connected_lock,0,1);

    pthread_t threads[num_threads];

    for(int i = 0; i < num_threads; ++i) {
        pthread_create(&threads[i], 0, phonecall, NULL);
    }
    for(int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}