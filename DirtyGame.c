#include<stdio.h>

int respect = 40;

int *pointer_1, *pointer_2, *pointer_3;

int main()
{
    enum GameState {
        startState,
        mainState,
        gameOverState,
        exit
    };

    enum Dirtyness {
        clean = 0,
        halfdirty = 1,
        dirty = 2
    };

    enum GameState currentState = startState;

    int number_rooms, number_creatures;

    int *pointer_rooms;

    while(currentState != exit){
        switch(currentState){
            case startState:
                scanf("%d",number_rooms);
                int rooms[number_rooms][6]; // 0 state, north, south, east, west, crowd
                //read state north south east west for each room
                for (int i = 0; i < number_rooms; i++){
                    scanf("%d %d %d %d %d", rooms[i][0], rooms[i][1], rooms[i][2], rooms[i][3], rooms[i][4]);
                    rooms[i][5] = 0;
                }
                scanf("%d",number_creatures);
                //read creature type and location
                int creatures[number_creatures][2] //type, room
                for (int i = 0; i < number_creatures; i++){
                    scanf("%d %d", creatures[i][0], creatures[i][1]);
                    rooms[creatures[i][1]][5] = rooms[creatures[i][1]][5] + 1;
                }
                currentState = mainState;
            case mainState:

                break;
            case gameOverState:

                break;
            default:
                printf("Current State was not recognized");
        }
    }
    return 0;
}

int readSetUp(){
    char word[256];
    fgets(word, sizeof(word), stdin);
    printf("Hello World %s", word);
}

void look(int room){
    //describe room, numb of creatures, state of room, kind of creatures
}

