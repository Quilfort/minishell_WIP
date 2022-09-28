/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: qfrederi <qfrederi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/22 13:08:27 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/09/28 15:16:25 by qfrederi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	commands_built(t_node *command_table, t_vars *vars)
{
	if ((ft_strncmp("pwd", command_table->command[0], 3) == 0) \
		&& (command_table->command[1] == NULL) \
		&& ft_strlen("pwd") == ft_strlen(command_table->command[0]))
		return (pwd());
	if ((ft_strncmp("echo", command_table->content, 4) == 0) \
		&& ft_strlen("echo") == ft_strlen(command_table->command[0]))
		return (echo(command_table, vars));
	if ((ft_strncmp("env", command_table->command[0], 3) == 0) \
		&& (command_table->command[1] == NULL) \
		&& ft_strlen("env") == ft_strlen(command_table->command[0]))
		return (env(vars));
	return (0);
}

int	pwd(void)
{
	char	string[PATH_MAX];

	getcwd(string, sizeof(string));
	ft_putendl_fd(string, 1);
	return (1);
}

int	env(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->env_count)
	{
		ft_putendl_fd(vars->enviroment[i], 1);
		i++;
	}
	return (1);
}
