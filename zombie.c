#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent PID: %d\n", getpid());

        // Parent is intentionally NOT calling wait()
        // This is the key reason zombie is created (previously missing wait was the issue)
        sleep(10); // keep parent alive so zombie can be observed

    } else if (pid == 0) {
        // Child process
        printf("Child PID: %d\n", getpid());
        printf("Child exiting...\n");

        _exit(0); 
    } else {
        printf("Fork failed\n");
    }

    return 0;
}