#include "libft.h"
#include "mlx.h"

int     main(void)
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
	ft_printf("Hello %d MLX!\n", 10);
    mlx_win = mlx_new_window(mlx, 500, 500, "Hello MLX!");
    mlx_loop(mlx);
}