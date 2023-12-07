#include "manager.h"
#include <chrono>

double score[5] = { 4.5, 4.5, 4.5, 4.5, 4.5 };
int stage; 
extern int gameMap1[22][37];
extern int gameMap2[22][37];
extern int gameMap3[22][37];
extern int gameMap4[22][37];

extern int gameMapHere[22][37];

extern int gameTitle[22][37];

int pKeyPressed = 0;
double keyInterval = 0.20;

int checkKey;

void BGMplayer(int sort, bool turn_on) {

    if (turn_on) {
        switch (sort) 
        {
        case GAME_OVER:
            PlaySound(TEXT("게임오버.wav"), NULL, SND_ASYNC); break;
        case GAME_CLEAR:
            PlaySound(TEXT("게임클리어.wav"), NULL, SND_ASYNC); break;
        case INTRO_BGM:
            PlaySound(TEXT("인트로.wav"), NULL, SND_ASYNC); break;
        case PLAY_BGM:
            PlaySound(TEXT("플레이.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); break;
        case RESULT_BGM:
            PlaySound(TEXT("성적표.wav"), NULL, SND_FILENAME | SND_ASYNC); break;
        }
        
    }

    else
        PlaySound(NULL, 0, 0);
    return;
}

int keyControl() {
    static auto lastKeyPressTime = std::chrono::high_resolution_clock::now();

    int flag = -1;
    if (_kbhit() != 0) {
        int key = _getch();
        flag = 0;

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedSeconds = currentTime - lastKeyPressTime;


        switch (key) {
        case 112:       // p: 112
            pKeyPressed = 1;
            checkKey = 112;
            return key;

        case SPACEBAR:
             pKeyPressed = 0;
             checkKey = key;
             return key;
        case LEFT:
        case RIGHT:
            if (pKeyPressed) break;
        case UP:
        case DOWN:
            if (elapsedSeconds.count() >= keyInterval) {
                lastKeyPressTime = currentTime;
                
                checkKey = key;
                return key;
            }
            break;
        }
    }
    return flag;
}


int drawPauseScreen() {
    system("cls");
    setBackgroundColor(0, 12);

    setCurrentCursorPos(34, 12); printf("> ");

    setCurrentCursorPos(38, 12); printf("CONTINUE");

    setCurrentCursorPos(38, 14); printf("GAME OVER");

    while (1) {
        int x = 36;
        int y = 12;

        while (1) {
            int n = keyControl();
            switch (n) {
            case UP:
                if (y > 12) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y -= 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case DOWN:
                if (y < 14) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y += 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case SPACEBAR:
                setBackgroundColor(0, 15);
                return y - 12;      // 0: 이어하기, 2: 게임 오버
            }
        }
    }

}


void setScore(int stage, double s) {
	score[stage] += s;
    if (score[stage] >= 4.5) score[stage] = 4.5;
    if (score[stage] <= 0) score[stage] = 0;
    drawInfo(score, stage); 
}

int initGame() {
    stage = 4;
    int menu = drawMenu();
    if (menu == 0) return 0;        // 게임 시작
    else if (menu == 2) return 1;
    else if (menu == 4) return 2;  // todo
    else if (menu == 6) return 3;  // 게임 종료
}

void drawPrologue() {
    setBackgroundColor(0, 15);

    const char* prologue1[] = {
        "힘들게 대학교에 입학했다.",
        "1학년부터 4학년까지 무사히 살아남아 졸업해야 한다...!!", "    ",
        "앞이 벽으로 가로막혀 답이 없는 상황이다.", "벽이 색깔로 빛난다면 주변의 같은 색의 버튼을 먹어 벽을 부숴보도록 하자.",
        "원하는 색이 없다면 두 가지 색을 조합해서 부숴보자!", "    ",
        "대학교에 입학했다고 느긋하게 있으면 안된다.",
        "지각을 하거나!! 감기 바이러스에 부딪힌다면 내 학점이 내려간다.",
        "시험 NPC가 날리는 스트레스도 잘 피해서 다녀보자.",
        "3out이니 부딪히지 않도록 조심하도록 하자"
    };
    
    for (int i = 0; i < 11; i++) {
        setCurrentCursorPos(10, 3 + (i + 1) * 2);
        if (i == 4) setBackgroundColor(0, 11);
        else if (i == 5) setBackgroundColor(0, 14);
        else if (i == 6) setBackgroundColor(0, 15);
        for (int j = 0; prologue1[i][j] != '\0'; j++) {
            Sleep(10);                                      // todo: 속도 조절
            printf("%c", prologue1[i][j]);
            fflush(stdout);
        }
    }

    setCurrentCursorPos(20, 28);
    setBackgroundColor(0, 8);
    printf("Press Anything to continue...");
    while (1)
        if (_getch()) break;

    system("cls");

    const char* prologue2[] = {
        "대학생이면 응당 술과 함께하는 삶이다.", "하지만 술과 부딪힌다면 어지러워지니 조심하자.",
        "정말 탈출할 방법이 없는 거 같다면 주변의 비상구로 들어가보자.", "예상치 못하게 나를 구해줄 수도..?","    ","    ",
        "열심히 3학년까지 달려왔다.", "곧 4학년... 갑자기 주변이 어두워진다..", "작은 빛에 의지해서 탈출해야 한다.", "주변을 잘 살피며 탈출해 보자."
    };

    setBackgroundColor(0, 15);
    for (int i = 0; i < 9; i++) {
        setCurrentCursorPos(10, 3 + (i + 1) * 2);
        if (i == 1) setBackgroundColor(0, 8);
        else if (i == 2) setBackgroundColor(0, 15);
        else if (i == 8) setBackgroundColor(0, 14);
        else if (i == 9) setBackgroundColor(0, 15);
        for (int j = 0; prologue2[i][j] != '\0'; j++) {
            Sleep(10);                                      // todo: 속도 조절
            printf("%c", prologue2[i][j]);
            fflush(stdout);
        }
    }

    setCurrentCursorPos(20, 28);
    setBackgroundColor(0, 8);
    printf("Press Anything to continue...");
    while (1)
        if (_getch()) break;

    setBackgroundColor(0, 15);
}

int drawMenu() {
    system("cls");

    setCurrentCursorPos(36, 9); setBackgroundColor(0, 10); printf("COLOR UNIV.");

    setBackgroundColor(0, 15);

    setCurrentCursorPos(32, 12); printf("> ");

    setCurrentCursorPos(36, 12); printf("[GAME START]");

    setCurrentCursorPos(36, 14);  printf("[HOW TO PLAY]");

    setCurrentCursorPos(36, 16); printf("[DEVELOPER INFORMAION]");

    setCurrentCursorPos(36, 18); printf("[EXIT]");

    while (1) {
        int x = 34;
        int y = 12;

        while (1) {
            int n = keyControl();
            switch (n) {
            case UP:
                if (y > 12) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y -= 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case DOWN:
                if (y < 18) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y += 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case SPACEBAR:
                setBackgroundColor(0, 15);
                return y - 12;      // 0: game start, 2:how to play, 4: dev,  6: exit
            }
        }
    }
    
}

void drawDevInfo() { // 임시화면
    system("cls");
    setCurrentCursorPos(36, 10); setBackgroundColor(0, 10); printf("[Developer Info]");

    setBackgroundColor(0, 15);

    setCurrentCursorPos(36, 12); printf("22011191 전지원");
    setCurrentCursorPos(36, 14); printf("22011819 복민정");
    setCurrentCursorPos(36, 16); printf("22011824 이지호");
    setCurrentCursorPos(36, 18); printf("22011839 신지우");

    setBackgroundColor(0, 8); setCurrentCursorPos(31, 23); printf("Press Anything to continue...");

    setBackgroundColor(0, 10);
    while (1)
        if (_getch()) break;
}

void drawHowToPlay() {
    system("cls");
    setCurrentCursorPos(39, 4);  setBackgroundColor(0, 10);  printf("[HOW TO PLAY]");

    setCurrentCursorPos(7, 8);    setBackgroundColor(0, 11);   printf("⊙");
    setCurrentCursorPos(8, 8);  setBackgroundColor(0, 15);  printf(" : 색버튼을 먹거나 조합하여 ");
    setCurrentCursorPos(8, 9);  setBackgroundColor(0, 15);  printf("   벽을 해제할 수 있습니다. ");

    setBackgroundColor(0, 14); setCurrentCursorPos(7, 12);  printf("⊙");
    setBackgroundColor(0, 15); setCurrentCursorPos(9, 12);  printf(" + "); setCurrentCursorPos(14, 12); printf(" = ");
    setBackgroundColor(0, 9); setCurrentCursorPos(12, 12);  printf("⊙");
    setBackgroundColor(0, 10); setCurrentCursorPos(17, 12);  printf("■");

    setBackgroundColor(0, 12); setCurrentCursorPos(7, 14);  printf("⊙");
    setBackgroundColor(0, 15); setCurrentCursorPos(9, 14);  printf(" + "); setCurrentCursorPos(14, 14); printf(" = ");
    setBackgroundColor(0, 14); setCurrentCursorPos(12, 14);  printf("⊙");
    setBackgroundColor(0, 6); setCurrentCursorPos(17, 14);  printf("■");

    setBackgroundColor(0, 9); setCurrentCursorPos(7, 16);  printf("⊙");
    setBackgroundColor(0, 15); setCurrentCursorPos(9, 16);  printf(" + "); setCurrentCursorPos(14, 16); printf(" = ");
    setBackgroundColor(0, 12); setCurrentCursorPos(12, 16);  printf("⊙");
    setBackgroundColor(0, 5); setCurrentCursorPos(17, 16);  printf("■");

   
    setCurrentCursorPos(7, 20);  setBackgroundColor(0, 15);  printf("ⓔ: 지우개로 색저장소를 비울 수 있습니다.");


    setCurrentCursorPos(55, 8);   setBackgroundColor(0, 6);  printf("★");
    setCurrentCursorPos(56, 8);  setBackgroundColor(0, 14);  printf(" : 족보 아이템");
    setCurrentCursorPos(56, 9);  setBackgroundColor(0, 15);  printf("   학점을 0.5점 올릴 수 있습니다. ");

    setCurrentCursorPos(55, 12);   setBackgroundColor(0, 4);  printf("♥");
    setCurrentCursorPos(56, 12);  setBackgroundColor(0, 14);  printf(" : 생명 아이템");
    setCurrentCursorPos(56, 13);  setBackgroundColor(0, 15);  printf("   생명을 1 증가시킬 수 있습니다.");

    setCurrentCursorPos(55, 16);  setBackgroundColor(0, 15);  printf("⒮: 스피드로 플레이어의 속도를 ");
    setCurrentCursorPos(55, 17);  setBackgroundColor(0, 15);  printf("    5초간 빠르게 할 수 있습니다.");

    setCurrentCursorPos(55, 20);   setBackgroundColor(0, 2);  printf("▥");
    setCurrentCursorPos(56, 20);  setBackgroundColor(0, 15);  printf(" : 비상구를 통해 ");
    setCurrentCursorPos(56, 21);  setBackgroundColor(0, 15);  printf("   다른 비상구로 나갈 수 있습니다.");

    
    setBackgroundColor(0, 8); setCurrentCursorPos(32, 30); printf("Press Anything to continue...");

    while (1) if (_getch()) break;
    setBackgroundColor(0, 10);
}

void drawResultScreen(int gameResult[22][37], int check) {
    setCurrentCursorPos(12, 28);
    printf("                                     ");

    int origin_x1 = 20, origin_y1 = 27, h = 2, w = 2;
    setCurrentCursorPos(origin_x1, origin_y1);
    printf("                           ");

    setCurrentCursorPos(origin_x1, origin_y1 + h);
    printf("       ");

    setCurrentCursorPos(origin_x1 + (w + 1) * 2, origin_y1);
    printf("                           ");


    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1);
        printf(" ");
    }
    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1 + h);
        printf(" ");
    }

    int origin_x2 = 28, origin_y2 = 27;
    setCurrentCursorPos(origin_x2, origin_y2);
    printf("                           ");

    setCurrentCursorPos(origin_x2, origin_y2 + h);
    printf("              ");

    setCurrentCursorPos(origin_x2 + (w + 1) * 2, origin_y2);
    printf("                           ");

    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2);
        printf(" ");
    }
    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2 + h);
        printf(" ");
    }

    int origin_x3 = 57, origin_y3 = 27, h3 = 2, w3 = 6;
    setCurrentCursorPos(50, 28);
    printf("                           ");

    setCurrentCursorPos(origin_x3, origin_y3);
    printf("                           ");

    setCurrentCursorPos(origin_x3, origin_y3 + h3);
    printf("                        ");

    setCurrentCursorPos(origin_x3 + (w3 + 1) * 2, origin_y3);
    printf("                           ");

    for (int x = 1; x < w3 + 1; x++) {
        setCurrentCursorPos(origin_x3 + x * 2, origin_y3);
        printf(" ");
    }
    for (int x = 1; x < w3 + 1; x++) {
        setCurrentCursorPos(origin_x3 + x * 2, origin_y3 + h3);
        printf(" ");
    }

    setCurrentCursorPos(59, 28);
    printf("           ");

    Sleep(10);

    int color = 0;
    if (check == 0)// game over 
    {
        color = 4;
        BGMplayer(GAME_OVER, false);
        BGMplayer(GAME_OVER, true);
    }
    else// game clear
    {
        color = 14;
        BGMplayer(GAME_CLEAR, false);
        BGMplayer(GAME_CLEAR, true);
    }

    if (check == 0) minusLife();

    int x = GBOARD_ORIGIN_X, y = GBOARD_ORIGIN_Y;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
    for (int j = 0; j < 37; j++) {
        for (int i = 0; i < 22; i++) {
            setCurrentCursorPos(x + j * 2, y + i);
            if (gameResult[i][j] == 0) {
                setBackgroundColor(0, 0);
                printf("■");
            }

            else {
                setBackgroundColor(0, color);
                printf("■");
            }
        }
        Sleep(30);
    }



    Sleep(100);
    system("cls");
}

