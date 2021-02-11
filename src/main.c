/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 18:46:26 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/11 22:10:00 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_error(char *title, char *msg)
{
	write(2, title, ft_strlen(title));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

char*	get_map_error(int code)
{
	const int n = 10; //Cannot use const due to norm error
	static char* errors[n];

	errors[0] = "Unknown error";
	errors[1] = "Bad extension of map";
	errors[2] = "No such file or directory";
	errors[3] = "";
	errors[4] = "";
	errors[5] = "";
	errors[6] = "";
	errors[7] = "";
	errors[7] = "";
	errors[8] = "";
	errors[9] = "";
	
	code = (code < 1 && code > n - 1) ? 0 : code;
	return (errors[code]);
}

int link_start()
{
	return (0);
}

int make_screen()
{
	return (0);
}

int main(int argc, char **argv)
{
	int code;

	if (argc == 2 || argc == 3)
	{
		if ((code = check_map_arg(argv[1])))
			print_error("Argument error: ", get_map_error(code));
		else if (argc == 3)
		{
			if (check_save_arg(argv[2]))
				print_error("Argument error: ", "Invalid flag");
			else
				make_screen();
		}
		else
			link_start();
	}
	else
		print_error("Argument error: ", "Invalid number of arguments");
	return (0);
}