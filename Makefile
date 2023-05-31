CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = get_next_line.c \
	get_next_line_utils.c \
			
OBJECTS = ${SRCS:.c=.o}
RM = rm -f

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}
	@echo "Library successfuly created."

clean:
	${RM} ${OBJECTS}
	@echo "Files .o successfuly removed"

fclean: clean
	${RM} ${NAME}
	@echo "Files .a successfuly removed"

re: fclean all