# TrafficBench

TrafficBench is a tool suite for the experimental exploration of concurrent packet transmissions 
and their consequences (physical layer effects) in low-power wireless networks. It integrates 
[RSSISpy](https://gitlab.com/nes-lab/rssispy), a software module that enables continuous RSSI 
measurements with bit-level time resolution, with a scheduling framework that provides a specialized, 
easy-to-use language to implement communication test patterns. The latter offloads the user from 
demanding implementation tasks like time-critical interrupt service routines, network bootstrapping, 
synchronization, and efficient data logging. Thus, TrafficBench greatly simplifies the experimentation 
with different traffic patterns and enables an in-depth inspection of the resulting effects.

TrafficBench consist of two major parts:

* A firmware that runs on the network nodes. Currently, TrafficBench supports Nordic 
  Semiconductor [nRF52840](https://www.nordicsemi.com/Products/nRF52840) devices in
  Bluetooth Low Energy (BLE) mode.

* Python scripts that can be used to extract, analyze, and visualize the recorded data.

To learn more about TrafficBench, please read on. You can also have a look at our
[EWSN'22 demo abstract](https://nes-lab.org/wordpress/wp-content/uploads/2022/08/herrmann22trafficbench.pdf)
to gain an impression.


## Installation

In the following we focus on Linux. However, the main host tools are written in Python, 
and we use the Python-based [Xonsh](https://xon.sh) shell for helper scripts, so installing
TrafficBench on other platforms should not be a big deal. On Windows, you should make
sure that `*.py` files are started with Python and `*.xsh` files with Xonsh, respectively.
You can also use the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/about).

Installation steps:

1. Install [SEGGER Embedded Studio for ARM](https://www.segger.com/downloads/embedded-studio/#ESforARM) (SES).[^fn-ses] 
   In our tests we have used SES version V6.34.
   You do not need the nRF Connect SDK.
   Depending on your test environment, you may need the 
   [nRF Command Line Tools](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools)
   to program the target devices.

2. Setup a [Python 3](https://www.python.org/) environment (we have used Python 3.8 for our tests).
   We recommend to use a Python virtual environment, which can be 
   created with `python3 -m venv <name_of_virtualenv>`
   and activated with `source <path_to_virtualenv>/bin/activate`.

3. Create a project directory and clone this repository into it: 
   `git clone https://gitlab.com/nes-lab/trafficbench.git`.

4. Go to subfolder [`host`](host/) and install all required Python modules: 
   `pip install -r requirements.txt`.

After these steps, you should be able to start SES (start menu), Xonsh (`xonsh`), 
ViTables (`vitables`), and Glue (`glue.xsh` in the [`host`](host/) subfolder).

[^fn-ses]: SES is free for Nordic customers,
  see [here](https://www.segger.com/news/segger-embedded-studio-ide-now-free-for-nordic-sdk-users/) 
  and [here](https://www.nordicsemi.com/Products/Development-tools/Segger-Embedded-Studio).

### Problems and Troubleshooting

We found that currently (Oct 22) some software components cause **trouble with Python > 3.8**.
Specifically,

* Starting Glue fails with error message `TypeError: setValue(self, int): argument 1 has unexpected type 'float'`.

* Starting ViTables fails with error message `AttributeError: module 'collections' has no attribute 'Iterable'`.

Both problems are known and fixed in the development versions of Glue and ViTables
(see https://github.com/glue-viz/glue/pull/2266 and https://github.com/uvemas/ViTables/pull/109 for details),
so hopefully there will be updates in the future. For the moment we recommend to **use Python 3.8**.
(Alternatively, you can incorporate the fixes manually into the installed software versions.
Do not use Glue > 1.2.4 because this causes other issues (see [requirements.txt](host/requirements.txt) for details)).


## Usage

### Firmware

The task of the TrafficBench firmware is to implement a user-defined communication schedule 
and to log all related data (events, transmitted and received packets, RSSI data streams, etc.) 
to the UART terminal. Here, "implement" means to do everything that is needed to realize the
schedule, i.e., network wake-up, clock and state synchronization, and schedule program execution.

The firmware is ready to use in the sense that providing the schedule of interest (formulated 
in the specialized language, see [below](#communication-scheduling-and-checkpoints)) is enough 
to be able to compile and run the firmware with the specific schedule.
To demonstrate the process, the source code comes with a tutorial schedule that can be used 
to test the tool chain and run a simple test on a few Nordic 
[nRF52840 DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK)
development boards forming a small wireless network (using three boards is perfect, but even
a single board is enough to test the tool chain).
To do so, use the following steps:

1. Start SES and open the project [`target/nrf52840/project_ses/TrafficBench.emProject`](
   target/nrf52840/project_ses/TrafficBench.emProject).

2. Make sure to select "Release" as the active configuration (do not use "Release_FlockLab").
   Compile the project and program the executable into all boards.

3. For each board: Open a terminal (UART settings 230400,8,N,1, hardware flow control enabled). 
   Press the reset button on the board and test if you see some output at the terminal.

   In case of problems, temporarily disable hardware flow control by setting 
   `GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE` to 0 in [`config.h`](target/nrf52840/project_ses/config.h) 
   and try again. If hardware flow control is the reason for problems, then re-enable it and find out 
   how to configure the terminal correctly (e.g. with PuTTY you can use -sercfg "230400,8,n,1,D"). 
   *Do not run the firmware without flow control on nRF52840 DK boards* because this can lead to 
   awkward data losses.

4. You will be asked for a node ID at each terminal. Provide a unique ID for each board starting from 1, 2, ...

   The ID is stored in the device's UICR area, so it is kept persistent and not asked for again 
   (also after re-programming). If you want to set a new ID, keep Button 1 pressed during boot-up,
   which enforces the ID prompt. See [`main.c`](target/nrf52840/main.c) for the details.

5. When everything is set up, press Button 1 at node 1. This starts communication and generates 
   output at all terminals.

To evaluate the data with the TrafficBench host tools, you need to log the UART output of each 
node to one or more files (e.g. one file per node). We do not provide any scripts for this task 
because the right way to do it depends on your setup and the used terminal program (e.g. with 
PuTTY you can use the command line option `-log <filename>`).
Public testbeds like [FlockLab](https://www.flocklab.ethz.ch) do it automatically (if UART
logging is turned on in the test configuration).

### Host Tools

After you have collected the UART log file(s), you can use the TrafficBench host tools to
extract the relevant data, analyze it, and visualize it using [Glue](https://glueviz.org).
The following tools are used for these steps:

* [`filter_logs.py`](host/filter_logs.py) extracts the relevant data from the log file(s). 
  The data is encapsulated in so-called *TRX records* (TX/RX records), which appear in the 
  log file(s) as fragmented BASE64 strings surrounded by special control characters.
  `filter_logs.py` extracts these records and stores them in a new file (`*-trx_filter.dat`) 
  with one record per line (still BASE64 encoded).

* [`trx_dump.py`](host/trx_dump.py) reads the BASE64 encoded TRX records and exports them
  to a PyTables HDF5 file (`*-trx_data.h5`). This file plays the role of a database for all
  following steps. In addition to this, `trx_dump.py` can dump all records to a human-readable 
  text file (`*-trx_dump.txt`), which can be used to inspect the recorded data.

* [`trx_analyze.py`](host/trx_analyze.py) analyzes the set of captured TRX records and sets
  the actions of all nodes in relation to each other. It determines which records belong to
  the same TRX operation in the schedule and combines them into a *transaction*. For each
  transaction, it estimates from which transmitter each received packet stems. The script
  estimates SNR and SINR values and creates user-configurable markers, which can be used
  to easily find transactions with interesting properties in the recorded data.
  As a side effect, `trx_analyze.py` prints a lot of human-readable diagnostic data.

* [`glue_config.py`](host/glue_config.py) adds specific support for TrafficBench data to 
  [Glue](https://glueviz.org), a GUI program for linked-data exploration. We cannot go
  into the details of Glue here, for more information see <https://glueviz.org>. The script 
  adds a specific loader (to be able to load the data from `*-trx_data.h5` into Glue), 
  an auto-linker (to automatically generate links between the data tables and enable the 
  exciting features of Glue), and a special viewer that shows RSSI traces and bitstreams 
  side by side (with synchronized zoom).

In a typical workflow these tools are used repeatedly in the same manner, so we provide a
helper script `extract_data.xsh` that automates the common steps. With your UART log file(s) 
named `terminal.log` or `terminal-<node_id>.log` you can use it as follows:

1. Copy your log files to the subfolder [`host/terminal/`](host/terminal/).

2. Enter the subfolder and call [`extract_data.xsh`](host/terminal/extract_data.xsh). 

   This is a Xonsh script. The Xonsh shell is installed automatically as a Python 
   requirement (see [above](#installation)). In case of problems, make sure 
   that the right Python virtual environment is active.

3. When asked for, enter one or multiple file name patterns that match your log file(s).
   
   The script performs all steps to extract and analyze the data. Have a look at the
   generated log files after processing has finished.

4. Start Glue by calling [`glue.xsh`](host/glue.xsh) in the [`host`](host/) subfolder.
   Using `glue.xsh` ensures that Glue starts with the TrafficBench support included.

   If you are unsure whether you started Glue the right way, press "Import Data" in Glue and
   check if the list of file types in the file dialog contains the entry "TrafficBench TRX loader".

5. Import the generated HDF5 files (`terminal-trx_data.h5`), accept the Auto-Linker
   suggestions, and play around. For example, create a TrafficBench Rx Viewer (`Ctrl-N`, 
   select list entry) and drag-and-drop rssi_... and bitstream_... data onto the 
   viewer window.

After getting familiar with the host tools, it is a good idea to look into the scripts
and understand what they do internally. In general, they should be seen as a starting 
ground for own adaptations and extensions, as your experiments may require to analyze
different things or to generate different kinds of plots. So, yes, there is a "workbench" 
connotation in Traffic*Bench*... :wink:

Hint: The installation of `requirements.txt` includes [ViTables](https://vitables.org), 
a GUI for browsing PyTables files (use `vitables` to start it). It can be used to inspect 
`*-trx_data.h5` files at the plain level, e.g. to understand the internal file structure
or as a helper to find bugs in the Python scripts.

### Adapting TrafficBench to Specific Testbeds

In general, TrafficBench is generic regarding the test environment.
However, some settings and concepts can be specific for a concrete testbed and may
need adaptations. In case, there are three main points to consider:

* GPIO pin mappings. 
  They are assigned in the generic platform interface ([`gpi/...`](target/gpi/))
  and depend on `GPI_ARCH_PLATFORM`, which is set in [`config.h`](target/nrf52840/project_ses/config.h).
  If the target platform is not supported directly but differs only in the pin assignments, 
  it is relatively easy to fork an existing platform and adapt `platform.c`.
  Besides this, [`radio.c`](target/nrf52840/radio.c) contains the macro `DEBUG_GPIO`,
  which allows to optionally route some internal signals to GPIO pins. Check the
  assignments in case `DEBUG_GPIO` is enabled.

* UART settings.
  The parameters can be changed in [`config.h`](target/nrf52840/project_ses/config.h).
  Check `GPI_STDOUT_UART_BAUDRATE` and `GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE`
  and make sure that the used settings are supported at the other end of the connection.
  Attention: TrafficBench can push UART activity to the limits, so use settings that 
  work reliable and not only under mild conditions.

* Node ID assignment.
  Each node needs a unique ID that must be provided to the firmware.
  The best way to do so is testbed-specific, and different concepts exist.
  The TrafficBench firmware reads the assigned ID in [`main.c`](target/nrf52840/main.c).
  Simply adapt this code to your needs.
  For optional node ID mapping, see [below](#node-id-mapping).

#### FlockLab

Support for the [FlockLab](https://www.flocklab.ethz.ch) testbed is already implemented.
To run the tutorial schedule on FlockLab instead of nRF52840 DK nodes:

1. Open the firmware project and select "Release_FlockLab" as the active configuration.

2. Build the project. 

   After compilation of the `TrafficBench.elf` file, the post-build script 
   [`flocklab_postprocess.sh`](target/nrf52840/project_ses/flocklab_postprocess.sh)
   starts automatically and generates `TrafficBench-flocklab.xml` in addition to the ELF file.

3. Log in to your FlockLab account and upload `TrafficBench-flocklab.xml` to start a test run.

4. When finished, download the results file to the subfolder [`host/flocklab/`](host/flocklab/) 
   and extract it.

5. Call `extract_data.xsh <test_run_number>` (in `host/flocklab/`) to analyze the UART output 
   collected in `<test_run_number>/serial.csv`.

To use your own schedules on FlockLab:

* Check [`config_flocklab.h`](target/nrf52840/project_ses/config_flocklab.h).
  Provide a test name and description and have a look at the other settings.

* Have a look at the implementation of the `NODE()` macro in [`schedule.inc`](target/nrf52840/project_ses/schedule.inc)
  to understand how node IDs are mapped from the schedule to the FlockLab observer IDs 
  (see also [Node ID Mapping](#node-id-mapping)).


## Important Concepts

### Communication Scheduling and Checkpoints

Schedules are provided in the file [`schedule.inc`](target/nrf52840/project_ses/schedule.inc).
They are formulated as sequential programs. Currently, the instruction set contains 
three main operations: `SLEEP`, `BRANCH`, and `TRX` (transmit/receive). 
`TRX` instructions are written as blocks, where the body of each block defines the 
corresponding packet’s content.
The provided tutorial schedule demonstrates the main instructions.
There is also a template file [`schedule_template.inc`](target/nrf52840/schedule_template.inc),
which describes all commands with all possible parameters.

During the firmware build process, the schedule program is translated to an internal 
representation and then stored in each node. Behind the scenes, the translation step 
is performed by the standard GNU assembler, i.e., the schedule indeed is an assembly 
program that emits machine code for an internal virtual machine (VM). The schedule 
instructions represent machine instructions of this VM. They are realized as macros 
that hide all arduous details from the user. As a side effect, this concept makes it 
possible to use other assembly language features like labels, macros, and constants.

After power-up, a user-defined root node (see `ROOT_NODE_ID` in [`config.h`](target/nrf52840/project_ses/config.h)) 
starts executing the schedule and transmitting packets when requested. Other nodes 
enter continuous listen mode until they receive a packet that includes a *checkpoint*. 
The latter contains state information (e.g., timestamps, VM program counter) that 
allows the receiver to synchronize its clock and its VM and, consequently, to join 
schedule execution. So, over time all nodes wake up, and finally all nodes have 
synchronized clocks and VMs, i.e., they perform the same operations at the same time.

To make this work, it is necessary that nodes include a checkpoint in their transmitted
packets once in a while (note that clock synchronization is a continuous process, so 
the exchange of checkpoints must continue and not stop after initial synchronization).
In favor of maximum flexibility, TrafficBench doesn't do this implicitly. Instead, 
it lets the user decide in which packets and at which positions checkpoints are to 
be inserted by using the special `TRX_data_checkpoint` content specifier. Wherever 
this specifier appears in a packet definition (aka. `TRX` block), it gets replaced 
by a checkpoint of constant size `TRX_CHECKPOINT_SIZE` (12 bytes at the moment) that 
contains the node's current internal state.

While this mechanism allows maximum flexibility (e.g. to align checkpoints with the
payload area of an emulated higher-layer protocol), it introduces a pitfall: 
During initial synchronization (i.e. without synchronized schedule execution),
how can a receiving node know if and in case where there is a checkpoint in the packet?
Since the node has no internal information about the corresponding `TRX` statement at 
this point, the only chance is to mark the presence and position of a checkpoint in 
the packet itself, at some predefined fixed position.
This is realized by a one-byte marker placed with `TRX_data_checkpoint_marker` at 
`TRX_CHECKPOINT_MARKER_POS` in each packet. `TRX_CHECKPOINT_MARKER_POS` is specified
by the user in [`schedule.inc`](target/nrf52840/project_ses/schedule.inc) and determines 
the position of the marker relative to the start or end of each packet's payload area 
(the latter can be beneficial for packets with variable length).[^fn-marker]

[^fn-marker]: Since the marker is contained in every packet, it could be generated 
automatically without the need for an explicit `TRX_data_checkpoint_marker` statement
in each packet. Indeed, although the statement is redundant, it is enforced explicitly
to avoid forgetting its existence when interpreting packet contents and bitstreams.

### Node ID Mapping

It may be of interest to run a schedule on different testbeds or different sets of nodes.
In this situation it is beneficial to have some mapping functionality between physical 
and logical node IDs to avoid the need to manually adapt each TRX operation in the 
schedule program. TrafficBench is prepared to support such mappings at two places:

1. One can implement a mapping in [`main.c`](target/nrf52840/main.c) (by default, 
   an identity mapping is used here).

2. One can implement a mapping via the `NODE()` macro in [`schedule.inc`](target/nrf52840/project_ses/schedule.inc)
   (which requires consistent usage of `NODE()` or `NODES()` instead of absolute 
   numbers in the schedule, see [`schedule_template.inc`](target/nrf52840/schedule_template.inc)
   for details).

Both options can be used simultaneously, so TrafficBench provides two mapping levels
that the user can adapt to her needs. We suggest to use the first option to implement 
mappings between testbed-specific physical IDs and testbed-independent logical IDs 
(if beneficial), and the second option to select the set of nodes used in the concrete 
schedule.[^fn-mapping]

[^fn-mapping]: The latter could also be understood as selecting a node for each 'role' 
defined in the schedule.


## Project Status, Problems and Questions

TrafficBench is an early stage project. We are quite confident that the core features 
work reliable and can be used to perform interesting experiments.

Some features are not yet fully supported and can cause minor problems, for example

* Setting `tx_carrier_period_1` or `tx_carrier_period_2` to a non-zero value is not 
  handled in `trx_analyze.py`, which leads to wrong SNR and SINR estimations in this 
  case.

* The TrafficBench Rx Viewer for Glue has a number of cosmetic issues (e.g. undesired
  reset of zoom factor after specific actions, turning off visibility of individual
  plot layers does not work).

We will try to fix such issues when there is time. We also have a long list of potential
minor and major improvements that would make TrafficBench more powerful and easy to use.
And, of course, documentation could be improved.

However, at the moment our focus is more on the conceptual side. We are discussing
some potential changes of the architecture that would enable TrafficBench to support
a much wider range of applications. We plan to investigate this direction in the near 
future to learn more about the challenges it brings along and find ways to solve them.

In case of problems, use the chance to compare your project with the tutorial schedule 
and look closely at the differences. If you experience significant issues or require 
additional features, please get in touch via e-mail.


## Research

TrafficBench has been developed in the [Networked Embedded Systems Lab](https://nes-lab.org) 
at [TU Dresden](https://tu-dresden.de) and [University of Freiburg](https://uni-freiburg.de/en/). 
Please visit <https://nes-lab.org> to find out more.


-----

**Footnotes**

