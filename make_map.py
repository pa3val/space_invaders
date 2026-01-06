#P - player
#E - basic enemy
#. - empty
#* - border

HEIGHT = 26
WIDTH = 78
BORDER_SIZE = 1
ENTITY_WIDTH = 5
ENTITY_HEIGHT = 1
ENTITY_SPACE = 2
ENEMY_COUNT = 4
ENEMY_ROW = 1

enemy_space = ENTITY_WIDTH * ENEMY_COUNT + ENTITY_SPACE * (ENEMY_COUNT - 1)
border_space = (WIDTH - 2 * BORDER_SIZE - enemy_space) // 2

enemy_positions = [border_space + i * (ENTITY_WIDTH + ENTITY_SPACE) for i in range(ENEMY_COUNT)]

file = open("levels/level_1.txt", "w")

for y in range(HEIGHT):
    for x in range(WIDTH):
        if y == 0 or y == HEIGHT - 1 or x == 0 or x == WIDTH - 1:
            file.write('*')
        elif y == ENEMY_ROW and x in enemy_positions:
            file.write('E')
        else:
            file.write('.')
    file.write('\n')
file.close()