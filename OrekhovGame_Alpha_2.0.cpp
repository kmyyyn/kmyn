#include <TXLib.h>
#include <windows.h>
#include <string>
#include "KmynMap.h"
#include "KmynPers.h"

int main(){
    Pers Monika;
    Map map0;
    txCreateWindow(1400,700);
    Monika.Init();
    map0.Init();
    map0.Set_Map();
    txSetFillColor(TX_WHITE);
    txClear();
    txBegin();

    while( !GetAsyncKeyState(VK_ESCAPE)){
        txClear();

        if( GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP))     Monika.Up(map0);
        if( GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN))   Monika.Down(map0);
        if( GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))   Monika.Left(map0);
        if( GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT) ) Monika.Right(map0);
        if( GetAsyncKeyState(0x46))                                Monika.Ultimate();

        map0.Trap();
        map0.DrawMap();
        Monika.Stop_Check();
        Monika.Draw();
        Monika.stats();
        if( Monika.GameOver() == 1 ){
            txMessageBox("YOU DIED");
            txSetFillColor(TX_BLACK);
            txClear();
            Monika.Draw_Die();
            map0.Delete();
            Monika.Delete();
            return 0;
        }
        if( Monika.Check_End(map0) == 1 ){
            Monika.Delete();
            txMessageBox("YOU WIN");
            txClear();
            map0.Draw_win();
            map0.Delete();
            return 0;
        }
        map0 = Monika.GetDamage(map0);

        txSleep(50);

    }

    map0.Delete();
    Monika.Delete();

    txEnd();

    return 0;
}



