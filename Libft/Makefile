CFLAGS = -g -Wall -Wextra -Werror -I. -I./check_char -I./management_memory -I./string -I./link_list -fPIE
NAME = libft.a
CC = cc

SRC_DI = ./check_char ./management_memory ./string ./link_list ./ft_printf ./gnl

SOURCES += \
    ./check_char/ft_isdigit.c \
    ./check_char/ft_isalnum.c \
    ./check_char/ft_isprint.c \
    ./check_char/ft_isalpha.c \
    ./check_char/ft_isascii.c \
    ./management_memory/ft_calloc.c \
    ./management_memory/ft_bzero.c \
    ./gnl/get_next_line.c \
    ./gnl/get_next_line_bonus.c \
    ./gnl/get_next_line_utils.c \
    ./gnl/get_next_line_utils_bonus.c \
    ./ft_printf/ft_putnbr_base_len_origin.c \
    ./ft_printf/ft_putnbr_base_len.c \
    ./ft_printf/ft_putstr_len.c \
    ./ft_printf/ft_printf.c \
    ./ft_printf/ft_putchar.c \
    ./string/ft_strchr.c \
    ./string/ft_memchr.c \
    ./string/ft_strtrim.c \
    ./string/ft_atoi_base.c \
    ./string/ft_striteri.c \
    ./string/ft_putnbr_fd.c \
    ./string/ft_strmapi.c \
    ./string/ft_substr.c \
    ./string/ft_strdup.c \
    ./string/ft_itoa.c \
    ./string/ft_memcpy.c \
    ./string/ft_strnstr.c \
    ./string/ft_free_tab.c \
    ./string/ft_tolower.c \
    ./string/ft_strlcpy.c \
    ./string/ft_putendl_fd.c \
    ./string/ft_strlen.c \
    ./string/ft_atoi.c \
    ./string/ft_memset.c \
    ./string/ft_memcmp.c \
    ./string/ft_putstr_fd.c \
    ./string/ft_strjoin.c \
    ./string/ft_strncmp.c \
    ./string/ft_putchar_fd.c \
    ./string/ft_strrchr.c \
    ./string/ft_split.c \
    ./string/ft_memmove.c \
    ./string/ft_strlcat.c \
    ./string/ft_toupper.c \
    ./string/ft_strcpy_map.c \
    ./string/ft_strlen_map.c \
	./string/ft_atol.c \
    ./link_list/ft_lstmap.c \
    ./link_list/ft_lstnew.c \
    ./link_list/ft_lstclear.c \
    ./link_list/ft_lstsize.c \
    ./link_list/ft_lstadd_front.c \
    ./link_list/ft_lstadd_back.c \
    ./link_list/ft_lstiter.c \
    ./link_list/ft_lstlast.c \
    ./link_list/ft_lstdelone.c \
	./link_list/ft_free_list.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus so clean fclean re
