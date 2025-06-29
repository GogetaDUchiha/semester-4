#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

// Thread function that adds array elements
void* add_array(void* arg) {
    int* numbers = (int*)arg;
    int* sum = new int; // Allocate memory for result
    
    *sum = numbers[0] + numbers[1];
    
    cout << "Thread: Calculating sum of " << numbers[0] << " and " << numbers[1] << endl;
    sleep(1); // Simulate some processing time
    
    pthread_exit(sum); // Return the sum
}

int main() {
    pthread_t thread_id;
    int numbers[2];
    void* thread_result;
    
    // Get input from user
    cout << "Enter first number: ";
    cin >> numbers[0];
    cout << "Enter second number: ";
    cin >> numbers[1];
    
    // Create thread and pass the array
    int res = pthread_create(&thread_id, NULL, add_array, (void*)numbers);
    if (res != 0) {
        cerr << "Thread creation failed" << endl;
        return 1;
    }
    
    cout << "Main: Waiting for thread to finish..." << endl;
    
    // Wait for thread to finish and get the result
    res = pthread_join(thread_id, &thread_result);
    if (res != 0) {
        cerr << "Thread join failed" << endl;
        return 1;
    }
    
    // Cast and print the result
    int* sum = (int*)thread_result;
    cout << "Main: The sum is " << *sum << endl;
    
    // Clean up
    delete sum;
    
    return 0;
}
