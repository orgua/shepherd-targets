"""
typer is currently a big compromise, missing features (as of v0.9:
- dict, unions as input type
- get help-text for arguments / options from docstring in fn()
- move initial argument-processing to pydantic model (and use it in typer)
    - https://pypi.org/project/clidantic/
    - would allow loading parameters from file (json, yaml), also storing it
"""
import signal
import sys
from contextlib import ExitStack

import typer

# decorator-object to add commands
app = typer.Typer()


def exit_stack() -> ExitStack:
    """offers cleaner exit and handler for entering contexts (with ... as .. :)

    :return: stack, use with .enter_context(obj)
    """
    stack = ExitStack()

    def exit_gracefully(*args):  # type: ignore
        stack.close()
        sys.exit(0)

    signal.signal(signal.SIGTERM, exit_gracefully)
    signal.signal(signal.SIGINT, exit_gracefully)
    return stack
