unit Tile_Data;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls, IniFiles;

type
  TForm3 = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    ComboBox1: TComboBox;
    ComboBox2: TComboBox;
    ComboBox3: TComboBox;
    ComboBox4: TComboBox;
    ComboBox5: TComboBox;
    ComboBox6: TComboBox;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormDestroy(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
  private
    { Private declarations }
      Edit:TEdit;
      Panel:TPanel;
//      ComboBox:TComboBox;
//      Image:TImage;



      Procedure Czytaj_Tilesa;
      Function numer_malego_tilesa(wartosc_SpeedButton_Numer:Byte):String;
  public
    { Public declarations }


  end;

var
  Form3: TForm3;
  Lista : TStringList;
  duzy_tiles,maly_tiles:String;
  List_terrain, List_Fill, List_Chance, List_Encounter_Table:TStringList;

implementation
uses worldmap_tile_editor, Edit_Tile, Unit5;

{$R *.dfm}

procedure TForm3.BitBtn1Click(Sender: TObject);
begin
  Form3.Close;
  Form3:=nil;
end;

procedure TForm3.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
end;

procedure TForm3.FormDestroy(Sender: TObject);
begin
  Edit.Free;
  Panel.Free;
  Form3:=nil;
end;

procedure TForm3.FormCreate(Sender: TObject);
var iter:Byte;
    linia_cala:String;
    pozycja_ciecia:Byte;

begin
  Screen.Cursor:=crHourGlass;

  Top:=Form2.Height;
  Left:=Form1.Panel1.Width+10;// ustawienie Form2 na pocz¹tku programu
  Width:=Form2.Width;
  Height:=Form1.Height-Form2.Height-30;
  if width<100 then width:=100;
  if height<200 then height:=200;

  Label1.Font.Style:=[fsBold];
  Label1.Caption:='Quadrant: '+numer_malego_tilesa(SpeedButton_Numer);

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
    Lista.Add('Fill_N - experimental!');
    Lista.Add('Fill_E - experimental!');
    Lista.Add('Fill_S - experimental!');
    Lista.Add('Fill_NW - experimental!');
    Lista.Add('Fill_NE - experimental!');
    Lista.Add('Fill_SW - experimental!');
    Lista.Add('Fill_SE - experimental!');
    ComboBox2.Items.Clear;
    ComboBox2.Items.AddStrings(Lista);
  finally
    Lista.Free;
  end;

//List_Chance
  Lista := TStringList.Create;
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


//List_Chance
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


//List_Encounter_Table
  Lista := TStringList.Create;
  try
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

          Lista.Add(linia_cala);

          ComboBox6.Items.Clear;
          ComboBox6.Items.AddStrings(Lista);
        end;
      end;
    finally
      plik_worldmap.Free;
    end;
  finally
    Lista.Free;
  end;


  Czytaj_Tilesa;

  Screen.Cursor:=crDefault;
end;

Function TForm3.numer_malego_tilesa(wartosc_SpeedButton_Numer:Byte):String;
begin
  case wartosc_SpeedButton_Numer of
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


Procedure TForm3.Czytaj_Tilesa;
var linia_cala:String;
    linia_terrain:String;
    linia_fill:String;
    linia_morning_chance:String;
    Linia_afternoon_chance:String;
    Linia_night_chance:String;
    Linia_type:String;
    pozycja_ciecia:Byte;
//    licznik:Byte;
// var s: string;
// begin
//   s := 'Honest Abe Lincoln';
//   Delete(s,8,4);
//   Canvas.TextOut(10, 10, s);	{ 'Honest Lincoln' }
// end;

// 5_3=Desert,No_Fill,Rare,Rare,Rare,Arro_D


//if pos('.',plik)=0 then plik:=plik+'.ini';
//  awlasciwosc:=s;
//  delete(awlasciwosc,pos('=',s),length(s));

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
  Linia_type:=linia_cala;

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

  Delete(linia_type,1,length(linia_terrain)); // wycina np. 'Mountain'
  Delete(linia_type,1,1);          // wycina pierwszy przecinek
  Delete(linia_type,1,length(linia_fill)); // wycina np. 'No_fill'
  Delete(linia_type,1,1);          // wycina drugi przecinek
  Delete(linia_type,1,length(linia_morning_chance)); // wycina np. pierwszy wyraz 'Rare'
  Delete(linia_type,1,1);          // wycina trzeci przecinek
  Delete(linia_type,1,length(Linia_afternoon_chance)); // wycina np. drugi wyraz 'Rare'
  Delete(linia_type,1,1);          // wycina czwarty przecinek
  Delete(linia_type,1,length(Linia_night_chance)); // wycina np. trzeci wyraz 'Rare'
  Delete(linia_type,1,1);          // wycina piaty przecinek   // i w³asnie mamy gotow¹ ostatni¹ liniê !!!!!!!!!!!!!!!!!!!!!!


  ComboBox1.ItemIndex:=comboBox1.Items.IndexOf(linia_terrain);
  ComboBox2.ItemIndex:=comboBox2.Items.IndexOf(linia_fill);
  ComboBox3.ItemIndex:=comboBox3.Items.IndexOf(linia_morning_chance);
  ComboBox4.ItemIndex:=comboBox4.Items.IndexOf(linia_afternoon_chance);
  ComboBox5.ItemIndex:=comboBox5.Items.IndexOf(linia_night_chance);
  ComboBox6.ItemIndex:=comboBox6.Items.IndexOf(linia_type);

end;


procedure TForm3.BitBtn2Click(Sender: TObject);
var linia:String;

begin
  maly_tiles:=Label1.Caption;
  Delete(maly_tiles,1,10);


  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
  linia:=Combobox1.Items[ComboBox1.ItemIndex]+','+Combobox2.Items[ComboBox2.ItemIndex]+','+Combobox3.Items[ComboBox3.ItemIndex]+
  ','+Combobox4.Items[ComboBox4.ItemIndex]+','+Combobox5.Items[ComboBox5.ItemIndex]+','+Combobox6.Items[ComboBox6.ItemIndex];
  
   plik_worldmap.WriteString('Tile '+IntToStr(numer_duzego_tilesa),maly_tiles,linia);
  finally
    plik_worldmap.Free;
  end;
end;

procedure TForm3.BitBtn3Click(Sender: TObject);
begin
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

end.

