/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_pipes.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/13 15:30:27 by rharing       #+#    #+#                 */
/*   Updated: 2022/11/01 18:59:15 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	openfiles(t_node *command_table, t_vars *vars)
{
	if (command_table->infile != NULL)
	{
		vars->f1 = open(command_table->infile, O_RDONLY, 0644);
		if (vars->f1 < 0)
		{
			perror(command_table->infile);
			g_vars2.exitcode = 1;
		}
	}
	if (command_table->outfile != NULL)
	{
		if (command_table->append == 1)
			vars->f2 = open(command_table->outfile, O_RDWR | O_APPEND);
		else
			vars->f2 = open(command_table->outfile, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (vars->f2 < 0)
		{
			perror(command_table->outfile);
			g_vars2.exitcode = 1;
		}
	}
}

void	open_infile(t_vars *vars, t_node *command_table)
{
	vars->f1 = open(command_table->infile, O_RDONLY, 0644);
	if (vars->f1 < 0)
	{
		perror(command_table->infile);
		exit(1);
		// g_vars2.exitcode = 1;
	}
	if (dup2(vars->f1, STDIN_FILENO) == -1)
		print_error(command_table, vars);
}

void	open_outfile(t_vars *vars, t_node *command_table)
{
	if (command_table->append == 1)
		vars->f2 = open(command_table->outfile, O_RDWR | O_APPEND);
	else
		vars->f2 = open(command_table->outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->f2 < 0)
	{
		perror(command_table->outfile);
		exit(1);
		// g_vars2.exitcode = 1;
	}
	if (dup2(vars->f2, STDOUT_FILENO) == -1)
		print_error(command_table, vars);
}

void	close_files(t_vars *vars, t_node *command_table)
{
	if (command_table->infile != NULL)
		close(vars->f1);
	if (command_table->outfile != NULL)
		close(vars->f2);
}