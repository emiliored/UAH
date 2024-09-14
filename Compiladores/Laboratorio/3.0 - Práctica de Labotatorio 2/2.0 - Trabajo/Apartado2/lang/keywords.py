from enum import Enum

class IDTypes(Enum):
    """
    All identifier types
    """
    VERB = 0,
    SYMBOL = 1

class Symbol(Enum):
    """
    Variable types 
    """
    VARIABLE = 0,
    UTENSIL = 1,
    PLACE = 2
    
verbs = [
    'cortar',
    'limpiar',
    'lavar',
    'licuar',
    'calentar'
]

implicit_utensils = {
    'cortar': ['cuchillo', 'tabla'],
    'licuar': ['licuadora']
}


