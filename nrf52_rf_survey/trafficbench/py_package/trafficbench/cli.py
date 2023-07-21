from pathlib import Path
from typing import Union, Optional, List

import typer
from pydantic import BaseModel

from .cli_proto import app

# CONFIG, TODO: CLI
duration_s = 60
baud_rate = 230400
log_path = Path(__file__).parent / "traffic.log"

#app = typer.Typer()

@app.command()
def hello(name: str):
    print(f"Hello {name}")




class SerialArgs(BaseModel):
    file_path: Path
    serial_ports: Union[None, str, list] = None
    duration_s: int = 600
    baud_rate: int = 230_400


#app.add_typer(sapp, name="receive")
#receive_serial = app.command(receive_serial.__name__)


if __name__ == "__main__":
    app()

