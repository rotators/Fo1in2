unit Worldmap_tile_editor;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, IniFiles, ExtCtrls, StdCtrls, Buttons, Menus, ToolWin, ComCtrls,
  ImgList;

type
  TForm1 = class(TForm)
    MainMenu1: TMainMenu;
    Zakocz1: TMenuItem;
    Edycja1: TMenuItem;
    Zakocz2: TMenuItem;
    Encounterfrequencypercentages1: TMenuItem;
    HElp1: TMenuItem;
    Panel1: TPanel;
    Image1: TImage;
    Image2: TImage;
    Image3: TImage;
    Image4: TImage;
    Image5: TImage;
    Image6: TImage;
    Image7: TImage;
    Image8: TImage;
    Image9: TImage;
    Image10: TImage;
    Image11: TImage;
    Image12: TImage;
    Image13: TImage;
    Image14: TImage;
    Image15: TImage;
    Image16: TImage;
    Image17: TImage;
    Image18: TImage;
    Image19: TImage;
    Image20: TImage;
    Panel2: TPanel;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    SpeedButton5: TSpeedButton;
    SpeedButton6: TSpeedButton;
    SpeedButton7: TSpeedButton;
    SpeedButton8: TSpeedButton;
    SpeedButton9: TSpeedButton;
    SpeedButton10: TSpeedButton;
    SpeedButton11: TSpeedButton;
    SpeedButton12: TSpeedButton;
    SpeedButton13: TSpeedButton;
    SpeedButton14: TSpeedButton;
    SpeedButton15: TSpeedButton;
    SpeedButton16: TSpeedButton;
    SpeedButton17: TSpeedButton;
    SpeedButton18: TSpeedButton;
    SpeedButton19: TSpeedButton;
    SpeedButton20: TSpeedButton;
    Panel3: TPanel;
    SpeedButton21: TSpeedButton;
    SpeedButton22: TSpeedButton;
    SpeedButton23: TSpeedButton;
    SpeedButton24: TSpeedButton;
    SpeedButton25: TSpeedButton;
    SpeedButton26: TSpeedButton;
    SpeedButton27: TSpeedButton;
    SpeedButton28: TSpeedButton;
    SpeedButton29: TSpeedButton;
    SpeedButton30: TSpeedButton;
    SpeedButton31: TSpeedButton;
    SpeedButton32: TSpeedButton;
    SpeedButton33: TSpeedButton;
    SpeedButton34: TSpeedButton;
    SpeedButton35: TSpeedButton;
    SpeedButton36: TSpeedButton;
    SpeedButton37: TSpeedButton;
    SpeedButton38: TSpeedButton;
    SpeedButton39: TSpeedButton;
    SpeedButton40: TSpeedButton;
    SpeedButton41: TSpeedButton;
    SpeedButton42: TSpeedButton;
    SpeedButton43: TSpeedButton;
    SpeedButton44: TSpeedButton;
    SpeedButton45: TSpeedButton;
    SpeedButton46: TSpeedButton;
    SpeedButton47: TSpeedButton;
    SpeedButton48: TSpeedButton;
    SpeedButton49: TSpeedButton;
    SpeedButton50: TSpeedButton;
    SpeedButton51: TSpeedButton;
    SpeedButton52: TSpeedButton;
    SpeedButton53: TSpeedButton;
    SpeedButton54: TSpeedButton;
    SpeedButton55: TSpeedButton;
    SpeedButton56: TSpeedButton;
    SpeedButton57: TSpeedButton;
    SpeedButton58: TSpeedButton;
    SpeedButton59: TSpeedButton;
    SpeedButton60: TSpeedButton;
    SpeedButton61: TSpeedButton;
    SpeedButton62: TSpeedButton;
    Image21: TImage;
    Panel4: TPanel;
    Label2: TLabel;
    Edit_art_idx: TEdit;
    Edit3: TEdit;
    Label4: TLabel;
    Edit_encounter_difficulty: TEdit;
    Label3: TLabel;
    Label_walk_mask_name: TLabel;
    Edit_walk_mask_name: TEdit;
    Panel5: TPanel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    ComboBox6: TComboBox;
    ComboBox5: TComboBox;
    ComboBox4: TComboBox;
    ComboBox3: TComboBox;
    ComboBox2: TComboBox;
    ComboBox1: TComboBox;
    SpeedButton63: TSpeedButton;
    BitBtn1: TBitBtn;
    EditEncounterTables1: TMenuItem;
    EditEncounterGroup1: TMenuItem;
    Maps1: TMenuItem;
    Worldmaptxt1: TMenuItem;
    Worldmapmsg1: TMenuItem;
    CrittersPid1: TMenuItem;
    ItemsPid1: TMenuItem;
    Scripts1: TMenuItem;
    About1: TMenuItem;
    Label_Nazwa_Tile: TLabel;
    Image22: TImage;
    Label12: TLabel;
    Label5: TLabel;
    ShowHideCities1: TMenuItem;
    ListBox1: TListBox;
    BitBtn3: TBitBtn;
    BitBtn4: TBitBtn;
    Label1: TLabel;
    BitBtn2: TBitBtn;
    BitBtn5: TBitBtn;
    ShowHideSpeedButtonCaption1: TMenuItem;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    ListBox2: TListBox;
    Setup1: TMenuItem;
    Backgroundmap1: TMenuItem;
    StatusBar1: TStatusBar;
    procedure Encounterfrequencypercentages1Click(Sender: TObject);
    procedure Zakocz2Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure SpeedButton63Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure ComboBox2Change(Sender: TObject);
    procedure ComboBox3Change(Sender: TObject);
    procedure ComboBox4Change(Sender: TObject);
    procedure ComboBox5Change(Sender: TObject);
    procedure ComboBox6Change(Sender: TObject);
    procedure ToolButton7Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure ShowHideCities1Click(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
    procedure BitBtn4Click(Sender: TObject);
    procedure BitBtn5Click(Sender: TObject);
    procedure EditEncounterTables1Click(Sender: TObject);
    procedure EditEncounterGroup1Click(Sender: TObject);
    procedure SpeedButton1MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton2MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton3MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton4MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton5MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton6MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton7MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton8MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton9MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure SpeedButton10MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton11MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton12MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton13MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton14MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton15MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton16MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton17MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton18MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton19MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SpeedButton20MouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure ShowHideSpeedButtonCaption1Click(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure CrittersPid1Click(Sender: TObject);
    procedure Edit_encounter_difficultyKeyPress(Sender: TObject;
      var Key: Char);
    procedure Edit_walk_mask_nameKeyPress(Sender: TObject; var Key: Char);
    procedure Backgroundmap1Click(Sender: TObject);


  private
    { Private declarations }
    procedure SpeedButton_Click(Sender: TObject);           // na mapie swiata
    procedure OnClick_SpeedButton(Sender: TObject);  // na mapie ma³ej pojedynczego Du¿ego Tilesa
    Procedure Miasta(numer_image:Integer; iter:Byte);

    Procedure Edytuj_Maly_Tiles(SpeedButton_Numer:Byte);
    Function numer_malego_tilesa(wartosc_SpeedButton_Numer:Integer):String;
    Procedure Czytaj_Tilesa;
    Procedure Edytuj_Duzy_Tiles(numer_tilesa:Byte);
    Procedure Ladowanie_List_Do_ComboBox;

    function Nazwa_terenu(numer_duzego_tiles:Byte;SpeedButtonNumer:Byte):String;

    Procedure mark_selected_tile(numer_licznika:integer);

  public
    { Public declarations }

end;

var
  Form1: TForm1;
  i,j:Integer;
  INI:TIniFile;
  plik_worldmap:TIniFile;
  plik_pro_crit:TIniFile;
  maps_txt:TIniFile;
  city_ini:TIniFile;
  numer_tilesa:Byte;
  numer_duzego_tilesa:Byte;
  walk_mask_name:String;
//  city_txt:TIniFile;
//  bitmap:TBitmap;

  poz_x,poz_y:Integer; //wspó³rzêdne napisu nazwy miasta na Image
  wsp_x,wsp_y:Double; // wpsólczynniki przeskalowywania mapy swiata
  napis:String;  // nazwa miasta (napis)
  rozmiar_miasta:String;
  tile_height,tile_width:Integer; {wysokosc, szerokosc obrazka przyjeta do wyswietlania}

  X1,X2,Y1,Y2:Integer; // zmienne wspolrzednych rysowania czerwonej obwodki na malym aktualnie kliknietym i edytowanym Tilesie \(rysuje na Canvas maly czerwony kwadrat)
  last_X1,last_Y1,last_X2,last_Y2:Integer; // to samo co wyzej ale dla czyszczenia kwadratu jako ostatnio wcisniete wpsolrzedne

  linia_terrain:String;

  Lista_Critters: TStringList;
  Lista_Items: TStringList;
  Lista_Scripts: TStringList;
  Lista: TStringList;
  Lista_maps: TStringList;
  Lista_Encounters:TStringList; // 25-06-2013 przeniesiona do Unit3_List_Encounters, do FormCreate
  Lista_Enc_Tables: TStringList;
//  Lista_terrains:TStringList;
//  Lista_fills:TStringList;
//  Lista_chances:TStringList;


  duzy_tiles,maly_tiles:String;
  SpeedButton_Numer:Integer;

  selected_encounter_table:String; // zmienna okreslajaca nazwe wybranego Enc. Table w zaleznosci gdzie byl wybrany (z menu lub z przycisku) 

  path_bmp:String; // sciezka do obrazkow mapy swiata FO1 lub FO2

implementation

uses Unit4_Enc_Percentage, Unit5, Unit3_List_Encounters, Unit9_add_maps,
  Unit10_lista_enc_table, Unit12, Unit13_Setup;

{$R *.dfm}


procedure TForm1.Encounterfrequencypercentages1Click(Sender: TObject);
begin
  If not Assigned(Form4) then
  begin
//    Form2:=TForm2.Create(Application);
    Form4:=TForm4.Create(nil);   // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form4.Show;
  end
  else
  Form4.Show;
end;

procedure TForm1.Zakocz2Click(Sender: TObject);
begin
  Form1.Close;
  Form1:=nil;
end;

procedure TForm1.FormActivate(Sender: TObject);
begin
  WindowState:=wsMaximized;
end;


function TForm1.Nazwa_terenu(numer_duzego_tiles:Byte;SpeedButtonNumer:Byte):String;
var linia_cala:String;
    linia_terrain:String;
    pozycja_ciecia:Byte;
begin
  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
   linia_cala:=plik_worldmap.ReadString('Tile '+IntToStr(numer_duzego_tilesa), numer_malego_tilesa(SpeedButtonNumer+20), 'blah blah i dupa');
  finally
    plik_worldmap.Free;
  end;
  linia_terrain:=linia_cala;
  pozycja_ciecia:=pos(',',linia_terrain);
  Delete(linia_terrain,pozycja_ciecia,length(linia_terrain)-(pozycja_ciecia-1));
  Nazwa_Terenu:=linia_terrain[1];
end;


Procedure TForm1.Edytuj_Duzy_Tiles(numer_tilesa:Byte);
var licznik_:Integer;
    i,j,licznik:Byte;  // zmienne iteracyjne
//    iter, joter:Byte; // zmienne iteracyjne (musza byc drugie bo i, j  s¹ zajete)
    Image:TImage;
begin
        numer_duzego_tilesa:=numer_tilesa;
        Label_Nazwa_Tile.Caption:='[Tile '+IntToStr(numer_tilesa)+']';
        plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
        try
          Edit_art_idx.Text:= plik_worldmap.ReadString('Tile '+IntToStr(numer_tilesa), 'art_idx', '339');
          Edit_encounter_difficulty.Text:=plik_worldmap.ReadString('Tile '+IntToStr(numer_tilesa), 'encounter_difficulty', '0');
          walk_mask_name:=plik_worldmap.ReadString('Tile '+IntToStr(numer_tilesa), 'walk_mask_name', '');
          Edit_walk_mask_name.Text:=walk_mask_name;
          if walk_mask_name='' then
          begin
//            Edit_walk_mask_name.Visible:=False;
//            Label_walk_mask_name.Visible:=False;
          end
          else
          begin
            Edit_walk_mask_name.Visible:=True;
            Label_walk_mask_name.Visible:=True;
          end
        finally
          plik_worldmap.Free;
        end;


        with Panel3 do
        begin
          Font.Color:=clYellow;
          Font.Size:=10;
          Font.Name := 'Arial'; // nazwa czcionki: Arial Black
         // Font.Style:=[fsBold];
        end;



        with Image21 do
        begin
          Parent:=Panel3;
          Height:=Panel3.Height-2;       //wysokosc
          Width:=Panel3.Width-2;        //szerokosc
          Top:=1;
          Left:=1;
          stretch:=True;

          if numer_tilesa<10 then Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp'+IntToStr(0)+IntToStr(numer_tilesa)+'.bmp');
          if numer_tilesa>=10 then Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp'+IntToStr(numer_tilesa)+'.bmp');

          Canvas.Pen.Color := clGray;
          Canvas.Pen.Width:=1;
          Canvas.Pen.Style := psSolid;
          for i:=0 to 7 do Canvas.Rectangle(i*50, 0, i*50+1, 300);
            for i:=0 to 6 do Canvas.Rectangle(0, i*50, 350, i*50+1);
        end;


        licznik:=0;
        i:=1;
        j:=0;

        with SpeedButton21 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

//instrukcja ponizej uzupe³niona 06-08-2008
          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_tilesa,licznik);

          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton22 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;


        with SpeedButton23 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;


        with SpeedButton24 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton25 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton26 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton27 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton28 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton29 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;


        with SpeedButton30 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton31 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton32 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;


        with SpeedButton33 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton34 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton35 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;


        with SpeedButton36 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton37 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;


        with SpeedButton38 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton39 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton40 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton41 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton42 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton43 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton44 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton45 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton46 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton47 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton48 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton49 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton50 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;


//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton51 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton52 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton53 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton54 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton55 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton56 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton57 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton58 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton59 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton60 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

        with SpeedButton61 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;


        with SpeedButton62 do
        begin
          inc(licznik);
          if licznik mod (i*7+1)=0 then
          begin
            inc(i);
            j:=0;
          end;
          inc(j);

          Parent:=Panel3;
          Height:=50;       //wysokosc
          Width:=50;        //szerokosc
          Top:=0;
          Left:=0;
          Top:=i*(50)-50;
          Left:=j*(50)-50;

//          Transparent:=True;  //?? --> dobrze siê wyswietla przy true i false
          Cursor:=crCross;
          Flat:=True;
          BringToFront;

          Caption:=IntToStr(j-1)+'_'+IntToStr(i-1)+' '+Nazwa_Terenu(numer_duzego_tilesa,licznik);
          OnClick := OnClick_SpeedButton;
        end;

  Edytuj_Maly_Tiles(21); //      Wykonaj_procedure_wczytywania_malego_tilesa SpeedButton nr 21, Maly_Tiles="0_0";

  with Image21 do  // powoduje zaznaczenie pierwszego malego tilesa w lewym gornym rogu podczas uruchamiania programu i kazdego kliknniecia duzego tilesa
  begin
    Canvas.Pen.Color:=clLime;
    Canvas.Pen.Style:=psSolid;
    Canvas.Pen.Width:=2;
    Canvas.Brush.Style := bsBDiagonal;
//    Canvas.Brush.Style := bsClear;

    Canvas.Rectangle(0,0,50,50);

//    Canvas.Pen.Color:=clRed;
//    Canvas.Pen.Style:=psSolid;

    last_X1:=0;
    last_Y1:=0;
    last_X2:=50;
    last_Y2:=50;
  end;

end;

procedure TForm1.SpeedButton_Click(Sender: TObject);    // dla Duzych Tilesów na panelu z lewej strony
var licznik_:Integer;
//    i,j,licznik:Byte;  // zmienne iteracyjne
//    iter, joter:Byte; // zmienne iteracyjne (musza byc drugie bo i, j  s¹ zajete)
//    Image:TImage;
//    SpeedButton:TSpeedButton;
begin
  licznik_:=0;
  While licznik_<>20 do
  begin
    inc(licznik_);
    numer_tilesa:=licznik_-1;
    if (Sender is TSpeedButton) then
    if (Sender as TSpeedButton).name = 'SpeedButton'+IntToStr(licznik_) then
    begin
      Edytuj_Duzy_Tiles(numer_tilesa);
    end;
  end;
end;

Procedure TForm1.mark_selected_tile(numer_licznika:integer);
var Lista:TStringList; // uniwersalna tymczasowa pomocnicza zmienna do tworzenia list i ich wpisywania do combobox itp i potem jest zaraz niszczona za pomoc¹ .Free

begin
  Lista := TStringList.Create;
  try
    Lista.Add(IntToStr(numer_licznika));

//    ListBox2.Items.Clear;                             //ListBox2 - komponent niewidoczny sluzacy do zbierania informacji o numerach zaznaczoncyh przyciskow malych Tilesów w celu jednoczesnego usatwienia typu random encountera dla wszystkich tilesdów jednym kliknieciem
    ListBox2.Items.AddStrings(Lista);
  finally
    Lista.Free;
  end;
end;

procedure TForm1.OnClick_SpeedButton(Sender: TObject);      // dla Malego_Tiles (dla SpeedButton malych tilesow
var licznik_:Integer;
//    i,j:Byte;
begin
//  i:=0;
//  j:=0;
  licznik_:=20; // nazwy malych przyciskow zaczynaja sie od SpeedButton21 i koncza na SpeddButton62
  While licznik_<=62 do
  begin
    inc(licznik_);
    SpeedButton_Numer:=licznik_;
    if (Sender is TSpeedButton) then
    if (Sender as TSpeedButton).name = 'SpeedButton'+IntToStr(licznik_) then
    begin
//      ShowMessage(' kliknales przycisk '+IntToStr(licznik_)); // debug!!!!
      if CheckBox1.Checked=False then begin
        Edytuj_Maly_Tiles(licznik_); //      Wykonaj_procedure_wczytywania_malego_tilesa;
      end
      else
      begin
//    ListBox2.Items.Clear;                             //ListBox2 - komponent niewidoczny sluzacy do zbierania informacji o numerach zaznaczoncyh przyciskow malych Tilesów w celu jednoczesnego usatwienia typu random encountera dla wszystkich tilesdów jednym kliknieciem
          ListBox2.Items.Append(numer_malego_tilesa(licznik_));
      end;


//      (Sender as TSpeedButton).Font.Color:=clRed{Maroon};     // - zaznacza ze ten SpeedButton zosta³ klikniety

    if checkBox2.Checked then begin
      if linia_terrain='Mountain' then
      begin
        (Sender as TSpeedButton).Caption:='M';
        (Sender as TSpeedButton).Font.Color:=clMaroon;
      end;
      if linia_terrain='City' then
      begin
        (Sender as TSpeedButton).Caption:='C';
        (Sender as TSpeedButton).Font.Color:=clWhite;
      end;
      if linia_terrain='Ocean' then
      begin
        (Sender as TSpeedButton).Caption:='O';
        (Sender as TSpeedButton).Font.Color:=clBlue;
      end;
      if linia_terrain='Desert' then
      begin
        (Sender as TSpeedButton).Caption:='D';
        (Sender as TSpeedButton).Font.Color:=clYellow;
      end;
    end;

      with Image21 do
      begin
        Canvas.Pen.Color:=clGray; // clGray - szary kolor obwodki, czyli tak jak oryginal
//        Canvas.Pen.Color:=clLime;  // clLime - jasnozielony kolor obwodki, czyli ze byl wczesniej juz klikniety
        Canvas.Pen.Style:=psSolid;
        Canvas.Pen.Width:=2;
        Canvas.Brush.Style := bsClear;
//        Canvas.Rectangle((i-1)*50,(j-1)*50,(i-1)*50+50,(j-1)*50+50);
        Canvas.Rectangle(last_X1,last_Y1,last_X2,last_Y2);

        j:=(licznik_ - 21) div 7+1; // to jest OK
        i:=licznik_ - 13-j*7;  // to te¿ jest OK :)
//        Showmessage('licznik= '+IntToStr(licznik_)+'  i= '+IntToStr(i)+'   j= '+IntToStr(j));
        X1:=(i-1)*50;
        Y1:=(j-1)*50;
        X2:=(i-1)*50+50;
        Y2:=(j-1)*50+50;

        Canvas.Pen.Color:=clLime;
        Canvas.Pen.Width:=2;
        Canvas.Pen.Style:=psSolid;
        Canvas.Brush.Style := bsBDiagonal;

//        Canvas.Rectangle((i-1)*50,(j-1)*50,(i-1)*50+50,(j-1)*50+50);
        Canvas.Rectangle(X1,Y1,X2,Y2);

        last_X1:=(i-1)*50;
        last_Y1:=(j-1)*50;
        last_X2:=(i-1)*50+50;
        last_Y2:=(j-1)*50+50;
      end;
    end;
  end;
end;


Function TForm1.numer_malego_tilesa(wartosc_SpeedButton_Numer:Integer):String;
begin
  case wartosc_SpeedButton_Numer-20 of        // odejmowanie 20 bo numery SpeddButtonow zaczynaja sie od 21!!!
  1:begin numer_malego_tilesa:='0_0'; end;
  2:begin numer_malego_tilesa:='1_0'; end;
  3:begin numer_malego_tilesa:='2_0'; end;
  4:begin numer_malego_tilesa:='3_0'; end;
  5:begin numer_malego_tilesa:='4_0'; end;
  6:begin numer_malego_tilesa:='5_0'; end;
  7:begin numer_malego_tilesa:='6_0'; end;
  8:begin numer_malego_tilesa:='0_1'; end;
  9:begin numer_malego_tilesa:='1_1'; end;
  10:begin numer_malego_tilesa:='2_1'; end;
  11:begin numer_malego_tilesa:='3_1'; end;
  12:begin numer_malego_tilesa:='4_1'; end;
  13:begin numer_malego_tilesa:='5_1'; end;
  14:begin numer_malego_tilesa:='6_1'; end;
  15:begin numer_malego_tilesa:='0_2'; end;
  16:begin numer_malego_tilesa:='1_2'; end;
  17:begin numer_malego_tilesa:='2_2'; end;
  18:begin numer_malego_tilesa:='3_2'; end;
  19:begin numer_malego_tilesa:='4_2'; end;
  20:begin numer_malego_tilesa:='5_2'; end;
  21:begin numer_malego_tilesa:='6_2'; end;
  22:begin numer_malego_tilesa:='0_3'; end;
  23:begin numer_malego_tilesa:='1_3'; end;
  24:begin numer_malego_tilesa:='2_3'; end;
  25:begin numer_malego_tilesa:='3_3'; end;
  26:begin numer_malego_tilesa:='4_3'; end;
  27:begin numer_malego_tilesa:='5_3'; end;
  28:begin numer_malego_tilesa:='6_3'; end;
  29:begin numer_malego_tilesa:='0_4'; end;
  30:begin numer_malego_tilesa:='1_4'; end;
  31:begin numer_malego_tilesa:='2_4'; end;
  32:begin numer_malego_tilesa:='3_4'; end;
  33:begin numer_malego_tilesa:='4_4'; end;
  34:begin numer_malego_tilesa:='5_4'; end;
  35:begin numer_malego_tilesa:='6_4'; end;
  36:begin numer_malego_tilesa:='0_5'; end;
  37:begin numer_malego_tilesa:='1_5'; end;
  38:begin numer_malego_tilesa:='2_5'; end;
  39:begin numer_malego_tilesa:='3_5'; end;
  40:begin numer_malego_tilesa:='4_5'; end;
  41:begin numer_malego_tilesa:='5_5'; end;
  42:begin numer_malego_tilesa:='6_5'; end;

  else numer_malego_tilesa:='0_0';
  end
end;








procedure TForm1.BitBtn1Click(Sender: TObject);
var linia:String;
    iter:Word;
    znak:Char;
    Linia2:String;
    i:byte;
//    fill_string:String;
begin
  Panel1.Enabled:=True;
  Panel4.Enabled:=True;
  Panel3.Enabled:=True;
  BitBtn1.Font.Color:=clBlack;
  BitBtn1.Font.Style := [];

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),'encounter_difficulty', Edit_encounter_difficulty.Text);
    //if Length(Trim(Edit_Walk_Mask_Name.Text))>0 then
      plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),'walk_mask_name', Trim(Edit_Walk_Mask_Name.Text));
  finally
    plik_worldmap.Free;
  end;

  if CheckBox1.Checked then      // Select Tiles mode - zaznaczanie malych tilesow do masowego ustawiania typu terenu itp  
  begin
    for i := 0 to ListBox2.Count - 1 do
    begin
