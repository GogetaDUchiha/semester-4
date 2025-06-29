#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4 

int main() {
    int num_processes, size, i, j;
    
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    
    int* processes[num_processes];
    int sizes[num_processes];
    
    // Allocate memory for each process
    for(i = 0; i < num_processes; i++) {
        printf("Enter size for process %d: ", i+1);
        scanf("%d", &size);
        sizes[i] = size;
        processes[i] = (int*)malloc(size * sizeof(int));
        if(!processes[i]) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        
        printf("Enter %d values for process %d: ", size, i+1);
        for(j = 0; j < size; j++)
            scanf("%d", &processes[i][j]);
    }
    
    // Print initial memory status
    printf("\nMemory Status:\n");
    for(i = 0; i < num_processes; i++)
        printf("Process %d: %d bytes\n", i+1, sizes[i]);
    
    // Simulate swapping (swap out process 1)
    printf("\nSwapping: Freeing Process 1...\n");
    free(processes[0]);
    processes[0] = NULL;
    
    printf("Memory Status After Swap Out:\n");
    for(i = 0; i < num_processes; i++)
        printf("Process %d: %s\n", i+1, processes[i] ? "In Memory" : "Swapped Out");
    
    // Swap back in
    printf("\nSwapping: Reallocating Process 1...\n");
    processes[0] = (int*)malloc(sizes[0] * sizeof(int));
    for(j = 0; j < sizes[0]; j++)
        processes[0][j] = j+100; // Sample data
    
    // Paging demonstration
    printf("\nPaging Demonstration:\n");
    for(i = 0; i < num_processes; i++) {
        int pages = (sizes[i] + PAGE_SIZE - 1) / PAGE_SIZE;
        printf("\nProcess %d (%d bytes, %d pages):\n", i+1, sizes[i], pages);
        printf("Logical -> Physical Address Mapping:\n");
        
        for(j = 0; j < pages; j++) {
            int physical_frame = (i * 10 + j) % 8; // Simple mapping
            printf("Page %d -> Frame %d\n", j, physical_frame);
        }
        
        // Show sample address translation
        if(sizes[i] > 0) {
            int logical_addr = 2; // Sample address
            int page = logical_addr / PAGE_SIZE;
            int offset = logical_addr % PAGE_SIZE;
            int physical_frame = (i * 10 + page) % 8;
            int physical_addr = physical_frame * PAGE_SIZE + offset;
            printf("Sample: Logical %d -> Physical %d\n", logical_addr, physical_addr);
        }
    }
    
    // Clean up
    for(i = 0; i < num_processes; i++)
        if(processes[i]) free(processes[i]);
    
    return 0;
}
