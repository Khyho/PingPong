//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *Background;
        TImage *paddleLeft;
        TImage *paddleRight;
        TTimer *paddleRightUp;
        TTimer *paddleRightDown;
        TTimer *paddleLeftUp;
        TTimer *paddleLeftDown;
        TImage *ball;
        TTimer *ballTimer;
        TButton *newGameButton;
        TLabel *helloLabel;
        TLabel *scoreTable;
        TButton *continueGameButton;
        TLabel *counterLabel;
        void __fastcall paddleRightUpTimer(TObject *Sender);
        void __fastcall paddleRightDownTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall paddleLeftUpTimer(TObject *Sender);
        void __fastcall paddleLeftDownTimer(TObject *Sender);
        void __fastcall ballTimerTimer(TObject *Sender);
        void __fastcall newGameButtonClick(TObject *Sender);
        void __fastcall continueGameButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
