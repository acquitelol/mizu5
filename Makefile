all: mizu5.g3a

mizu5.g3a: mizu5.out mizu5.bmp
	mkg3a -n basic:mizu5 -i uns:mizu5.bmp -i sel:mizu5.bmp mizu5.out mizu5.g3a
	rm mizu5.out

mizu5.out: mizu5.bin
	sh3eb-elf-gcc -o mizu5.out src/mizu5.c src/util.c -L../libfxcg/lib -I../libfxcg/include -Isrc -lc -lfxcg -lgcc -nostdlib -T../libfxcg/toolchain/prizm.x -mb -m4a-nofpu -mhitachi

mizu5.bin: mizu5.png
	ffmpeg -i mizu5.png -f rawvideo -pix_fmt rgb565le mizu5.bin
