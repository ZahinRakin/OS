import java.util.Scanner;

public class preemptiveSjf_1447 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number_of_process = scanner.nextInt();
        String[] process = new String[number_of_process];
        int[] burst_time = new int[number_of_process];
        int[] new_burst_time = new int[number_of_process];
        int[] priority = new int[number_of_process];
        int[] arrival_time = new int[number_of_process];

        for (int i = 0; i < number_of_process; i++) {
            process[i] = scanner.next();
            burst_time[i] = scanner.nextInt();
            priority[i] = scanner.nextInt();
            arrival_time[i] = scanner.nextInt();
            new_burst_time[i] = burst_time[i];
        }

        int[] start_time = new int[number_of_process];
        int[] finish_time = new int[number_of_process];
        int[] check_done = new int[number_of_process];
        int[] already_added_in_queue = new int[number_of_process];

        for (int i = 0; i < number_of_process; i++) {
            check_done[i] = 0;
            already_added_in_queue[i] = 0;
        }

        String[] queue_line = new String[500];
        int[] queue_time = new int[500];
        int[] gantt_chart_start = new int[500];
        int[] gantt_chart_finish = new int[500];

        int time = 0, index = 0;
        for (int i = 1; ; i++) {
            int minimum_burst_time = Integer.MAX_VALUE;
            int working_process = i;

            for (int j = 0; j < number_of_process; j++) {
                if (burst_time[j] < minimum_burst_time && check_done[j] == 0 && arrival_time[j] <= time) {
                    minimum_burst_time = burst_time[j];
                    working_process = j;
                }
            }

            queue_line[index] = process[working_process];
            gantt_chart_start[index] = time;

            if (already_added_in_queue[working_process] == 0) {
                start_time[working_process] = time;
                already_added_in_queue[working_process] = 1;
            }

            int minimum_time = Integer.MAX_VALUE;
            for (int j = 0; j < number_of_process; j++) {
                if (arrival_time[j] < minimum_time && arrival_time[j] > time) {
                    minimum_time = arrival_time[j];
                }
            }

            if (time + burst_time[working_process] > minimum_time) {
                queue_time[index] = minimum_time;
                burst_time[working_process] -= (minimum_time - time);
                time = minimum_time;
            } else {
                queue_time[index] = time + burst_time[working_process];
                time += burst_time[working_process];
                burst_time[working_process] = 0;
                finish_time[working_process] = time;
            }

            gantt_chart_finish[index] = time;
            index++;

            if (burst_time[working_process] == 0) {
                check_done[working_process] = 1;
                int another_minimum_time = Integer.MAX_VALUE;

                for (int j = 0; j < number_of_process; j++) {
                    if (arrival_time[j] < another_minimum_time && check_done[j] == 0) {
                        another_minimum_time = arrival_time[j];
                    }
                }

                if (another_minimum_time > time) {
                    time = another_minimum_time;
                }
            }

            int flag = 0;
            for (int j = 0; j < number_of_process; j++) {
                if (check_done[j] == 0) {
                    flag = 1;
                }
            }

            if (flag == 0) {
                break;
            }
        }

        System.out.println("                                             Gantt chart");
        System.out.print("|---" + queue_line[0] + "---|");

        for (int i = 1; i < index; i++) {
            if (gantt_chart_start[i] > gantt_chart_finish[i - 1]) {
                System.out.print("---idle---|");
            }
            System.out.print("----" + queue_line[i] + "----|");
        }

        System.out.println();
        System.out.print("0        " + gantt_chart_finish[0]);

        for (int i = 1; i < index; i++) {
            if (gantt_chart_start[i] > gantt_chart_finish[i - 1]) {
                System.out.print("         " + gantt_chart_start[i]);
            }
            System.out.print("         " + gantt_chart_finish[i]);
        }

        double average_turnaround_time = 0.0;
        double average_waiting_time = 0.0;

        System.out.println();
        System.out.println("Turn around time for each process: ");

        for (int i = 0; i < number_of_process; i++) {
            System.out.println(process[i] + "=" + (finish_time[i] - arrival_time[i]));
            average_turnaround_time += (finish_time[i] - arrival_time[i]);
        }

        System.out.println("Waiting time for each process: ");

        for (int i = 0; i < number_of_process; i++) {
            System.out.println(process[i] + "=" + (finish_time[i] - arrival_time[i] - new_burst_time[i]));
            average_waiting_time += (finish_time[i] - arrival_time[i] - new_burst_time[i]);
        }

        System.out.println("Average turnaround time: " + average_turnaround_time / number_of_process);
        System.out.println("Average waiting time: " + average_waiting_time / number_of_process);
    }
}