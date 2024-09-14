from typing import Any, List
from bin.eppParserVisitor import eppParserVisitor as Visitor
from bin.eppParser import eppParser

import compiler.expression as expr
import compiler.symbol as symbol

from compiler.errors import error

import compiler.jasmin as jasmin

class EPPVisitor(Visitor):
    def __init__(self) -> None:
        super().__init__()
        self.symbol_table = {}

    def visitProg(self, ctx: eppParser.ProgContext):
        return self.visitChildren(ctx)

    # Asignations
    def visitAssign_initializing(self, ctx: eppParser.Assign_initializingContext):
        # Add variable to symbol table
        var_name = ctx.ID().getText()
        assign_expr = self.visit(ctx.expr_start())
        if not var_name in self.symbol_table:
            self.symbol_table[var_name] = symbol.Symbol(name=var_name, type=assign_expr.type, index=len(self.symbol_table))
        else:
            error(f'Variable {var_name} already defined')
        print(self.symbol_table)

    # Other types
    
    def visitExpr_start(self, ctx: eppParser.Expr_startContext):
        ipn = self.visit(ctx.expr())
        type, ipn = expr.get_ipn_type(ipn)
        # TODO: delete
        for line in jasmin.from_ipn(ipn):
            print(line)
        return expr.Expression(type, ipn) 
    # Expressions
    def visitExpr_addition(self, ctx: eppParser.Expr_additionContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.ADDITION]
    def visitExpr_substraction(self, ctx: eppParser.Expr_substractionContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.SUBTRACTION]
    def visitExpr_multiplication(self, ctx: eppParser.Expr_multiplicationContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.MULTIPLICATION]
    def visitExpr_division(self, ctx: eppParser.Expr_divisionContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.DIVISION]
    def visitExpr_less_than(self, ctx: eppParser.Expr_less_thanContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.LESS_THAN]
    def visitExpr_less_equals(self, ctx: eppParser.Expr_less_equalsContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.LESS_EQUALS]
    def visitExpr_more_than(self, ctx: eppParser.Expr_more_thanContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.MORE_THAN]
    def visitExpr_more_equals(self, ctx: eppParser.Expr_more_equalsContext):
        return [*self.visit(ctx.lhs), *self.visit(ctx.rhs), expr.Operator.MORE_EQUALS]

    def visitExpr_float(self, ctx: eppParser.Expr_floatContext):
        return [expr.Leaf(type=expr.DataType.FLOAT, value=float(ctx.getText())),]
    def visitExpr_integer(self, ctx: eppParser.Expr_integerContext):
        return [expr.Leaf(type=expr.DataType.INTEGER, value=int(str(ctx.NUMBER()))),]
    def visitExpr_bool(self, ctx: eppParser.Expr_boolContext):
        return [expr.Leaf(type=expr.DataType.BOOL, value=(ctx.BOOL_CONST() == 'true')),]
    def visitExpr_string(self, ctx: eppParser.Expr_stringContext):
        return [expr.Leaf(type=expr.DataType.STRING, value=str(ctx.STRING()))]

    def visitExpr_variable(self, ctx: eppParser.Expr_variableContext):
        # Check if variable is inside symbol table
        var_name = ctx.ID().getText()
        if not var_name in self.symbol_table:
            error(f'Variable {var_name} used before being declared')
        return [expr.Leaf(type=expr.LeafType.SYMBOL, value=self.symbol_table[var_name]),]

    # Aggregation
    def aggregateResult(self, aggregate: List[Any], nextResult):
        # Filter None from nextResult
        if nextResult != None:
            if aggregate != None:
                aggregate.append(nextResult)
            else:
                return [nextResult]

        return aggregate

if __name__ == "__main__":
    visitor = EPPVisitor()
