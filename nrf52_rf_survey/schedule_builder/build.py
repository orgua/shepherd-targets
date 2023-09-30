"""
this script assembles a schedule for measuring link-quality in the shepherd-testbed

"""
from pathlib import Path

# CONFIG

node_count: int = 12
path_local = Path(__file__).parent
path_schedule = (
    path_local.parent / "trafficbench/target/nrf52840/project_ses/schedule.inc"
)

# Schedule-builder

with open(path_schedule, "w") as schedule:
    with open(path_local / "schedule_head.inc") as sh:
        schedule.write(sh.read())

    with open(path_local / "schedule_block.inc") as sb:
        block = sb.read()

    for node in range(node_count):
        block_node = block.replace("SHP_ID_PLACEHOLDER", str(node))
        schedule.write(block_node)

    with open(path_local / "schedule_footer.inc") as sf:
        schedule.write(sf.read())
