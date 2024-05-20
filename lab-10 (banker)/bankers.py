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


if __name__ == "__main__":
    max_need = ((7, 5, 3), (3, 2, 2), (9, 0, 2), (2, 2, 2), (4, 3, 3))
    res_instance = (10, 5, 7)
    allocated = [[0, 1, 0], [2, 0, 0], [3, 0, 2], [2, 1, 1], [0, 0, 2]]

    bankers_algo(max_need, res_instance, allocated)
