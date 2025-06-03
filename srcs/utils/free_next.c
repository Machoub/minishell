/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:02:29 by machouba          #+#    #+#             */
/*   Updated: 2024/07/30 17:56:37 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui free tous les arguments*/
void	free_argumts(char ***args)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = *args;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	if (ptr)
		free(ptr);
	*args = NULL;
}

/*Fonction qui free la commande passee en parametre*/
void	free_cmd(t_command *cmd)
{
	if (cmd)
	{
		if (cmd->tokens)
			free_token(&cmd->tokens);
		if (cmd->args_lst)
			free_args_list(&cmd->args_lst);
		if (cmd->infiles)
			free_infiles(&cmd->infiles);
		if (cmd->outfiles)
			free_outfiles(&cmd->outfiles);
		if (cmd->args)
			free_argumts(&cmd->args);
		if (cmd->path)
			free(cmd->path);
		free(cmd);
	}
}

/*Fonction qui free tout la liste des commandes*/
void	free_commands_list(t_command **command)
{
	t_command	*current_command;
	t_command	*next;

	current_command = *command;
	while (current_command)
	{
		next = current_command->next;
		free_cmd(current_command);
		current_command = next;
	}
	*command = NULL;
}

/*Fonction qui free tous les tokens*/
void	free_token(t_token **tok)
{
	t_token	*current_token;
	t_token	*next;

	if (*tok == NULL)
		return ;
	current_token = *tok;
	while (current_token)
	{
		next = current_token->next;
		if (current_token->value)
			free(current_token->value);
		if (current_token->heredoc)
			free(current_token->heredoc);
		free(current_token);
		current_token = next;
	}
	*tok = NULL;
}

/*Fonction qui free tous les envs*/
void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	if (env)
		free(env);
}
