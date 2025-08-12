.PHONY: all rename_spaces clean

all: rename_spaces Tortimer.z64

rename_spaces:
	@find ./roms -maxdepth 1 -type f -name "* *" | while read file; do \
		newfile=$$(echo "$$file" | tr ' ' '_'); \
		mv "$$file" "$$newfile"; \
		echo "Renamed: $$file -> $$newfile"; \
	done

CFLAGS += \
	-O2 -funroll-loops \
	-std=c89 -Wall -Wextra

BUILD_DIR = build
SRC_DIR = src
include $(N64_INST)/include/n64.mk

assets_fnt = $(wildcard assets/*.fnt)
assets_ttf = $(wildcard assets/*.ttf)
assets_png = $(wildcard assets/*.png)

assets_nes = $(wildcard roms/*.nes)

assets_conv = \
	$(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64))) \
	$(addprefix filesystem/,$(notdir $(assets_fnt:%.fnt=%.font64))) \
    $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
	$(addprefix filesystem/roms/,$(notdir $(assets_nes:%.nes=%.nes)))

MKSPRITE_FLAGS ?=
MKFONT_FLAGS ?= --range all

src = \
	$(SRC_DIR)/pak_rom.c \
	$(SRC_DIR)/pak_letter.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/yay0tool/yay0.c \

filesystem/%.font64: assets/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -o filesystem "$<"

filesystem/%.font64: assets/%.fnt
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -o filesystem "$<"

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"

filesystem/roms/%: roms/%
	@mkdir -p "$(dir $@)"
	@echo "    [ROM] $@"
	@cp "$<" "$@"

$(BUILD_DIR)/Tortimer.dfs: $(assets_conv) 
$(BUILD_DIR)/Tortimer.elf: $(src:%.c=$(BUILD_DIR)/%.o)

# Get the current git version
GIT_VERSION := $(shell git rev-parse --short=8 HEAD)

# Define the N64 ROM title with the git version
N64_ROM_TITLE_WITH_VERSION := "Tortimer $(GIT_VERSION)"

Tortimer.z64: N64_ROM_TITLE = $(N64_ROM_TITLE_WITH_VERSION)
Tortimer.z64: $(BUILD_DIR)/Tortimer.dfs

clean:
	rm -rf $(BUILD_DIR) filesystem *.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: clean
