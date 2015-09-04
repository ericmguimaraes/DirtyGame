#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    int type; //creatureType is 0 for the PC, 1 for an animal, 2 for an NPC
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

char * getCommand(char * action);
creature_type * getPlayer(char *action, int number_creatures);
room_type * getPlayerRoom(creature_type *creature, int number_rooms);
void look(room_type *room, creature_type *player);
void clean(room_type *room, creature_type *player);
void dirty(room_type *room, creature_type *player);
int move(room_type *origin_room, room_type *destination_room, creature_type *player);
int add_creature(creature_type *creature, room_type *room);
creature_type * getPC(int number_creatures);
room_type * findRoomById(int id, int number_rooms);
creature_type * findCreatureById(int id_creature, int number_creatures);
void initCreaturesInRooms(int number_rooms);
void creature_drill_hole(creature_type *creature, room_type *room);
int reaction(int action, room_type *room, creature_type *player);
int calculate_creature_reaction(int action, creature_type *creature);
void creature_react(int respect_change, creature_type *creature);
void check_creatures_reaction(int action, room_type *room, creature_type *player);
void move_sad_creatures(room_type *room);
int creature_can_not_stay(int creature_type, int state);

int respect = 40;
room_type *pointer_rooms;
creature_type *pointer_creatures;
creature_type *deleted_creature;

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
                    move(findRoomById(player_room->north, number_rooms), player_room, player);
                } else if (strcmp(command, "south") == 0){
                    move(findRoomById(player_room->south, number_rooms), player_room, player);
                } else if (strcmp(command, "east") == 0){
                    move(findRoomById(player_room->east, number_rooms), player_room, player);
                } else if (strcmp(command, "west") == 0){
                    move(findRoomById(player_room->west, number_rooms), player_room, player);
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

char* roomStateToString(int state)
{
   switch (state)
   {
      case 0: return "clean";
      case 1: return "half-dirty";
	  case 2: return "dirty";
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
	int i ;
	for(i=0; i < 10; i++){
        if(!room->creatures[i]->deleted){
            if(room->creatures[i]->type == 0){
                printf("PC\n");
            } else if(room->creatures[i]->type == 1){
                printf("animal %d \n",room->creatures[i]->id);
            } else if(room->creatures[i]->type == 2){
                printf("human %d \n",room->creatures[i]->id);
            }
        } else {
            break;
        }
	}
};

void initCreaturesInRooms(int number_rooms){
    int i, j;
    deleted_creature = malloc(sizeof(creature_type));
    deleted_creature->id = -1;
    deleted_creature->room = -1;
    deleted_creature->type = -1;
    deleted_creature->deleted = 1;
    for(i=0;i<number_rooms;i++){
        for(j=0;j<10;j++){
            pointer_rooms[i].creatures[j] = deleted_creature;
        }
    }
}

int add_creature(creature_type *creature, room_type *room){
    int i, found_space = 0;
    for(i=0; i < 10; i++){
        if(room->creatures[i]->deleted){
            free(room->creatures[i]);
            room->creatures[i] = creature;
            found_space = 1;
            break;
        }
    }
    return found_space;
};

void remove_creature(creature_type *creature, room_type *room){
    int i;
    for(i=0; i < 10; i++){
        if(room->creatures[i]==creature){
           room->creatures[i] = deleted_creature;
        }
    }
};

int change_room_state(int action, room_type *room){
    room->state = room->state + action;
    if(room->state<0){
        room->state=0;
        return 0;
    } else if (room->state>2){
        room->state=2;
        return 0;
    }
    return 1;
}

void clean(room_type *room, creature_type *player){
    if(change_room_state(-1, room)){
        reaction(-1, room, player);
    }
};

void dirty(room_type *room, creature_type *player){
    if(change_room_state(+1, room)){
        reaction(+1, room, player);
    }
};

int reaction(int action, room_type *room, creature_type *player){
    check_creatures_reaction(action, room, player);
    move_sad_creatures(room);

}

void move_sad_creatures(room_type *room){
    int i;
    for(i=0; i < 10; i++){
        if(!room->creatures[i]->deleted && room->creatures[i]->type != 0){
            if(creature_can_not_stay(room->creatures[i]->type, room->state){
                  if(!move_creature_from(room->creatures[i],room){
                      creature_drill_hole(room->creatures[i],room);
                  }
             }
        }
    }
}

int creature_can_not_stay(int type, int state){
    if((type == 1 && state == 2) || (type == 2 && state == 0)){ 
        return 1;
    }
    return 0;
}

int move_creature_from(creature_type *creature,  room_type *room){

}

void check_creatures_reaction(int action, room_type *room, creature_type *player){
    int i;
    for(i=0; i < 10; i++){
        if(!room->creatures[i]->deleted && room->creatures[i] != player && room->creatures[i]->type != 0){
            creature_react(calculate_creature_reaction(action, room->creatures[i]), room->creatures[i]);
        }
    }
    if(player->type!=0){
        creature_react(3 * calculate_creature_reaction(action, player), player);
    }
}

void creature_react(int respect_change, creature_type *creature){
    //npc smile and grumble. Animals can growl and lickFace.
    respect=respect+respect_change;
    if(creature->type==1){
        if(respect_change>0){
            printf("%d lickFace",creature->id);
        } else {
            printf("%d growl",creature->id);
        }
    } else {
        if(respect_change>0){
            printf("%d smile",creature->id);
        } else {
            printf("%d grumble",creature->id);
        }
    }
    if(respect_change>1 || respect_change<-1){
        printf(" a lot");
    }
    printf(".");
    printf(" Respect is now %d \n",respect);
}

int calculate_creature_reaction(int action, creature_type *creature){
    if(creature->type==1){
        if(action<0){
            return 1;
        } else {
            return -1;
        }
    } else if(creature->type==2){
        if(action>0){
            return 1;
        } else {
            return -1;
        }
    }
    return 0;
}

void creature_drill_hole(creature_type *creature, room_type *room){
    creature->deleted = 1;
    //TODO add PC penalty
}

int move(room_type *origin_room, room_type *destination_room, creature_type *player){
    printf("funcionou \n");
}
