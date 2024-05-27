import java.util.Arrays;

public class ParallelSieveControl {
    private static final int LIMIT = 1_000_000_000;
    private static boolean[] isPrime = new boolean[LIMIT + 1];

    public static void main(String[] args) throws InterruptedException {
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;

        int sqrtLimit = (int) Math.sqrt(LIMIT);

        for (int numThreads = 2; numThreads <= 6; numThreads++){
            Thread[] threads = new Thread[numThreads];

            long startTime = System.currentTimeMillis();

            for (int i = 2; i <= sqrtLimit; i++) {
                if (isPrime[i]) {
                    final int prime = i;

                    int threadIndex = (i - 2) % numThreads;
                    if (threadIndex == 0 && threads[threadIndex] != null)
                        threads[threadIndex].join();    
                    
                    threads[threadIndex] = new Thread(() -> {
                        for (int k = prime * prime; k <= LIMIT; k += prime) {
                            isPrime[k] = false;
                        }
                    });
                    threads[threadIndex].start();
                }
            }

            for (Thread thread : threads) {
                if (thread != null) {
                    thread.join();
                }
            }

            long endTime = System.currentTimeMillis();
            long elapsedTime = endTime - startTime;
            System.out.println("Elapsed Time: " + elapsedTime + " milliseconds");
            System.out.println();
        }


        // Print prime numbers (optional)
        // for (int i = 2; i <= LIMIT; i++) {
        //     if (isPrime[i]) {
        //         System.out.print(i + " ");
        //     }
        // }
    }
}
