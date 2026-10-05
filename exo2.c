#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
    int fd = open("test.txt", O_RDWR);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    struct stat infos_fichier;

    if (fstat(fd, &infos_fichier) == -1) {
        perror("Erreur lors de la récupération des infos");
        close(fd);
        return 1;
    }

    if (infos_fichier.st_size <= 1) {
        close(fd);
        return 0;
    }

    printf("Taille du fichier : %ld octets\n", infos_fichier.st_size);

    char *addr = mmap(NULL, infos_fichier.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("Erreur lors de la mmap");
        close(fd);
        return 1;
    }

    close(fd);

    //inversion
    long i = 0;
    long j = infos_fichier.st_size - 1;
    while (i < j) {
        char temp = addr[i];
        addr[i] = addr[j];
        addr[j] = temp;
        i++;
        j--;
    }
    //pour vérifier que la fonction marche (on peut aussi ouvrir le fichier modifié)
    printf("Nouveau contenu :\n%.*s\n", (int)infos_fichier.st_size, addr);

    //fin du mapping mémoire
    if (munmap(addr, infos_fichier.st_size) == -1) {
        perror("Erreur lors de munmap");
        return 1;
    }

    return 0;
}