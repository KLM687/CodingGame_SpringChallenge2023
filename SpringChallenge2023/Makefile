NAME		=	../codingame_sync_file
BINARY		=	compiled

CC			=	gcc

CPPFLAGS	=	-MMD
CFLAGS	=	-Wall -Wextra #-Werror

#ADD YOUR SOURCES BELOW WITHOUT THE SOURCE PREFIX MAIN.C GIVEN AS EXAMPLE
SRCS		=	main.c \
				parse.c \
				compute.c \
				strategy.c \
				cell_operations.c \

#IF YOU HAVE HEADER FILES YOU ABSOLUTELY NEED TO ADD THEM IN THE INC_FILES VAR
INC_FILES	= 	ant.h /
INC_PATH	=	includes/
INC			=	-I $(INC_PATH)


SRCS_PATH	=	./sources/
OBJS_PATH	=	./objects/

OBJS		=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
DEPS		=	$(OBJS:.o=.d)


all: $(NAME)

$(NAME):	$(addprefix $(INC_PATH), $(INC_FILES)) $(addprefix $(SRCS_PATH), $(SRCS))
			@cat $^ | grep -v '#\s*include\s*"' > $(NAME)
			make $(BINARY)
			@echo "Created merged file"

$(BINARY): $(OBJS)
			$(CC) $(CFLAGS) $^ -o $(BINARY) $(INC)


$(OBJS_PATH):
				mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.c
					@mkdir -p $(dir $@)
					$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(INC)
				

clean:
		rm -rf $(OBJS_PATH)

fclean:		clean
		rm -rf $(NAME)

re:	fclean
	make all

test: $(NAME)
		./$(BINARY)

vtest: $(NAME)
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BINARY)

-include $(DEPS)

.PHONY: clean fclean re test vtest

