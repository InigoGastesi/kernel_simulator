main: src/main.c
	gcc -pthread -o kernel_simulator src/main.c src/timer.c src/clock.c src/pcb_list_manager.c src/schedule.c src/process_queue_manager.c src/machine.c