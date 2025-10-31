/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidebonl <tidebonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:05:35 by tidebonl          #+#    #+#             */
/*   Updated: 2025/10/31 11:08:37 by tidebonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *src)
{
	int i;

	i = 0;
	if (src == NULL)
		return (i);
	while (src[i] != '\0')
		i++;
	return (i);
}

void	ft_write(char **dest, char *buff)
{
	int i;

	i = 0;
	while (buff[i] != '\0')
	{
		((*dest)[i]) = buff[i];
		i++;
	}
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
		result[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	size;
	size_t	switcher;

	result = 0;
	i = 0;
	size = ft_strlen((char *)s + start);
	if (size <= len)
		switcher = size;
	else
		switcher = len;
	result = malloc(sizeof(char) * switcher + 1);
	if (!result)
		return (NULL);
	while (i != switcher)
		result[i++] = s[start++];
	result[i] = '\0';
	return (result);

	result = ft_add(result, s, start, len);
	return (result);
}

char	*ft_strchr(const char *str, int to_find)
{
	size_t		i;
	char		*result;
	char		cast;

	cast = (char)to_find;
	result = (char *)str;
	i = 0;
	while (result[i] != '\0')
	{
		if (result[i] == cast && cast != 0)
			return (result + i);
		i++;
	}
	if (cast == 0)
		return (result + i);
	return (NULL);
}

char *get_line(int fd, char *buff, char *stack)
{
	int i;
	char *new;
	char *line;

	line = NULL;
	i = 0;
	read(fd, buff, BUFFER_SIZE);

}

char	*get_next_line(int fd)
{
	char buff[BUFFER_SIZE];
	static char	*stack = NULL;

	if (stack == NULL)
	{

	}
}

int	main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
}
