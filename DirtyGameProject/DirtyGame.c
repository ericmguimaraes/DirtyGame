
#include<stdio.h>
#include<stdlib.h>

int respect = 40;

int *pointer_1, *pointer_2, *pointer_3;
char *getCommand(char *action);
int getPlayer(char *action, int *pointer_creatures);
int getPlayerRoom(int *pointer_creatures, int *pointer_rooms);
void look(int *room, int *player);
void clean(int *room, int *player);
void dirty(int *room, int *player);
void move(char *direction, int *room, int *player);

int main()
{
    enum GameState {
        startState,
        mainState,
        gameOverState,
        done
    };

    enum Dirtyness {
        clean = 0,
        halfdirty = 1,
        dirty = 2
    };

    enum GameState currentState = startState;

    int number_rooms, number_creatures;

    int *pointer_rooms, *pointer_creatures;

    while(currentState != done){
        switch(currentState){
            case startState:
                scanf("%d",&number_rooms);
                pointer_rooms = (int *)malloc(sizeof(int)*number_rooms*6);// 0 state, north, south, east, west, crowd
                //read state north south east west for each room
                int i;
                for(i=0; i < number_rooms; i++) {
                        pointer_rooms[i*6 +0] = 0;
                        scanf("%d %d %d %d %d", &pointer_rooms[i*6 +0], &pointer_rooms[i*6 +1], &pointer_rooms[i*6 +2], &pointer_rooms[i*6 +3], &pointer_rooms[i*6 +4]);
                        pointer_rooms[i*6 +5] = 0;
                }
                scanf("%d",&number_creatures);
                //read creature type and location
               pointer_creatures = (int *)malloc(sizeof(int)*number_creatures*2); //type, room
               //creatureType is 0 for the PC, 1 for an animal, 2 for an NPC
                for (i = 0; i < number_creatures; i++){
                    scanf("%d %d", &pointer_creatures[i*2+0], &pointer_creatures[i*2 +1]);
                    pointer_rooms[pointer_creatures[i*2+1]*6+5] = pointer_rooms[pointer_creatures[i*2+1]*6+5] + 1;
                }
                currentState = mainState;
                break;
            case mainState:
                printf("The Game Started");
                char action[10];
                scanf("%s", &action[0]);
                char *command;
                command = (char *)getCommand(action);
                int *player;
                player = (int *)getPlayer(action, pointer_creatures);
                int *player_room;
                player_room = (int *)getPlayerRoom(pointer_creatures, pointer_rooms);
                if (strcmp(*command, "look") == 0){
                    look(player_room, player);
                } else if (strcmp(*command, "clean") == 0){
                    clean(player_room, player);
                } else if (strcmp(*command, "dirty") == 0){
                    dirty(player_room, player);
                } else if (strcmp(*command, "north") == 0){
                    move("north", player_room, player);
                } else if (strcmp(*command, "south") == 0){
                    move("south", player_room, player);
                } else if (strcmp(*command, "east") == 0){
                    move("east", player_room, player);
                } else if (strcmp(*command, "west") == 0){
                    move("west", player_room, player);
                } else if (strcmp(*command, "exit") == 0){
                    currentState=done;
                }
                if(respect<1 || respect>80)
                    currentState=gameOverState;
                break;
            case gameOverState:
                if(respect<1){
                    printf("Shame on you! You lose.");
                } else {
                    printf("Congratulations, you are praised!");
                }
                currentState=done;
                break;
            case done:
                printf("Goodbye!");
            default:
                printf("Current State was not recognized");
        }
    }
    printf("Done");
    return 0;
}

char *getCommand(char *action){

}

int getPlayer(char *action, int *pointer_creatures){

}

int getPlayerRoom(int *pointer_creatures, int *pointer_rooms){

}

void look(int *room, int *player){
    //describe room, numb of creatures, state of room, kind of creatures
}

void clean(int *room, int *player){

}

void dirty(int *room, int *player){

}

void move(char *direction, int *room, int *player){

}



