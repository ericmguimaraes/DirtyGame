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

enum Dirtyness {
	clean_state = 0,
	halfdirty_state = 1,
	dirty_state = 2
};

typedef struct {
	int id;
    enum Dirtyness state;
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
void initCreaturesInRooms(int number_rooms);

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
						int state_int;
                        scanf("%d %d %d %d %d", &state_int, &pointer_rooms[i].north, &pointer_rooms[i].south, &pointer_rooms[i].east, &pointer_rooms[i].west);
                        pointer_rooms[i].state = state_int;
                }
                scanf("%d",&number_creatures);
                //read creature type and location
				pointer_creatures = (creature_type *)malloc(sizeof(creature_type)*number_creatures);
				initCreaturesInRooms(number_rooms);
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
                } else if (strcmp(command, "unit-tests") == 0) {
					//TODO unitTests();
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
    printf("Goodbye! \n");
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

char* roomStateToString(enum Dirtyness state)
{
   switch (state)
   {
      case clean_state: return "clean";
      case halfdirty_state: return "half-dirty";
	  case dirty_state: return "dirty";
   }
   return NULL;
}

//sample content
//Room 0, half-dirty, neighbors 1 to the south 2 to the west, contains:
//animal 0
//PC
//human 2
void look(room_type *room, creature_type *player){
	int room_number = ((room_type) *room).id;
	char* state = roomStateToString(((room_type) *room).state);
	printf("Room %d, %s, neighbors ",room_number,state);
	int counter = 0;
	if(((room_type) *room).north != -1){
		printf("%d to the north, ",((room_type) *room).north);
		counter++;
	}
	if(((room_type) *room).south != -1){
		printf("%d to the south, ",((room_type) *room).south);
		counter++;
	}
	if(((room_type) *room).east != -1){
		printf("%d to the east, ",((room_type) *room).east);
		counter++;
	}
	if(((room_type) *room).west != -1){
		printf("%d to the west, ",((room_type) *room).west);
		counter++;
	}
	if(counter==0){
		printf(": none, ");
	}
	printf("contains: \n");
	int animal = 0 , pc = 0 , npc = 0, i ;
	for(i=0; i < 10; i++){
	 //   printf("%d\n",i);
        if(room->creatures[i] != NULL){
            if(room->creatures[i]->type == 0){
                pc++;
            }
            if(room->creatures[i]->type == 1){
                animal++;
            }
            if(room->creatures[i]->type == 2){
                npc++;
            }
        }
	}
	printf("animal: %d \n",animal);
	printf("PC: %d \n",pc);
	printf("npc: %d \n",npc);
};

void initCreaturesInRooms(int number_rooms){
    int i, j;
    for(i=0;i<number_rooms;i++){
        for(j=0;j<number_rooms;j++){
            pointer_rooms[i].creatures[j] = malloc(sizeof(creature_type));
        }
    }
}

void add_creature(creature_type *creature, room_type *room){
    printf("creature type %d",creature->type);
    int i;
    for(i=0; i < 10; i++){
        if(room->creatures[i] == NULL){ //TODO after verify it in the right way it is good to go
            printf("add creature %d\n", i);
            room->creatures[i] = creature;
            break;
        }
    }
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
