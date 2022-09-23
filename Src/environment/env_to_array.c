/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_to_array.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 15:18:45 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/21 17:10:00 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	lst_size(t_envp *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

// alleen nodig bij testen.
void	print_array(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 38)
	{
		printf("%s\n", vars->enviroment[i]);
		i++;
	}
}

void	envp_to_array(t_envp *env, t_vars *vars)
{
	int	i;
	int	count;

	count = lst_size(env);
	printf("ditsis: %d\n", count);
	i = 0;
	vars->enviroment = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		vars->enviroment[i] = ft_strdup(env->content);
		i++;
		env = env->next;
	}
	vars->enviroment[i] = "\0";
	vars->env_count = i;
	printf("ditsisI: %d\n", i);
	// vars->enviroment[i] = ft_strdup("\0");
}
