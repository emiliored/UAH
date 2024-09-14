from enum import Enum

from lang.item import Item
from typing import List

class Types(Enum):
    ASSIGN = 0,
    METHOD = 1

class Expression:
    """
    Basic expression 
    """
    def __init__(self, assigned: str, type: Types, items: List[Item], verb: str = None) -> None:
        self.lhs = assigned
        self.type = type
        self.items = items
        self.verb = verb

    def __str__(self) -> str:
        if self.type == Types.ASSIGN:
            return f'{self.type}: {self.lhs} <- {self.items}'
        else:
            return f'{self.type}: {self.lhs} <- {self.verb} {self.items}'
