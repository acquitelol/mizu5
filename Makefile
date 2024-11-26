TMP ?= tmp
SRC ?= src
FXCG ?= ../libfxcg

SRCS = $(SRC)/mizu5.c $(SRC)/util.c
FXCG_FLAGS = -L$(FXCG)/lib -I$(FXCG)/include -T$(FXCG)/toolchain/prizm.x
CFLAGS = -Isrc -Itmp -lc -lfxcg -lgcc -nostdlib -O3 -flto -mb -m4a-nofpu -mhitachi

all: ensure_tmp mizu5.g3a

ensure_tmp:
	@mkdir -p $(TMP)

mizu5.g3a: $(TMP)/mizu5.out assets/sel.bmp assets/uns.bmp
	mkg3a -n basic:mizu5 -i uns:assets/uns.bmp -i sel:assets/sel.bmp $< $@

$(TMP)/mizu5.out: $(TMP)/data.h $(SRCS)
	sh3eb-elf-gcc -o $@ $(SRCS) $(CFLAGS) $(FXCG_FLAGS)

$(TMP)/data.h: $(TMP)/mizu5.bin
	xxd -i $< > $@

$(TMP)/mizu5.bin: assets/mizu5.png
	ffmpeg -i assets/mizu5.png -f rawvideo -pix_fmt rgb565be $@
