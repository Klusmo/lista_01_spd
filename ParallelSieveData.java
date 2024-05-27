import java.util.Arrays;

public class ParallelSieveData {
    private static final int LIMIT = 1_000_000_000;
    private static boolean[] isPrime = new boolean[LIMIT + 1];

    public static void main(String[] args) throws InterruptedException {
        Arrays.fill(isPrime, true);
        isPrime[0] = isPrime[1] = false;

        // int numThreads = Runtime.getRuntime().availableProcessors();
        for (int numThreads = 2; numThreads <= 6; numThreads++){
            System.out.println("Number of Threads: " + numThreads);

            long startTime = System.currentTimeMillis();

            Thread[] threads = new Thread[numThreads];
            final int finalNumThreads = numThreads;

            for (int i = 0; i < numThreads; i++) {
                final int threadId = i;
                threads[i] = new Thread(() -> {
                    for (int j = 2 + threadId; j * j <= LIMIT; j += finalNumThreads){
                        if (isPrime[j]) {
                            for (int k = j * j; k <= LIMIT; k += j) {
                                isPrime[k] = false;
                            }
                        }
                    }
                });
                threads[i].start();
            }

            for (Thread thread : threads) {
                thread.join();
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
