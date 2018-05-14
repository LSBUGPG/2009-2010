const int INVADER_ROWS = 5;
const int INVADER_COLUMNS = 11;
const int INVADER_SHOTS = 2;

// +1 for the invisible commander +1 bonus ship
const int INVADER_TOTAL = INVADER_ROWS * INVADER_COLUMNS + INVADER_SHOTS + 2; 

struct Object;

int load_invaders(Object *object_array[]);
bool collide_invaders(int position[], int size[]);
