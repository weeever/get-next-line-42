/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidebonl <tidebonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:05:35 by tidebonl          #+#    #+#             */
/*   Updated: 2025/11/04 12:26:05 by tidebonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *check_stack(char **stack)
{
	int seed;
	char *tmp;

	if ((*stack) != NULL)
	{
		tmp = *stack;
		free(*stack);
		seed = ft_strchr(tmp, '\n');
		if (seed != -1)
		{
			if ((tmp[seed + 1]) !=  '\0')
			{
				*stack = ft_substr(tmp, seed + 1, ft_strlen(tmp + seed + 1));
			}
		}
	}
	return (NULL);
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
			if (*stack != NULL)
			{
				if (tmp != NULL)
					free(tmp);
				free(*stack);
				tmp = (*stack);
				(*stack) = ft_substr(tmp, seed , ft_strlen(tmp) - seed);
			}
			tmp = ft_substr(buff , 0, seed + 1);
			result = ft_strjoin((*stack), tmp);
			free(tmp);
			return (result);
		}
		tmp = (*stack);
		(*stack) = ft_strjoin((*stack), buff);
		if (tmp != NULL)
			free(tmp);
	}
	return(NULL);
}

char	*get_next_line(int fd)
{
	static char *stack = NULL;
	char buff[BUFFER_SIZE + 1];
	char *result;

	result = get_new_line(fd, &stack, buff);
	return (result);
}

int main(void)
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	printf("Line: %s\n", get_next_line(fd));
	printf("Line: %s\n", get_next_line(fd));
	printf("Line: %s\n", get_next_line(fd));
	printf("Line: %s\n", get_next_line(fd));
	printf("Line: %s\n", get_next_line(fd));
	printf("Line: %s\n", get_next_line(fd));

	close(fd);
}
