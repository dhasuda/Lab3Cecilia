#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <math.h>

#define WINAPI

// Variáveis globais acessadas por todas as threads
int insidePoints;
int outsidePoints;
int pointsPerThread;

// Variavel das threads
sem_t mutex;

#define up(SEM) _up(SEM,#SEM)
#define down(SEM) _down(SEM,#SEM)

void _up(sem_t *sem, const char * name) {
	sem_post(sem);
}
void _down(sem_t *sem, const char * name) {
	sem_wait(sem);
}

unsigned long WINAPI pointGenerator(void *lpParam) {

  double min = -1;
  double max = 1;

	int selfInsidePoints = 0;
	int selfOutsidePoints = 0;

  int *threadId = (int *)lpParam;
	unsigned int seed = abs(threadId);

  int i;
  for (i=0; i<pointsPerThread; i++) {
    double xPos = (double)rand_r(&seed)/(double)RAND_MAX;
    xPos = min + xPos*(max-min);

    double yPos = (double)rand_r(&seed)/(double)RAND_MAX;
    yPos = min + yPos*(max-min);
    /* Posição aleatoria (xPos, yPos) gerada */

    if (yPos*yPos + xPos*xPos < 1) {
      /* Ponto está dentro do círculo */
      selfInsidePoints++;
    } else {
      /* Ponto está fora do círculo */
      selfOutsidePoints++;
    }

  }

	down(&mutex); /* Entra na região crítica */
	insidePoints += selfInsidePoints;
	outsidePoints += selfOutsidePoints;
	up(&mutex); /* Sai da região crítica */

  return 0;

}

int main(int argc, char **argv) {

  /* Inicialização da contagem dos pontos */
  insidePoints = 0;
  outsidePoints = 0;

	/* Clock variables */
	struct timespec start, finish;
	double elapsed;

  int i;
  int numberOfThreads;

  /* Buscando entrada do usuário para número de threads e pontos por thread */
  if (argv[1] != NULL && argv[2] != NULL) {
    numberOfThreads = atoi(argv[1]);
    pointsPerThread = atoi(argv[2]);
  } else {
    numberOfThreads = 10;
    pointsPerThread = 100;
  }
  if (numberOfThreads > 100) {
    numberOfThreads = 100;
  }

  sem_init(&mutex, 0, 1);
  void *threadFunc[100];
  pthread_t threadId[100];

  for (i=0; i<numberOfThreads; i++) {
    threadFunc[i] = pointGenerator;
  }

	/* Começando a contar o tempo */
	// clock_t begin = clock();
	clock_gettime(CLOCK_MONOTONIC, &start);

  for (i=0; i<numberOfThreads; i++) {
    pthread_create (&threadId[i],
        NULL,
        threadFunc[i],
        (void *)i);
  }

  for (i=0; i<numberOfThreads; i++) {
    pthread_join (threadId[i], NULL);
  }
	/* Terminando de contar o tempo */
	clock_gettime(CLOCK_MONOTONIC, &finish);

  /* Imprimindo resultados */
  printf("insidePoints = %d\noutsidePoints = %d\n", insidePoints, outsidePoints);

  double pi = 4.0 * (double)insidePoints / ((double)outsidePoints + (double)insidePoints);
  printf("pi = %lf\n", pi);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  printf("execution time: %lf\n", elapsed);

}