//        ShowMessage('wartosc_SpeedButton_Numer = '+ListBox2.Items.Strings[i]);
      maly_tiles:=ListBox2.Items.Strings[i];
//        ShowMessage('maly tiles = '+maly_tiles);

      plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
      try
        linia:=Combobox1.Items[ComboBox1.ItemIndex]+','+Combobox2.Items[ComboBox2.ItemIndex]{fill_string}+','+Combobox3.Items[ComboBox3.ItemIndex]+
        ','+Combobox3.Items[ComboBox3.ItemIndex]+','+Combobox3.Items[ComboBox3.ItemIndex]+','+Combobox6.Items[ComboBox6.ItemIndex];

//        linia:=Combobox1.Items[ComboBox1.ItemIndex]+','+Combobox2.Items[ComboBox2.ItemIndex]{fill_string}+','+Combobox3.Items[ComboBox3.ItemIndex]+
//        ','+Combobox4.Items[ComboBox4.ItemIndex]+','+Combobox5.Items[ComboBox5.ItemIndex]+','+Combobox6.Items[ComboBox6.ItemIndex];

//  ShowMessage(linia);
//  ShowMessage('Tile '+IntToStr(numer_duzego_tilesa));
//  ShowMessage('maly_tiles '+(maly_tiles));

        plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),maly_tiles,linia);

      finally
        plik_worldmap.Free;
      end;

      plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
      try
        linia2:='';
        linia:=ListBox1.Items.CommaText;
        for iter:=1 to Length(linia) do
        begin
          znak:=linia[iter];
          if znak <> '"' then
          begin
            linia2:=linia2+znak;
          end;
