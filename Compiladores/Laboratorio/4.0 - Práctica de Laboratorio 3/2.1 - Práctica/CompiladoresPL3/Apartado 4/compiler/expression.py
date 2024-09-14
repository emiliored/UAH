from enum import Enum
from dataclasses import dataclass
from typing import Union, List, Dict, Any

class DataType(Enum):
    INTEGER         = 0,
    FLOAT           = 1,
    BOOLEAN         = 2,
    STRING          = 3,
    UNDEFINED       = 4

class LeafType(Enum):
    SYMBOL          = 0,
    CONSTANT_INT    = 1,
    CONSTANT_FLOAT  = 2,
    CONSTANT_STR    = 3,
    CONSTANT_BOOL   = 4

class Operator(Enum):
    ADDITION        = 0,
    SUBTRACTION     = 1,
    MULTIPLICATION  = 2,
    DIVISION        = 3,
    LESS_THAN       = 4,
    MORE_THAN       = 5,
    LESS_EQUALS     = 6,
    MORE_EQUALS     = 7,
    EQUALS          = 8


@dataclass
class Operation:
    lhs: DataType
    rhs: DataType
    ret: DataType
    inter: str

    def __eq__(self, obj):
        return (obj.lhs == self.lhs) and (obj.rhs == self.rhs)

AVAILABLE_CASTS: Dict[DataType, Dict[DataType, str]] = {
    DataType.INTEGER: {
        DataType.INTEGER: "",
        DataType.FLOAT: """
new java/lang/Integer
dup
{load}
invokespecial java/lang/Integer/<init>(I)V
invokevirtual java/lang/Integer/floatValue()F""",
        DataType.STRING: ""
    },
    DataType.FLOAT: {
        DataType.FLOAT: "",
        DataType.INTEGER: """
new java/lang/Float
dup
{load}
invokespecial java/lang/Float/<init>(I)V
invokevirtual java/lang/Float/intValue()V
""",
        DataType.STRING: """
{load}
invokestatic java/lang/Float/toString(F)Ljava/lang/String;"""
    },
    DataType.BOOLEAN: {
        DataType.BOOLEAN: "",
        DataType.INTEGER: "",
        DataType.STRING: ""
    },
    DataType.STRING: {
        DataType.STRING: ""
    }
}

operation_label_index = 0
AVAILABLE_OPERATIONS: Dict[Operator, List[Operation]] = {
    Operator.ADDITION: [
        Operation(DataType.INTEGER, DataType.INTEGER, DataType.INTEGER, 'iadd'),
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.FLOAT, 'fadd'),
        Operation(DataType.STRING, DataType.STRING, DataType.STRING, """
new java/lang/StringBuilder
dup
invokespecial java/lang/StringBuilder/<init>()V
{lhs}
invokevirtual java/lang/StringBuilder/append(Ljava/lang/String;)Ljava/lang/StringBuilder;
{rhs}
invokevirtual java/lang/StringBuilder/append(Ljava/lang/String;)Ljava/lang/StringBuilder;
invokevirtual java/lang/StringBuilder/toString()Ljava/lang/String;""")
    ],
    Operator.SUBTRACTION: [
        Operation(DataType.INTEGER, DataType.INTEGER, DataType.INTEGER, 'isub'),
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.FLOAT, 'fsub'),
    ],
    Operator.MULTIPLICATION: [
        Operation(DataType.INTEGER, DataType.INTEGER, DataType.INTEGER, 'imul'),
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.FLOAT, 'fmul'),
    ],
    Operator.DIVISION: [
        Operation(DataType.INTEGER, DataType.INTEGER, DataType.INTEGER, 'idiv'),
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.FLOAT, 'fdiv')
    ],
    Operator.LESS_THAN: [
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.BOOLEAN, """
"""),
        Operation(DataType.INTEGER, DataType.INTEGER, DataType.BOOLEAN, """
{rhs}
{lhs}
if_icmplt {L1}
ldc 0
goto {L2}
{L1}:
ldc 1
{L2}:""")
    ],
    # There are no float to float comparisons because I lack the time to implement them
    Operator.MORE_THAN: [
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.BOOLEAN, '')
    ],
    Operator.LESS_EQUALS: [
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.BOOLEAN, '')
    ],
    Operator.MORE_EQUALS: [
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.BOOLEAN, '')
    ],
    Operator.EQUALS: [
        Operation(DataType.INTEGER, DataType.INTEGER, DataType.BOOLEAN, ''),
        Operation(DataType.FLOAT, DataType.FLOAT, DataType.BOOLEAN, ''),
        Operation(DataType.BOOLEAN, DataType.BOOLEAN, DataType.BOOLEAN, '')
    ]
}

