import random
import numpy as np

def total_distance(route, distance_matrix):
    return sum(distance_matrix[route[i]][route[i + 1]] for i in range(len(route) - 1)) + distance_matrix[route[-1]][route[0]]

def get_neighbors(route):
    neighbors = []
    for i in range(1, len(route) - 1):
        for j in range(i + 1, len(route)):
            neighbor = route[:]
            neighbor[i], neighbor[j] = neighbor[j], neighbor[i]
            neighbors.append(neighbor)
    return neighbors

def simple_hill_climb(route, distance_matrix):
    current = route[:]
    while True:
        neighbors = get_neighbors(current)
        best_neighbor = min(neighbors, key=lambda x: total_distance(x, distance_matrix))
        if total_distance(best_neighbor, distance_matrix) >= total_distance(current, distance_matrix):
            break
        current = best_neighbor
    return current, total_distance(current, distance_matrix)

def steepest_ascent_hill_climb(route, distance_matrix):
    current = route[:]
    while True:
        neighbors = get_neighbors(current)
        best_neighbor = min(neighbors, key=lambda x: total_distance(x, distance_matrix))
        if total_distance(best_neighbor, distance_matrix) >= total_distance(current, distance_matrix):
            break
        current = best_neighbor
    return current, total_distance(current, distance_matrix)

def stochastic_hill_climb(route, distance_matrix):
    current = route[:]
    while True:
        neighbors = get_neighbors(current)
        better_neighbors = [n for n in neighbors if total_distance(n, distance_matrix) < total_distance(current, distance_matrix)]
        if not better_neighbors:
            break
        current = random.choice(better_neighbors)
    return current, total_distance(current, distance_matrix)

def random_restart_hill_climb(distance_matrix, iterations=10):
    best_route = None
    best_distance = float('inf')
    for _ in range(iterations):
        route = list(range(len(distance_matrix)))
        random.shuffle(route)
        result, dist = steepest_ascent_hill_climb(route, distance_matrix)
        if dist < best_distance:
            best_distance = dist
            best_route = result
    return best_route, best_distance

# Example Distance Matrix (for 5 cities)
distance_matrix = np.array([
    [0, 2, 9, 10, 7],
    [2, 0, 6, 4, 3],
    [9, 6, 0, 8, 5],
    [10, 4, 8, 0, 6],
    [7, 3, 5, 6, 0]
])

initial_route = list(range(len(distance_matrix)))
random.shuffle(initial_route)

print("Initial Route:", initial_route)
route, distance = simple_hill_climb(initial_route, distance_matrix)
print(f"Simple Hill Climbing: Route = {route}, Distance = {distance}")
route, distance = steepest_ascent_hill_climb(initial_route, distance_matrix)
print(f"Steepest Ascent Hill Climbing: Route = {route}, Distance = {distance}")
route, distance = stochastic_hill_climb(initial_route, distance_matrix)
print(f"Stochastic Hill Climbing: Route = {route}, Distance = {distance}")
route, distance = random_restart_hill_climb(distance_matrix)
print(f"Random Restart Hill Climbing: Route = {route}, Distance = {distance}")