//    else
          if znak = ',' then
          begin
            linia2:=linia2+' ';
          end;
        end;

        plik_worldmap.WriteString('Encounter Table '+IntToStr(ComboBox6.ItemIndex),'maps',linia2);

//  ShowMessage(linia);
//  ShowMessage(linia2);
//  ShowMessage('Tile '+IntToStr(numer_duzego_tilesa));
//  ShowMessage('maly_tiles '+(maly_tiles));

//   plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),maly_tiles,linia);

      finally
        plik_worldmap.Free;
      end;
    end;

    Edytuj_Duzy_Tiles(numer_duzego_tilesa);          // odswieza widok planszy malych tilesow
    ListBox2.Clear;
//    CheckBox1.Checked:=False;

  end
  else
  begin   // zapis Tilesa do worldmap.txt
    maly_tiles:=Label5.Caption;


//  Delete(maly_tiles,1,10);  - ta linia moze sie jeszcze przydac!!!

{ //Sa problemy z zaprogramowaniem odczytu do ComboBox gdy jest dodany napis " - experimantal!" wiec pni¿sze sa wy³aczone a w ComboBox wywalony ten dodatkowy napis
  fill_string:=Combobox2.Items[ComboBox2.ItemIndex];
  if (ComboBox2.ItemIndex>=2) and (ComboBox2.ItemIndex<=4) then delete(fill_string,7,length(fill_string)-(7-1));
  if (ComboBox2.ItemIndex>=5) and (ComboBox2.ItemIndex<=7) then delete(fill_string,8,length(fill_string)-(8-1));
}

    plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
    try
      linia:=Combobox1.Items[ComboBox1.ItemIndex]+','+Combobox2.Items[ComboBox2.ItemIndex]{fill_string}+','+Combobox3.Items[ComboBox3.ItemIndex]+
      ','+Combobox3.Items[ComboBox3.ItemIndex]+','+Combobox3.Items[ComboBox3.ItemIndex]+','+Combobox6.Items[ComboBox6.ItemIndex];

//    linia:=Combobox1.Items[ComboBox1.ItemIndex]+','+Combobox2.Items[ComboBox2.ItemIndex]{fill_string}+','+Combobox3.Items[ComboBox3.ItemIndex]+
//    ','+Combobox4.Items[ComboBox4.ItemIndex]+','+Combobox5.Items[ComboBox5.ItemIndex]+','+Combobox6.Items[ComboBox6.ItemIndex];


//  ShowMessage(linia);
//  ShowMessage('Tile '+IntToStr(numer_duzego_tilesa));
//  ShowMessage('maly_tiles '+(maly_tiles));

      plik_worldmap.WriteString('Tile ' + IntToStr(numer_duzego_tilesa), maly_tiles, linia);

    finally
      plik_worldmap.Free;
    end;

    plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
    try
      linia2:='';
      linia:=ListBox1.Items.CommaText;
      for iter:=1 to Length(linia) do
      begin
        znak:=linia[iter];
        if znak <> '"' then
        begin
          linia2:=linia2+znak;
        end;
//    else
        if znak = ',' then
        begin
          linia2:=linia2+' ';
        end;
      end;

      plik_worldmap.WriteString('Encounter Table ' + IntToStr(ComboBox6.ItemIndex), 'maps', linia2);

//  ShowMessage(linia);
//  ShowMessage(linia2);
//  ShowMessage('Tile '+IntToStr(numer_duzego_tilesa));
//  ShowMessage('maly_tiles '+(maly_tiles));

//   plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),maly_tiles,linia);

    finally
      plik_worldmap.Free;
    end;
  end;


  // Dzia³a poprawnie ale za kazdym przycisnieciem "save" czysci juz przegladniete male tilesy :( :( :(
//  Edytuj_Duzy_Tiles(numer_duzego_tilesa);
end;



Procedure TForm1.Miasta(numer_image:Integer; iter:Byte);
var string_x,string_y:string;
    string_xy:string[9];
    sekcja:String;
    pozycja_ciecia:Integer;
    x,y:Integer;
    area_name:String;  // nazwa miasta (napis)
    size:String;
    iter2:integer;
    string_tymcz:string;

begin
    begin
      city_ini:= TINIFile.Create(ExtractFilePath(Application.ExeName) + 'city.txt');
      try
        if iter<10 then sekcja:='Area 0'+IntToStr(iter);
        if iter>=10 then sekcja:='Area '+IntToStr(iter);
        string_xy:=city_ini.ReadString(sekcja, 'world_pos', '10,10');
//        ShowMessage('string_xy = '+string_xy+';');
        if string_xy[length(string_xy)]=' ' then
        begin
          string_tymcz:='';
          for iter2:=1 to length(string_xy)-1 do
          begin
            string_tymcz:=string_tymcz+string_xy[iter2];
          end;
          string_xy:='';
          string_xy:=string_tymcz;
        end;

