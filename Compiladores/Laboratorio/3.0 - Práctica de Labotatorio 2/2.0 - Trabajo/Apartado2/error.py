from antlr4.error.DiagnosticErrorListener import ErrorListener

class RecipesErrorManager(ErrorListener):
    def __init__(self) -> None:
        super().__init__()

    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        return super().syntaxError(recognizer, offendingSymbol, line, column, msg, e)

def error(msg: str, ctx = None):
    if ctx != None:
        print(f'\033[31m{msg}\033[0m\n\t{ctx.getText()}')
    else:
        print(f'\033[31m{msg}\033[0m')

    exit(1)
