PROJDIRS := include boot init kernel lib
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
ASMFILES := $(shell find $(PROJDIRS) -type f -name "*.s")
#HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) $(patsubst %.s, %.o, $(ASMFILES))
DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
ALLFILES := $(SRCFILES) $(HDRFILES)
INCLUDES := $(addprefix -I, $(PROJDIRS))

CFLAGS   := $(INCLUDES) -m32 -nostdlib -fno-builtin -nostartfiles -fno-stack-protector -Wall -Wextra
LDFLAGS  := -Tlink.ld -melf_i386
ASFLAGS  := -felf

.PHONY: all clean dist check


all: $(OBJFILES) link

link:
	ld $(LDFLAGS) -o kernel.img $(OBJFILES)
clean:
	$(RM) $(wildcard $(OBJFILES) $(DEPFILES) kernel.img)
.s.o:
	nasm $(ASFLAGS) $<
