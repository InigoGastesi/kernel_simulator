main: src/main.c src/timer.c
	gcc -pthread -o kernel_simulator src/main.c src/timer.c src/clock.c