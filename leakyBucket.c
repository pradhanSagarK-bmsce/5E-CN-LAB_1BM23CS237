#include <stdio.h>
#include <string.h>

int min(int x, int y) {
    if (x < y)
        return x;
    else
        return y;
}

int main() {
    int drop = 0, mini, nsec, cap, count = 0, i, inp[25], process;

    // Input for bucket size, processing rate, and simulation time
    printf("Enter the bucket size:\n");
    scanf("%d", &cap);
    printf("Enter the processing rate:\n");
    scanf("%d", &process);
    printf("Enter the number of seconds you want to simulate:\n");
    scanf("%d", &nsec);

    // Input the packet sizes for each second
    for (i = 0; i < nsec; i++) {
        printf("Enter the size of the packet entering at second %d:\n", i + 1);
        scanf("%d", &inp[i]);
    }

    // Output header
    printf("\n Second | Packet received | Packet sent | Packet left | Dropped \n");
    printf("--------------------------------------------------------------------------\n");

    // Simulation for each second
    for (i = 0; i < nsec; i++) {
        count += inp[i]; // Add the incoming packet size to the total

        if (count > cap) {
            drop = count - cap; // Calculate the dropped packets
            count = cap; // Set count to the bucket capacity
        }

        // Output the simulation data for the current second
        printf("%d", i + 1);
        printf("\t%d", inp[i]); // Packet received

        mini = min(count, process); // Determine the minimum of processing rate and remaining packets
        printf("\t\t%d", mini); // Packet sent

        count -= mini; // Decrease the remaining count by the packets sent
        printf("\t\t%d", count); // Remaining packets

        printf("\t\t%d\n", drop); // Dropped packets
        drop = 0; // Reset dropped packets for the next iteration
    }

    // Handle remaining packets after the simulation time ends
    for (; count != 0; i++) {
        if (count > cap) {
            drop = count - cap;
            count = cap;
        }

        printf("%d", i + 1);
        printf("\t0"); // No new packets are received after the simulation time ends

        mini = min(count, process);
        printf("\t\t%d", mini); // Packet sent

        count -= mini; // Decrease remaining packets
        printf("\t\t%d", count); // Remaining packets

        printf("\t\t%d\n", drop); // Dropped packets
        drop = 0; // Reset dropped packets for the next iteration
    }

    return 0;
}
