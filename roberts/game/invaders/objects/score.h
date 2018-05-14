const int SCORE_TOTAL = 1; // only 1 Score object

struct Object;
void load_score(void);
Object **add_score(Object **object_array);
void add_points(int score);
void reset_score(void);