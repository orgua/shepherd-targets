#! /bin/bash

BUILD_DIR=$1
BASE_NAME=$BUILD_DIR/$2
#PROJECT_DIR=$3
CC=$4
#OBJCOPY=$5

ELF=$BASE_NAME.elf
XML=${BASE_NAME}-flocklab.xml

echo "creating FlockLab XML"


##### assemble XML file
# example script: <https://gitlab.ethz.ch/tec/public/flocklab/flocklab/blob/master/tools/scripts/embed_image.sh>

echo "... building XML file (from $ELF)"

# encode ELF file
base64 "$ELF" > "$ELF.b64"

# preprocess template file
# remove leading empty lines, which would cause trouble otherwise
# for some reason, CC prints a time report as if -ftime-report is set
$CC -E -P -C -D_XML_ "-DIMAGE=$ELF.b64" -imacros config_flocklab.h flocklab_template.xml \
| python3 -c "import sys; print(sys.stdin.read().lstrip())" > "$XML"

rm -f "$ELF.b64"
