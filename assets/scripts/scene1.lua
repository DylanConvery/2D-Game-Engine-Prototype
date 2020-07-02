local time = os.date("*t").hour
local map_texture = "terrain-texture-day"
if time > 9 and time < 21 then
    map_texture = "terrain-texture-day"
else 
    map_texture = "terrain-texture-night"
end

scene1 = {
	    assets = {
        [0] = { type="texture", id = "terrain-texture-day", file = "./assets/tilemaps/jungle.png" },
        [1] = { type="texture", id = "terrain-texture-night", file = "./assets/tilemaps/jungle-night.png" },
        [2] = { type="texture", id = "chopper-texture", file = "./assets/images/chopper-spritesheet.png" },
        [3] = { type="texture", id = "projectile-texture", file = "./assets/images/bullet-enemy.png" },
        [4] = { type="texture", id = "obstacles-texture", file = "./assets/images/obstacles.png" },
        [5] = { type="texture", id = "truck-left-texture", file = "./assets/images/truck-left.png" },
        [6] = { type="texture", id = "truck-right-texture", file = "./assets/images/truck-right.png" },
        [7] = { type="texture", id = "truck-down-texture", file = "./assets/images/truck-down.png" },
        [8] = { type="texture", id = "tank-big-down-texture", file = "./assets/images/tank-big-down.png" },
        [9] = { type="texture", id = "tank-big-left-texture", file = "./assets/images/tank-big-left.png" },
        [10] = { type="texture", id = "tank-big-right-texture", file = "./assets/images/tank-big-right.png" },
        [11] = { type="texture", id = "tank-small-left-texture", file = "./assets/images/tank-small-left.png" },
        [12] = { type="texture", id = "tank-small-right-texture", file = "./assets/images/tank-small-right.png" },
        [13] = { type="texture", id = "army-group-1-texture", file = "./assets/images/army-group-1.png" },
        [14] = { type="texture", id = "army-group-2-texture", file = "./assets/images/army-group-2.png" },
        [15] = { type="texture", id = "army-group-3-texture", file = "./assets/images/army-group-3.png" },
        [16] = { type="texture", id = "rock-big-1-texture", file = "./assets/images/rock-big-1.png" },
        [17] = { type="texture", id = "rock-big-2-texture", file = "./assets/images/rock-big-2.png" },
        [18] = { type="texture", id = "rock-big-3-texture", file = "./assets/images/rock-big-3.png" },
        [19] = { type="texture", id = "rock-big-4-texture", file = "./assets/images/rock-big-4.png" },
        [20] = { type="texture", id = "rock-small-1-texture", file = "./assets/images/rock-small-1.png" },
        [21] = { type="texture", id = "tree-small-1-texture", file = "./assets/images/tree-small-1.png" },
        [22] = { type="texture", id = "tree-small-2-texture", file = "./assets/images/tree-small-2.png" },
        [23] = { type="texture", id = "tree-small-3-texture", file = "./assets/images/tree-small-3.png" },
        [24] = { type="texture", id = "tree-small-4-texture", file = "./assets/images/tree-small-4.png" },
        [25] = { type="texture", id = "tree-small-5-texture", file = "./assets/images/tree-small-5.png" },
        [26] = { type="texture", id = "tree-small-6-texture", file = "./assets/images/tree-small-6.png" },
        [27] = { type="texture", id = "tree-small-7-texture", file = "./assets/images/tree-small-7.png" },
        [28] = { type="texture", id = "tree-small-8-texture", file = "./assets/images/tree-small-8.png" },
        [29] = { type="texture", id = "start-texture", file = "./assets/images/start.png" },
        [30] = { type="texture", id = "heliport-texture", file = "./assets/images/heliport.png" },
        [31] = { type="texture", id = "bullet-friendly-texture", file = "./assets/images/bullet-friendly.png" },
        [32] = { type="texture", id = "radar-texture", file = "./assets/images/radar.png" },
        [33] = { type="sound", id = "blades-sound", file = "./assets/sounds/blades.wav" },
        [33] = { type="font", id = "charriot-font", file = "./assets/fonts/charriot.ttf", size = 14 }
    },
	map = {
        texture_id = map_texture,
        scale = 2,
        tile_size = 32,
        file = "./assets/tilemaps/jungle.map", 
        width = 25, 
        height = 20
    },
	entities = {
        [0] = {
            name = "player",
            layer = 4,
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
                    asset_texture_id = "chopper-texture",
                    animated = true,
                    frames = 2,
                    speed = 90,
                    directed = true,
                    fixed = false
                },
                input = {
                    speed = 150,
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
            name = "helipad",
            layer = 3,
            components = {
                transform = {
                    x = 1395,
                    y = 495,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "heliport-texture",
                    animated = false,
                },
                collider = {
                    tag = "TARGET"
                }
            }
        },
        [2] = {
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
                    asset_texture_id = "radar-texture",
                    animated = true,
                    frames = 8,
                    speed = 150,
                    directed = false,
                    fixed = true
                },
            }
        },
        [3] = {
            name = "fps_label",
            layer = 6,
            components = {
                label = {
                    x = 10,
                    y = 10,
                    text = " ",
                    font = "charriot-font",
                    color = {
                        r = 255,
                        g = 255,
                        b = 255,
                        a = 255
                    }
                },
            }
        },
        [4] = {
            name = "start",
            layer = 3,
            components = {
                transform = {
                    x = 240,
                    y = 115,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "start-texture",
                    animated = false
                }
            }
        },
        [5] = {
            name = "tank_1",
            layer = 2,
            components = {
                transform = {
                    x = 650,
                    y = 405,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-big-left-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 180,
                    loop = true
                }
            }
        },
        [6] = {
            name = "tank_2",
            layer = 2,
            components = {
                transform = {
                    x = 660,
                    y = 535,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-big-down-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 90,
                    loop = true
                }
            }
        },
        [7] = {
            name = "tank_3",
            layer = 2,
            components = {
                transform = {
                    x = 470,
                    y = 390,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-small-right-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 0,
                    loop = true
                }
            }
        },
        [8] = {
            name = "tank_4",
            layer = 2,
            components = {
                transform = {
                    x = 203,
                    y = 1088,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-big-right-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 0,
                    loop = true
                }
            }
        },
        [9] = {
            name = "tank_5",
            layer = 2,
            components = {
                transform = {
                    x = 115,
                    y = 760,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-small-right-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 0,
                    loop = true
                }
            }
        },
        [10] = {
            name = "tank_6",
            layer = 2,
            components = {
                transform = {
                    x = 515,
                    y = 665,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-small-left-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 180,
                    loop = true
                }
            }
        },
        [11] = {
            name = "tank_7",
            layer = 2,
            components = {
                transform = {
                    x = 920,
                    y = 160,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-big-down-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 90,
                    loop = true
                }
            }
        },
        [12] = {
            name = "tank_8",
            layer = 2,
            components = {
                transform = {
                    x = 1120,
                    y = 525,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tank-small-right-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 0,
                    loop = true
                }
            }
		},
		[13] = {
            name = "truck_1",
            layer = 2,
            components = {
                transform = {
                    x = 243,
                    y = 497,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "truck-right-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 270,
                    loop = true
                }
            }
		},
		[14] = {
            name = "truck_2",
            layer = 2,
            components = {
                transform = {
                    x = 111,
                    y = 993,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "truck-down-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 90,
                    loop = true
                }
            }
		},
		[15] = {
            name = "truck_3",
            layer = 2,
            components = {
                transform = {
                    x = 760,
                    y = 200,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "truck-left-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 180,
                    loop = true
                }
            }
		},
		[16] = {
            name = "truck_4",
            layer = 2,
            components = {
                transform = {
                    x = 1361,
                    y = 222,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "truck-down-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 90,
                    loop = true
                }
            }
		},
		[17] = {
            name = "truck_5",
            layer = 2,
            components = {
                transform = {
                    x = 1220,
                    y = 760,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "truck-right-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 270,
                    loop = true
                }
            }
        },
        [18] = {
            name = "truck_6",
            layer = 2,
            components = {
                transform = {
                    x = 1170,
                    y = 790,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "truck-right-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = 270,
                    loop = true
                }
            }
        },
        [19] = {
            name = "army_1",
            layer = 2,
            components = {
                transform = {
                    x = 460,
                    y = 445,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "army-group-1-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = math.random(360),
                    loop = true
                }
            }
        },
        [20] = {
            name = "army_2",
            layer = 2,
            components = {
                transform = {
                    x = 645,
                    y = 787,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "army-group-2-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = math.random(360),
                    loop = true
                }
            }
        },
        [21] = {
            name = "army_3",
            layer = 2,
            components = {
                transform = {
                    x = 645,
                    y = 740,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "army-group-3-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = math.random(360),
                    loop = true
                }
            }
        },
        [22] = {
            name = "army_4",
            layer = 2,
            components = {
                transform = {
                    x = 881,
                    y = 482,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 32,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "army-group-1-texture",
                    animated = false,
                },
                collider = {
                    tag = "ENEMY"
                },
                projectile_emitter = {
                    asset_texture_id = "projectile-texture",
                    width = 4,
                    height = 4,
                    speed = 200,
                    range = 500,
                    angle = math.random(360),
                    loop = true
                }
            }
        },
        [23] = {
            name = "tree_1",
            layer = 1,
            components = {
                transform = {
                    x = 700,
                    y = 380,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false,
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [24] = {
            name = "tree_2",
            layer = 1,
            components = {
                transform = {
                    x = 680,
                    y = 365,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false,
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [25] = {
            name = "tree_3",
            layer = 1,
            components = {
                transform = {
                    x = 200,
                    y = 480,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false,
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [26] = {
            name = "tree_4",
            layer = 1,
            components = {
                transform = {
                    x = 310,
                    y = 490,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 18,
                    height = 32,
                    scale = 1,
                },
                sprite = {
                    asset_texture_id = "tree-small-4-texture",
                    animated = false,
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [27] = {
            name = "tree_5",
            layer = 1,
            components = {
                transform = {
                    x = 295,
                    y = 495,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 18,
                    height = 22,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-4-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [28] = {
            name = "tree_6",
            layer = 1,
            components = {
                transform = {
                    x = 370,
                    y = 480,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 18,
                    height = 22,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-4-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [29] = {
            name = "tree_7",
            layer = 1,
            components = {
                transform = {
                    x = 214,
                    y = 982,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [30] = {
            name = "tree_8",
            layer = 1,
            components = {
                transform = {
                    x = 182,
                    y = 943,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [31] = {
            name = "tree_9",
            layer = 1,
            components = {
                transform = {
                    x = 86,
                    y = 1064,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [32] = {
            name = "tree_10",
            layer = 1,
            components = {
                transform = {
                    x = 171,
                    y = 492,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-8-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [33] = {
            name = "tree_11",
            layer = 1,
            components = {
                transform = {
                    x = 1020,
                    y = 103,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-8-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [34] = {
            name = "tree_12",
            layer = 1,
            components = {
                transform = {
                    x = 1117,
                    y = 100,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-7-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [35] = {
            name = "tree_13",
            layer = 1,
            components = {
                transform = {
                    x = 1130,
                    y = 115,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-7-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [36] = {
            name = "tree_14",
            layer = 1,
            components = {
                transform = {
                    x = 1270,
                    y = 190,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-7-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [37] = {
            name = "tree_15",
            layer = 1,
            components = {
                transform = {
                    x = 1280,
                    y = 205,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-7-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [38] = {
            name = "tree_16",
            layer = 1,
            components = {
                transform = {
                    x = 1060,
                    y = 745,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-7-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [39] = {
            name = "tree_17",
            layer = 1,
            components = {
                transform = {
                    x = 1075,
                    y = 760,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [40] = {
            name = "tree_18",
            layer = 1,
            components = {
                transform = {
                    x = 1090,
                    y = 760,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-6-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [41] = {
            name = "tree_19",
            layer = 1,
            components = {
                transform = {
                    x = 1285,
                    y = 173,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-7-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [42] = {
            name = "tree_20",
            layer = 1,
            components = {
                transform = {
                    x = 1036,
                    y = 93,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "tree-small-8-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [43] = {
            name = "rock_1",
            layer = 1,
            components = {
                transform = {
                    x = 360,
                    y = 450,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 24,
                    height = 24,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "rock-big-2-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [44] = {
            name = "rock_2",
            layer = 1,
            components = {
                transform = {
                    x = 450,
                    y = 380,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 16,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "rock-small-1-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [45] = {
            name = "rock_3",
            layer = 1,
            components = {
                transform = {
                    x = 435,
                    y = 400,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 16,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "rock-small-1-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [46] = {
            name = "rock_4",
            layer = 1,
            components = {
                transform = {
                    x = 115,
                    y = 637,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 16,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "rock-small-1-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [47] = {
            name = "rock_5",
            layer = 1,
            components = {
                transform = {
                    x = 124,
                    y = 660,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 16,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "rock-small-1-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        },
        [48] = {
            name = "rock_6",
            layer = 1,
            components = {
                transform = {
                    x = 116,
                    y = 827,
                    velocity_x = 0,
                    velocity_y = 0,
                    width = 16,
                    height = 16,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    asset_texture_id = "rock-small-1-texture",
                    animated = false
                },
                collider = {
                    tag = "VEGETATION"
                }
            }
        }
	}
}