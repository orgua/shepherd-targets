"""Assemble a schedule for measuring link-quality in the shepherd-testbed."""

from pathlib import Path

# CONFIG

node_count: int = 20
path_local = Path(__file__).parent
path_schedule = path_local.parent / "trafficbench/target/nrf52840/project_ses/schedule.inc"

# Schedule-builder

with path_schedule.open("w") as schedule:
    with (path_local / "schedule_head.inc").open() as sh:
        schedule.write(sh.read())

    with (path_local / "schedule_block.inc").open() as sb:
        block = sb.read()

    for node in range(node_count):
        block_node = block.replace("SHP_ID_PLACEHOLDER", str(node))
        schedule.write(block_node)

    with (path_local / "schedule_footer.inc").open() as sf:
        schedule.write(sf.read())
