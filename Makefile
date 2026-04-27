# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/13 13:40:58 by jdelsol-          #+#    #+#              #
#    Updated: 2026/04/27 14:02:24 by lflandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = Duck

KERNEL = DuckyKernel

OUTPUT_DIR = CompiledFiles

SRCS =	../srcs/BootLoader/start.s \
		 ../srcs/Kernel/kernel.c \
		 ../srcs/Kernel/Colors/colors.c \
		 ../srcs/Kernel/IO/cursor.c \
		 ../srcs/Kernel/IO/io.c \
		 ../srcs/Kernel/IO/numpad_SCK.c \
		 ../srcs/Kernel/Printf/printf.c \
		 ../srcs/Kernel/terminal-management/term_init.c \
		 ../srcs/Kernel/terminal-management/term_scrolling.c \
		 ../srcs/Kernel/Write_functions/write_functions.c \
		 ../srcs/Kernel/GDT/gdt.c \
		 ../srcs/Kernel/Console/command.c \
		 ../srcs/Kernel/Console/console.c


SRCS.O = ../${OUTPUT_DIR}/start.o \
		 ../${OUTPUT_DIR}/kernel.o \
		 ../${OUTPUT_DIR}/colors.o \
		 ../${OUTPUT_DIR}/cursor.o \
		 ../${OUTPUT_DIR}/io.o \
		 ../${OUTPUT_DIR}/numpad_SCK.o \
		 ../${OUTPUT_DIR}/printf.o \
		 ../${OUTPUT_DIR}/term_init.o \
		 ../${OUTPUT_DIR}/term_scrolling.o \
		 ../${OUTPUT_DIR}/write_functions.o \
		 ../${OUTPUT_DIR}/gdt.o \
		 ../${OUTPUT_DIR}/command.o \
		 ../${OUTPUT_DIR}/console.o

LINKER = ../srcs/Linker/linker.ld

NIX_ENV = ./Kfs-env.nix

CC = i686-elf-gcc

DEFAULT_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

all: compile grub-setup start

${OUTPUT_DIR} :
	mkdir CompiledFiles

start: 
	qemu-system-i386 -cdrom ${OUTPUT_DIR}/${OS}.iso 

compile:	${OUTPUT_DIR}
		cd CompiledFiles && ${CC} ${DEFAULT_FLAGS} -std=gnu99 -ffreestanding -g -c ${SRCS} && \
		${CC} -T ${LINKER} -o $(KERNEL).elf ${DEFAULT_FLAGS} -ffreestanding -g ${SRCS.O} -lgcc 
	 
test:
	qemu-system-i386 -kernel ${OUTPUT_DIR}/$(KERNEL).elf

grub-update:	
	cp ./${OUTPUT_DIR}/DuckyKernel.elf ./IsoDir/boot

grub-setup: grub-update
	grub-mkrescue ./IsoDir -o ${OUTPUT_DIR}/$(OS).iso

nix:
	nix-shell ${NIX_ENV}

gdt:

clean: 
	rm -rf ./${OUTPUT_DIR}/*.o
	

fclean: clean
	rm -rf ./${OUTPUT_DIR}/*.elf
	rm -rf ./${OUTPUT_DIR}/*.iso
	rm -rf ./IsoDir/boot/*.elf
	
re: fclean all


.PHONY: all clean fclean re start grub-setup test grub-update compile
