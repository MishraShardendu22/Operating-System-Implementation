#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent PID: %d\n", getpid());
        printf("Parent exiting...\n");
    }else if (pid == 0) {
        // Child process
        sleep(2); // ensure parent exits first

        printf("Child PID: %d\n", getpid());

        // This will print the parent's PID after re-parenting.
        // Traditionally expected: 1 (init process).
        
        // On modern Linux (Fedora using systemd), it may NOT be 1.
        // Reason:
        // - Linux supports "subreapers" (via prctl).
        // - systemd runs a user-level instance (systemd --user).
        // - Orphan processes are adopted by the nearest subreaper, not necessarily PID 1.
        // - In this system, child is adopted by systemd --user (e.g., PID 3585).
        
        // So output will be:
        // getppid() = PID of systemd --user, not 1.
        printf("Child's new Parent PID (after orphan): %d\n", getppid()); 
    } else {
        printf("Fork failed\n");
    }

    return 0;
}