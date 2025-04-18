from collections import deque

def is_valid_state(state, jug1_capacity, jug2_capacity):
    jug1, jug2 = state
    return 0 <= jug1 <= jug1_capacity and 0 <= jug2 <= jug2_capacity

def bfs_water_jug(jug1_capacity, jug2_capacity, target):
    # Initialize the BFS queue with the initial state (0, 0)
    queue = deque([(0, 0)])
    visited = set()  # To track visited states
    parent = {}  # To track the path

    # Directions for possible actions
    directions = [
        "Fill Jug1", "Fill Jug2", "Empty Jug1", "Empty Jug2", "Pour Jug1 to Jug2", "Pour Jug2 to Jug1"
    ]

    while queue:
        current_jug1, current_jug2 = queue.popleft()
        visited.add((current_jug1, current_jug2))

        # Print the current state and the direction
        print(f"Current state: ({current_jug1}, {current_jug2})")

        # If the target is achieved
        if current_jug1 == target or current_jug2 == target:
            # Reconstruct the solution path
            path = []
            state = (current_jug1, current_jug2)
            while state in parent:
                path.append(state)
                state = parent[state]
            path.append((0, 0))
            path.reverse()
            print("Solution path:")
            for step in path:
                print(step)
            return True

        # Generate all possible next states
        next_states = []

        # Fill Jug1
        next_states.append((jug1_capacity, current_jug2))
        
        # Fill Jug2
        next_states.append((current_jug1, jug2_capacity))
        
        # Empty Jug1
        next_states.append((0, current_jug2))
        
        # Empty Jug2
        next_states.append((current_jug1, 0))

        # Pour Jug1 to Jug2
        pour_to_jug2 = min(current_jug1, jug2_capacity - current_jug2)
        next_states.append((current_jug1 - pour_to_jug2, current_jug2 + pour_to_jug2))
        
        # Pour Jug2 to Jug1
        pour_to_jug1 = min(current_jug2, jug1_capacity - current_jug1)
        next_states.append((current_jug1 + pour_to_jug1, current_jug2 - pour_to_jug1))

        for i, next_state in enumerate(next_states):
            if next_state not in visited and is_valid_state(next_state, jug1_capacity, jug2_capacity):
                queue.append(next_state)
                parent[next_state] = (current_jug1, current_jug2)
                print(f"{directions[i]} -> {next_state}")

    print("No solution found.")
    return False

if __name__ == "__main__":
    jug1_capacity = int(input("Enter capacity of Jug1: "))
    jug2_capacity = int(input("Enter capacity of Jug2: "))
    target = int(input("Enter target amount: "))

    if not bfs_water_jug(jug1_capacity, jug2_capacity, target):
        print("No solution exists.")
