/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:50:59 by gino              #+#    #+#             */
/*   Updated: 2024/09/04 15:13:54 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui recupere la position de l'erreur*/
static int	where_is_error(t_command *cmd)
{
	t_token	*current;
	int		pos;

	pos = -1;
	current = cmd->tokens;
	while (current)
	{
		if (current->flag_error == TRUE)
		{
			pos = current->pos;
			return (pos);
		}
		else if (current->pipe_flag == TRUE)
			return (current->next->pos);
		current = current->next;
	}
	return (pos);
}

/*Fonction qui compte les heredocs avant l'erreur*/
static int	hd_nbr_while_no_error(t_command *cmd)
{
	t_token	*current;
	int		pos;
	int		nbr;

	if (!cmd)
		return (0);
	pos = 0;
	nbr = 0;
	pos = where_is_error(cmd);
	current = cmd->tokens;
	while (current && current->pos < pos)
	{
		if (current->type == HEREDOC && current->next && current->next->type
			== LIM && current->flag_error == FALSE
			&& current->next->flag_error == FALSE)
			nbr++;
		current = current->next;
	}
	if (current && current->pos == pos && current->pipe_flag == TRUE)
		nbr++;
	return (nbr);
}

/*Fonction qui compte les heredoc*/
static	int	count_heredocs(t_token *tokens)
{
	t_token	*current;
	int		ret;

	if (!tokens)
		return (0);
	current = tokens;
	ret = 0;
	while (current)
	{
		if (current->type == HEREDOC && current->next
			&& current->next->type == LIM && current->flag_error == FALSE
			&& current->next->flag_error == FALSE)
			ret++;
		current = current->next;
	}
	return (ret);
}

/*Fonction qui renvoie le nobre de heredoc pour un input donne*/
int	get_heredocs_nbr(t_command *cmds)
{
	int			ret;
	t_command	*cmd;
	t_token		*token;

	ret = 0;
	cmd = cmds;
	while (cmd)
	{
		token = cmd->tokens;
		while (token)
		{
			if (token->flag_error == TRUE || token->pipe_flag == TRUE)
				break ;
			token = token->next;
		}
		if (token && (token->flag_error == TRUE || token->pipe_flag == TRUE))
			break ;
		ret += count_heredocs(cmd->tokens);
		cmd = cmd->next;
	}
	if (cmd && (token->flag_error == TRUE || token->pipe_flag == TRUE))
		ret += hd_nbr_while_no_error(cmd);
	return (ret);
}
