//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
        int x=4;
        int y=4;
        int leftScore=0;
        int rightScore=0;
        int counter=0;
        char whoScoredThePoint = 'P';

void stopTheGame(){
        Form1->ballTimer->Enabled =false;
        Form1->ball->Visible=false;
        Form1->continueGameButton->Caption = "Kolejna runda";
        Form1->continueGameButton->Visible = true;
        Form1->newGameButton->Caption = "Nowa gra";
        Form1->newGameButton->Visible = true;
        Form1->counterLabel->Caption = "Liczba odbic: "+IntToStr(counter);
        Form1->counterLabel->Visible = True;
        Form1->scoreTable->Caption=IntToStr(leftScore)+":"+IntToStr(rightScore);
        Form1->scoreTable->Visible=true;
}

void windowSettings(){
        //ustawienia okien
        Form1->Label1->Left = Form1->Background->Width/2-Form1->Label1->Width/2;
        Form1->Label1->Top = 20;
        Form1->continueGameButton->Left = Form1->Background->Width/2-Form1->continueGameButton->Width/2;
        Form1->continueGameButton->Top = 50+Form1->Label1->Height+Form1->scoreTable->Height+Form1->counterLabel->Height;
        Form1->newGameButton->Left = Form1->Background->Width/2-Form1->newGameButton->Width/2;
        Form1->newGameButton->Top = Form1->Background->Height-Form1->newGameButton->Height-20;
        Form1->counterLabel ->Left = Form1->Background->Width/2-Form1->counterLabel->Width/2;
        Form1->counterLabel ->Top = 40+Form1->Label1->Height+Form1->scoreTable->Height;
        Form1->scoreTable->Left = Form1->Background->Width/2-Form1->scoreTable->Width/2;
        Form1->scoreTable->Top = 30+Form1->Label1->Height;
}

void paddleAndBallSettings(){
        Form1->ball -> Left = Form1->Background->Width/2;
        Form1->ball -> Top = Form1->Background->Height/2;
        Form1->paddleLeft -> Top = Form1->Background->Height/2-Form1->paddleLeft->Height/2;
        Form1->paddleLeft -> Left = 20;
        Form1->paddleRight -> Top = Form1->Background->Height/2-Form1->paddleRight->Height/2;
        Form1->paddleRight -> Left = Form1->Background->Width-20-Form1->paddleRight->Width;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::paddleRightUpTimer(TObject *Sender)
{
       if (paddleRight->Top>5) paddleRight->Top -=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleRightDownTimer(TObject *Sender)
{
       if (paddleRight->Top+paddleRight -> Height < Background->Height-5) paddleRight->Top +=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key==VK_UP) paddleRightUp->Enabled = true;
        if (Key==VK_DOWN) paddleRightDown->Enabled = true;
        if (Key==65) paddleLeftUp->Enabled = true;
        if (Key==90) paddleLeftDown->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key==VK_UP) paddleRightUp->Enabled = false;
        if (Key==VK_DOWN) paddleRightDown->Enabled = false;
        if (Key==65) paddleLeftUp->Enabled = false;
        if (Key==90) paddleLeftDown->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleLeftUpTimer(TObject *Sender)
{
        if (paddleLeft->Top>5) paddleLeft->Top -=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::paddleLeftDownTimer(TObject *Sender)
{
        if (paddleLeft->Top+paddleLeft -> Height < Background->Height-5) paddleLeft->Top +=10;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ballTimerTimer(TObject *Sender)
{
        windowSettings();

        //ruch pilki
        ball->Left+=x;
        ball->Top+=y;

        //odbij od gornej sciany
        if (ball->Top-5<=Background->Top) y=-y;

        //odbij od dolnej sciany
        if (ball->Top+ball->Height+5>=Background -> Height) y=-y;

        //faule i odbicia pilki od paletek
        if (ball->Left <paddleLeft->Left+paddleLeft->Width-40){
                rightScore++;
                whoScoredThePoint = 'P';
                stopTheGame();
                Label1->Caption = "Punkt dla gracza prawego! >";
                Label1->Visible = true;
        }else if (ball->Left>paddleRight->Left+40){
                leftScore++;
                whoScoredThePoint = 'L';
                stopTheGame();
                Label1->Caption = "< Punkt dla gracza lewego!";
                Label1->Visible = true;
        }else if (ball->Top > paddleLeft->Top-ball->Height/2 &&
        ball->Top+ball->Height/2 < paddleLeft->Top + paddleLeft->Height &&
        ball->Left<paddleLeft->Left+paddleLeft->Width){
                if (x<=0){
                        x=-x;
                        x+=1;
                 }
                counter ++;
        }else if (ball->Top > paddleRight->Top-ball->Height/2 &&
        ball->Top+ball->Height/2<paddleRight->Top + paddleRight->Height &&
        ball->Left+ball->Width>paddleRight->Left){
                if (x>=0){
                        x=-x;
                        x-=1;
                }
                counter++;
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::newGameButtonClick(TObject *Sender)
{       if(Application->MessageBox("Czy chcesz rozpoczac nowa gre?","Nowa gra", MB_YESNO | MB_ICONQUESTION) == IDYES ){
                paddleAndBallSettings();
                ball ->Visible = true;
                Label1->Visible = false;
                continueGameButton->Visible = false;
                newGameButton->Visible = false;
                scoreTable->Visible = false;
                counterLabel -> Visible = false;
                ballTimer->Enabled = true;
                leftScore = 0;
                rightScore = 0;
                counter = 0;
                x=4;
                y=4;
        }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::continueGameButtonClick(TObject *Sender)
{       paddleAndBallSettings();
        ball ->Visible = true;
        Label1->Visible = false;
        continueGameButton->Visible = false;
        newGameButton->Visible = false;
        scoreTable->Visible = false;
        counterLabel ->Visible = false;
        ballTimer->Enabled = true;
        counter = 0;
        if(whoScoredThePoint == 'P'){
                x=-4;
                y=4;
        }else if (whoScoredThePoint =='L'){
                x=4;
                y=4;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{       Application->MessageBox("Witaj w grze w Ping Ponga.\nSterowanie lewa paletka: A - do gory, Z - w dol. \nSterowanie prawa paletka: strzalka w gore i w dol. \n"
        "Im dluzej grasz tym szybciej leci pilka. \nMozesz zmieniac pole gry. \nPowodzenia i milej zabawy!","Witaj!", MB_OK);
        Label1->Caption = "Witaj w grze Ping Pong!";
        Label1->Left = Background->Width/2-Label1->Width/2;
        Label1->Top = 20;
        newGameButton->Left = Background->Width/2-newGameButton->Width/2;
        newGameButton->Top = Background->Height-newGameButton->Height-20;
        Label1->Visible = true;
        newGameButton->Visible = true;

        newGameButton->Caption = "Nowa gra";
}
//---------------------------------------------------------------------------

