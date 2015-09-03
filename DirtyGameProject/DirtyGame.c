#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    int type;
	int room;
	int deleted;
} creature_type;

typedef struct {
	int id;
    int state;
    int north;
    int south;
    int east;
    int west;
    creature_type* creatures[10];
} room_type;

enum GameState {
        startState,
        mainState,
        gameOverState,
        exitState,
        done
    };

enum Dirtyness {
	clean_state = 0,
	halfdirty_state = 1,
	dirty_state = 2
};

char * getCommand(char * action);
creature_type * getPlayer(char *action, int number_creatures);
room_type * getPlayerRoom(creature_type *creature, int number_rooms);
void look(room_type *room, creature_type *player);
void clean(room_type *room, creature_type *player);
void dirty(room_type *room, creature_type *player);
void move(char *direction, room_type *room, creature_type *player);
void add_creature(creature_type *creature, room_type *room);
creature_type * getPC(int number_creatures);
room_type * findRoomById(int id, int number_rooms);
creature_type * findCreatureById(int id_creature, int number_creatures);

int respect = 40;
room_type *pointer_rooms;
creature_type *pointer_creatures;

int main()
{
    enum GameState currentState = startState;

	int number_rooms, number_creatures;

    while(currentState != done){
        switch(currentState){
            case startState:
                scanf("%d",&number_rooms);
                pointer_rooms = (room_type *)malloc(sizeof(room_type)*number_rooms);
                //read state north south east west for each room
                int i;
                for(i=0; i < number_rooms; i++) {
						pointer_rooms[i].id = i;
                        scanf("%d %d %d %d %d", &pointer_rooms[i].state, &pointer_rooms[i].north, &pointer_rooms[i].south, &pointer_rooms[i].east, &pointer_rooms[i].west);
                }
                scanf("%d",&number_creatures);
                //read creature type and location
				pointer_creatures = (creature_type *)malloc(sizeof(creature_type)*number_creatures);
				//creatureType is 0 for the PC, 1 for an animal, 2 for an NPC
                for (i = 0; i < number_creatures; i++){
					pointer_creatures[i].id = i;
					pointer_creatures[i].deleted = 0;
                    scanf("%d %d", &pointer_creatures[i].type, &pointer_creatures[i].room);
					add_creature(&pointer_creatures[i], &pointer_rooms[pointer_creatures[i].room]);
                }
                printf("The Game Started \n");
                currentState = mainState;
                break;
            case mainState:
                ; //to avoid error: a label can only be part of a statement and a declaration is not a statement
                char action[10];
                scanf("%s", &action[0]);
                char *command;
                command = getCommand(action);
                printf(command);
                printf("\n");
                creature_type *player;
                player = (creature_type *)getPlayer(action, number_creatures);
                room_type *player_room;
                player_room = (room_type *)getPlayerRoom(player, number_rooms);
                if (strcmp(command, "look") == 0){
                    look(player_room, player);
                } else if (strcmp(command, "clean") == 0){
                    clean(player_room, player);
                } else if (strcmp(command, "dirty") == 0){
                    dirty(player_room, player);
                } else if (strcmp(command, "north") == 0){
                    move("north", player_room, player);
                } else if (strcmp(command, "south") == 0){
                    move("south", player_room, player);
                } else if (strcmp(command, "east") == 0){
                    move("east", player_room, player);
                } else if (strcmp(command, "west") == 0){
                    move("west", player_room, player);
                } else if (strcmp(command, "exit") == 0){
                    currentState=exitState;
                }
                if(respect<1 || respect>80)
                    currentState=gameOverState;
                break;
            case gameOverState:
                if(respect<1){
                    printf("Shame on you! You lose. \n");
                } else {
                    printf("Congratulations, you are praised! \n");
                }
                currentState=done;
                break;
            case exitState:
                printf("DO STUFF BEFORE CLOSE GAME! \n");
                currentState=done;
                break;
            case done:
                break;
            default:
                printf("Current State was not recognized \n");
        }
    }
    printf("Good Bye! \n");
    return 0;
}

char * getCommand(char * action){
    char * result;
    if (isdigit(action[0])) {
        int i;
        for(i=0;i<strlen(action);i++){
            if(isalpha(action[i])){
                result = malloc(sizeof(char) * (strlen(action)-i+1));
                strncpy(result, action+i, strlen(action)-i);
                result[(strlen(action)-i)] = 0;
                break;
            }
        }
    } else {
        result=action;
    }
    return result;
};

creature_type * getPC(int number_creatures){
    int i;
    for(i=0; i<number_creatures; i++){
        if(pointer_creatures[i].type==0){
            return &pointer_creatures[i];
        }
    }
    return NULL;
};

creature_type * findCreatureById(int id_creature, int number_creatures){
    int i;
    for(i=0;i<number_creatures;i++){
        if(pointer_creatures[i].id==id_creature){
            return &pointer_creatures[i];
        }
    }
    return NULL;
}

creature_type * getPlayer(char *action, int number_creatures){
    if (isdigit(action[0])) {
        int i, id_creature;
        char * c;
        for(i=0;i<strlen(action);i++){
            if(!isdigit(action[i])){
                c = malloc(sizeof(char) * (i+1));
                strncpy(c, action, i+1);
                c[(i+1)] = 0;
                break;
            }
        }
        sscanf(c, "%d", &id_creature);
        return findCreatureById(id_creature, number_creatures);
    } else {
        return getPC(number_creatures);
    }
};

room_type * findRoomById(int id, int number_rooms){
    int i;
    for(i=0;i<number_rooms;i++){
        if(pointer_rooms[i].id==id){
            return &pointer_rooms[i];
        }
    }
    return NULL;
}

room_type * getPlayerRoom(creature_type *creature, int number_rooms){
    return findRoomById(((creature_type) *creature).room,number_rooms);
};

void look(room_type *room, creature_type *player){

};

void add_creature(creature_type *creature, room_type *room){

};

void remove_creature(creature_type *creature, room_type *room){

};

void move(char *direction, room_type *room, creature_type *player){
    printf("funcionou \n");
};

void clean(room_type *room, creature_type *player){

};

void dirty(room_type *room, creature_type *player){

};
