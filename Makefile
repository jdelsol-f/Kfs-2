# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdelsol- <jdelsol-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/13 13:40:58 by jdelsol-          #+#    #+#              #
#    Updated: 2026/03/16 17:34:52 by jdelsol-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS = Duck
KERNEL = DuckyKernel

SRCS = \

OBJS= ${SRCS:.c=.o} ${SRCS:.s=.o}

all: compile grub-setup start

start: qemu-system-i386 -cdrom $(OS).iso || qemu-system-i386 -cdrom $(OS).img

compile:
	i686-elf-gcc -fno-builtin -fno-exception -fno-stack-protector \
	 -fno-rtti -nostdlib -nodefaultlibs -std=gnu99 -ffreestanding -g -c ${OBJS}

	i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld ${OBJS} -o $(KERNEL).elf -lgcc


	 
test: compile
	qemu-system-i386 -kernel $(KERNEL).elf


grub-update:	
	

grub-setup: grub-mkrescue isodir -o mykernel.iso
	grub-update


clean: rm -rf ./*.o
	

fclean: clean
	rm -rf ./*.iso
	rm -rf ./*.img

re: fclean all


.PHONY: all clean fclean re run