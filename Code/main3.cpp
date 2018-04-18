#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <vector>
#include "cmake-build-debug/Population.h"

#include <stdio.h>
#include <semaphore.h>

// Variaveis acessadas por todas as threads
double m_globalBest;
vector<double> m_globalBestPosition;

// Variaveis globais
int numberOfThreads = 4;
int sizeOfPopulation = 25;

// Variavel das threads
pthread_mutex_t sincVar;

#define up(SEM) _up(SEM,#SEM)
#define down(SEM) _down(SEM,#SEM)

void _up(sem_t *sem, const char * name) {
    sem_post(sem);
}
void _down(sem_t *sem, const char * name) {
    sem_wait(sem);
}

void *popGenerator(void *lpParam) {

    unsigned int seed = time(NULL);

    vector<double> lowerBound;
    lowerBound.push_back(1.0);
    lowerBound.push_back(0.0);

    vector<double> upperBound;
    upperBound.push_back(1000.0);
    upperBound.push_back(1000000.0);

    Population pop = Population(sizeOfPopulation, 2, lowerBound, upperBound, seed);

    for (int i=0; i<1000; i++) {
        pop.runOneIteration();
        if (pop.getGlobalBest() > m_globalBest) {
            pthread_mutex_lock(&sincVar);
            m_globalBest = pop.getGlobalBest();
            m_globalBestPosition = pop.getGlobalBestPosition();
            pthread_mutex_unlock(&sincVar);
        }
    }

    return 0;
}

/* Código com multi thread, mas sem sincronização */
int main() {

    m_globalBest = -999999999999999;

    /* Clock variables */
    struct timespec start, finish;
    double elapsed;

    pthread_mutex_init(&sincVar, NULL);
    pthread_t threadId[100];

    /* Começando a contar o tempo */
    // clock_t begin = clock();
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i=0; i<numberOfThreads; i++) {
        pthread_create(&threadId[i], NULL, popGenerator, (void *)i);
    }

    for (int i=0; i<numberOfThreads; i++) {
        pthread_join(threadId[i], NULL);
    }

    /* Terminando de contar o tempo */
    clock_gettime(CLOCK_MONOTONIC, &finish);

    printf("Price: %lf, Marketing investment: %lf\n", m_globalBestPosition[0], m_globalBestPosition[1]);

    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("execution time: %lf\n", elapsed);

    return 0;
}