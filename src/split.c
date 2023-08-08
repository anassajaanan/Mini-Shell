/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:17:09 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/07 13:18:19 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_seperator(char c, char sep)
{
	if (c == sep || c == '\0' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	count_words(char *str, char sep)
{
	int	i;
	int	in_quote;
	int	counter;

	i = 0;
	counter = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			in_quote = !in_quote;
		if (!in_quote && !is_seperator(str[i], sep) && is_seperator(str[i + 1],
				sep))
			counter++;
		i++;
	}
	return (counter);
}

static char	*get_next_word(char *str, char sep, int *i)
{
	int		j;
	char	*word;

	j = *i;
	if (str[*i] == '\"' || str[*i] == '\'')
	{
		j++;
		while (str[j] && str[j] != str[*i])
			j++;
		word = (char *)malloc(sizeof(char) * (j - *i));
		ft_strlcpy(word, str + *i + 1, j - *i);
		*i = j + 1;
		return (word);
	}
	else
	{
		while (str[j] && !is_seperator(str[j], sep))
			j++;
		word = (char *)malloc(sizeof(char) * (j - *i + 1));
		ft_strlcpy(word, str + *i, j - *i + 1);
		*i = j;
		return (word);
	}
}

char	**split(char *str, char sep)
{
	int		i;
	int		count;
	int		words;
	char	**array;

	words = count_words(str, sep);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_seperator(str[i], sep))
			i++;
		else
			array[count++] = get_next_word(str, sep, &i);
	}
	array[words] = NULL;
	return (array);
}
