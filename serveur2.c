#define _POSIX_C_SOURCE 199309L
 
#include <stdlib.h>    /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <signal.h>    /* Pour signal */
#include <stdio.h>     /* Pour printf */
#include <unistd.h>     /* Pour sleep */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void	ft_putstr(int fd, char c);

int cpt = 0;    /* Permet de marquer les signaux recus */
int d = 0;
int size = 10;

/**
 * Ceci est le gestionnaire qui est associe aux signaux SIGUSR1 et SIGUSR2.
 * @param signum le numero du signal recu
 */
void handler(int signum) {
	char	c;

	c = '\0';
	if(signum == SIGUSR1 && cpt == 0) {
		printf("Serveur : Signal 1 recu\n");
		cpt = 1;
	}
	if (signum == SIGUSR1 && cpt == 1) {
		d++;
	}
	if (signum == SIGUSR2 && cpt == 1) {
		size = d;
		d = 0;
		cpt = 2;
		printf("Serveur : size = %d\n", size);
	}
	if(signum == SIGUSR1 && cpt > 1 && cpt < (size + 2)) {
		d++;
	}
	if(signum == SIGUSR2 && cpt < (size + 2) && cpt > 1) {
		//printf("Signal 2 recu cpt = %d\n", cpt);
		c = (char)d;
		d = 0;
		ft_putstr(1, c);
		cpt++;
	}
	if (signum == SIGUSR2 && cpt == (size + 2)) {
		printf("\nServeur : Signal 2 recue et cpt = size\n");
		cpt = size + 3; 
	}
}
 
int main() {
	struct sigaction action;
 
  /* Positionnement du gestionnaire pour SIGUSR1 */
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if(sigaction(SIGUSR1, &action, NULL) == -1) {
		perror("Erreur lors du positionnement ");
		exit(EXIT_FAILURE);
	}
 
  /* Positionnement du gestionnaire pour SIGUSR2 */
	if(sigaction(SIGUSR2, &action, NULL) == -1) {
		perror("Erreur lors du positionnement ");
		exit(EXIT_FAILURE);
	}
 
	printf("Pret a recevoir des signaux. Mon PID : %d\n", getpid());
 
  /* Mise en attente jusqu'a recevoir au moins un signal SIGUSR1 et SIGUSR2 */
	while(cpt != (size + 3)) {
		pause();
	}
	return EXIT_SUCCESS;
}
