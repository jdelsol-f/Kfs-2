# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/13 13:40:58 by jdelsol-          #+#    #+#              #
#    Updated: 2026/03/18 19:11:55 by jdelsol-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARS

OS = Duck
KERNEL = DuckyKernel

SRCS =	BootLoader/start.s \
		 Kernel/kernel.c

SRCS.O = start.o \
		 kernel.o

LINKER = Linker/linker.ld

OUTPUT_DIR = ./CompiledFiles

CC = i686-elf-gcc

DEFAULT_FLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

OBJS =  ${SRCS:.s=.o} ${SRCS:.c=.o}


all: compile grub-setup start

start: qemu-system-i386 -cdrom ${OS}.iso || qemu-system-i386 -cdrom ${OS}.img

compile:	${OBJS}
		${CC} ${DEFAULT_FLAGS} -std=gnu99 -ffreestanding -g -c ${SRCS}
		
		mv ./$(wildcard *.o) ${OUTPUT_DIR}

# 		${CC} ${DEFAULT_FLAGS}  -ffreestanding -nostdlib -g \
		 -T ${LINKER} ${SRCS.O} -o $(KERNEL).elf -lgcc
	 
test: compile
	qemu-system-i386 -kernel $(KERNEL).elf

grub-update:	
	

grub-setup: grub-mkrescue isodir -o mykernel.iso
	grub-update

clean: rm -rf ./$(OUTPUT_DIR)/*.o
	

fclean: clean
	rm -rf ./$(OUTPUT_DIR)/*

re: fclean all


.PHONY: all clean fclean re run