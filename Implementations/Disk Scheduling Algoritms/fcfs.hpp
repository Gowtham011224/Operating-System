#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void printDiskStatus(int n, int RQ[], int initial) {
    printf("Disk Sequence:\n");
    printf("Head: %d\n", initial);
    printf("Track: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", RQ[i]);
    }
    printf("\n\n");
}

void one() {
    int RQ[100], i, n, TotalHeadMovement = 0, initial;
    printf("Enter the number of Requests: ");
    scanf("%d", &n);
    printf("Enter the Requests sequence: ");
    for(i = 0; i < n; i++)
        scanf("%d", &RQ[i]);
    printf("Enter initial head position: ");
    scanf("%d", &initial);

    // Print initial disk sequence
    printDiskStatus(n, RQ, initial);

    // Logic for FCFS disk scheduling
    for(i = 0; i < n; i++) {
        TotalHeadMovement += abs(RQ[i] - initial);
        initial = RQ[i];
    }

    printf("Total head movement is %d\n", TotalHeadMovement);
    return ;
}