//        ShowMessage('string_xy = '+string_xy+';');

        if string_xy[length(string_xy)]=' ' then
        begin
          string_tymcz:='';
          for iter2:=1 to length(string_xy)-1 do
          begin
            string_tymcz:=string_tymcz+string_xy[iter2];
          end;
          string_xy:='';
          string_xy:=string_tymcz;
        end;

        if string_xy[length(string_xy)]=' ' then
        begin
          string_tymcz:='';
          for iter2:=1 to length(string_xy)-1 do
          begin
            string_tymcz:=string_tymcz+string_xy[iter2];
          end;
          string_xy:='';
          string_xy:=string_tymcz;
        end;

        if string_xy[length(string_xy)]=' ' then
        begin
          string_tymcz:='';
          for iter2:=1 to length(string_xy)-1 do
          begin
            string_tymcz:=string_tymcz+string_xy[iter2];
          end;
          string_xy:='';
          string_xy:=string_tymcz;
        end;


        string_x:=string_xy;
        string_y:=string_xy;
        pozycja_ciecia:=pos(',',string_x);
        delete(string_x,pozycja_ciecia,length(string_x)-pozycja_ciecia+1);

        pozycja_ciecia:=pos(',',string_y);
        delete(string_y,1,pozycja_ciecia);
        delete(string_y,pos(Char(9),string_y),length(string_y)-pozycja_ciecia+1);

        area_name:=city_ini.ReadString(sekcja, 'area_name', 'Pipidówa');
        size:=city_ini.ReadString(sekcja, 'size', 'King size');
        delete(size,pos(Char(9),size),length(size)-pos(Char(9),size)+1);

        x:=Trunc(StrToInt(string_x)*wsp_x);
        y:=Trunc(StrToInt(string_y)*wsp_y);


        case numer_image of
        1: begin
             //if (x<=tile_width) and (y<=tile_height) then
             begin
//        ShowMessage('Wspó³rzêdne: '+IntToStr(x)+','+IntToStr(y));
               poz_x:=x;
               poz_y:=y;
               napis:=area_name;
//               ShowMessage('Nazwa miasta: '+napis);
               rozmiar_miasta:=size;
             end;
           end;
        2: begin
           end;
        end;
      finally
        city_ini.Free;
      end;
    end;
end;



procedure TForm1.FormCreate(Sender: TObject);
var iter:byte;
    Image: TImage;
    Bitmapa_1,Bitmapa_2:TBitMap;
    nazwa_1,nazwa_2:String;


begin
  Caption:='FO2 Worldmap Tile Editor - ver 1.0.0.32';
// create Form1
  DoubleBuffered := True;
  with Panel1 do
  begin
//    Parent:=Form1;
    DoubleBuffered := True;
    BevelInner:=bvRaised;
    BevelOuter:=bvLowered;
    Caption:='';
    Top:=2;
    Left:=2;
    INI := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'tile_editor.ini');
    try
      if not INI.ValueExists('Panel', 'width') then
      begin
        INI.WriteInteger('Panel', 'width', 600);
      end;

      if not INI.ValueExists('Panel', 'height') then
      begin
        INI.WriteInteger('Panel', 'height', 700);
      end;

      if not INI.ValueExists('Background picture', 'path_bmp') then
      begin
        INI.WriteString('Background picture', 'path_bmp', '\FO2_BMP\');
      end;


      Width:=INI.ReadInteger('Panel', 'width', 600);
      Height:=INI.ReadInteger('Panel', 'height', 700);
      path_bmp:=INI.ReadString('Background picture', 'path_bmp', '\FO2_BMP\')


    finally
      INI.Free;
    end;
//    ShowMessage('Rozmiary Panel1: '+IntToStr(Width)+','+IntToStr(Height));
  end;

  with Panel2 do
  begin
    Parent:=Form1;
//    BevelInner:=bvRaised;
//    BevelOuter:=bvLowered;
    Caption:='';
    Left:=Panel1.Left+Panel1.Width+5;
    Top:=2;
    Width:=369;
    Height:=696;
  end;


  wsp_x:=Panel1.Width/1400;
  wsp_y:=Panel1.Height/1500;


  tile_width:=Trunc((Panel1.Width)/4);
  tile_height:=Trunc((Panel1.Height)/5);


  with Image22 do
  begin
    DoubleBuffered := True;
    Transparent:=True;
    Parent:=Panel1;
    Width:=Panel1.Width;
    Height:=Panel1.Height;
    Align:=alClient;
//    SendToBack;
//    BringToFront;

//    Canvas.Pen.Color:=clLime;
//    Canvas.Pen.Width:=2;
//    Canvas.Pen.Style:=psDash;
//    Canvas.Brush.Style := bsBDiagonal;
//    Canvas.Rectangle(0,0,Width,Height);


    Canvas.Font.Size:=9;
    Canvas.Font.Color:=clyellow;
    for iter:=0 to 255 do
    begin
      Miasta(1,iter);
//      Image22.Picture.LoadFromFile('medium.bmp');
//      Canvas.TextOut(poz_x,poz_y,IntToStr(poz_x)+','+IntToStr(poz_y)+':'+napis);
      Canvas.TextOut(poz_x,poz_y-20,napis);

      Canvas.Brush.Color := clGreen;
      Canvas.Brush.Style := bsDiagCross;
      Canvas.Ellipse(poz_x,poz_y,poz_x+15,poz_y+15);

//      Refresh;
    end;
  end;


{  for iter:=0 to 19 do
  begin
    Bitmapa_1 := TBitmap.Create;

    if iter<10 then
      nazwa_1:='wrldmp0'+IntToStr(iter)+'.bmp'
    else
      nazwa_1:='wrldmp'+IntToStr(iter)+'.bmp';

    Bitmapa_1.LoadFromFile(nazwa_1);

    Bitmapa_2 := TBitmap.Create;
    Bitmapa_2.Width:= Round(wsp_x*Bitmapa_1.Width);
    Bitmapa_2.Height:= Round(wsp_y*Bitmapa_1.Height);
    Bitmapa_2.Canvas.StretchDraw(Rect(0, 0, Bitmapa_2.Width, Bitmapa_2.Height),Bitmapa_1);

    if iter<10 then
      nazwa_2:='bitmapa0'+IntToStr(iter)+'.bmp'
    else
      nazwa_2:='bitmapa'+IntToStr(iter)+'.bmp';

    Bitmapa_2.SaveToFile(nazwa_2);
    Bitmapa_1.Free;
    Bitmapa_2.Free;
  end;
}



  with Image1 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*0;
    Top:=tile_height*0;
//    Picture.LoadFromFile('bitmapa00.bmp');
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp00.bmp');
    stretch:=True;
{
    Canvas.Font.Size:=9;
    Canvas.Font.Color:=clyellow;
    for iter:=0 to 48 do
    begin
      Miasta(1,iter);
      Canvas.TextOut(poz_x,poz_y-20,napis);

      Canvas.Brush.Color := clRed;
      Canvas.Brush.Style := bsDiagCross;
      Canvas.Ellipse(poz_x,poz_y,poz_x+15,poz_y+15);
    end;
 }
  end;

  with Image2 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*1;
    Top:=tile_height*0;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp01.bmp');
{
    Canvas.Font.Size:=9;
    Canvas.Font.Color:=clyellow;
    for iter:=0 to 48 do
    begin
      Miasta(1,iter);
      Canvas.TextOut(poz_x,poz_y-20,napis);

      Canvas.Brush.Color := clRed;
      Canvas.Brush.Style := bsDiagCross;
      Canvas.Ellipse(poz_x,poz_y,poz_x+15,poz_y+15);
    end;}

  end;

  with Image3 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*2;
    Top:=tile_height*0;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp02.bmp');
  end;

  with Image4 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*3;
    Top:=tile_height*0;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp03.bmp');
  end;

  with Image5 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*0;
    Top:=tile_height*1;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp04.bmp');
  end;

  with Image6 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*1;
    Top:=tile_height*1;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp05.bmp');
  end;

  with Image7 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*2;
    Top:=tile_height*1;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp06.bmp');
  end;

  with Image8 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*3;
    Top:=tile_height*1;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp07.bmp');
  end;

  with Image9 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*0;
    Top:=tile_height*2;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp08.bmp');
  end;

  with Image10 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*1;
    Top:=tile_height*2;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp09.bmp');
  end;

  with Image11 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*2;
    Top:=tile_height*2;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp10.bmp');
  end;

  with Image12 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*3;
    Top:=tile_height*2;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp11.bmp');
  end;

  with Image13 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*0;
    Top:=tile_height*3;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp12.bmp');
  end;

  with Image14 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*1;
    Top:=tile_height*3;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp13.bmp');
  end;

  with Image15 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*2;
    Top:=tile_height*3;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp14.bmp');
  end;

  with Image16 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*3;
    Top:=tile_height*3;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp15.bmp');
  end;

  with Image17 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*0;
    Top:=tile_height*4;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp16.bmp');
  end;

  with Image18 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*1;
    Top:=tile_height*4;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp17.bmp');
  end;

  with Image19 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*2;
    Top:=tile_height*4;
    stretch:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp18.bmp');
  end;

  with Image20 do
  begin
    Parent:=Panel1;
    Height:=tile_height;       //wysokosc
    Width:=tile_width;        //szerokosc
    Left:=tile_width*3;
    Top:=tile_height*4;
    stretch:=True;
//    Transparent:=True;
    Picture.LoadFromFile(ExtractFileDir(Application.ExeName)+ path_bmp+'wrldmp19.bmp');
    SendToBack;
  end;
{******************************** End Of Image's **********************************}




{******************************* Start Of SpeedButton's **********************************}

  with SpeedButton1 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*0;
    Top:=tile_height*0;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 0]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton2 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*1;
    Top:=tile_height*0;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 1]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton3 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*2;
    Top:=tile_height*0;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 2]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton4 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*3;
    Top:=tile_height*0;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 3]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton5 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*0;
    Top:=tile_height*1;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 4]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton6 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*1;
    Top:=tile_height*1;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 5]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton7 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*2;
    Top:=tile_height*1;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 6]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton8 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*3;
    Top:=tile_height*1;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 7]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton9 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*0;
    Top:=tile_height*2;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 8]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton10 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*1;
    Top:=tile_height*2;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 9]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton11 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*2;
    Top:=tile_height*2;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 10]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton12 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*3;
    Top:=tile_height*2;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 11]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton13 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*0;
    Top:=tile_height*3;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 12]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton14 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*1;
    Top:=tile_height*3;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 13]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton15 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*2;
    Top:=tile_height*3;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 14]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton16 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*3;
    Top:=tile_height*3;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 15]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton17 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*0;
    Top:=tile_height*4;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 16]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton18 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*1;
    Top:=tile_height*4;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 17]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton19 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*2;
    Top:=tile_height*4;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 18]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  with SpeedButton20 do
  begin
    Parent:=Panel1;
    Height:=tile_height;
    Width:=tile_width;
    Left:=tile_width*3;
    Top:=tile_height*4;
    Font.Color:=clLime;
    Font.Size:=12;
    Caption:='[Tile 19]';

    Transparent:=True;
    Cursor:=crCross;
    Flat:=True;
    OnClick:=SpeedButton_Click;
    BringToFront;
  end;

  Ladowanie_List_Do_ComboBox;  // Ladowanie roznych list do ComboBox

  Edytuj_Duzy_Tiles(0); // podczas ³adowania programu wczytaj [Tiles 0]
