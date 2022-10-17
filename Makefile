main: src/main.c
	gcc -pthread -o kernel_simulator src/main.c src/timer.c src/clock.c src/process_queue_manager.c