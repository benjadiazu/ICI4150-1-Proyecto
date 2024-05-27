class Maze:
    def __init__(self):
        self.__maze =  [[1, 1, 1, 1, 1, 1, 1, 1, 1],
                        [1, 0, 1, 0, 1, 0, 0, 0, 1],
                        [1, 0, 0, 0, 1, 0, 1, 0, 1],
                        [1, 0, 1, 0, 0, 0, 1, 0, 1],
                        [1, 0, 1, 1, 1, 1, 1, 0, 1],
                        [1, 0, 0, 0, 0, 0, 1, 0, 1],
                        [1, 0, 1, 1, 1, 0, 1, 0, 1],
                        [1, 0, 0, 0, 1, 0, 0, 0, 1],
                        [1, 1, 1, 1, 1, 1, 1, 1, 1]]
        
        self.__rows = len(self.__maze)
        self.__colums = len(self.__maze[0])

    def get_maze(self):
        return self.__maze


