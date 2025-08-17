#include <stdio.h>
#include <omp.h>

#define N 5   // number of items to produce/consume

int main() {
    int buffer[N];       // shared buffer
    int count = 0;       // number of items in buffer
    int produced = 0;    // index for producer
    int consumed = 0;    // index for consumer

    #pragma omp parallel sections shared(buffer, count, produced, consumed)
    {
        // Producer section
        #pragma omp section
        {
            for (int i = 0; i < N; i++) {
                #pragma omp critical
                {
                    buffer[produced] = i + 1;  // produce item
                    printf("Producer produced: %d\n", buffer[produced]);
                    produced++;
                    count++;
                }
                #pragma omp flush(count)  // make count visible to other threads
            }
        }

        // Consumer section
        #pragma omp section
        {
            for (int i = 0; i < N; i++) {
                int item;
                // wait until something is produced
                while (count <= 0) {
                    #pragma omp flush(count)
                }

                #pragma omp critical
                {
                    item = buffer[consumed];  // consume item
                    printf("Consumer consumed: %d\n", item);
                    consumed++;
                    count--;
                }
                #pragma omp flush(count)
            }
        }
    }

    return 0;
}
