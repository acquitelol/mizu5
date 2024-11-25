all: mizu5.g3a

mizu5.g3a: mizu5.out
	mkg3a -n basic:mizu5 -i uns:mizu5.bmp -i sel:mizu5.bmp mizu5.out mizu5.g3a
	rm mizu5.out

mizu5.out:
	sh3eb-elf-gcc -o mizu5.out mizu5.c -L../libfxcg/lib -I../libfxcg/include -lc -lfxcg -lgcc -nostdlib -T../libfxcg/toolchain/prizm.x -mb -m4a-nofpu -mhitachi
