const int INVADER_ROWS = 5;
const int INVADER_COLUMNS = 5;
const int INVADER_SHOTS = 5;

// +1 for the invisible commander
const int INVADER_TOTAL = INVADER_ROWS * INVADER_COLUMNS + INVADER_SHOTS + 1;

struct Object;

void load_invaders(void);
void reset_invaders(void);
Object **add_invaders(Object *object_array[]);
bool collide_invaders(int position[], int size[]);
 