end;


Procedure TForm1.Ladowanie_List_Do_ComboBox;
var iter:Byte;
//    iter2:Integer;
    linia_cala:String;
//    temp_string:String; //tymczasowa pomocnicza zmienna
    pozycja_ciecia:Byte;
    sekcja:String;
    Lista:TStringList; // uniwersalna tymczasowa pomocnicza zmienna do tworzenia list i ich wpisywania do combobox itp i potem jest zaraz niszczona za pomoc¹ .Free
    licznik:Integer;
    NazwaCrittersa:String;
begin
  Screen.Cursor:=crHourGlass;
//  List_terrain
  Lista := TStringList.Create;
  try
    Lista.Add('Desert');
    Lista.Add('Mountain');
    Lista.Add('City');
    Lista.Add('Ocean');

    ComboBox1.Items.Clear;
    ComboBox1.Items.AddStrings(Lista);
  finally
    Lista.Free;
  end;

//List_Fill
  Lista := TStringList.Create;
  try
    Lista.Add('No_Fill');
    Lista.Add('Fill_W');
{ //problemy z odczytem gdy jest " - experimantal!"
  Lista.Add('Fill_N - experimental!');
    Lista.Add('Fill_E - experimental!');
    Lista.Add('Fill_S - experimental!');
    Lista.Add('Fill_NW - experimental!');
    Lista.Add('Fill_NE - experimental!');
    Lista.Add('Fill_SW - experimental!');
    Lista.Add('Fill_SE - experimental!');}
{    Lista.Add('Fill_N');
    Lista.Add('Fill_E');
    Lista.Add('Fill_S');
    Lista.Add('Fill_NW');
    Lista.Add('Fill_NE');
    Lista.Add('Fill_SW');
    Lista.Add('Fill_SE');
 }
    ComboBox2.Items.Clear;
    ComboBox2.Items.AddStrings(Lista);
  finally
    Lista.Free;
  end;

//List_Chance
{  Lista := TStringList.Create;
  try
    Lista.Add('Forced');
    Lista.Add('Frequent');
    Lista.Add('Common');
    Lista.Add('Uncommon');
    Lista.Add('Rare');
    Lista.Add('None');
    //morning
    ComboBox3.Items.Clear;
    ComboBox3.Items.AddStrings(Lista);
    //afternoon
    ComboBox4.Items.Clear;
    ComboBox4.Items.AddStrings(Lista);
    //night
    ComboBox5.Items.Clear;
    ComboBox5.Items.AddStrings(Lista);
  finally
    Lista.Free;
  end;
}

//List_Chance_
  Lista := TStringList.Create;
  try
    plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
    try
      sekcja:='Data';
      plik_worldmap.ReadSection(Sekcja, Lista);
      Lista.Delete(Lista.IndexOf('terrain_types'));
      Lista.Delete(Lista.IndexOf('terrain_short_names'));

    finally
      plik_worldmap.Free;
    end;
    //morning
    ComboBox3.Items.Clear;
    ComboBox3.Items.AddStrings(Lista);
    //afternoon
    ComboBox4.Items.Clear;
    ComboBox4.Items.AddStrings(Lista);
    //night
    ComboBox5.Items.Clear;
    ComboBox5.Items.AddStrings(Lista);
  finally
    Lista.Free;
  end;


//List_Encounter_Table  // istnieje caly czas podczas dzialania programu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  Lista_Enc_Tables: TStringList;
  Lista_Enc_Tables := TStringList.Create;
//  try
    plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
    try
      sekcja:='';
      for iter:=0 to 255 do
      begin
        if plik_worldmap.SectionExists('Encounter Table '+IntToStr(iter)) then
        begin
          sekcja:='Encounter Table '+IntToStr(iter);
          linia_cala:=plik_worldmap.ReadString(Sekcja, 'lookup_name', 'blah blah i dupa');
          pozycja_ciecia:=pos(' ',linia_cala);
          Delete(linia_cala,pozycja_ciecia,length(linia_cala)-(pozycja_ciecia-1));

          Lista_Enc_Tables.Add(linia_cala);
        end;
      end;
      ComboBox6.Items.Clear;
      ComboBox6.Items.AddStrings(Lista_Enc_Tables);
    finally
      plik_worldmap.Free;
    end;
//  finally
//    Lista_Enc_Tables.Free;
//  end;


//List_Maps  // istnieje caly czas podczas dzialania programu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  Lista_Maps: TStringList;
  Lista_maps := TStringList.Create;
  maps_txt := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'maps.txt');
  try
    sekcja:='';
    for iter:=0 to 255 do
    begin
      if iter<10 then sekcja:='Map 00';
      if (iter>=10) and (iter<100) then sekcja:='Map 0';
      if iter>=100 then sekcja:='Map ';

      if maps_txt.SectionExists(sekcja+IntToStr(iter)) then
      begin
        sekcja:=sekcja+IntToStr(iter);
//        linia_cala:=maps_txt.ReadString(Sekcja, 'saved', 'blah blah i nie ma mapy!');
//        Delete(linia_cala,3,Length(linia_cala)-2);
//        if (linia_cala='No') or (linia_cala='no') or (linia_cala='NO') then
        begin
          linia_cala:=maps_txt.ReadString(Sekcja, 'lookup_name', 'blah blah i nie ma mapy!');
//        pozycja_ciecia:=pos(' ',linia_cala);
//        Delete(linia_cala,pozycja_ciecia,length(linia_cala)-(pozycja_ciecia-1));
          Lista_maps.Add(linia_cala);
        end;

// lista_maps pozostaje caly czas w pamieci !!!!!!
      end;
    end;
  finally
    maps_txt.Free;
  end;


{
//Lista_Encounters  // 25-06-2013 Przeniesiona do Unit3_Kist_Emcounters w FormCreate, zeby sprawdzac za kazdym otworzeniem okienka, czy nie ma dodanej nowej grupy Encounters
//Lista_Encounters  // istnieje caly czas podczas dzialania programu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    Lista_Encounters:TStringList;
  Lista_Encounters := TStringList.Create;  // beda tu umieszczone TYLKO grupy Encounters (te, ktore opisuj¹ dok³adnie jakie crittersy w nich bed¹ )
  Lista_Encounters.Clear;

  Lista := TStringList.Create; // tymczasowa
  Lista.Clear;
  try
  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    plik_worldmap.ReadSections(Lista);  // W Lista znajduj¹ sie wszystkie sekcje z worldmap.txt

    for iter:=0 to 255 do
    begin
      if plik_worldmap.SectionExists('Encounter Table '+IntToStr(iter)) then
        Lista.Delete(Lista.IndexOf('Encounter Table '+IntToStr(iter)));
    end;

    for iter:=0 to 19 do //np. [Tile 0]
      Lista.Delete(Lista.IndexOf('Tile '+IntToStr(iter)));

    Lista.Delete(Lista.IndexOf('Tile Data'));
    Lista.Delete(Lista.IndexOf('Random Maps: Desert'));
    Lista.Delete(Lista.IndexOf('Random Maps: Mountain'));
    Lista.Delete(Lista.IndexOf('Random Maps: City'));
    Lista.Delete(Lista.IndexOf('Random Maps: Ocean'));
    Lista.Delete(Lista.IndexOf('Data'));


    for iter:=0 to Lista.Count-1 do
    begin
//      if plik_worldmap.SectionExists(Lista.Names[iter]) then
      if plik_worldmap.SectionExists(Lista.Strings[iter]) then
      begin
//        ShowMessage(Lista.Strings[iter]);
        linia_cala:=Lista.Strings[iter];
        Delete(linia_cala,1,11);

        Lista_Encounters.Add(linia_cala);
      end;
    end;

// lista_encounters pozostaje caly czas w pamieci !!!!!!
  finally
    plik_worldmap.Free;
  end;
  finally
    Lista.Free;
  end;
}



//Lista_Critters  // istnieje caly czas podczas dzialania programu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    Lista_Critters:TStringList;
  Lista_Critters := TStringList.Create;  // beda tu umieszczone TYLKO nazwy crittersów z pliku pro_crit.msg
  Lista_Critters.Clear;

  Lista := TStringList.Create; // tymczasowa
  Lista.Clear;
  try
  plik_pro_crit := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'pro_crit.ini');
  licznik:=0;
  try
//    plik_pro_crit.ReadSections(Lista);  // W Lista znajduj¹ sie wszystkie sekcje z pro_crit.ini
    while licznik<483 do
    begin
      inc(licznik);
      NazwaCrittersa:=plik_pro_crit.ReadString('Description',IntToStr(100*licznik),'brak nazwy crittersa');
//      NazwaCrittersa:=ReadIni('pro_crit.ini','Description',IntToStr(100*StrToInt(licznik)));
      Lista_Critters.Add(NazwaCrittersa);

    end;

// Lista_Critters pozostaje caly czas w pamieci !!!!!!
  finally
    plik_pro_crit.Free;
  end;
  finally
    Lista.Free;
  end;

//  Lista_Items: TStringList;
//  Lista_Scripts: TStringList;



  Screen.Cursor:=crDefault;
end;



procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
//  Lista_Encounters.Clear; // 25-06-2013, lista ta obslugiwana w Unit3_List_Encounters
//  Lista_Encounters.Free;  // 25-06-2013, lista ta obslugiwana w Unit3_List_Encounters

  Lista_Enc_Tables.Clear;
  Lista_maps.Clear;


  Lista_Enc_Tables.Free;
  Lista_maps.Free;

  Lista_Critters.Free;
  Lista_Items.Free;
  Lista_Scripts.Free;

end;