void getStage(int gameMap[22][37], int stage) {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 37; j++) {
            if (stage == 1)
                gameMap[i][j] = gameMap1[i][j];
            else if (stage == 2)
                gameMap[i][j] = gameMap2[i][j];
            else if (stage == 3)
                gameMap[i][j] = gameMap3[i][j];
            else if (stage == 4)
                gameMap[i][j] = gameMap4[i][j];
        }
    }
}

int getNpcSleepTime(int stage) {
    switch (stage) {
    case 1: return 150;
    case 2: return 150;
    case 3: return 300;
    case 4: return 150;
    }
    return 150;
}

void calculateAvgScore() {
    double sum = 0.0;
    for (int i = 1; i <= stage; i++) sum += score[i];

    score[0] = sum / stage;
}

void drawReport() {
    BGMplayer(RESULT_BGM, true);
    system("cls");
    
    setCurrentCursorPos(38, 9);
    setBackgroundColor(0, 10);
    printf("[성 적 표]");

    setBackgroundColor(0, 15);
    setCurrentCursorPos(38, 12);
    printf("1학년: %.1f", score[1]);

    setCurrentCursorPos(38, 14);
    printf("2학년: %.1f", score[2]);

    setCurrentCursorPos(38, 16);
    printf("3학년: %.1f", score[3]);

    setCurrentCursorPos(38, 18);
    printf("4학년: %.1f", score[4]);

    setCurrentCursorPos(36, 20);
    printf("평균 학점: %.1f", score[0]);

    setBackgroundColor(0, 8);
    setCurrentCursorPos(31, 23);
    printf("Press Anything to continue...");

    setBackgroundColor(0, 10);

    while (1)
        if (_getch()) break;
    system("cls");
}

void drawTitle() {
    BGMplayer(INTRO_BGM, true);
    int x = GBOARD_ORIGIN_X + 5, y = GBOARD_ORIGIN_Y;
    for (int j = 0; j < 37; j++) {
        for (int i = 0; i < 10; i++) {
            setCurrentCursorPos(x + j * 2, y + i);
            if (gameTitle[i][j] == 0) {
                setBackgroundColor(0, 0);
                printf("■");
            }

            else {
                setBackgroundColor(0, 14);
                printf("■");
            }
        }
        Sleep(50);
    }

    for (int j = 0; j < 37; j++) {
        for (int i = 10; i < 22; i++) {
            setCurrentCursorPos(x + j * 2, y + i);
            if (gameTitle[i][j] == 0) {
                setBackgroundColor(0, 0);
                printf("■");
            }

            else {
                setBackgroundColor(0, 14);
                printf("■");
            }
        }
        Sleep(50);
    }

    Sleep(2000);
    system("cls");
}