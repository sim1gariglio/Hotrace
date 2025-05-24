#ifndef hotrace_h
#   define hotrace_h

#   include <stdlib.h>
#   include <unistd.h>
#   include <stdio.h>
#   define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_read(char *old_str, int fd);
char	*ft_newstrjoin(char *old_str, char *buf);
char	*ft_correctline(char *old_str);
char	*ft_resto(char *old_str);
size_t	    ft_strlen(char *str);
char	*ft_strchr(char *s, int c);


#endif