procedure TForm1.SpeedButton63Click(Sender: TObject);
begin
// edit encounter table
  selected_encounter_table:=Combobox6.Items[ComboBox6.ItemIndex];
  
  If not Assigned(Form5) then
  begin
//    Form3:=TForm3.Create(Application);
    Form5:=TForm5.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form5.Show;
  end
  else
  begin
    Form5.Close;
    Form5.Destroy;
    Form5:=TForm5.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form5.Show;
  end;
end;

procedure TForm1.ComboBox1Change(Sender: TObject);
begin
   BitBtn1.Font.Color:=clRed;
   BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  Panel4.Enabled:=False;

end;

procedure TForm1.ComboBox2Change(Sender: TObject);
begin
   BitBtn1.Font.Color:=clRed;
   BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  Panel4.Enabled:=False;
   
end;

procedure TForm1.ComboBox3Change(Sender: TObject);
begin
   BitBtn1.Font.Color:=clRed;
   BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  Panel4.Enabled:=False;
end;

procedure TForm1.ComboBox4Change(Sender: TObject);
begin
   BitBtn1.Font.Color:=clRed;
   BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  Panel4.Enabled:=False;
   
end;

procedure TForm1.ComboBox5Change(Sender: TObject);
begin
  BitBtn1.Font.Color:=clRed;
  BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  Panel4.Enabled:=False;

end;


procedure TForm1.ToolButton7Click(Sender: TObject);
begin
  If not Assigned(Form2) then
  begin
//    Form3:=TForm3.Create(Application);
    Form2:=TForm2.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form2.Show;
  end
  else
  begin
    Form2.Close;
    Form2.Destroy;
    Form2:=TForm2.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form2.Show;
  end;
end;

procedure TForm1.BitBtn2Click(Sender: TObject);
begin
  Panel1.Enabled:=True;
  Panel4.Enabled:=True;
  Panel3.Enabled:=True;
  BitBtn1.Font.Color:=clBlack;
  BitBtn1.Font.Style := [];

  Edytuj_Duzy_Tiles(numer_duzego_tilesa);          // odswieza widok planszy malych tilesow
  ListBox2.Clear;
end;

procedure TForm1.ShowHideCities1Click(Sender: TObject);
begin
  if ShowHideCities1.Checked=False then
  begin
    ShowHideCities1.Checked:=True;
    Image22.Visible:=True;
    Image22.Enabled:=True;
  end
  else
  if ShowHideCities1.Checked=True then
  begin
    ShowHideCities1.Checked:=False;
    Image22.Visible:=False;
    Image22.Enabled:=False;
  end;
  
  with Image22 do
  begin
    DoubleBuffered := False;
    Transparent := True;
    SendToBack;
  end;

end;

Procedure TForm1.Czytaj_Tilesa;
var linia_cala:String;
//    linia_terrain:String;
    linia_fill:String;
    linia_morning_chance:String;
    Linia_afternoon_chance:String;
    Linia_night_chance:String;
    Linia_type_enc_table:String;
    pozycja_ciecia:Byte;

    i,j:Byte;
    Sekcja:String;
    lookup_name:String;
    mapy:String; //mapy1,mapy2,mapy3 - pomocnicze gdy linia mapy jest za d³uga i nie zmiesci sie w jednym Label1.Caption
    nazwa_mapy:String;
    znak:Char;

//    Lista_temp: TStringList;   // tymczasowa pomocnicza zmienna


begin
  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    linia_cala:=plik_worldmap.ReadString('Tile '+IntToStr(numer_duzego_tilesa), numer_malego_tilesa(SpeedButton_Numer), 'blah blah i dupa');
  finally
    plik_worldmap.Free;
  end;
//  ShowMessage('Numer duzego Tilesa = '+ IntToStr(numer_duzego_tilesa)); // for debug bo jakies problemy z wartosci¹ "numer_tilesa" jest!!!! wrrr... ale dzia¹³ ju¿ :)

  linia_terrain:=linia_cala;
  linia_fill:=linia_cala;
  linia_morning_chance:=linia_cala;
  Linia_afternoon_chance:=linia_cala;
  Linia_night_chance:=linia_cala;
  Linia_type_enc_table:=linia_cala;

  pozycja_ciecia:=pos(',',linia_terrain);
  Delete(linia_terrain,pozycja_ciecia,length(linia_terrain)-(pozycja_ciecia-1));

  Delete(linia_fill,1,length(linia_terrain));
  Delete(linia_fill,1,1);
  pozycja_ciecia:=pos(',',linia_fill);
  Delete(linia_fill,pozycja_ciecia,length(linia_fill)-(pozycja_ciecia-1));

  Delete(linia_morning_chance,1,length(linia_terrain)); // wycina np. 'Mountain'
  Delete(linia_morning_chance,1,1);          // wycina przecinek
  Delete(linia_morning_chance,1,length(linia_fill)); // wycina np. 'No_fill'
  Delete(linia_morning_chance,1,1);          // wycina przecinek
  pozycja_ciecia:=pos(',',linia_morning_chance);   // ustawia pozycje ciecia na pierwszym napotkanym przecinku (w calej linii to juz trzeci przecinek)
  Delete(linia_morning_chance,pozycja_ciecia,length(linia_morning_chance)-(pozycja_ciecia-1));  //tnie wszytko to co znajduje sie za przecinkiem

  Delete(Linia_afternoon_chance,1,length(linia_terrain)); // wycina np. 'Mountain'
  Delete(Linia_afternoon_chance,1,1);          // wycina pierwszy przecinek
  Delete(Linia_afternoon_chance,1,length(linia_fill)); // wycina np. 'No_fill'
  Delete(Linia_afternoon_chance,1,1);          // wycina drugi przecinek
  Delete(Linia_afternoon_chance,1,length(linia_morning_chance)); // wycina np. pierwszy wyraz 'Rare'
  Delete(Linia_afternoon_chance,1,1);          // wycina trzeci przecinek
  pozycja_ciecia:=pos(',',Linia_afternoon_chance);   // ustawia pozycje ciecia na pierwszym napotkanym przecinku (w calej linii to juz czwarty przecinek)
  Delete(Linia_afternoon_chance,pozycja_ciecia,length(Linia_afternoon_chance)-(pozycja_ciecia-1));  //tnie wszytko to co znajduje sie za przecinkiem

  Delete(Linia_night_chance,1,length(linia_terrain)); // wycina np. 'Mountain'
  Delete(Linia_night_chance,1,1);          // wycina pierwszy przecinek
  Delete(Linia_night_chance,1,length(linia_fill)); // wycina np. 'No_fill'
  Delete(Linia_night_chance,1,1);          // wycina drugi przecinek
  Delete(Linia_night_chance,1,length(linia_morning_chance)); // wycina np. pierwszy wyraz 'Rare'
  Delete(Linia_night_chance,1,1);          // wycina trzeci przecinek
  Delete(Linia_night_chance,1,length(Linia_afternoon_chance)); // wycina np. drugi wyraz 'Rare'
  Delete(Linia_night_chance,1,1);          // wycina czwarty przecinek
  pozycja_ciecia:=pos(',',Linia_night_chance);   // ustawia pozycje ciecia na pierwszym napotkanym przecinku (w calej linii to juz piaty przecinek)
  Delete(Linia_night_chance,pozycja_ciecia,length(Linia_night_chance)-(pozycja_ciecia-1));  //tnie wszytko to co znajduje sie za przecinkiem

  Delete(linia_type_enc_table,1,length(linia_terrain)); // wycina np. 'Mountain'
  Delete(linia_type_enc_table,1,1);          // wycina pierwszy przecinek
  Delete(linia_type_enc_table,1,length(linia_fill)); // wycina np. 'No_fill'
  Delete(linia_type_enc_table,1,1);          // wycina drugi przecinek
  Delete(linia_type_enc_table,1,length(linia_morning_chance)); // wycina np. pierwszy wyraz 'Rare'
  Delete(linia_type_enc_table,1,1);          // wycina trzeci przecinek
  Delete(linia_type_enc_table,1,length(Linia_afternoon_chance)); // wycina np. drugi wyraz 'Rare'
  Delete(linia_type_enc_table,1,1);          // wycina czwarty przecinek
  Delete(linia_type_enc_table,1,length(Linia_night_chance)); // wycina np. trzeci wyraz 'Rare'
  Delete(linia_type_enc_table,1,1);          // wycina piaty przecinek   // i w³asnie mamy gotow¹ ostatni¹ liniê !!!!!!!!!!!!!!!!!!!!!!


  ComboBox1.ItemIndex:=comboBox1.Items.IndexOf(linia_terrain);
  ComboBox2.ItemIndex:=comboBox2.Items.IndexOf(linia_fill);
  ComboBox3.ItemIndex:=comboBox3.Items.IndexOf(linia_morning_chance);
  ComboBox4.ItemIndex:=comboBox4.Items.IndexOf(linia_afternoon_chance);
  ComboBox5.ItemIndex:=comboBox5.Items.IndexOf(linia_night_chance);
  ComboBox6.ItemIndex:=comboBox6.Items.IndexOf(linia_type_enc_table);


  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    sekcja:='';
    for i:=0 to 255 do
    begin
      if plik_worldmap.SectionExists('Encounter Table '+IntToStr(i)) then
      begin
        sekcja:='Encounter Table '+IntToStr(i);
        lookup_name:=plik_worldmap.ReadString(Sekcja, 'lookup_name', 'blah blah i dupa blada');
//        showMessage('lookup_name= '+lookup_name);//debug
        delete(lookup_name,pos(' ',lookup_name),length(lookup_name)-pos(' ',lookup_name)+1);
//        showMessage('delete(lookup_name)= '+lookup_name);//debug
        if lookup_name=Form1.Combobox6.Items[Form1.ComboBox6.ItemIndex] then
        begin
          mapy:='';

          mapy:=plik_worldmap.ReadString(Sekcja, 'maps', 'blah blah i dupa blada');

          pozycja_ciecia:=pos(';',mapy);                                         //wyczyszczenie konca linii ze znaku ; i opisu za nim
          Delete(mapy,pozycja_ciecia,length(mapy)-(pozycja_ciecia-1));           //

          nazwa_mapy:='';
          ListBox1.Clear;

          for j:=1 to Length(mapy) do
          begin
            znak:=mapy[j];
            if (znak<>',') then
            begin
              nazwa_mapy:=nazwa_mapy+znak;
            end;

            if (znak=',') or (j=Length(mapy)) then
            begin
              if nazwa_mapy[1]=' ' then
              begin
                Delete(nazwa_mapy,1,1);  // wycina niepotrzebna spacjê (pierwszy znak z nazwy) z przedniej czesci nazwy mapy
              end;
              ListBox1.Items.Append(nazwa_mapy);
              nazwa_mapy:=''
            end;
          end;

          Break; // koñczy pêtlê gdy sukces!
        end;
      end;
    end;
  finally
    plik_worldmap.Free;
  end;

