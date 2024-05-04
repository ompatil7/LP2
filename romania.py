import heapq

# Define the map of Romania as a graph with nodes and edges
romania_map = {
    'Arad': {'Zerind': 75, 'Sibiu': 140, 'Timisoara': 118},
    'Zerind': {'Arad': 75, 'Oradea': 71},
    'Oradea': {'Zerind': 71, 'Sibiu': 151},
    'Sibiu': {'Arad': 140, 'Oradea': 151, 'Fagaras': 99, 'Rimnicu': 80},
    'Timisoara': {'Arad': 118, 'Lugoj': 111},
    'Lugoj': {'Timisoara': 111, 'Mehadia': 70},
    'Mehadia': {'Lugoj': 70, 'Drobeta': 75},
    'Drobeta': {'Mehadia': 75, 'Craiova': 120},
    'Craiova': {'Drobeta': 120, 'Rimnicu': 146, 'Pitesti': 138},
    'Rimnicu': {'Sibiu': 80, 'Craiova': 146, 'Pitesti': 97},
    'Fagaras': {'Sibiu': 99, 'Bucharest': 211},
    'Pitesti': {'Rimnicu': 97, 'Craiova': 138, 'Bucharest': 101},
    'Bucharest': {'Fagaras': 211, 'Pitesti': 101, 'Giurgiu': 90, 'Urziceni': 85},
    'Giurgiu': {'Bucharest': 90},
    'Urziceni': {'Bucharest': 85, 'Vaslui': 142, 'Hirsova': 98},
    'Hirsova': {'Urziceni': 98, 'Eforie': 86},
    'Eforie': {'Hirsova': 86},
    'Vaslui': {'Urziceni': 142, 'Iasi': 92},
    'Iasi': {'Vaslui': 92, 'Neamt': 87},
    'Neamt': {'Iasi': 87}
}

# Define the heuristic function (straight-line distance to Bucharest)
heuristic = {
    'Arad': 366, 'Zerind': 374, 'Oradea': 380,
    'Sibiu': 253, 'Timisoara': 329, 'Lugoj': 244,
    'Mehadia': 241, 'Drobeta': 242, 'Craiova': 160,
    'Rimnicu': 193, 'Fagaras': 178, 'Pitesti': 98,
    'Bucharest': 0, 'Giurgiu': 77, 'Urziceni': 80,
    'Hirsova': 151, 'Eforie': 161, 'Vaslui': 199,
    'Iasi': 226, 'Neamt': 234
}

def a_star(start, goal):
    # Priority queue for open nodes
    open_nodes = [(heuristic[start], start)]
    # Set of visited nodes
    visited = set()
    # Parent nodes for path reconstruction
    parents = {}
    # Cost from start to each node and initialize to infinty for all cities 
    g_values = {city: float('inf') for city in romania_map}
    g_values[start] = 0

    while open_nodes:
        # Pop the node with the lowest cost from the priority queue
        current_cost, current_node = heapq.heappop(open_nodes)
        # Mark the current node as visited
        visited.add(current_node)

        # If goal reached, reconstruct path and return
        if current_node == goal:
            path = []
            while current_node in parents:
                path.insert(0, current_node)
                current_node = parents[current_node]
            path.insert(0, start)
            total_cost = g_values[goal]
            return path, total_cost

        # Explore neighbors
        for neighbor, cost in romania_map[current_node].items():
            if neighbor in visited:
                continue
            # Calculate the total cost to reach the neighbor through the current node
            total_cost = g_values[current_node] + cost
            # Update g_value if a better path is found
            if total_cost < g_values[neighbor]:
                g_values[neighbor] = total_cost
                # f(n) = g(n) + h(n)
                f_value = total_cost + heuristic[neighbor]
                # Add the neighbor to the priority queue
                heapq.heappush(open_nodes, (f_value, neighbor))
                # Update parent for path reconstruction
                parents[neighbor] = current_node

    # No path found
    return None

# Example usage
start_city = 'Arad'
goal_city = 'Bucharest'
path, total_cost = a_star(start_city, goal_city)
if path:
    print(f"Path from {start_city} to {goal_city}: {' -> '.join(path)}")
    print(f"Total cost of the path: {total_cost}")
else:
    print(f"No path found from {start_city} to {goal_city}")
