scene1 = {
	assets = {
        [0] = { 
            type="texture", 
            id = "terrain-texture-day", 
            file = "./assets/tilemaps/jungle.png"
        },
        [1] = { 
        },
		[2] = {
            type = "texture",
            id = "tank",
            file = "./assets/images/tank-big-right.png"
        },
		[3] = {
            type = "texture",
            id = "chopper_spritesheet",
            file = "./assets/images/chopper-spritesheet.png"
        },
		[4] = {
            type = "texture",
            id = "radar",
            file = "./assets/images/radar.png"
        },
		[5] = {
            type = "texture",
            id = "jungle_tilemap",
            file = "./assets/tilemaps/jungle.png"
        },
		[5] = {
            type = "texture",
            id = "helipad",
            file = "./assets/images/heliport.png"
        },
		[6] = {
            type = "texture",
            id = "bounding_box", 
            file = "./assets/images/collision-texture.png"
        },
		[7] = {
            type = "texture",
            id = "projectile", 
            file = "./assets/images/bullet-enemy.png"
        },
		[8] = {
            type = "font",
            id = "charriot", 
            file = "./assets/fonts/charriot.ttf", 
            size = 16
        },    
    },
	map = {
        texture_id = "terrain-texture-day",
        scale = 2,
        tile_size = 32,
        file = "./assets/tilemaps/jungle.map", 
        width = 25, 
        height = 20
    },
	entities = {
        [0] = {
            name = "player",
            layer = 3,
            components = {
                transform = {
                    x = 240,
                    y = 106,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "chopper_spritesheet",
                    animated = true,
                    frames = 2,
                    speed = 90,
                    directed = true,
                    fixed = false
                },
                input = {
                    speed = 200,
                    keyboard = {
                        up = "w",
                        left = "a",
                        down = "s",
                        right = "d",
                        shoot = "space"
                    }
                },
                collider = {
                    tag = "PLAYER"
                }
            }
        },
        [1] = {
            name = "tank_1",
            layer = 2,
            components = {
                transform = {
                    x = 150,
                    y = 495,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile",
                    width = 4,
                    height = 4,
                    speed = 70,
                    range = 300,
                    angle = 180,
                    loop = true
                }
            }
        },
        [2] = {
            name = "helipad",
            layer = 5,
            components = {
                transform = {
                    x = 470,
                    y = 420,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "helipad",
                    animated = false,
                },
                collider = {
                    tag = "TARGET"
                }
            }
        },
        [3] = {
            name = "radar",
            layer = 6,
            components = {
                transform = {
                    x = 720,
                    y = 15,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 64,
                    height = 64,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "radar",
                    animated = true,
                    frames = 8,
                    speed = 150,
                    directed = false,
                    fixed = true
                },
            }
        },
        [4] = {
            name = "fps_label",
            layer = 6,
            components = {
                label = {
                    x = 10,
                    y = 10,
                    text = " ",
                    font = "charriot",
                    color = {
                        r = 255,
                        g = 255,
                        b = 255,
                        a = 255
                    }
                },
            }
        },
	}
}