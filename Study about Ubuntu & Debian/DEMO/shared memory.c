#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024
#define PROCESS_DELAY 2 // Time gap in seconds

int main() {
    int shm_id;
    key_t key;
    char *shm_ptr;
    char message[SHM_SIZE];

    // Generate a key for the shared memory segment
    key = ftok("/tmp", 'a');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    shm_id = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    shm_ptr = shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Get message from user
    printf("Enter the message to be shared: ");
    fgets(message, SHM_SIZE, stdin);
    // Remove newline character if present
    if (message[strlen(message) - 1] == '\n') {
        message[strlen(message) - 1] = '\0';
    }

    // Write message to shared memory
    strncpy(shm_ptr, message, SHM_SIZE);
    printf("Process A has written the message to shared memory.\n");

    // Pause execution for a specified time
    sleep(PROCESS_DELAY);

    // Fork a new process
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process (Process B)
        // Pause execution for a specified time
        sleep(PROCESS_DELAY);

        // Attach to the shared memory segment
        shm_ptr = shmat(shm_id, NULL, 0);
        if (shm_ptr == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        // Read message from shared memory and display it
        printf("Process B is reading the message from shared memory: %s\n", shm_ptr);

        // Detach from the shared memory segment
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }
    } else { // Parent process (Process A)
        // Wait for the child process to finish
        wait(NULL);
        printf("Process B has finished reading the message from shared memory.\n");

        // Pause execution for a specified time
        sleep(PROCESS_DELAY);

        // Delete the shared memory segment
        if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
        printf("Shared memory segment has been deleted.\n");
    }

    return 0;
}
