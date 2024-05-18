public class SJF_1447 {
    public static void main(String[] args) {
        String[] process = {"p1", "p2", "p3", "p4", "p5"};
        int[] burst_time = {2, 1, 8, 4, 5};
        int i, j;

        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5 - i - 1; j++) {
                if (burst_time[j] > burst_time[j + 1]) {
                    // Swap burst_time
                    int temp = burst_time[j];
                    burst_time[j] = burst_time[j + 1];
                    burst_time[j + 1] = temp;

                    // Swap process
                    String tempString = process[j];
                    process[j] = process[j + 1];
                    process[j + 1] = tempString;
                }
            }
        }

        int[] cumulative = new int[6];
        for (i = 1; i < 6; i++) {
            cumulative[i] = cumulative[i - 1] + burst_time[i - 1];
        }

        System.out.print("|");
        for (i = 0; i < 5; i++) {
            System.out.print("---" + process[i] + "---|");
        }
        System.out.println();

        for (i = 0; i < 6; i++) {
            System.out.print(cumulative[i] + "        ");
        }
        System.out.println();

        int[] turnaround_time = new int[5];
        double average_turnaround_time = 0.0;
        System.out.println("Turnaround time for each process: ");
        for (i = 1; i < 6; i++) {
            turnaround_time[i - 1] = cumulative[i];
            System.out.println(process[i - 1] + "=" + cumulative[i]);
            average_turnaround_time += turnaround_time[i - 1];
        }

        int[] waiting_time = new int[5];
        double average_waiting_time = 0.0;
        System.out.println("Waiting time for each process: ");
        for (i = 1; i < 6; i++) {
            waiting_time[i - 1] = cumulative[i] - burst_time[i - 1];
            System.out.println(process[i - 1] + "=" + (cumulative[i] - burst_time[i - 1]));
            average_waiting_time += waiting_time[i - 1];
        }

        System.out.println("Average turnaround time=" + average_turnaround_time / 5);
        System.out.println("Average waiting time=" + average_waiting_time / 5);
    }
}