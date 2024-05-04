class Node:
    def __init__(self, data, level, f_val):#initialize
        self.data = data #puzzle
        self.level = level#level
        self.f_val = f_val#function value

    def generate_child(self):# generating all possible next moves
        x, y = self.find(self.data, 0)
        children = []
        if x - 1 >= 0:
            temp = [row[:] for row in self.data]  # Make a copy of the data
            temp[x][y], temp[x - 1][y] = temp[x - 1][y], temp[x][y]
            children.append(temp)
        if y - 1 >= 0:
            temp = [row[:] for row in self.data]
            temp[x][y], temp[x][y - 1] = temp[x][y - 1], temp[x][y]
            children.append(temp)
        if y + 1 < len(self.data):
            temp = [row[:] for row in self.data]
            temp[x][y], temp[x][y + 1] = temp[x][y + 1], temp[x][y]
            children.append(temp)
        if x + 1 < len(self.data):
            temp = [row[:] for row in self.data]
            temp[x][y], temp[x + 1][y] = temp[x + 1][y], temp[x][y]
            children.append(temp)
        return children

    def find(self, matrix, val): #returning x,y of zero
        for i in range(len(matrix)):
            for j in range(len(matrix)):
                if matrix[i][j] == val:
                    return i, j
        print("Value not present in the puzzle")
        return 0, 0


class Puzzle:
    def __init__(self, n):#initialize
        self.n = n#size
        self.open = []#open list storing node
        self.close = []#closed list storing puzzle

    def f(self, start, goal): # level + heuristic function
        return self.h(start.data, goal) + start.level

    def h(self, start, goal):# heuristic function checks the difference between current and goal
        temp = 0
        for i in range(self.n):
            for j in range(self.n):
                if start[i][j] != goal[i][j]:
                    temp += 1
        return temp

    def process(self):
        start = [[1,0,3],
                 [4,2,6],
                 [7,5,8]]
        goal = [[1, 2, 3],
                [4, 5, 6],
                [7, 8, 0]]
        start_node = Node(start, 0, 0)
        start_node.f_val = self.f(start_node, goal)
        self.open.append(start_node)
        while True:
            curr = self.open[0]
            if curr.data not in self.close:
                for i in curr.data:
                    for j in i:
                        print(j, end="")
                    print()
                print("====================================")
                if self.h(curr.data, goal) == 0:
                    break
                for i in curr.generate_child():
                    if i is not None:
                        child_node = Node(i, curr.level + 1, 0)
                        child_node.f_val = self.f(child_node, goal) 
                        self.open.append(child_node)
                self.close.append(curr.data)
            del self.open[0]
            self.open.sort(key=lambda x: x.f_val, reverse=False)


puz = Puzzle(3)
puz.process()
