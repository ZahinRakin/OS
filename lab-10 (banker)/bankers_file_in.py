def bankers_algo(max_need, res_instance, allocated):
    ROW, COL = len(max_need), len(max_need[0])
    cur_res_need = []
    available = [res_instance[i] for i in range(COL)]

    # Calculate current needs and initial available resources
    for need, alloc in zip(max_need, allocated):
        cur_res_need.append([need[i] - alloc[i] for i in range(COL)])
        available = [available[i] - alloc[i] for i in range(COL)]

    print('Initial available: ', available)
    ans = []
    finished = [False] * ROW

    while len(ans) < ROW:
        allocated_this_round = False
        for i in range(ROW):
            if finished[i]:
                continue
            elif all(cur_res_need[i][j] <= available[j] for j in range(COL)):
                for k in range(COL):
                    available[k] += allocated[i][k]
                ans.append(i)
                finished[i] = True
                allocated_this_round = True
                print(f'Process {i} can be completed, available: {available}')
                break

        if not allocated_this_round:
            break

    if len(ans) == ROW:
        print('Safe sequence: ', ans)
    else:
        print('No safe sequence found.')

def read_input_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    # Extract number of processes and resources
    num_processes, num_resources = map(int, lines[0].strip().split())

    # Extract max_need matrix
    max_need = []
    for i in range(1, num_processes + 1):
        row = list(map(int, lines[i].strip().split()))
        max_need.append(row)

    # Extract res_instance
    res_instance = list(map(int, lines[num_processes + 1].strip().split()))

    # Extract allocated matrix
    allocated = []
    for i in range(num_processes + 2, num_processes + 2 + num_processes):
        row = list(map(int, lines[i].strip().split()))
        allocated.append(row)

    return max_need, res_instance, allocated

if __name__ == "__main__":
    filename = 'input.txt'
    max_need, res_instance, allocated = read_input_from_file(filename)

    bankers_algo(max_need, res_instance, allocated)
