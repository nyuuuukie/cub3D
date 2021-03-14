


int main()
{
	int color = color_trgb(256, 12, 32, 75);
	int trgb = 0x007faabb;
	printf("t:%d\n", color_get_t(trgb));
	printf("r:%d\n", color_get_r(trgb));
	printf("g:%d\n", color_get_g(trgb));
	printf("b:%d\n", color_get_b(trgb));
	printf("t:%d\n", color_get_t(color));
	printf("r:%d\n", color_get_r(color));
	printf("g:%d\n", color_get_g(color));
	printf("b:%d\n", color_get_b(color));
	return (0);
}