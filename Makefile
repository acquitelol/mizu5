TMP ?= tmp
SRC ?= src
FXCG ?= ../libfxcg
MK3GA ?= mkg3a
GCC ?= sh3eb-elf-gcc

NAME = mizu5
CFLAGS = -Isrc -Itmp -lfxcg -lgcc -lc -nostdlib -Os -Wall -Wextra -Wpedantic
FXCG_FLAGS = -L$(FXCG)/lib -I$(FXCG)/include -T$(FXCG)/toolchain/prizm.x
EXTRA_CFLAGS =  -flto -ffat-lto-objects -mb -m4a-nofpu -mhitachi
SRCS = $(wildcard src/*.c)

all: $(TMP) $(NAME).g3a

$(NAME).g3a: $(TMP)/$(NAME).out assets/sel.bmp assets/uns.bmp
	$(MK3GA) -n basic:$(NAME) -i uns:assets/uns.bmp -i sel:assets/sel.bmp $< $@

$(TMP)/$(NAME).out: $(TMP)/data.h $(SRCS)
	$(GCC) -o $@ $(SRCS) $(CFLAGS) $(FXCG_FLAGS) $(EXTRA_CFLAGS)

$(TMP)/data.h: $(TMP)/$(NAME).bin
	xxd -i $< > $@

$(TMP)/$(NAME).bin: assets/$(NAME).png
	ffmpeg -y -i $< -f rawvideo -pix_fmt rgb565be $@

.PHONY: $(TMP)
$(TMP):
	mkdir -p $(TMP)

.PHONY: clean
clean:
	rm -rf tmp
	rm $(NAME).g3a
