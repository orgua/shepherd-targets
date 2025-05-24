ifndef SDK_ROOT
  $(error SDK_ROOT is not set)
endif
ifndef GNU_INSTALL_ROOT
  $(error GNU_INSTALL_ROOT is not set)
endif

PREFIX := $(GNU_INSTALL_ROOT)arm-none-eabi-
PROJ_DIR := ./
OUTPUT_DIR := _build
SRC_DIR := src
LINKER_SCRIPT:= linker.ld

# Source files common to all targets
SRC_FILES += \
  startup.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

# Include folders common to all targets
INC_FOLDERS += \
  $(PROJ_DIR)/include \
  $(SDK_ROOT)/modules/nrfx/hal \
  $(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd \
  $(SDK_ROOT)/modules/nrfx/drivers/include \
  $(SDK_ROOT)/components/toolchain/cmsis/include \
  $(SDK_ROOT)/components/libraries/delay \
  $(SDK_ROOT)/components \
  $(SDK_ROOT)/integration/nrfx \
  $(SDK_ROOT)/components/libraries/util \
  $(SDK_ROOT)/modules/nrfx/mdk \
  $(SDK_ROOT)/modules/nrfx \
  $(SDK_ROOT)/integration/nrfx/legacy \
  $(SDK_ROOT)/config/nrf52840/config

INCLUDES = $(INC_FOLDERS:%=-I%)
CFLAGS += -g3 -O3
CFLAGS += ${INCLUDES}
CFLAGS += -DNRF52840_XXAA
CFLAGS += -DARM_MATH_CM4
CFLAGS += -Wall
CFLAGS += -fno-builtin
CFLAGS += -mthumb
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mabi=aapcs
CFLAGS += -mfloat-abi=hard
CFLAGS += -mfpu=fpv4-sp-d16
CFLAGS += -fsingle-precision-constant

LDFLAGS += ${CFLAGS}
LDFLAGS += -nostartfiles
LDFLAGS += -T$(LINKER_SCRIPT)

# let linker dump unused sections
LDFLAGS += -Wl,--gc-sections,-Map=${OUTPUT_DIR}/build.map
# use newlib in nano version
LDFLAGS += --specs=nano.specs

LIB_FILES += -lc -lnosys -lm

all: ${OUTPUT_DIR}/build.hex ${OUTPUT_DIR}/build.elf

${OUTPUT_DIR}/%.o: ${SRC_DIR}/%.c
	@${PREFIX}gcc ${CFLAGS} -c $< -o $@
	@echo "CC $<"


${OUTPUT_DIR}/build.elf: $(OBJ_FILES:%=${OUTPUT_DIR}/%)
	@${PREFIX}gcc ${LDFLAGS} $^ -o $@ ${LIB_FILES}
	@${PREFIX}size $@

${OUTPUT_DIR}/build.hex: ${OUTPUT_DIR}/build.elf
	@${PREFIX}objcopy -O ihex $< $@
	@echo "Preparing $@"

.PHONY: clean flash erase

clean:
	rm -rf _build/*

# Flash the program
flash: ${OUTPUT_DIR}/build.hex
	@echo Flashing: $<
	nrfjprog -f nrf52 --program $< --sectorerase
	nrfjprog -f nrf52 --reset

erase:
	nrfjprog -f nrf52 --eraseall
