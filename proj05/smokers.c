#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

sem_t tobacco, paper, matches, smoked;
void* agent(void *data) {
    while (1) {
	switch (rand() % 3) {
	case 0:
	    /* Missing tobacco */
	    sem_post(&paper);
	    sem_post(&matches);
	    printf("Agent places [ ] Tobacco [X] Paper [X] Matches\n");
	    break;
	case 1:
	    /* Missing paper */
	    sem_post(&tobacco);
	    sem_post(&matches);
	    printf("Agent places [X] Tobacco [ ] Paper [X] Matches\n");
	    break;
	case 2:
	    /* Missing matches */
	    sem_post(&tobacco);
	    sem_post(&paper);
	    printf("Agent places [X] Tobacco [X] Paper [ ] Matches\n");
	    break;
	default:
	    printf("Error!\n");
	    exit(-1);
	}

	/* Wait for the smoker to signal they're done */
	sem_wait(&smoked);
	printf("Agent has been signaled a smoker is done\n");
	sleep(3);
    }
}

int main(int argc, char** argv) {
    sem_init(&tobacco, 0, 0);
    sem_init(&paper, 0, 0);
    sem_init(&matches, 0, 0);
    sem_init(&smoked, 0, 0);    
    srand(getpid());
    
    pthread_t a;
    pthread_create(&a, NULL, agent, NULL);

    pthread_join(a, NULL);
    return 0;
}
