def error(msg: str, ctx = None):
    if ctx != None:
        print(f'\033[31m{msg}\033[0m\n\t{ctx.getText()}')
    else:
        print(f'\033[31m{msg}\033[0m')

    exit(1)
