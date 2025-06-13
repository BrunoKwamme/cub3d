#!/bin/bash
maps=(
	"srcs/maps/bad/color_invalid_rgb.cub"
	"srcs/maps/bad/color_missing_ceiling_rgb.cub"
	"srcs/maps/bad/color_missing.cub"
	"srcs/maps/bad/color_missing_floor_rgb.cub"
	"srcs/maps/bad/color_none.cub"
	"srcs/maps/bad/empty.cub"
	"srcs/maps/bad/file_letter_end.cub"
	"srcs/maps/bad/filetype_missing"
	"srcs/maps/bad/filetype_wrong.buc"
	"srcs/maps/bad/forbidden.cub"
	"srcs/maps/bad/map_first.cub"
	"srcs/maps/bad/map_middle.cub"
	"srcs/maps/bad/map_missing.cub"
	"srcs/maps/bad/map_only.cub"
	"srcs/maps/bad/map_too_small.cub"
	"srcs/maps/bad/player_multiple.cub"
	"srcs/maps/bad/player_none.cub"
	"srcs/maps/bad/player_on_edge.cub"
	"srcs/maps/bad/textures_dir.cub."
	"srcs/maps/bad/textures_duplicates.cub"
	"srcs/maps/bad/textures_forbidden.cub"
	"srcs/maps/bad/textures_invalid.cub"
	"srcs/maps/bad/textures_missing.cub"
	"srcs/maps/bad/textures_none.cub"
	"srcs/maps/bad/textures_not_xpm.cub"
	"srcs/maps/bad/wall_hole_east.cub"
	"srcs/maps/bad/wall_hole_north.cub"
	"srcs/maps/bad/wall_hole_south.cub"
	"srcs/maps/bad/wall_hole_west.cub"
	"srcs/maps/bad/wall_none.cub"
)
bla=1
for item in "${maps[@]}"; do
   # ./cub3D "$item" | grep "map is" > log_"$bla" && ./cub3D "$item" ; echo $? >> log_"$bla"
   	mapname=$(basename "$item")
	./cub3D "$item" | grep "map is" > "logs/log_$mapname" && ./cub3D "$item"; status=$?; if [ "$status" -eq 2 ]; then echo -e "Validação deu certo\t" >> "logs/log_$mapname"; elif [ "$status" -eq 0 ]; then echo -e "Validação deu errado\t" >> "logs/err_log_$mapname"; else echo "Código de saída: $status" >> "logs/att_log_$mapname"; fi
	((bla++))

done
