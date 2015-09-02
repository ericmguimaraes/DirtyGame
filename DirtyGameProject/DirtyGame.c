#include<stdio.h>
#include<stdlib.h>

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
        done
    };

enum Dirtyness {
	clean_state = 0,
	halfdirty_state = 1,
	dirty_state = 2
};

char * getCommand(char *action);
creature_type * getPlayer(char *action);
room_type * getPlayerRoom(creature_type *creature);
void look(room_type *room, creature_type *player);
void clean(room_type *room, creature_type *player);
void dirty(room_type *room, creature_type *player);
void move(char *direction, room_type *room, creature_type *player);
void add_creature(creature_type *creature, room_type *room);

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
                currentState = mainState;
                break;
            case mainState:
                printf("The Game Started");
                char action[5];
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



