#ifndef WORKFLOW_H
#define WORKFLOW_H

#define W_INIT 0
#define W_TITLESCREEN 1
#define W_INGAME 2
#define W_LOSELIFE 3
#define W_GAMEOVER 4
#define W_NEXTLEVEL 5

int w_get();

void w_set(int value);


#endif // WORKFLOW_H
