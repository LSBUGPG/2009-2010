typedef void (*func)(void);
bool init_console(func game);
void console_print(const char *text);
void console_update(void);
void console_draw(void);
char console_get_key(void);
void console_put_key(char key);