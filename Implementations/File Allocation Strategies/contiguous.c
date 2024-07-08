#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct file 
{
    char name[50];
    int size;
    int start_block;
};

struct disk 
{
    int total_blocks;
    int *used_blocks;
    int *free_blocks;
};

void init_disk(struct disk *d, int total_blocks) 
{
    d->total_blocks = total_blocks;
    d->used_blocks = (int *)calloc(total_blocks, sizeof(int));
    d->free_blocks = (int *)calloc(total_blocks, sizeof(int));
    for (int i = 0; i<total_blocks; i++) 
        d->free_blocks[i] = 1;
}

struct file *allocate_file(struct disk *d, char *name, int size, int start_block) 
{
    for (int i = start_block; i<start_block + size; i++) 
    {
        if (d->free_blocks[i] != 1) 
        {
            printf("Not enough contiguous free blocks starting from block %d\n", start_block);
            return NULL;
        }
    }
    for (int i = start_block; i<start_block + size; i++) 
    {
        d->used_blocks[i] = 1;
        d->free_blocks[i] = 0;
    }
    struct file *f = (struct file *)malloc(sizeof(struct file));
    strcpy(f->name, name);
    f->size = size;
    f->start_block = start_block;
    return f;
}

void free_file(struct disk *d, struct file *f) 
{
    for (int i = f->start_block; i< f->start_block + f->size; i++) 
    {
        d->used_blocks[i] = 0 ;
        d->free_blocks[i] = 1 ;
    }
    free(f);
}

void display_disk(struct disk *d)
{
    printf("\nDisk Status:\n");
    printf("Block:\tStatus:\n");
    for (int i = 0; i < d->total_blocks; i++)
        printf("%d\t%d\n", i,d->used_blocks[i]);
    
}

int main() 
{
    int choice;
    int total_blocks, num_files;
    char name[50];
    int size, start_block;
    printf("Enter the total number of blocks on the disk: ");
    scanf("%d", &total_blocks);
    
    struct disk d;
    init_disk(&d, total_blocks);

    while(true)
    {   
        printf("\nMenu:\n");
        printf("1. Allocate File\n");
        printf("2. Display Disk Status\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) 
        {
            case 3:
                return 0;
            case 1:
                printf("\nEnter details for file:\n");
                printf("Enter file name: ");
                scanf("%s", name);
                printf("Enter file size: ");
                scanf("%d", &size);
                printf("Enter start block: ");
                scanf("%d", &start_block);
                struct file *f = allocate_file(&d, name, size, start_block);
                if (f == NULL )
                    printf("Could not allocate space for %s\n", name);
                else
                    printf("File allocated successfully.\n");
                break;
            case 2:
                display_disk(&d);
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
                break;
        }
    }
    return 0;
}

