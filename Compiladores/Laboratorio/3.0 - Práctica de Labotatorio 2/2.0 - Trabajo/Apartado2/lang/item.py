from enum import Enum
from lang.units import Unit, UnitTypes

class Type(Enum):
    RAW_ITEM = 0,
    VARIABLE = 1

class Item:
    """

    """
    def __init__(self, type: Type, name: str, ammount: Unit = None) -> None:
        if ammount == None:
            ammount = Unit(1, '')

        self.type = type
        self.ammount = ammount
        self.name = name
        pass

    def __str__(self) -> str:
        return f'{self.name}: {self.ammount} ({self.type})'
