import heapq

def best_first_search(graph, start, goal, heuristic):
    open_list = []  # Priority queue
    closed_list = set()
    parent = {start: None}
    heapq.heappush(open_list, (heuristic[start], start))

    while open_list:
        _, current = heapq.heappop(open_list)
        closed_list.add(current)

        print(f"Current Node: {current}")
        print(f"OPEN List: {[n for _, n in open_list]}")
        print(f"CLOSED List: {list(closed_list)}\n")

        if current == goal:
            print(f"Goal {goal} reached!")
            return reconstruct_path(parent, goal)

        for neighbor in graph[current]:
            if neighbor not in closed_list and neighbor not in [n for _, n in open_list]:
                parent[neighbor] = current
                heapq.heappush(open_list, (heuristic[neighbor], neighbor))

    return None

def reconstruct_path(parent, goal):
    path = []
    while goal:
        path.append(goal)
        goal = parent[goal]
    path.reverse()
    return path

# Graph representation
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F', 'G'],
    'D': [],
    'E': [],
    'F': [],
    'G': []
}

# Heuristic values
heuristic = {'A': 6, 'B': 4, 'C': 3, 'D': 7, 'E': 2, 'F': 5, 'G': 0}

# Run the algorithm
optimal_path = best_first_search(graph, 'A', 'G', heuristic)
print(f"Optimal Path: {optimal_path}")
