
void	arr_print(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd("|", 1);
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("|", 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}