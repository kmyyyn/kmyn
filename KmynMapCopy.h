#ifndef _KmynMapCopy_H_                                         //
#define _KmynMapCopy_H_                                         //

class Map{
private:
    int map0[14][28];                              // массив карты
    int side;                                      // сторона одного квадрата карты
    int m, n;                                      // сколько на сколько квадратов карта
    int attack;                                    // буферная переменная
    HDC DC;                                               // картинка карты
public:
    Map();
    ~Map();
    void Set_Map();                                // сеттер для карты
    void DrawMap();                                // отрисовка карты
    void Init();                                   //
    int  GPS( int x, int y);                       // геттер для одной карты
    void Deconstruction(int x, int y, int state);  // сеттер
    void Trap();                                   // изменение ловушек
    void Delete();
    void Draw_win();                                 // освождение холста
};

void Map::Init(){
    side = 50;
    DC = txLoadImage("OrekhovMap.bmp");
    m = 14; n = 28;
    attack = 0;
};

void Map::Set_Map(){
    int bufmap[14][28] = {  {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 1, 0, 1, 4, 1, 0, 4, 1, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 4, 0, 4, 0, 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 1, 4, 1, 0, 1, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 1, 0, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 4, 1, 1, 1, 1, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 4, 0, 1, 4, 1, 1, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 4, 0, 1, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 1, 0, 1, 4, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 4, 0, 0, 0, 4, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 1, 1, 1, 4, 1, 0, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    for( int i = 0; i < m; i++){
        for( int j = 0; j < n; j++){
            map0[i][j] = bufmap[i][j];
        }
    }
};

void Map::DrawMap(){
    for( int i = 0; i < m; i++){
        for( int j = 0; j < n; j++){
            if( map0[i][j] == 1 ){
                txSetColor( TX_BLACK);
                txSetFillColor(TX_BLACK);
                txBitBlt( txDC(), j*side, i*side, side, side, DC,  51, 0);
                //txRectangle( j*side, i*side, j*side+side, i*side+side);
            }
            if(map0[i][j] == 0){
                txSetColor( TX_WHITE);
                txSetFillColor(TX_WHITE);
                txBitBlt( txDC(), j*side, i*side, side, side, DC, 0, 0);
                //txRectangle( j*side, i*side, j*side+side, i*side+side);
            }
            if( map0[i][j] == 3){
                txSetColor( TX_YELLOW);
                txSetFillColor(TX_YELLOW);
                txRectangle( j*side, i*side, j*side+side, i*side+side);
            }
            if( map0[i][j] == 4 ){
                txSetColor( TX_RED);
                txSetFillColor(TX_RED);
                txBitBlt( txDC(), j*side, i*side, side, side, DC,  101, 0);
                //txRectangle( j*side, i*side, j*side+side, i*side+side);
            }
            if(map0[i][j] == 5){
                txSetColor( TX_PINK);
                txSetFillColor(TX_PINK);
                txBitBlt( txDC(), j*side, i*side, side, side, DC,  151, 0);
                //txRectangle( j*side, i*side, j*side+side, i*side+side);
            }
        }
    }
}

int Map::GPS( int x, int y){
    return map0[y/50][x/50];
}

void Map::Deconstruction(int x, int y, int state){
    map0[y/50][x/50] = state;
};

void Map::Trap(){
    if( attack%25 == 0)
    for( int i = 0; i < m; i++){
        for( int j = 0; j < n; j++){
            if( map0[i][j] == 4) map0[i][j] = 5;
            else if( map0[i][j] == 5) map0[i][j] = 4;
        }
    }
    attack++;
}

void Map::Delete(){
    txDeleteDC(DC);
}

void Map::Draw_win(){
    for( int i = 0; i < m; i++){
        for( int j = 0; j < n; j++){
            txBitBlt( txDC(), j*side, i*side, side, side, DC, 0, 0);
        }
    }
}

Map::Map(){
    Init();
    Set_Map();
}

Map::~Map(){
    Delete();
}

#endif
