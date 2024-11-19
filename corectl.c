#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <fcntl.h>

const char* STR_PARK = "park";
const char* STR_UNPARK = "unpark";
const char* STR_LIST = "list";
int N_CORES = 0;

void printusage(char *execname) {
    printf("Usage:\n\t%s park - Parks half of the cpu cores\n\t%s unpark - Unparks all cores\n\n", execname, execname);
    return;
}

void park() {
    unsigned int half_cores = N_CORES/2;
    printf("Parking %d cores...\n", half_cores);
    
    /* From the midle core to the last */
    /* Is the buffer too large? Yes. */
    char* buff = calloc(512, sizeof(char));
    for (int i = N_CORES - half_cores; i < N_CORES; i++) {
        snprintf(buff, 511, "/sys/devices/system/cpu/cpu%d/online", i);
        int fd = open(buff, O_WRONLY);
        write(fd, "0", 1);
        close(fd);
    }
}

void unpark() {
    printf("Unparking %d cores...\n", N_CORES);

    char* buff = calloc(512, sizeof(char));
    for (int i = 0; i < N_CORES; i++) {
        snprintf(buff, 511, "/sys/devices/system/cpu/cpu%d/online", i);
        int fd = open(buff, O_WRONLY);
        write(fd, "1", 1);
        close(fd);
    }
}

void list() {
    int actv = get_nprocs();
    printf("Total cores: %d\n", N_CORES);
    printf("Active cores: %d\n", actv);
    if (N_CORES - actv > 0) {
        printf("Parked cores: %d\n", N_CORES-actv);
    }

}

int main(int argc, char **argv) {
    /* Pre run checks */
    /* Number of CPU cores */
    N_CORES = get_nprocs_conf();

    if (N_CORES < 4) {
        printf("Number of configured cores < 4!\n");
        exit(EXIT_FAILURE);
    }

    /* Root user */
    if (geteuid() != 0) {
        printf("Not running as UID 0 (root). Cannot enable/disable CPU cores.\n");
        exit(EXIT_FAILURE);
    }

    /* Arguments */
    if (argc != 2) {
        printusage(argv[0]);
        exit(EXIT_FAILURE);
    }
    else{
        /* Park command */
        if (strcoll(argv[1], STR_PARK) == 0) park();
        else if (strcoll(argv[1], STR_UNPARK) == 0) unpark();
        else if (strcoll(argv[1], STR_LIST) == 0) list();
        else {
            printusage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}