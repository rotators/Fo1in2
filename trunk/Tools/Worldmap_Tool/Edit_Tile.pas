unit Edit_Tile;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls, IniFiles;

type
  TForm2 = class(TForm)
    BitBtn_Zamknij: TBitBtn;
    Label_Nazwa_Tile: TLabel;
    Panel1: TPanel;
    BitBtn1: TBitBtn;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label_walk_mask_name: TLabel;
    Edit_art_idx: TEdit;
    Edit_encounter_difficulty: TEdit;
    Edit3: TEdit;
    Edit_walk_mask_name: TEdit;
//    Panel1: TPanel;
    procedure BitBtn_ZamknijClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormDestroy(Sender: TObject);
    procedure FormCreate(Sender: TObject);
//    procedure OnClick_Image1(Sender: TObject);
    procedure OnClick_SpeedButton(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
//    procedure Image1Click(Sender: TObject);
  private
    Image:TImage;
    SpeedButton:TSpeedButton;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;
  SpeedButton_Numer:Byte;
  numer_duzego_tilesa:Byte;
implementation
uses worldmap_tile_editor, Unit3_List_Maps;

{$R *.dfm}


procedure TForm2.BitBtn_ZamknijClick(Sender: TObject);
begin
  Form2.Close;
//  Form2:=nil;
end;

procedure TForm2.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if Assigned(Form3) then
  begin
    Form3.Close;
    Form3.Destroy;
  end;

  Action:=caFree;
end;

procedure TForm2.FormDestroy(Sender: TObject);
begin
  SpeedButton.Free;
  Image.Free;

  Form2:=nil;
end;

procedure TForm2.FormCreate(Sender: TObject);
var i,j,licznik:Byte;  // zmienne iteracyjne
//    iter, joter:Byte; // zmienne iteracyjne (musza byc drugie bo i, j  s¹ zajete)

begin

  Top:=0;// ustawienie Form2 na pocz¹tku programu
  Left:=Form1.Panel1.Width+10;// ustawienie Form2 na pocz¹tku programu

  Edit3.Text:=IntToStr(numer_tilesa);
  Label_Nazwa_Tile.Caption:='[Tile '+IntToStr(numer_tilesa)+']';

  numer_duzego_tilesa:=numer_tilesa;
//  ShowMessage('Numer duzego Tilesa = '+ IntToStr(numer_duzego_tilesa));

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    Edit_art_idx.Text:= plik_worldmap.ReadString('Tile '+IntToStr(numer_tilesa), 'art_idx', '339');
    Edit_encounter_difficulty.Text:=plik_worldmap.ReadString('Tile '+IntToStr(numer_tilesa), 'encounter_difficulty', '0');
    walk_mask_name:=plik_worldmap.ReadString('Tile '+IntToStr(numer_tilesa), 'walk_mask_name', '');
    Edit_walk_mask_name.Text:=walk_mask_name;
    if walk_mask_name='' then
    begin
      Edit_walk_mask_name.Visible:=False;
      Label_walk_mask_name.Visible:=False;
    end
    else
    begin
      Edit_walk_mask_name.Visible:=True;
      Label_walk_mask_name.Visible:=True;
    end
    finally
      plik_worldmap.Free;
  end;

{start - dynamiczne tworzenie komponentów n formie}

  Image:=TImage.Create(Panel1);
  with Image do
  begin
    name:='Image'+IntToStr(numer_tilesa);
    Parent:=Panel1;
    Height:=Panel1.Height-2;       //wysokosc
    Width:=Panel1.Width-2;        //szerokosc
    Top:=1;
    Left:=1;
    stretch:=False;

    if numer_tilesa<10 then Picture.LoadFromFile('wrldmp'+IntToStr(0)+IntToStr(numer_tilesa)+'.bmp');
    if numer_tilesa>=10 then Picture.LoadFromFile('wrldmp'+IntToStr(numer_tilesa)+'.bmp');

{    Canvas.Brush.Style := bsClear; // ustaw t³o na przezroczyste
    Canvas.Font.Color := clYellow; // kolor czcionki: bia³y
    Canvas.Font.Name := 'Arial'; // nazwa czcionki: Arial Black
    Canvas.Font.Size := 8; // rozmiar czcionki: 16 pkt.
{    for i:=0 to 6 do
      for j:=0 to 5 do
      Canvas.TextOut(i*50+30,j*50+35, IntToStr(i)+'_'+IntToStr(j)); // wyœwietlenie tekstu typu 0_0 (2_5 itd) w ma³ych krateczkach
}
    Canvas.Pen.Color := clGray;
    Canvas.Pen.Width:=1;
    Canvas.Pen.Style := psSolid;
    for i:=0 to 7 do Canvas.Rectangle(i*50, 0, i*50+1, 300);
      for i:=0 to 6 do Canvas.Rectangle(0, i*50, 350, i*50+1);
  end;

  licznik:=0;
  i:=1;
  j:=0;

  While licznik<=42 do
  begin
    Inc(licznik);
    SpeedButton:=TSpeedButton.Create(Panel1);
    with SpeedButton do
    begin
      if licznik mod (i*7+1)=0 then
      begin
        inc(i);
        j:=0;
      end;
      inc(j);

      name:='SpeedButton'+IntToStr(licznik);
      Parent:=Panel1;
      Height:=50;       //wysokosc
      Width:=50;        //szerokosc
      Top:=0;
      Left:=0;
      Top:=i*(50)-50;
      Left:=j*(50)-50;

      Flat:=True;
//      Transparent:=True;
      Font.Color:=clYellow;
      Font.Size:=11;
      Font.Name := 'Arial'; // nazwa czcionki: Arial Black
      Font.Style:=[fsBold];
      Cursor:=crCross;

      OnClick := OnClick_SpeedButton;

      Caption:=IntToStr(j-1)+'_'+IntToStr(i-1);
    end;
  end;
end;

procedure TForm2.OnClick_SpeedButton(Sender: TObject);
var licznik_:Integer;
//    Tile_numer:String;
//    art_idx:String;
//    encounter_difficulty:String;

//    i,j:Byte;

begin
  licznik_:=0;
  While licznik_<=42 do
  begin
    inc(licznik_);
    SpeedButton_Numer:=licznik_;

    if (Sender is TSpeedButton) then
    if (Sender as TSpeedButton).name = 'SpeedButton'+IntToStr(licznik_) then
    begin
      If not Assigned(Form3) then
      begin
//        Form3:=TForm3.Create(Application);
        Form3:=TForm3.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
        Form3.Show;
      end
      else
      begin
        Form3.Close;
        Form3.Destroy;
        Form3:=TForm3.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
        Form3.Show;
      end;
    end;
  end;
end;

procedure TForm2.BitBtn1Click(Sender: TObject);
begin
  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),'encounter_difficulty',Edit_encounter_difficulty.Text);
  finally
    plik_worldmap.Free;
  end;
  Form2.Close;
end;

end.
