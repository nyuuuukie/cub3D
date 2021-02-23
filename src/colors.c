int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int add_shade(double dist, int color)
{
	if (dist < 0) dist = 0;
	if (dist > 1) dist = 1;
	return ((color & 0x00FFFFFF) | ((int)((1 - dist) * 0xFF) << 24));
}

int	get_opposite(int color)
{
	return (~color - 1);
}


int main(void)
{
	int t = 255;
	int r = 255;
	int g = 255;
	int b = 127;
	int trgb = create_trgb(t, r, g, b);
	printf("%x\n", trgb);
	printf("%x\n", get_opposite(get_opposite(trgb)));
}