class RetError(Exception):
    pass

def get_expr_ret_type(lhs: DataType, op: Operator, rhs: DataType):
    available = AVAILABLE_OPERATIONS[op]
    try:
        return available[available.index(Operation(lhs, rhs, DataType.UNDEFINED, ''))]
    except ValueError as e:
        try:
            return available[available.index(Operation(rhs, lhs, DataType.UNDEFINED, ''))]
        except ValueError as e:
            pass
        raise RetError(f'\033[31mOperation {op} between {lhs} and {rhs} does not exist\033[0m')

@dataclass
class CastInformation:
    from_type: DataType
    to_type: DataType
    inter_action: str

def get_ipn_type(ipn):
    print('ipn')
    tmp_ipn = [*ipn]
    tmp_ipn.reverse()
    casted_ipn = []

    stack = []
    while len(tmp_ipn) != 0:
        last_type = tmp_ipn.pop()
        if isinstance(last_type, Operator):
            lhs = stack.pop()
            rhs = stack.pop()
            # Check if expression is doable trying all castings until one works
            type = DataType.UNDEFINED
            for lhs_cast in AVAILABLE_CASTS[lhs]:
                for rhs_cast in AVAILABLE_CASTS[rhs]:
                    # Try expression
                    try:
                        operation = get_expr_ret_type(lhs_cast, last_type, rhs_cast)
                        print('iteration')
                        # Add castings to ipn 
                        if not lhs_cast == lhs:
                            casted_ipn.append(CastInformation(lhs, lhs_cast, AVAILABLE_CASTS[lhs][lhs_cast]))
                            print(f'Casting lhs to: {lhs_cast}')
                            if not rhs_cast == rhs:
                                print(f'Casting rhs to: {rhs_cast}')
                                casted_ipn.insert(-2, CastInformation(rhs, rhs_cast, AVAILABLE_CASTS[rhs][rhs_cast]))
                        elif not rhs_cast == rhs:
                            casted_ipn.insert(-1, CastInformation(rhs, rhs_cast, AVAILABLE_CASTS[rhs][rhs_cast]))
                            print(f'Casting rhs to: {rhs_cast}')
                        break
                    except RetError as e:
                        pass
                else:
                    continue
                break
            

            if operation.ret == DataType.UNDEFINED:
               raise Exception(f'\033[31mOperation {last_type} with operands of type: {lhs} and {rhs} does not exit\033[0m')

            stack.append(operation.ret)
            casted_ipn.append(operation)
        else:
            if last_type.type == LeafType.SYMBOL:
                stack.append(last_type.value.type)
            else:
                stack.append(last_type.type)

            casted_ipn.append(last_type)


    # Lenght has to be one
    ret_type = DataType.UNDEFINED
    if isinstance(stack[0], Leaf):
        ret_type = stack[0].type
    else:
        ret_type = stack[0]

    print(f'\033[33m{casted_ipn}\033[0m')
    return (ret_type, casted_ipn)

@dataclass
class Leaf:
    type: LeafType 
    value: Union[Operator, float, int, str]

@dataclass
class Expression:
    type: DataType
    ipn: List[Any]

if __name__ == "__main__":
    op1 = Operation(DataType.INTEGER, DataType.INTEGER)
