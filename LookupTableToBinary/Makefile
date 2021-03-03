
all: from01 to01 demo

from01 : from01.c
	cc -o from01 from01.c

to01 : to01.c
	cc -o to01 to01.c

demo : to01 from01
	./to01 eg.data | tee eg.01
	cat eg.01 | ./from01 eg.rebuilt
	cmp eg.data eg.rebuilt

