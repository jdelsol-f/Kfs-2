# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/13 13:40:58 by jdelsol-          #+#    #+#              #
#    Updated: 2026/03/16 18:34:08 by jdelsol-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = Duck
KERNEL = DuckyKernel

SRCS =	./BootLoader/start.s \
		./Kernel/kernel.c \

SRCS.O = ./CompiledFiles/start.o \
		 ./CompiledFiles/kernel.o

LINKER = ./Linker/linker.ld

OUTPUT_DIR = ./CompiledFiles

CC = i686-elf-gcc

$(OUTPUT_DIR)/%.o: %.c
	$(CC) -c $< -o $@

OBJS= ${SRCS:.c=.o} ${SRCS:.s=.o}



all: compile grub-setup start

start: qemu-system-i386 -cdrom ${OS}.iso || qemu-system-i386 -cdrom ${OS}.img

compile:
	${CC} -fno-builtin -fno-exceptions -fno-stack-protector \
	 -fno-rtti -nostdlib -nodefaultlibs -std=gnu99 -ffreestanding -g -c ${OBJS}

	${CC} -fno-builtin -fno-exceptions -fno-stack-protector \
	 -fno-rtti -nodefaultlibs  -ffreestanding -nostdlib -g \
	 -T ${LINKER} ${SRCS.O} -o $(KERNEL).elf -lgcc
	 
test: compile
	qemu-system-i386 -kernel $(KERNEL).elf

grub-update:	
	

grub-setup: grub-mkrescue isodir -o mykernel.iso
	grub-update

clean: rm -rf ./CompiledFiles/*.o
	

fclean: clean
	rm -rf ./CompiledFiles/*

re: fclean all


.PHONY: all clean fclean re run