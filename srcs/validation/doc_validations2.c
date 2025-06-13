#include "cub3D.h"

void validate_player_dir(t_instance *inst, int fd)
{
    int hor;
    int ver;
    int player_encountered;
    int encountered_dir;

    printf("VALIDATING PLAYER DIR");
    encountered_dir = 0;
    player_encountered = 0;
    ver = 0;
    while (ver < inst->map.vertical_size)
    {
        hor = 0;
        while (hor < inst->map.horizontal_size)
        {
            encountered_dir = inst->map.map_layout[ver][hor] >= NORTH + STAGING;
            printf("PASSING Horizontal\n");
            printf("Encountered Dir: %d | Player Enc: %d\n", encountered_dir, player_encountered);
            if (encountered_dir && player_encountered == 0)
                player_encountered = 1;
            else if (encountered_dir && player_encountered == 1)
                put_error("DUPLICATED PLAYER POSITION\n", &inst, fd);
            hor++;
        }
        ver++;
    }
    
}