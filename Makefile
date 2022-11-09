# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
TARGETS=$(OBJS:%.o=%)

build:
	gcc -g -Wall -Wextra apply_image.c crop_image.c exit.c image_actions.c image_editor.c load_image.c rotate_image.c save_image.c select_image.c -o image_editor -lm

pack:
	zip 312CA_GheorghiuVlad_Tema3.zip README Makefile *.c *.h

run:
	./image_editor

clean:
	rm -f *.o image_editor

.PHONY: pack clean
