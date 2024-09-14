from typing import List

from lang.section import Section
from lang.item import Type as ItemTypes 

from lang.expression import Types as ExpressionTypes
from lang.keywords import implicit_utensils

def get_stats(AST: List[Section]):
    ret = {}
    # Read ingredients
    ingredients = {} 
    for section in AST:
        for timestamp in section.timestamps:
            for expr in timestamp[1]:
                # Check expression
                for item in expr.items:
                    if item.type == ItemTypes.RAW_ITEM:
                        # Check if item is already in item list
                        if not item.name in ingredients:
                            ingredients[item.name] = item.ammount
                        else:
                            ingredients[item.name] += item.ammount
    
    return ingredients

def get_implicit_utensils(AST):
    implicit = set()
    for section in AST:
        for timestamp in section.timestamps:
            for expr in timestamp[1]:
                if expr.type == ExpressionTypes.METHOD:
                    # Get implicit utensils 
                    implicit = implicit.union(implicit_utensils.get(expr.verb, []))
    return implicit

def get_total_time(AST):
    total = 0
    for section in AST:
        for timestamp in section.timestamps:
            total += timestamp[0]
    return total 

    return implicit
