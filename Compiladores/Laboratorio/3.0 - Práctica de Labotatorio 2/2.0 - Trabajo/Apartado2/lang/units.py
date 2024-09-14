from enum import Enum
from error import error

class UnitTypes(Enum):
    MASS = 0
    VOLUME = 1
    TIME = 2
    ERROR = 3,
    UNIT = 4,
    TEMPERATURE = 5

SCALES = {
    'K': 1000,
    'd': 0.1,
    'c': 0.01,
    'm': 0.001
}

TIME_SCALES = {
    's': 1,
    'm': 60,
    'h': 3600
}

UNITS = {
    'g': UnitTypes.MASS,
    'l': UnitTypes.VOLUME,
    's': UnitTypes.TIME,
    'm': UnitTypes.TIME,
    'h': UnitTypes.TIME,
    '' : UnitTypes.UNIT
}

TEMP_UNIT = 'C' # No imperial nonsense here
class TempTypes(Enum):
    ABSOLUTE = 0,
    RELATIVE = 1

RELATIVE_TEMP_UNITS = {
    'bajo',
    'medio',
    'alto'
}

class Temp:
    def __init__(self, ammount: float, unit: str = None) -> None:
        if unit == None: # Relative units
            if not ammount in RELATIVE_TEMP_UNITS:
                error(f'{ammount} is not a possible relative temperature unit')
            self.ammount = ammount
            self.type = TempTypes.RELATIVE
        else:
            if not unit == TEMP_UNIT:
                error(f'{unit} is not a temperature unit')
            self.ammount = ammount
            self.type = TempTypes.ABSOLUTE


class Unit(object):
    """
    Standard unit class
    """
    def __init__(self, ammount: float = None, unit: str = None) -> None:
        if ammount == None:
            return
        
        if not unit == '':
            self.ammount = ammount
            self.type = UNITS.get(unit[-1], UnitTypes.ERROR)
        
            # Check for time to apply scaling
            if self.type == UnitTypes.TIME:
                self.ammount *= TIME_SCALES.get(unit, 1)

            if not len(unit) == 1:
                # Scale proportionaly
                self.ammount *= SCALES.get(unit[:-1], 1)
        else:
            self.type = UnitTypes.UNIT
            self.ammount = int(ammount)

    def __str__(self) -> str:
        type_unit = list(UNITS.keys())[list(UNITS.values()).index(self.type)]
        return f'{self.ammount}{type_unit}'

    def __add__(self, o):
        # Check types
        if not self.type == o.type:
            raise Exception(f'Can\'t add units of different types: {self.type} {o.type}')
        new = self.__class__()
        new.ammount = self.ammount + o.ammount
        new.type = self.type
        return new

def get_time(ammount: float, unit: str):
    pass
        
# TODO: add possiblity to pass multiple time values in time_section
