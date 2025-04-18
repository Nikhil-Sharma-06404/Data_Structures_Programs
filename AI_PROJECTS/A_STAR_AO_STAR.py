import heapq

##############################
# A* Algorithm Implementation
##############################

class AStarNode:
    def __init__(self, name, h_val):
        self.name = name
        self.g = float('inf')  # cost from start (infinity initially)
        self.h = h_val         # heuristic cost to goal
        self.f = float('inf')  # f = g + h
        self.parent = None
        self.neighbors = []    # list of tuples: (neighbor, arc_cost)
        
    def __lt__(self, other):
        return self.f < other.f

def a_star(start, goal):
    # Initialize start node
    start.g = 0
    start.f = start.h

    open_list = []
    closed_list = {}
    heapq.heappush(open_list, start)
    
    step = 1
    while open_list:
        current = heapq.heappop(open_list)
        print(f"[Step {step}] {current.name} | g: {current.g}, h: {current.h}, f: {current.f}")
        step += 1
        
        if current.name == goal.name:
            path = []
            temp = current
            while temp:
                path.append(temp.name)
                temp = temp.parent
            path.reverse()
            print("\nA* Final Optimal Path:", " -> ".join(path))
            print("A* Final Cost:", current.f)
            return
        closed_list[current.name] = current
        
        for neighbor, cost in current.neighbors:
            if neighbor.name in closed_list:
                continue
            temp_g = current.g + cost
            if temp_g < neighbor.g:
                neighbor.g = temp_g
                neighbor.f = neighbor.g + neighbor.h
                neighbor.parent = current
                print(f"   Update: {neighbor.name} | new g: {neighbor.g}, h: {neighbor.h}, f: {neighbor.f}")
                heapq.heappush(open_list, neighbor)

##############################
# AO* Algorithm Implementation
##############################

class AONode:
    def __init__(self, name, heuristic, node_type):
        """
        node_type: 'OR' or 'AND'
        children: list of tuples (child_node, arc_cost)
        """
        self.name = name
        self.heuristic = heuristic  # initial heuristic estimate
        self.node_type = node_type
        self.children = []  # list of tuples: (child, arc_cost)

def ao_star_recursive(node):
    # Leaf node: simply return its heuristic and its name as path.
    if not node.children:
        print(f"{node.name}:{node.heuristic}", end="  ")
        return node.heuristic, [node.name]

    # For OR nodes: choose branch with minimal cost.
    if node.node_type == 'OR':
        results = []
        for child, arc_cost in node.children:
            cost, path = ao_star_recursive(child)
            total = arc_cost + cost
            print(f"{node.name}->{child.name}:{total}", end="  ")
            results.append((total, path))
        best_cost, best_path = min(results, key=lambda x: x[0])
        return best_cost, [node.name] + best_path

    # For AND nodes: all children must be solved; sum the costs.
    elif node.node_type == 'AND':
        total = 0
        path_accum = [node.name]
        for child, arc_cost in node.children:
            cost, path = ao_star_recursive(child)
            branch_cost = arc_cost + cost
            print(f"{node.name}+{child.name}:{branch_cost}", end="  ")
            total += branch_cost
            path_accum += path
        return total, path_accum

def run_ao_star():
    # Construct an example AO* tree:
    #            S (OR, heuristic 10)
    #           /       \
    #    (OR) A (5)     (OR) B (8)
    #        /     \          \
    # (AND) C (3)  D (2)       E (5)
    #      |          \          \
    #   G (0)         H (0)       F (0)
    #
    # Arc costs:
    # S -> A: 1,  S -> B: 2
    # A -> C: 2,  A -> D: 2
    # C -> G: 1,  D -> H: 1
    # B -> E: 3,  E -> F: 1

    S = AONode("S", 10, "OR")
    A = AONode("A", 5, "OR")
    B = AONode("B", 8, "OR")
    C = AONode("C", 3, "AND")
    D = AONode("D", 2, "OR")
    E = AONode("E", 5, "OR")
    G = AONode("G", 0, "OR")
    H = AONode("H", 0, "OR")
    F = AONode("F", 0, "OR")

    S.children = [(A, 1), (B, 2)]
    A.children = [(C, 2), (D, 2)]
    C.children = [(G, 1)]
    D.children = [(H, 1)]
    B.children = [(E, 3)]
    E.children = [(F, 1)]

    print("\nAO* progression (format: Branch:ComputedCost):")
    cost, path = ao_star_recursive(S)
    print("\n\nAO* Final Optimal Path:", " -> ".join(path))
    print("AO* Final Cost:", cost)

##############################
# Main Execution
##############################

if __name__ == '__main__':
    # A* Algorithm
    print("=== A* Algorithm ===")
    S_astar = AStarNode("S", 5)
    A_astar = AStarNode("A", 3)
    B_astar = AStarNode("B", 2)
    C_astar = AStarNode("C", 1)
    G_astar = AStarNode("G", 0)

    # Set infinite cost for all nodes except start.
    for node in [S_astar, A_astar, B_astar, C_astar, G_astar]:
        node.g = float('inf')
        node.f = float('inf')
    S_astar.g = 0
    S_astar.f = S_astar.h

    S_astar.neighbors = [(A_astar, 1), (B_astar, 4)]
    A_astar.neighbors = [(C_astar, 2)]
    C_astar.neighbors = [(G_astar, 1)]
    
    a_star(S_astar, G_astar)
    
    # AO* Algorithm
    run_ao_star()
