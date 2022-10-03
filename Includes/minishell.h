/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rharing <rharing@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 17:42:30 by qfrederi      #+#    #+#                 */
/*   Updated: 2022/10/03 15:03:03 by rharing       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <limits.h>

//pipex
typedef struct s_vars {
	int		f1;
	int		f2;
	int		no_infile;
	int		no_outfile;
	int		env_count;
	char	**enviroment;
	char	**cmd;
	char	**path;
	char	*path_cmd;
	char	*my_path;
	char	*string_infile;
	char	*string_outfile;
	int		com;
	int		com_count;
	pid_t	pid;
}	t_vars;

extern t_vars	g_vars;

//input to commands
typedef struct s_node
{
	char			*content;
	char			*words;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	char			**command;
	int				token;

	struct s_node	*next;
}	t_node;

//envp in list
typedef struct s_envp
{
	char			*content;
	char			*key;
	char			*output;

	struct s_envp	*next;
}	t_envp;

void	main_loop(int flag, t_envp *env);

// Commands_build
		// cd.c
int		open_folder(t_node *command_table);

		// commands.c
int		commands_built(t_node *command_table);
int		builtin(t_node *command_table, t_envp *env);
int		pwd(void);
int		env(void);

		//echo.c
int		echo(t_node *command_table);

		// export.c
void	export(t_envp *env_list, t_node *command_table);

		// unset.c
void	unset(t_envp *env_list, t_node *command_table);

// environment
		// env_to_array.c
int		lst_size(t_envp *list);
void	print_array(void);
void	envp_to_array(t_envp *env);

		// env_var.c
void	print_envp(t_envp *list);
char	*env_var(t_envp *list, char *var);
void	key_output(char *split, t_envp **temp);

		// envp list
t_envp	*lstlast_envp(t_envp *lst);
void	lstadd_back_envp(t_envp **lst, char *split);
t_envp	*create_head_envp(char *first);
t_envp	*put_envp_in_list(char **envp);

// executioner
		// executioner.c
void	q_preform_cmd(t_node *command_table);
void	multiple_fork(t_node *command_table);
void	q_pipex_start(t_node *command_table);

		// child.c
void	first_child(t_node *command_table, \
					int (*fd)[g_vars.com][2]);
void	middle_child(t_node *command_table, \
					int (*fd)[g_vars.com][2]);
void	last_child(t_node *command_table, \
					int (*fd)[g_vars.com][2]);

		// fork_with_both.c
void	in_out_file_fork_process(t_node *command_table);

		// fork_with_infile.c
void	just_infile_multiple_fork_process(t_node *command_table);

		// fork_with_outfile.c
void	just_outfile_multiple_fork_process(t_node *command_table);

		// get_path.c
void	right_path(t_node *command_table);
void	find_path(void);
char	*q_find_token_infile(t_node *command_table);
char	*q_find_token_outfile(t_node *command_table);

		// init_pipes.c
void	init_pipes(int (*fd)[g_vars.com - 2][2]);
void	close_pipes(int (*fd)[g_vars.com - 2][2]);
void	ft_wait(void);

		// pipex_error.c
void	print_error(t_node *command_table);
void	pexit(char *str, int exit_code);

// parsing
		// create_command_table.c
void	exec_init(t_node *command_table);
t_node	*create_command_table_list(char *split, t_envp *env);
void	command_table(char *split, t_envp *env);
int		make_pipes(char *split, int i);
int		add_to_list(t_node *node, int i, char *split);

		// here_doc.c
int		list_heredoc(t_node **temp, char *split, int i, t_envp *env);

		// lexer_util.c
int		list_outfile(t_node **temp, int i, char *split);
int		list_infile(t_node **temp, int i, char *split);
int		find_var(t_node **temp, int i, char *split, t_envp *env);
int		var_first_char(char *split, int i, t_node **temp);

		// lexer.c
void	list_print_command(t_node *list);
int		redirect_infile(t_node *temp, char *split, int i);
int		redirect_here_doc(t_node *temp, char *split, int i, t_envp *env);
int		redirect_outfile(t_node *temp, char *split, int i);
char	split_pipe(char *split, t_node *temp, t_envp *env);

		// list.c
int		lstsize(t_node *list);
void	lstadd_back(t_node **lst, char *split);
t_node	*create_head(char *first);

		// quotes.c
void	list_quotes(t_node **temp, char *word);
int		find_quote(t_node **temp, int i, char *split, int start);
int		list_double_quote(t_node **temp, int i, char *split, t_envp *env);
int		list_single_quote(t_node **temp, int i, char *split, t_envp *env);
int		var_in_double_quotes(t_node **temp, int i, char *split, t_envp *env);

		// words.c
int		split_word(t_node **temp, int i, char *split, t_envp *env);
int		find_word(t_node **temp, int i, char *split, int start);
void	list_word(t_node **temp, char *word, int space);
void	add_space(t_node **temp, char *split, int start);

// signals
void	signals(void);

#endif