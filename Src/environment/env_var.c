/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_var.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:43:32 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/11/04 14:12:18 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_var(t_envp *list, char *var)
{
	char	*output;

	while ((ft_strncmp(var, list->key, ft_strlen(list->key)) != 0) && \
			list->next != NULL)
	{
		list = list->next;
	}
	if (ft_strncmp(var, list->key, ft_strlen(list->key)) == 0 && \
		(ft_strlen(var) == ft_strlen(list->key)))
	{
		output = list->output;
		free(var);
		if (output == NULL)
			return ("");
		else
			return (output);
	}	
	else
	{
		free(var);
		return ("");
	}
}

void	key_output(char *split, t_envp **temp)
{
	int		i;
	int		start;
	char	*key;
	char	*output;

	i = 0;
	if (split != NULL)
	{
		while (split[i] != '=' && split[i] != '\0')
			i++;
		key = ft_substr(split, 0, i);
		(*temp)->key = ft_strdup(key);
		free(key);
		if (split[i] != '\0')
		{
			i++;
			start = i;
			while (split[i] != '\0')
				i++;
			output = ft_substr(split, start, (i - start));
			(*temp)->output = ft_strdup(output);
			free(output);
		}
	}
}
