/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_with_both.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:20:46 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/01 17:14:25 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_out_file_one_command(t_node *command_table, t_vars *vars, \
									t_envp *env_list)
{
	int status;

	find_path(vars);
	g_vars2.pid = fork();
	if (g_vars2.pid == -1)
		perror("fork error\n");
	if (g_vars2.pid == 0)
	{
		if (dup2(vars->f1, STDIN_FILENO) == -1)
			print_error(command_table, vars);
		if (dup2(vars->f2, STDOUT_FILENO) == -1)
			print_error(command_table, vars);
		close(vars->f1);
		close(vars->f2);
		q_preform_cmd(command_table, vars, env_list);
	}
	else
	{
		wait(&status);
		close(vars->f1);
		close(vars->f2);
		if (WIFEXITED(status))
			g_vars2.exitcode = WEXITSTATUS(status);
	}
}

void	in_out_file_fork_process(t_node *command_table, t_vars *vars, \
								t_envp *env_list)
{
	if (vars->com == 1)
	{
		in_out_file_one_command(command_table, vars, env_list);
		close(vars->f1);
		close(vars->f2);
	}
	else
		multiple_fork(command_table, vars, env_list);
}
