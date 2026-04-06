# KFS-1

## Infomation

KFS-1 is a 42 introduction project to kernel coding and light bootloader management around GRUB.
The goal was to make a simple kernel in the language we wanted (we chosen C) with an asm bootable base to enable a multiboot header as asked.
This kernel can only print text and will by default print 42 for the mandatory part.
Then we have the bonus part, with scroll plus cursor support, colors support, a new helper like printf or printk (printf in our case), keyboard entries Handling plus printing and different screens handling with a shortcut.

## Commande

#### Make All
Compile Code, create an ISO file and launch it with qemu.

#### Make Start
Launch the iso with qemu.

#### Make compile
Compile the code.

#### Make test
Launch the kernel alone, outside the iso for basic testing.

#### Make grub-setup
Create the ISO file from compiled code.

#### Make clean
    Remove temporary file made for the compilation.

#### Make fclean
    Remove all files create by other rules.


## Contributor

**jdesol-f**  🔗 [GitHub](https://github.com/jdesol-f)</br>
**LekaUila** 🔗 [GitHub](https://github.com/LekaUila)