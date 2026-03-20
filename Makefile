# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/13 13:40:58 by jdelsol-          #+#    #+#              #
#    Updated: 2026/03/20 15:15:15 by jdelsol-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = Duck

KERNEL = DuckyKernel

OUTPUT_DIR = CompiledFiles

SRCS =	../BootLoader/start.s \
		 ../Kernel/kernel.c

SRCS.O = ../${OUTPUT_DIR}/start.o \
		 ../${OUTPUT_DIR}/kernel.o

LINKER = ../Linker/linker.ld

CC = i686-elf-gcc

DEFAULT_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

all: compile grub-setup start

start: 
	qemu-system-i386 -cdrom ${OUTPUT_DIR}/${OS}.iso 

compile:	
		cd CompiledFiles && ${CC} ${DEFAULT_FLAGS} -std=gnu99 -ffreestanding -g -c ${SRCS} && \
		${CC} ${DEFAULT_FLAGS}  -ffreestanding -g \
		 -T ${LINKER} ${SRCS.O} -o $(KERNEL).elf -lgcc 
	 
test:
	qemu-system-i386 -kernel ${OUTPUT_DIR}/$(KERNEL).elf

grub-update:	
	cp ./${OUTPUT_DIR}/DuckyKernel.elf ./IsoDir/boot

grub-setup: grub-update
	grub-mkrescue ./IsoDir -o $(OS).iso

clean: 
	rm -rf ./${OUTPUT_DIR}/*.o
	

fclean: clean
	rm -rf ./${OUTPUT_DIR}/*.elf
	rm -rf ./${OUTPUT_DIR}/*.iso
	
re: fclean all


.PHONY: all clean fclean re run