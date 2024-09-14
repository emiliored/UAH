from typing import Tuple, List
from lang.expression import Expression

class Section:
    """
    Section separating the entire code
    """
    def __init__(self, name: str) -> None:
        self.name = name
        self.timestamps: List[Tuple[int, List[Expression]]] = []
        # Append starting timestamp (0 seconds)
        self.timestamps.append((0, [])) 

    def __str__(self) -> str:
        s = self.name
        for timestamp in self.timestamps:
            delta = timestamp[0]
            s += str(delta) + '\n'
            for expr in timestamp[1]:
                s += '\t' + str(expr) + '\n'
        return s
