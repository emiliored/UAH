from typing import List

from lang.section import Section

from lang.item import Type as ItemTypes

from error import error

def sections(AST):
    for section in AST:
        yield section

def time_sections(AST):
    for section in sections(AST):
        for time_section in section.timestamps:
            yield time_section 

def expressions(AST):
    for time_section in time_sections(AST):
        for expression in time_section[1]:
            yield expression

def items(AST):
    for expression in expressions(AST):
        for item in expression.items:
            yield item

def check(AST: List[Section]):
    # Check that all of the same ingredients have the same units
    check_item_types(AST)

def check_item_types(AST: List[Section]):
    item_types = {}
    for item in items(AST):
        if item.type == ItemTypes.RAW_ITEM:
            # Check if already in dictionary
            if not item.name in item_types:
                item_types[item.name] = item.ammount.type

            if item.ammount.type != item_types[item.name]:
                error(f'Ingredient {item.name} does not have the same type as defined\n\t{item.ammount.type} when {item_types[item.name]} as defined')

