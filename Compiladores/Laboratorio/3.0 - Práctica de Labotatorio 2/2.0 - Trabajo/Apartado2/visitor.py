from antlr4.CommonTokenFactory import CommonToken
from bin.RecetasParserVisitor import RecetasParserVisitor as Visitor
from bin.RecetasParser import RecetasParser

from typing import Dict, List, Any, Literal

from lang.section import Section
from lang.units import Unit, UnitTypes, Temp
from lang.expression import Expression, Types as ExpressionTypes
import lang.keywords as keywords 
from lang.item import Item, Type as ItemTypes

from error import error

class RecipeVisitor(Visitor):
    """

    """
    def __init__(self) -> None:
        super().__init__()

        # Variables
        self.symbol_table: Dict[str, keywords.Symbol] = {} 
        self.parsed: Dict[str, Section] = {}
        self.current_section: Section = None

    def run(self, tree):
        sections = self.visitChildren(tree)

        return (self.symbol_table, sections)

    def visitSection(self, ctx: RecetasParser.SectionContext):
        # Create section
        name = self.visit(ctx.section_header())
        section = Section(name)
        self.current_section = section 
        self.visit(ctx.section_body())
        return section

    def visitSection_header(self, ctx: RecetasParser.Section_headerContext):
        token: CommonToken = ctx.name_
        return str(token.text)
    # Sections
    def visitTime_section(self, ctx: RecetasParser.Time_sectionContext):
        delta = self.visitAmmount(ctx.delta_)
        # Check if it's time
        if not delta.type == UnitTypes.TIME:
            error(f'Unit {delta} is not time', ctx)
        # Create time section
        self.current_section.timestamps.append((delta.ammount, []))

    def visitExpression(self, ctx: RecetasParser.ExpressionContext):
        # Create expression
        asignee = self.visit(ctx.assignment_)
        expr = self.visit(ctx.rhs_)
        expression = Expression(asignee, expr['type'], expr['items'], expr['verb'] if 'verb' in expr else None)
        # Append expressino
        self.current_section.timestamps[-1][1].append(expression)

    def visitDetails(self, ctx: RecetasParser.DetailsContext):
        items = [self.visit(i) for i in ctx.item()]
        if ctx.utensil_ != None:
            self.visit(ctx.utensil_)
        if ctx.temp_ != None:
            self.visit(ctx.temp_)
        return items 

    def visitRhs_assign(self, ctx: RecetasParser.Rhs_assignContext):
        return {
            'type': ExpressionTypes.ASSIGN,
            'items': self.visit(ctx.details_)
        }

    def visitRhs_expression(self, ctx: RecetasParser.Rhs_expressionContext):
        # Check verb
        verb = self.visit(ctx.id_)
        if not verb in keywords.verbs:
            error(f'Verb {verb} is not in the list of possible actions', ctx)

        return {
            'type': ExpressionTypes.METHOD,
            'verb': verb,
            'items': self.visit(ctx.details_)
        }

    # Items
    def visitItem_Raw(self, ctx: RecetasParser.Item_RawContext):
        ammount: Unit = self.visit(ctx.ammount_)
        name = self.visit(ctx.name_)
        return Item(ItemTypes.RAW_ITEM, name, ammount)

    def visitItem_UnitRaw(self, ctx: RecetasParser.Item_UnitRawContext):
        name = self.visit(ctx.name_)
        return Item(ItemTypes.RAW_ITEM, name)

    def visitItem_AmmountVariable(self, ctx: RecetasParser.Item_AmmountVariableContext):
        ammount: Unit = self.visit(ctx.ammount_)
        name = self.visit(ctx.name_)
        # Check if already defined
        if not name in self.symbol_table:
            error(f'using {name} as variable (which is not defined)', ctx)
        return Item(ItemTypes.VARIABLE, name, ammount)

    def visitItem_UnitVariable(self, ctx: RecetasParser.Item_UnitVariableContext):
        name = self.visit(ctx.name_)
        if not name in self.symbol_table:
            error(f'using {name} as variable (which is not defined)', ctx)
        return Item(ItemTypes.VARIABLE, name)

    # Utensils
    def visitUtensil(self, ctx: RecetasParser.UtensilContext):
        name = ctx.TEXT().getText()
        self.symbol_table[name] = keywords.Symbol.UTENSIL
    # Symbols
    def visitAssignment(self, ctx: RecetasParser.AssignmentContext):
        name = self.visit(ctx.asignee_)
        # Add to variables
        self.symbol_table[name] = keywords.Symbol.VARIABLE
        return self.visit(ctx.asignee_)

    def visitId(self, ctx: RecetasParser.IdContext):
        return ctx.ID().getText()


    # Collapsable expressions
    def visitAmmount(self, ctx: RecetasParser.AmmountContext):
        quantity = float(ctx.quantity_.text)
        unit = ctx.unit_.text if ctx.unit_ else ''
        return Unit(quantity, unit) 

    def visitText(self, ctx: RecetasParser.TextContext):
        return ctx.getText()

    # TODO: add temperature reading section to this visitor
    def visitTemperature_numeric(self, ctx: RecetasParser.Temperature_numericContext):
        ammount = float(str(ctx.NUMBER()))
        unit = str(ctx.ID())
        return Temp(ammount, unit)

    def visitTemperature_id(self, ctx: RecetasParser.Temperature_idContext):
        ammount = str(ctx.ID())
        return Temp(ammount)
    
    # Aggregation
    def aggregateResult(self, aggregate: List[Any], nextResult):
        # Filter None from nextResult
        if nextResult != None:
            if aggregate != None:
                aggregate.append(nextResult)
            else:
                return [nextResult]

        return aggregate