end;

procedure TForm1.BitBtn3Click(Sender: TObject);
begin
  BitBtn1.Font.Color:=clRed;
  BitBtn1.Font.Style := [fsBold];
  Panel3.Enabled:=False;
  Panel1.Enabled:=False;
  Panel4.Enabled:=False;

  If not Assigned(Form9) then
  begin
//    Form3:=TForm3.Create(Application);
    Form9:=TForm9.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form9.Show;
  end
  else
  begin
    Form9.Close;
    Form9.Destroy;
    Form9:=TForm9.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form9.Show;
  end;

end;

procedure TForm1.BitBtn4Click(Sender: TObject);
begin
  BitBtn1.Font.Color:=clRed;
  BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  Panel4.Enabled:=False;


  ListBox1.DeleteSelected;
end;

procedure TForm1.ComboBox6Change(Sender: TObject);
var // linia_cala:String;
//    linia_terrain:String;
//    linia_fill:String;
//    linia_morning_chance:String;
//    Linia_afternoon_chance:String;
//    Linia_night_chance:String;
//    Linia_type_enc_table:String;
    pozycja_ciecia:Byte;

    i,j:Byte;
    Sekcja:String;
    lookup_name:String;
    mapy:String; //mapy1,mapy2,mapy3 - pomocnicze gdy linia mapy jest za d³uga i nie zmiesci sie w jednym Label1.Caption
    nazwa_mapy:String;
    znak:Char;

//    Lista_temp: TStringList;   // tymczasowa pomocnicza zmienna


begin
  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    sekcja:='';
    for i:=0 to 255 do
    begin
      if plik_worldmap.SectionExists('Encounter Table '+IntToStr(i)) then
      begin
        sekcja:='Encounter Table '+IntToStr(i);
        lookup_name:=plik_worldmap.ReadString(Sekcja, 'lookup_name', 'blah blah i dupa blada');
//        showMessage('lookup_name= '+lookup_name);//debug
        delete(lookup_name,pos(' ',lookup_name),length(lookup_name)-pos(' ',lookup_name)+1);
//        showMessage('delete(lookup_name)= '+lookup_name);//debug
        if lookup_name=Form1.Combobox6.Items[Form1.ComboBox6.ItemIndex] then
        begin
          mapy:='';

          mapy:=plik_worldmap.ReadString(Sekcja, 'maps', 'blah blah i dupa blada');

          pozycja_ciecia:=pos(';',mapy);                                         //wyczyszczenie konca linii ze znaku ; i opisu za nim
          Delete(mapy,pozycja_ciecia,length(mapy)-(pozycja_ciecia-1));           //

          nazwa_mapy:='';
          ListBox1.Clear;

          for j:=1 to Length(mapy) do
          begin
            znak:=mapy[j];
            if (znak<>',') then
            begin
              nazwa_mapy:=nazwa_mapy+znak;
            end;

            if (znak=',') or (j=Length(mapy)) then
            begin
              if nazwa_mapy[1]=' ' then
              begin
                Delete(nazwa_mapy,1,1);  // wycina niepotrzebna spacjê (pierwszy znak z nazwy) z przedniej czesci nazwy mapy
              end;
              ListBox1.Items.Append(nazwa_mapy);
              nazwa_mapy:=''
            end;
          end;

          Break; // koñczy pêtlê gdy sukces!
        end;
      end;
    end;
  finally
    plik_worldmap.Free;
  end;
  BitBtn1.Font.Color:=clRed;
  BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  Panel4.Enabled:=False;
end;

Procedure TForm1.Edytuj_Maly_Tiles(SpeedButton_Numer:Byte);
begin
  Label5.Font.Style:=[fsBold];
  Label5.Font.Color:=clBlue;
  Label5.Caption:=numer_malego_tilesa(SpeedButton_Numer);

  Czytaj_Tilesa;
end;




procedure TForm1.BitBtn5Click(Sender: TObject); //Cancel
begin
  Panel1.Enabled:=True;
  Panel4.Enabled:=True;
  Panel3.Enabled:=True;
  BitBtn1.Font.Color:=clBlack;
  BitBtn1.Font.Style := [];

  with Label5 do
  begin
    if Caption = '0_0' then begin SpeedButton_Numer:=1+20; end;
    if Caption = '1_0' then begin SpeedButton_Numer:=2+20; end;
    if Caption = '2_0' then begin SpeedButton_Numer:=3+20; end;
    if Caption = '3_0' then begin SpeedButton_Numer:=4+20; end;
    if Caption = '4_0' then begin SpeedButton_Numer:=5+20; end;
    if Caption = '5_0' then begin SpeedButton_Numer:=6+20; end;
    if Caption = '6_0' then begin SpeedButton_Numer:=7+20; end;

    if Caption = '0_1' then begin SpeedButton_Numer:=8+20; end;
    if Caption = '1_1' then begin SpeedButton_Numer:=9+20; end;
    if Caption = '2_1' then begin SpeedButton_Numer:=10+20; end;
    if Caption = '3_1' then begin SpeedButton_Numer:=11+20; end;
    if Caption = '4_1' then begin SpeedButton_Numer:=12+20; end;
    if Caption = '5_1' then begin SpeedButton_Numer:=13+20; end;
    if Caption = '6_1' then begin SpeedButton_Numer:=14+20; end;

    if Caption = '0_2' then begin SpeedButton_Numer:=15+20; end;
    if Caption = '1_2' then begin SpeedButton_Numer:=16+20; end;
    if Caption = '2_2' then begin SpeedButton_Numer:=17+20; end;
    if Caption = '3_2' then begin SpeedButton_Numer:=18+20; end;
    if Caption = '4_2' then begin SpeedButton_Numer:=19+20; end;
    if Caption = '5_2' then begin SpeedButton_Numer:=20+20; end;
    if Caption = '6_2' then begin SpeedButton_Numer:=21+20; end;

    if Caption = '0_3' then begin SpeedButton_Numer:=22+20; end;
    if Caption = '1_3' then begin SpeedButton_Numer:=23+20; end;
    if Caption = '2_3' then begin SpeedButton_Numer:=24+20; end;
    if Caption = '3_3' then begin SpeedButton_Numer:=25+20; end;
    if Caption = '4_3' then begin SpeedButton_Numer:=26+20; end;
    if Caption = '5_3' then begin SpeedButton_Numer:=27+20; end;
    if Caption = '6_3' then begin SpeedButton_Numer:=28+20; end;

    if Caption = '0_4' then begin SpeedButton_Numer:=29+20; end;
    if Caption = '1_4' then begin SpeedButton_Numer:=30+20; end;
    if Caption = '2_4' then begin SpeedButton_Numer:=31+20; end;
    if Caption = '3_4' then begin SpeedButton_Numer:=32+20; end;
    if Caption = '4_4' then begin SpeedButton_Numer:=33+20; end;
    if Caption = '5_4' then begin SpeedButton_Numer:=34+20; end;
    if Caption = '6_4' then begin SpeedButton_Numer:=35+20; end;

    if Caption = '0_5' then begin SpeedButton_Numer:=36+20; end;
    if Caption = '1_5' then begin SpeedButton_Numer:=37+20; end;
    if Caption = '2_5' then begin SpeedButton_Numer:=38+20; end;
    if Caption = '3_5' then begin SpeedButton_Numer:=39+20; end;
    if Caption = '4_5' then begin SpeedButton_Numer:=40+20; end;
    if Caption = '5_5' then begin SpeedButton_Numer:=41+20; end;
    if Caption = '6_5' then begin SpeedButton_Numer:=42+20; end;

  end;


  Edytuj_Maly_Tiles(SpeedButton_Numer); //      Wykonaj_procedure_wczytywania_malego_tilesa SpeedButton nr 21, Maly_Tiles="0_0";

end;



procedure TForm1.EditEncounterTables1Click(Sender: TObject);
begin
// edit encounter table
  If not Assigned(Form10) then
  begin
//    Form3:=TForm3.Create(Application);
    Form10:=TForm10.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form10.Show;
  end
  else
  begin
    Form10.Close;
    Form10.Destroy;
    Form10:=TForm10.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form10.Show;
  end;

end;

procedure TForm1.EditEncounterGroup1Click(Sender: TObject);
begin
// edit encounter Groups
  If not Assigned(Form2) then
  begin
//    Form3:=TForm3.Create(Application);
    Form2:=TForm2.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form2.Show;
  end
  else
  begin
    Form2.Close;
    Form2.Destroy;
    Form2:=TForm2.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form2.Show;
  end;
end;

