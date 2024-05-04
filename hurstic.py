from queue import PriorityQueue

def heuristic(state, target):
    # Using the absolute difference between the current state and the target as the heuristic
    return abs(state - target)

def a_star(start, target):
    frontier = PriorityQueue()
    # f = g + h where g is the cost so far, h is the heuristic
    frontier.put((0, 0, start, [start]))
    explored = set()

    while not frontier.empty():
        _, cost, current, path = frontier.get()
        if current == target:
            return path
        explored.add(current)

        for move in [current * 2,current + 1]:
            if move <= target and move not in explored:
                new_cost = cost + 1
                new_path = path + [move]
                frontier.put((new_cost + heuristic(move, target), new_cost, move, new_path))
    return None

start_number = 1
target_number = 18
solution = a_star(start_number, target_number)
if solution:
    print(f"Shortest path from {start_number} to {target_number}:", solution)
else:
    print(f"No path from {start_number} to {target_number}")