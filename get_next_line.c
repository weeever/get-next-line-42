/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tidebonl <tidebonl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:05:35 by tidebonl          #+#    #+#             */
/*   Updated: 2025/10/30 12:47:36 by tidebonl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_current_line(char *buff, char *result)
{
	int i;

	i = 0;

	while (buff[i] != '\0')
	{
		if (buff[i] == '\n')
			return (i);
	}
	return(-1);
}
char	*put_single_or_double(char *dest, char *src, char *src2)
{
	int j;
	int i;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (src2 != NULL)
	{
		while (src2[j] != '\0')
		{
			dest[i] = src[j];
			j++;
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*del_and_replace(char *stack, char *buff)
{
	int i;
	int j;
	char *stock;
	i = 0;

	if (stack == NULL)
	{
		stack = malloc(sizeof(char) * ft_strlen(buff));
		stack = put_single_or_double(stack, buff, NULL);
		return (stack);
	}
	stock = malloc(sizeof(char) * ft_strlen(stack));
	stock = put_single_or_double(stock , stack, NULL);
	free(stack);
	i = ft_strlen(buff) + ft_strlen(stock);
	stack = malloc(sizeof(char) * i + 1);
	stack = put_single_or_double(stack, stock, buff);
	free(stock);
	return(stack);
}

char	*get_next_line(int fd)
{
	char buff[BUFFER_SIZE];
	static char	*stack = NULL;
	int i;

	i = 0;
	read(fd, buff, BUFFER_SIZE);
	stack = del_and_replace(stack, buff);
	printf("%s", stack);
	return (stack);
}

int	main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
}
