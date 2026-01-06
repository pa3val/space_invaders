global_states = {
    enemies = {
        enemy_shoot_chance = 5,
        basic_enemy = {
            enemy_movement_delay = 50,
            enemy_shoot_delay = 10,
            enemy_max_bullets = 2,
            health = 1,
            score = 100,
            appearance = {
                { '(', '0', '.', '0', ')' }
            },
            enemy_bullet_appearance = {
                { '*' }
            }
        }
    },

    player = {
        player_shoot_delay = 20,
        player_max_bullets = 10,
        health = 3,
        player_appearance = {
            { '/', '_', 'T', '_', '\\' }
        },
        player_bullet_appearance = {
            { '|' }
        }
    }
}

colors = {
    ALIEN_COLOR = "#7CFC00",
    PLAYER_COLOR = "#FF0000",
    PLAYER_BULLET_COLOR = "#FF0000",
    ENEMY_BULLET_COLOR = "#ADFF2F",
    BORDER_COLOR = "#191970",
    TEXT_COLOR = "#FFFFFF",
    SELECTED_TEXT_COLOR = "#FFFFFF"
}

sounds = {
    PLAYER_SHOOT_SOUND = "sounds/shoot.mp3",
    ENEMY_SHOOT_SOUND = "sounds/enemy_shoot.mp3",
    BACKGROUND_MUSIC = "sounds/background.mp3"
}

levels_queue = {
    { "regrg",   "rggrg" },
    { "rergerg", "ergeg" }
}
