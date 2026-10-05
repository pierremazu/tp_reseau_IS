#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int global_data = 42; //DATA - variable initialisé 

int gloabal_bss; //BSS - variable initialisé par défault 

int main(void) {
    // Variables pour observer :
    // -> String
    char* str = "Hello World!";
    // -> HEAP
    int* heap = malloc(sizeof(int));
    // -> Stack
    int stack_var = 42;
    // -> Mmap
    void* mmap_area = mmap(
        NULL,                      
        4096,                 
        PROT_READ | PROT_WRITE,     
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,                        
        0                           
    );

    printf("|-------------------- Exercice 1: --------------------|\n");
    printf("DATA : %p\n", &global_data);
    printf("BSS  : %p\n", &gloabal_bss);      
    printf("STR  : %p\n", str);
    printf("HEAP : %p\n", heap);
    printf("STACK: %p\n", &stack_var);
    printf("TEXT : %p\n", &main);
    printf("LibC : %p\n", &printf);
    printf("Mmap : %p\n", mmap_area);

    int pid = getpid();
    printf("\nPID : %d\n", pid);

    printf("\n|---------------------- PMAP ----------------------|\n");
    int child = fork();

    if (child == -1) {
        perror("fork");
        munmap(mmap_area, 4096);
        free(heap);
        return EXIT_FAILURE;
    }
    if (child == 0) {
        //fils
        char pid_str[16];
        snprintf(pid_str, sizeof(pid_str), "%d", pid);
        execlp("pmap", "pmap", "-X", pid_str, NULL);
        perror("execlp");
        return EXIT_FAILURE;
    }
    
    waitpid(child, NULL, 0);

    // free
    munmap(mmap_area, 4096);
    free(heap);

    return 0;
}
