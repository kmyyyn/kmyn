#ifndef  _KmynPers_H_                                           //
#define  _KmynPers_H_                                           //

class Pers{
private:
    int x, y;
    double scale;
    int x0, y0, xorig, yorig, speed;
    HDC DC;
    COLORREF col;
    int Buf, tu, td, tl, tr, Form, Formx;
    int HP, maxHP;
public:
    Pers();
    ~Pers();
    void Up(Map &map0);
    void Down(Map &map0);
    void Left(Map &map0);
    void Right(Map &map0);
    void Ultimate();
    void Draw();
    void Stop_Check();
    void Init();
    void stats();
    void GetDamage(Map &map0);
    int GameOver();
    void Delete();
    int Win(Map &map0);
    void Draw_Die();
    void Check(Map &map0);
    void Start();
};

void Pers::Up( Map &map0){
    y -= speed;
    x0 = 1+(xorig+1)*(tu%4);
    y0 = yorig*2+3;
    tu++;
    Buf++;
    if( map0.GPS( x, y) == 0 ){
        y+=speed;
        tu = 0;
    }
    //if( map0.GPS( x, y) == 4 ) HP--;
};

void Pers::Down(Map &map0){
    y += speed;
    x0 = 1+(int(xorig+1))*(td%4);
    y0 = 1;
    td++;
    Buf++;
    if( map0.GPS( x, y+int(yorig*scale)) == 0 ){
        y-=speed;
        td = 0;
    }
    //if( map0.GPS( x, y+yorig*scale) == 4 ) HP--;
};

void Pers::Left(Map &map0){
    x -= speed;
    x0 = 1+(xorig+1)*(tl%2);
    y0 = yorig+2;
    tl++;
    Buf++;
    if( map0.GPS(x, int(y+yorig*scale)) == 0 || map0.GPS( x, y) == 0  ){
        x+=speed;
    }
};

void Pers::Right(Map &map0){
    x+=speed;
    x0=(xorig+1)*2+1+(xorig+1)*(tr%2);
    y0= yorig+2;
    tr++;
    Buf++;
    if( map0.GPS( int(x+xorig), int(y+yorig*scale)) == 0 || map0.GPS( x+xorig, y) == 0 ){
        x-=(speed);
    }
};

void Pers::Ultimate(){
    if( Form == 0 ) Form = Formx;
    else Form = 0;

};

void Pers::Stop_Check(){
    if(Buf == 0){
        if((x0>=37)&&(y0==33)) x0 = 37;
        else x0 = 1;
        tu = 1;
        td = 1;
        tl = 1;
        tr = 1;
    }
    Buf = 0;
};

void Pers::Draw(){
    Win32::TransparentBlt(txDC(), x , y, int(xorig*scale), int(yorig*scale), DC, x0, y0+Form, xorig, yorig, col);
};

void Pers::Init(){
    x = 0; y = 0;
    scale = 1.2;
    x0 = 1; y0 = 1;
    xorig = 17; yorig = 31; speed = 5;
    DC = txLoadImage("mb.bmp");
    col = RGB(195,134,255);
    Buf = 0; tu = 0; td = 0; tl = 0; tr = 0; Form = 0; Formx = 98;
    maxHP = 5; HP = maxHP;
};

void Pers::stats(){
    txSelectFont ("Comic Sans MS", 60, 20);
    txSetColor( RGB(rand()%255, rand()%255, rand()%255));
    txDrawText( 1210, 630, 1300, 690, "Hp ");
    char s[1];
    s[0] = char('0'+HP);
    txDrawText( 1300, 630, 1330, 690, s);
    txDrawText( 1330, 630, 1360, 690, "/");
    s[0] = char('0'+maxHP);
    txDrawText( 1360, 630, 1390, 690, s);

};

void Pers::GetDamage(Map &map0){
    if( map0.GPS(x, y) == 4){
        HP--;
        map0.Deconstruction( x, y, 5);
    }
    if( map0.GPS(x+int(xorig*scale-1), y+int(yorig*scale-1)) == 4 ){
        HP--;
        map0.Deconstruction( x+int(xorig*scale)-1, y+int(yorig*scale)-1, 5);
    }
}

int Pers::GameOver(){
    if( HP == 0) return 1;
    return 0;
}

int Pers::Win(Map &map0){
    if( map0.GPS(x, y) == 3){
        return 1;
    }
    if( map0.GPS(x+int(xorig*scale-1), y+int(yorig*scale-1)) == 3 ){
        return 1;
    }
    return 0;
}

void Pers::Draw_Die(){
    Win32::TransparentBlt(txDC(), 0 , 0, 1400, 700, DC, 1, 1, xorig, yorig, col);
}

void Pers::Delete(){
    txDeleteDC(DC);
}

Pers::Pers(){
    Init();
}

Pers::~Pers(){
    Delete();
}

void Pers::Start(){
    txSetFillColor(TX_BLACK);
    txClear();
    txSelectFont ("Comic Sans MS", 100, 20);
    txDrawText( 100, 100, 1300, 200, "#МНЕ_ЛЕНЬ_ПРИДУМАТЬ_НАЗВАНИЕ");
    txSelectFont ("Comic Sans MS", 30, 10);
    txDrawText( 10, 690, 150, 660, "Автор: Кмун");
    txSelectFont ("Comic Sans MS", 30, 10);
    txDrawText( 100, 200, 1300, 230, "Управление на WASD или стрелками, управляете моникой");
    txDrawText( 100, 230, 1300, 260, "Если HP равно 0, вы проиграли, если наступили на желтую клетку- победили");
    txDrawText( 100, 260, 1300, 290, "Если Юри (девка с фиолетовыми волосами) начинает глючить, то наступив на нее вы теряете хп");
    txDrawText( 100, 290, 1300, 320, "При нажатии на F (вставьте шутку про пресс F) Моника переходит во вторую форму (пока бесполезно)");
    txDrawText( 100, 600, 1300, 630, "нажмите лкм для продолжения");
    while (txMouseButtons() != 1){
        txSleep(1);
    }
}

#endif
