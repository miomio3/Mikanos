NAME = kernel.elf
OBJS = main.o
CXXFLAGS = -O2 -Wall -g --target=x86_64-elf -ffreestanding  -fno-exceptions -mno-red-zone -fno-exceptions -fno-rtti -std=c++17
LXFLAGS = --entry KernelMain -z norelro --image-base 0x100000 --static

all		: $(NAME)
%.o		: %.cpp
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c $<
$(NAME)	: $(OBJS)
	ld.lld $(LDFLAGS) $(LXFLAGS) $(OBJS) -o $(NAME)

fclean	:
	rm -f $(OBJS)
clean	: fclean
	rm -f $(NAME)
re		: clean all

.PHONY : all fclean clean