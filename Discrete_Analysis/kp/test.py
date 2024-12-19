import random
import sys

def generate_graph_data():
    n, m = random.randint(1, 10), random.randint(1, 10)
    vertices = []
    edges = []

    for _ in range(n):
        x, y = random.randint(-1000000000, 1000000000), random.randint(-1000000000, 1000000000)
        vertices.append((x, y))

    for _ in range(m):
        u, v = random.randint(1, n), random.randint(1, n)
        edges.append((u, v))

    q = random.randint(1, 300)
    queries = []
    for _ in range(q):
        a, b = random.randint(1, n), random.randint(1, n)
        queries.append((a, b))

    return n, m, vertices, edges, q, queries

def main():
    n, m, vertices, edges, q, queries = generate_graph_data()

    print(f"{n} {m}")
    for vertex in vertices:
        print(f"{vertex[0]} {vertex[1]}")

    for edge in edges:
        print(f"{edge[0]} {edge[1]}")

    print(f"{q}")
    for query in queries:
        print(f"{query[0]} {query[1]}")

if __name__ == "__main__":
    main()