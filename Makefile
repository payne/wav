all: from01 to01 demo main

from01 : from01.c nibbles.h
	cc -o from01 from01.c

to01 : to01.c nibbles.h
	cc -o to01 to01.c

demo : to01 from01
	echo eg.data has this data:
	cat eg.data
	./to01 eg.data | tee eg.01
	cat eg.01 | ./from01 eg.rebuilt
	cmp eg.data eg.rebuilt
	echo eg.rebuilt has this data
	cat eg.rebuilt
	echo we know they are the same because, this does not fail: cmp eg.data eg.rebuilt

clean-up : 
	rm eg.01 eg.rebuilt from01 to01

main debug: helper_functions.c helper_functions.h main.c wav_data.c wav_data.h wav_header.c wav_header.h wav_types.h wav_process.c wav_process.h
	gcc main.c helper_functions.c wav_data.c wav_header.c wav_process.c -o wave

clean:
	rm wave

