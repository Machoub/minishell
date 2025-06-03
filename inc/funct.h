/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:21:46 by machouba          #+#    #+#             */
/*   Updated: 2024/08/30 14:54:36 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_H
# define FUNCT_H

/*Utils*/
int			ft_is_var(char c);
int			ft_isquote(char c);
int			is_space(char c);
char		*ft_strsjoin(char *the_str, char *str_to_add);
char		*ft_strndup(char *s, int size);
int			ft_isoperator(char *str);
int			gettype(char *str);
int			ft_isop(char *str);
int			envs_lst_size(t_env *env);
int			args_lst_len(t_arg *args);
int			append_check(t_command	*cmd, char *name);
void		exit_display(t_data *data, int status);
/*Error*/
void		ft_print_err(int error);
void		error_token(t_token *token, int error_model);
int			error_pipe_at_end(t_token *lst);
void		ft_check_errors(t_data *data, t_command *cmd);
int			ft_isdirectory(char *path);
void		ft_print_err(int errno);
/*Token*/
t_token		*ft_tokenization(char *input);
t_token		*findlast_token(t_token *lst);
void		addlast_token(t_token **token_lst, t_token *new);
t_token		*token_before_last(t_token *list);
t_token		*ft_init_token(char *str, int type, int i, bool exp_flag);
t_token		*get_token(t_token *token);
int			token_checker(t_data *data, t_token *lst);
int			lexing(t_data *data);
int			check_pipe_errors(t_data *data, t_token *token);
void		exit_stat(t_data *data);
/*Init*/
t_data		*ft_init_data(int argc, char **argv, char **envp);
void		handler_dprompt(int signal);
/*Exec*/
void		execute(t_data *data);
int			exec_sing_cmd(t_data *data);
t_redirect	*redir(t_data *data, t_command *cmd);
int			make_fork(t_data *data);
void		exec_one_cmd(t_data *data);
void		special_check(t_data *data, char *str);
char		**create_environment(t_data *data);
char		*get_path_command(t_data *data, const char *command_name);
int			execve_cmd(t_data *data, t_command *command);
void		handle_child_process(t_data *data, int process_idx);
void		exit_null(t_data *data, t_redirect *redir);
void		close_unused_pipes(t_data *data, t_redirect *redir);
/*Pipe*/
int			**create_pipes_fd(int nbr);
void		close_pipes(t_data *data);
/*Parsing*/
char		**tab_of_args(t_arg *args);
t_token		*get_token(t_token *token);
int			parse_command(t_data *data);
/*Builtins*/
int			is_builtin(t_command *cmd);
bool		is_option(char *cmd);
int			excec_builtin(t_data *data, t_command *cmd);
int			ft_cd(t_env *envs, t_command *cmd);
int			ft_export(t_data *data, t_command *cmd);
int			ft_exit(t_data *data, t_arg *args);
int			ft_pwd(t_command *cmd);
int			ft_echo(t_data *data, t_command *cmd);
int			ft_unset(t_data *data, t_arg *args);
/*Args*/
t_arg		*create_args_list(t_token *token);
/*Infiles*/
t_infile	*create_infile_list(t_data *data, t_token *tok);
/*Outfiles*/
t_outfile	*create_outfiles_list(t_token *current);
/*Heredocs*/
int			launch_hd(t_data *data);
void		create_hd_files(t_data *data);
char		**create_hd_names(int nbr);
int			get_heredocs_nbr(t_command *cmds);
int			check_error_print(t_token *tokens);
t_infile	*gni(t_infile *infile, char *name);
/*Environnements*/
void		delete_env(t_env **envs, char *key);
int			set_env(t_env **envs, char *key, char *value);
char		*get_env(t_env *env, char *key);
int			ft_env(t_data *data);
t_env		*init_env(char *name, char *key, char *value);
t_env		*env_from_input(char *input);
void		free_envs(t_env **envs);
t_env		*create__new_env(char *var, char *key, char *value);
t_env		*default_env(void);
t_env		*creates_envs_list(char **env);
/*Frees*/
void		free_env(char **env);
void		delete_env(t_env **envs, char *key);
void		free_all(t_data *data);
void		reinit_data(t_data *data);
void		free_token(t_token **tok);
void		free_commands_list(t_command **command);
void		free_cmd(t_command *cmd);
void		free_args_list(t_arg **lst);
void		free_infiles(t_infile **infiles);
void		free_outfiles(t_outfile **outfiles);
/*Expand*/
void		expand_tokens(t_data *data, t_token **token_list);
char		*expand_string(t_data *data, char *str);
char		*get_expansion(t_data *data, char *var_name, char *str);
char		*extract_variable_name(char *str);
char		*extract_until_limit(char *str, char *limset);
char		*remove_quotes(char *str);
char		*extract_quoted_string(t_data *data, char *str);
/*Export*/
void		add_export_to_lst(t_env **exports, t_env *new);
t_env		*create_export(void);
t_env		*create_export_list(char **env);
void		print_exports(t_data *data);
void		remove_export(t_env **exports, char *key);
int			add_export(t_env **exports, char *name, char *key, char *value);
int			handle_input(t_data *data, char *input);
#endif