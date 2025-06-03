/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:01:13 by machouba          #+#    #+#             */
/*   Updated: 2024/08/07 15:23:33 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_stat(t_data *data)
{
	data->exit_return = 2;
}

static int	firstcheck(t_data *context, t_token *current_token)
{
	if (current_token->next == NULL && ft_isop(current_token->value) == FALSE
		&& current_token->type != PIPE)
		return (FALSE);
	if (ft_isop(current_token->value) == TRUE && current_token->next
		&& ft_isop(current_token->next->value) == TRUE)
		return (error_token(current_token, current_token->next->type),
			exit_stat(context), TRUE);
	if (ft_isop(current_token->value) == TRUE && current_token->next == NULL)
		return (error_token(current_token, NEWLINE_ERROR), exit_stat(context),
			TRUE);
	return (SKIP);
}

static int	error_detected(t_data *data, t_token *token_list,
		t_token *current_token)
{
	int	return_value;

	if (!token_list || !current_token)
		return (FALSE);
	return_value = firstcheck(data, current_token);
	if (return_value != SKIP)
		return (return_value);
	if (current_token->type == PIPE)
	{
		return_value = check_pipe_errors(data, current_token);
		if (return_value)
			return (return_value);
	}
	if (ft_isop(current_token->value) == TRUE && current_token->next != NULL
		&& current_token->next->type == PIPE)
		return (error_token(current_token, current_token->next->type),
			exit_stat(data), TRUE);
	if (ft_isoperator(current_token->value) >= 1 && current_token->next == NULL)
		return (error_token(current_token, NEWLINE_ERROR), exit_stat(data),
			TRUE);
	return (FALSE);
}

static int	double_pipe(t_data *data, t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
			return (exit_stat(data), TRUE);
		token = token->next;
	}
	return (FALSE);
}

int	token_checker(t_data *data, t_token *lst)
{
	t_token	*current;
	t_token	*last;

	current = lst;
	if (!current)
		return (1);
	last = findlast_token(lst);
	if (double_pipe(data, current) == TRUE)
		return (ft_print_err(DOUBLE_PIPE_ERROR), FAIL);
	if (current->value && current->value[0] == '|')
		return (ft_print_err(PIPE), exit_stat(data), FAIL);
	while (current)
	{
		if (error_detected(data, lst, current) == TRUE)
			break ;
		current = current->next;
	}
	if (current)
	{
		if (last->type == PIPE)
			return (error_token(token_before_last(lst), PIPE_AT_END), SUCCESS);
	}
	return (1);
}
