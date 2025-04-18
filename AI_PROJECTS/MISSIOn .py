from collections import deque

def is_valid(m, c):
    return (m == 0 or m >= c) and (3 - m == 0 or (3 - m) >= (3 - c))

def get_successors(state):
    m, c, boat = state
    moves = [(1, 0), (2, 0), (0, 1), (0, 2), (1, 1)]
    successors = []

    for dm, dc in moves:
        if boat == 1:  # boat on left side
            new_m, new_c = m - dm, c - dc
            new_boat = 0
        else:  # boat on right side
            new_m, new_c = m + dm, c + dc
            new_boat = 1

        if 0 <= new_m <= 3 and 0 <= new_c <= 3 and is_valid(new_m, new_c):
            successors.append((new_m, new_c, new_boat))
    return successors

def bfs():
    start = (3, 3, 1)
    goal = (0, 0, 0)
    queue = deque([(start, [start])])
    visited = set()

    while queue:
        current, path = queue.popleft()
        if current == goal:
            return path
        if current in visited:
            continue
        visited.add(current)

        for successor in get_successors(current):
            if successor not in visited:
                queue.append((successor, path + [successor]))
    return None

# Run the solution
solution = bfs()

print("Solution path:")
for step in solution:
    left_m, left_c, boat = step
    right_m = 3 - left_m
    right_c = 3 - left_c
    boat_side = "Left" if boat == 1 else "Right"
    print(f"Left[{left_m}M, {left_c}C] --- Boat:{boat_side} --- Right[{right_m}M, {right_c}C]")
