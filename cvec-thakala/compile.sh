gcc -g -fsanitize=address -include assert.h -include stdio.h -Wall -Wextra -Werror -Wpedantic -Wunreachable-code -Wtype-limits main.c vec.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memset.c -o vec.out
