import compiler.expression as expr
import compiler.symbol as symbol

MNEMONICS = {
    expr.DataType.INTEGER: 'i',
    expr.DataType.FLOAT: 'f',
    expr.DataType.BOOLEAN: 'i',
    expr.DataType.STRING: 'a',
}

DESCRIPTORS = {
    expr.DataType.INTEGER: 'I',
    expr.DataType.FLOAT: 'F',
    expr.DataType.BOOLEAN: 'Z',
    expr.DataType.STRING: 'L'
}

# Unique label counter 
ulc = 0

from string import Formatter
def from_ipn(ipn):
    global ulc
    ret_code = [] 
    stack = []
    for elem in ipn:
        if isinstance(elem, expr.CastInformation):
            ret_code.append(elem.inter_action.format(load=ret_code.pop()))
        elif isinstance(elem, expr.Leaf):
            # Check leaf type
            if elem.type == expr.LeafType.SYMBOL:
                ret_code.append(f'{MNEMONICS[elem.value.type]}load_{elem.value.index}')
                pass
            else: # Load as constant
                if elem.type == expr.DataType.STRING:
                    ret_code.append(f'ldc "{elem.value}"')
                else:
                    ret_code.append(f'ldc {elem.value}')
        elif isinstance(elem, expr.Operation):
            # Check if operation has lhs and rhs operands
            operation_implementation = elem.inter
            if len([tup[1] for tup in Formatter().parse(operation_implementation) if tup[1] is not None]) != 0:
                # Send with arguments
                rhs = ret_code.pop()
                lhs = ret_code.pop()
                ret_code.append(operation_implementation.format(rhs=rhs, lhs=lhs, L1=f'unique_l{ulc}', L2=f'unique_l{ulc + 1}', L3=f'unique_l{ulc + 2}'))
                ulc += 3
            else: 
                # Send without arguments
                ret_code.append(operation_implementation)

    return ret_code
