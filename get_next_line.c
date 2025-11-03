/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidebonl <tidebonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:05:35 by tidebonl          #+#    #+#             */
/*   Updated: 2025/11/03 16:37:37 by tidebonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *src)
{
	int i;

	i = 0;
	if (src == NULL)
		return (i);
	while (src[i] != '\0')
		i++;
	return (i);
}
char	*ft_strdup(const	char *source)
{
	size_t	i;
	char	*dest;

	if (source == NULL)
		return(NULL);
	i = ft_strlen(source);
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (s1 == NULL)
	{
		result = ft_strdup(s2);
		return (result);
	}
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
}

int	ft_strchr(const char *str, int to_find)
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
			return (i);
		i++;
	}
	if (cast == 0)
		return (-1);
	return (-1);
}

char *get_new_line(int fd, char **stack, char *buff)
{
	int i;
	char *tmp;
	char *result;
	int seed;

	i = 1;
	result = NULL;
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		buff[i] = '\0';
		seed = ft_strchr(buff, '\n');
		if (seed != -1)
		{
			tmp = ft_substr(buff, 0, seed);
			result = ft_strjoin((*stack), tmp);
			free(tmp);
			if ((*stack) != NULL)
			{
				free((*stack));
				(*stack) = ft_substr(buff, seed, BUFFER_SIZE - seed);
			}
			return (result);
		}
		tmp = *stack;
		*stack = ft_strjoin(*stack, buff);

		if (tmp != NULL)
			free(tmp);
	}
	return(NULL);
}
char	*get_next_line(int fd)
{
	static char *stack = NULL;
	char buff[BUFFER_SIZE];
	char *result;

	result = get_new_line(fd, &stack, buff);
	return (result);
}

int	main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	close(fd);
}
