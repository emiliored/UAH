from dataclasses import dataclass
from enum import Enum
import compiler.expression as expr 
from compiler.errors import error

from typing import List, Any


@dataclass
class Symbol:
    name: str
    type: expr.DataType
    index: int

