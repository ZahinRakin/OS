import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class ROUND_ROBIN_1447 {
    public static void main(String[] args) {
        String[] process = {"p1", "p2", "p3", "p4", "p5"};
        int[] burst_time = {2, 1, 8, 4, 5};
        int[] new_burst_time = {2, 1, 8, 4, 5};
        int time_quantum, i;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the time quantum: ");
        time_quantum = scanner.nextInt();

        Queue<String> round_robin_queue = new LinkedList<>();
        Queue<String> line = new LinkedList<>();
        Queue<Integer> round_robin_time = new LinkedList<>();

        for (i = 0; i < 5; i++) {
            round_robin_queue.add(process[i]);
        }

        for (i = 1; ; i++) {
            String popped = round_robin_queue.poll();
            line.add(popped);

            if (burst_time[popped.charAt(1) - '0' - 1] >= time_quantum) {
                round_robin_time.add(time_quantum);
                burst_time[popped.charAt(1) - '0' - 1] -= time_quantum;
            } else {
                round_robin_time.add(burst_time[popped.charAt(1) - '0' - 1]);
                burst_time[popped.charAt(1) - '0' - 1] = 0;
            }

            if (burst_time[popped.charAt(1) - '0' - 1] > 0) {
                round_robin_queue.add(popped);
            }

            if (round_robin_queue.size() == 0) {
                break;
            }
        }

        System.out.println("                                           gantt chart");
        String[] new_process = new String[line.size()];
        int[] new_time = new int[round_robin_time.size()];
        int index = 0, sum = 0;
        System.out.print("|");

        while (!line.isEmpty()) {
            new_process[index] = line.poll();
            System.out.print("---" + new_process[index] + "---|");
            index++;
        }

        System.out.println();
        System.out.print("0");
        index = 0;

        while (!round_robin_time.isEmpty()) {
            sum += round_robin_time.poll();
            new_time[index] = sum;
            System.out.print("        " + sum);
            index++;
        }

        System.out.println();

        int[] completion_time = new int[5];
        for (i = index - 1; i >= 0; i--) {
            int new_index = new_process[i].charAt(1) - '0' - 1;
            if (completion_time[new_index] == 0) {
                completion_time[new_index] = new_time[i];
            }
        }

        double average_turnaround_time = 0.0;
        double average_waiting_time = 0.0;

        System.out.println("Turnaround time for each process: ");
        for (i = 0; i < 5; i++) {
            System.out.println(process[i] + "=" + completion_time[i]);
            average_turnaround_time += completion_time[i];
        }

        System.out.println("Waiting time for each process: ");
        for (i = 0; i < 5; i++) {
            System.out.println(process[i] + "=" + (completion_time[i] - new_burst_time[i]));
            average_waiting_time += completion_time[i] - new_burst_time[i];
        }

        System.out.println("Average turnaround time: " + average_turnaround_time / 5);
        System.out.println("Average waiting time: " + average_waiting_time / 5);

        scanner.close();
    }
}