procedure TForm1.SpeedButton1MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton2MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton3MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(2*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton4MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(3*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton5MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(0*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(1*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton6MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(1*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(1*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton7MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(2*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(1*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton8MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(3*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(1*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton9MouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(0*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(2*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton10MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(1*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(2*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton11MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(2*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(2*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton12MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(3*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(2*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton13MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(0*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(3*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton14MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(1*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(3*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton15MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(2*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(3*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton16MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(3*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(3*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton17MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(0*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(4*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton18MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(1*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(4*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton19MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(2*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(4*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.SpeedButton20MouseMove(Sender: TObject;
  Shift: TShiftState; X, Y: Integer);
begin
  Caption:='X= '+ IntToStr(Round(3*350+X*350/SpeedButton1.Width)) + ',  Y= '+IntToStr(Round(4*300+Y*300/SpeedButton1.Height));
end;

procedure TForm1.ShowHideSpeedButtonCaption1Click(Sender: TObject);
{var tymcz1:String;}
begin
{  if ShowHideSpeedButtonCaption1.Checked=False then
  begin
    ShowHideSpeedButtonCaption1.Checked:=True;
    Tymcz1:=SpeedButton1.Caption;
    SpeedButton1.Caption:='';
  end
  else
  if ShowHideSpeedButtonCaption1.Checked=True then
  begin
    ShowHideSpeedButtonCaption1.Checked:=False;
    SpeedButton1.Caption:=tymcz1;
  end;}
end;

procedure TForm1.CheckBox1Click(Sender: TObject);
begin
  if CheckBox1.Checked=True then ListBox2.Visible:=True
  else
    ListBox2.Visible:=False;

  Edytuj_Duzy_Tiles(numer_duzego_tilesa);          // odswieza widok planszy malych tilesow
  ListBox2.Clear;
    
end;

procedure TForm1.CrittersPid1Click(Sender: TObject);
begin
  If not Assigned(Form12) then
  begin
//    Form2:=TForm2.Create(Application);
    Form12:=TForm12.Create(nil);   // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form12.Show;
  end
  else
  Form12.Show;
end;

procedure TForm1.Edit_encounter_difficultyKeyPress(Sender: TObject;
  var Key: Char);
begin
  BitBtn1.Font.Color:=clRed;
  BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  //Panel4.Enabled:=False;

end;

procedure TForm1.Edit_walk_mask_nameKeyPress(Sender: TObject;
  var Key: Char);
begin
  BitBtn1.Font.Color:=clRed;
  BitBtn1.Font.Style := [fsBold];
  Panel1.Enabled:=False;
  Panel3.Enabled:=False;
  //Panel4.Enabled:=False;

end;

procedure TForm1.Backgroundmap1Click(Sender: TObject);
begin
  If not Assigned(Form13) then
  begin
    Form13:=TForm13.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form13.Show;
  end
  else
  begin
    Form13.Close;
    Form13.Destroy;
    Form13:=TForm13.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form13.Show;
  end;
end;

end.

// ****************************************** END *****************************************************
// ****************************************** END *****************************************************
// ****************************************** END *****************************************************

Function TForm1.numer_malego_tilesa(wartosc_SpeedButton_Numer:Byte):String;
begin
  case wartosc_SpeedButton_Numer-20 of        // odejmowanie 20 bo numery SpeddButtonow zaczynaja sie od 21!!!
  1:begin numer_malego_tilesa:='0_0'; end;
  2:begin numer_malego_tilesa:='1_0'; end;
  3:begin numer_malego_tilesa:='2_0'; end;
  4:begin numer_malego_tilesa:='3_0'; end;
  5:begin numer_malego_tilesa:='4_0'; end;
  6:begin numer_malego_tilesa:='5_0'; end;
  7:begin numer_malego_tilesa:='6_0'; end;
  8:begin numer_malego_tilesa:='0_1'; end;
  9:begin numer_malego_tilesa:='1_1'; end;
  10:begin numer_malego_tilesa:='2_1'; end;
  11:begin numer_malego_tilesa:='3_1'; end;
  12:begin numer_malego_tilesa:='4_1'; end;
  13:begin numer_malego_tilesa:='5_1'; end;
  14:begin numer_malego_tilesa:='6_1'; end;
  15:begin numer_malego_tilesa:='0_2'; end;
  16:begin numer_malego_tilesa:='1_2'; end;
  17:begin numer_malego_tilesa:='2_2'; end;
  18:begin numer_malego_tilesa:='3_2'; end;
  19:begin numer_malego_tilesa:='4_2'; end;
  20:begin numer_malego_tilesa:='5_2'; end;
  21:begin numer_malego_tilesa:='6_2'; end;
  22:begin numer_malego_tilesa:='0_3'; end;
  23:begin numer_malego_tilesa:='1_3'; end;
  24:begin numer_malego_tilesa:='2_3'; end;
  25:begin numer_malego_tilesa:='3_3'; end;
  26:begin numer_malego_tilesa:='4_3'; end;
  27:begin numer_malego_tilesa:='5_3'; end;
  28:begin numer_malego_tilesa:='6_3'; end;
  29:begin numer_malego_tilesa:='0_4'; end;
  30:begin numer_malego_tilesa:='1_4'; end;
  31:begin numer_malego_tilesa:='2_4'; end;
  32:begin numer_malego_tilesa:='3_4'; end;
  33:begin numer_malego_tilesa:='4_4'; end;
  34:begin numer_malego_tilesa:='5_4'; end;
  35:begin numer_malego_tilesa:='6_4'; end;
  36:begin numer_malego_tilesa:='0_5'; end;
  37:begin numer_malego_tilesa:='1_5'; end;
  38:begin numer_malego_tilesa:='2_5'; end;
  39:begin numer_malego_tilesa:='3_5'; end;
  40:begin numer_malego_tilesa:='4_5'; end;
  41:begin numer_malego_tilesa:='5_5'; end;
  42:begin numer_malego_tilesa:='6_5'; end;

  else numer_malego_tilesa:='0_0';
  end
end;



procedure TForm1.OnClick_SpeedButton(Sender: TObject);      // dla Malego_Tiles (dla SpeedButton malych tilesow
var licznik_:Integer;
    i,j:Byte;
begin
  i:=0;
  j:=0;
  licznik_:=20; // nazwy malych przyciskow zaczynaja sie od SpeedButton21 i koncza na SpeddButton62
  While licznik_<=62 do
  begin
    inc(licznik_);
    SpeedButton_Numer:=licznik_;
    if (Sender is TSpeedButton) then
    if (Sender as TSpeedButton).name = 'SpeedButton'+IntToStr(licznik_) then
    begin
//      ShowMessage(' kliknales przycisk '+IntToStr(licznik_)); // debug!!!!
      Edytuj_Maly_Tiles(licznik_); //      Wykonaj_procedure_wczytywania_malego_tilesa;
//      (Sender as TSpeedButton).Font.Color:=clRed{Maroon};     // - zaznacza ze ten SpeedButton zosta³ klikniety
{
      if linia_terrain='Mountain' then
      begin
        (Sender as TSpeedButton).Caption:='M';
        (Sender as TSpeedButton).Font.Color:=clMaroon;
      end;
      if linia_terrain='City' then
      begin
        (Sender as TSpeedButton).Caption:='C';
        (Sender as TSpeedButton).Font.Color:=clWhite;
      end;
      if linia_terrain='Ocean' then
      begin
        (Sender as TSpeedButton).Caption:='O';
        (Sender as TSpeedButton).Font.Color:=clBlue;
      end;
      if linia_terrain='Desert' then
      begin
        (Sender as TSpeedButton).Caption:='D';
        (Sender as TSpeedButton).Font.Color:=clYellow;
      end;
}
      with Image21 do
      begin
        Canvas.Pen.Color:=clGray; // clGray - szary kolor obwodki, czyli tak jak oryginal
//        Canvas.Pen.Color:=clLime;  // clLime - jasnozielony kolor obwodki, czyli ze byl wczesniej juz klikniety
        Canvas.Pen.Style:=psSolid;
        Canvas.Pen.Width:=2;
        Canvas.Brush.Style := bsClear;
//        Canvas.Rectangle((i-1)*50,(j-1)*50,(i-1)*50+50,(j-1)*50+50);
        Canvas.Rectangle(last_X1,last_Y1,last_X2,last_Y2);

        j:=(licznik_ - 21) div 7+1; // to jest OK
        i:=licznik_ - 13-j*7;  // to te¿ jest OK :)
//        Showmessage('licznik= '+IntToStr(licznik_)+'  i= '+IntToStr(i)+'   j= '+IntToStr(j));
        X1:=(i-1)*50;
        Y1:=(j-1)*50;
        X2:=(i-1)*50+50;
        Y2:=(j-1)*50+50;

        Canvas.Pen.Color:=clLime;
        Canvas.Pen.Width:=2;
        Canvas.Pen.Style:=psSolid;
        Canvas.Brush.Style := bsBDiagonal;

//        Canvas.Rectangle((i-1)*50,(j-1)*50,(i-1)*50+50,(j-1)*50+50);
        Canvas.Rectangle(X1,Y1,X2,Y2);

        last_X1:=(i-1)*50;
        last_Y1:=(j-1)*50;
        last_X2:=(i-1)*50+50;
        last_Y2:=(j-1)*50+50;
      end;
    end;
  end;
end;


procedure TForm1.BitBtn1Click(Sender: TObject);
var linia:String;
    iter:Word;
    znak:Char;
    Linia2:String;

//    fill_string:String;
begin
  Panel1.Enabled:=True;
  Panel4.Enabled:=True;
  Panel3.Enabled:=True;
  BitBtn1.Font.Color:=clBlack;
  BitBtn1.Font.Style := [];

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),'encounter_difficulty',Edit_encounter_difficulty.Text);
  finally
    plik_worldmap.Free;
  end;

  maly_tiles:=Label5.Caption;
//  Delete(maly_tiles,1,10);  - ta linia moze sie jeszcze przydac!!!

{ //Sa problemy z zaprogramowaniem odczytu do ComboBox gdy jest dodany napis " - experimantal!" wiec pni¿sze sa wy³aczone a w ComboBox wywalony ten dodatkowy napis
  fill_string:=Combobox2.Items[ComboBox2.ItemIndex];
  if (ComboBox2.ItemIndex>=2) and (ComboBox2.ItemIndex<=4) then delete(fill_string,7,length(fill_string)-(7-1));
  if (ComboBox2.ItemIndex>=5) and (ComboBox2.ItemIndex<=7) then delete(fill_string,8,length(fill_string)-(8-1));
}

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
  linia:=Combobox1.Items[ComboBox1.ItemIndex]+','+Combobox2.Items[ComboBox2.ItemIndex]{fill_string}+','+Combobox3.Items[ComboBox3.ItemIndex]+
  ','+Combobox4.Items[ComboBox4.ItemIndex]+','+Combobox5.Items[ComboBox5.ItemIndex]+','+Combobox6.Items[ComboBox6.ItemIndex];
//  ShowMessage(linia);
//  ShowMessage('Tile '+IntToStr(numer_duzego_tilesa));
//  ShowMessage('maly_tiles '+(maly_tiles));

   plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),maly_tiles,linia);

  finally
    plik_worldmap.Free;
  end;

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
  linia2:='';
  linia:=ListBox1.Items.CommaText;
  for iter:=1 to Length(linia) do
  begin
    znak:=linia[iter];
    if znak <> '"' then
    begin
      linia2:=linia2+znak;
    end;
//    else
    if znak = ',' then
    begin
      linia2:=linia2+' ';
    end;

  end;

  plik_worldmap.WriteString('Encounter Table '+IntToStr(ComboBox6.ItemIndex),'maps',linia2);

//  ShowMessage(linia);
//  ShowMessage(linia2);
//  ShowMessage('Tile '+IntToStr(numer_duzego_tilesa));
//  ShowMessage('maly_tiles '+(maly_tiles));

//   plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),maly_tiles,linia);

  finally
    plik_worldmap.Free;
  end;



  // Dzia³a poprawnie ale za kazdym przycisnieciem "save" czysci juz przegladniete male tilesy :( :( :(
//  Edytuj_Duzy_Tiles(numer_duzego_tilesa);
end;

