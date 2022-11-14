//cubaan ke-2

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

void sigint_handler (int sig) {
	printf("Jangan Kacau Saya!\n");
}

int main(void) {
	void sigint_handler(int sig);

	if(signal(SIGINT, sigint_handler) == SIG_ERR) {
		perror("signal SIGINT");
		exit(1);
	}
	while(1) {
		int pipefds[2];
		char m[20];
		pipe(pipefds);
		pid_t pid = fork();

		if (pid == 0) {
			close(pipefds[0]);
			write(pipefds[1], m, sizeof(m));
			printf("From Parent:%s\n", m);
			exit(EXIT_SUCCESS);
		}
		if (pid > 0) {
			wait(NULL);
			close(pipefds[1]);
			read(pipefds[0], m, sizeof(m));
			close(pipefds[0]);
			printf("Enter Message:\n");
			scanf("%s", m);
		}
	}
	return EXIT_SUCCESS;
}
