unit Unit6;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, IniFiles, StdCtrls, ExtCtrls, Buttons;

type
  TForm6 = class(TForm)
    Memo1: TMemo;
    Panel1: TPanel;
    Panel2: TPanel;
    Label1: TLabel;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    BitBtn4: TBitBtn;
    BitBtn5: TBitBtn;
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
    procedure BitBtn5Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form6: TForm6;
  Sekcja:String;
//  Labelek:Array of TLabel;
//  Edit:Array of TEdit;
  max:Integer;

implementation
uses worldmap_tile_editor, Unit5, Unit12, Unit7_show_worldmap_txt;
{$R *.dfm}

procedure TForm6.BitBtn2Click(Sender: TObject);
begin
  Close();
end;



// Save Encounter Group to worldmap.txt
procedure TForm6.BitBtn1Click(Sender: TObject);
var i:Byte;
    string_i:String;
    new_group_name:String;
    pozycja_ciecia:Integer;
    linia:String;

begin
//  Zapisywanie
  Memo1.Lines.SaveToFile('memo_crit.bak');	{ save into backup file }

//  24-06-2013, ulepszenie Save, jesli zmieniona zosta³a naza grupy enco ma inna to utowrzy nowa grupe enco o nowej nazwie, a stara pozostanie niezmieniona, np [Encounter: Merchant_Party] na  [Encounter: Handlarze]

  sekcja:=''; // zresetowanie zmiennej Sekcja
  new_group_name:='';  // zresetowanie/inicjalizacja wartosci

  linia:=Trim(Memo1.Lines[0]);
  pozycja_ciecia:=pos(':', linia);
  Delete(linia, 1, pozycja_ciecia);
  pozycja_ciecia:=pos(']', linia);
  Delete(linia, pozycja_ciecia, 1);
  linia:=Trim(linia);
  //ShowMessage('--'+linia+'--');
  new_group_name:=linia;
  //ShowMessage('--'+new_group_name+'--');


  // jesli nie istnieje jeszcze taka grupa, tzn, tworzymy nowa grupe
  if new_group_name<>selected_encounter_group then
  begin
    sekcja:='Encounter: '+new_group_name;
  end
  else
    sekcja:='Encounter: '+selected_encounter_group;


  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    //w przeciwnym razie najpierw wyczyszczenie ca³ej sekcji jesli istnieje przed zapisaniem nowych danych
    if plik_worldmap.SectionExists(sekcja) then
    begin
      if MessageBox(Handle,'Encounter Group exists! Overwrite?','Saving...',MB_YesNo + MB_IconQuestion) = IdYes then
      begin
        //wyczyszczenie zawartosci sekcji (kluczy, bo sama sekcja musi pozostac, aby nowe dane zostaly zapisane do niej w tym samym miejscu w pliku, a nie na koncu jak to bylo do 25-06-2013!!!
        //plik_worldmap.EraseSection(Sekcja);

        if plik_worldmap.ValueExists(Sekcja, 'position') then plik_worldmap.DeleteKey(sekcja, 'position');
        if plik_worldmap.ValueExists(Sekcja, 'team_num') then plik_worldmap.DeleteKey(sekcja, 'team_num');

        for i:=0 to 255 do
        begin
          if i<10 then string_i:='0'+IntToStr(i);
          if i>=10 then string_i:=IntToStr(i);

          if plik_worldmap.ValueExists(Sekcja,'type_'+string_i) then plik_worldmap.DeleteKey(sekcja, 'type_'+string_i);
        end;


        //Zapis z plikow tymczasowych
        INI:= TINIFile.Create(ExtractFilePath(Application.ExeName) + 'memo_crit.bak');
        try
          for i:=0 to 255 do
          begin
            if i<10 then string_i:='0'+IntToStr(i);
            if i>=10 then string_i:=IntToStr(i);
            if INI.ValueExists(Sekcja,'type_'+string_i) then plik_worldmap.WriteString(Sekcja, 'type_'+string_i,INI.ReadString(Sekcja,'type_'+string_i,'yyy'));
          end;

          if INI.ValueExists(Sekcja,'position') then plik_worldmap.WriteString(Sekcja, 'position',INI.ReadString(Sekcja,'position','yyy'));
          if INI.ValueExists(Sekcja,'team_num') then plik_worldmap.WriteString(Sekcja, 'team_num',INI.ReadString(Sekcja,'team_num','yyy'));

        finally
          INI.Free;
        end;
      end; // end of MeesageBox
    end

    else  // jesli sekcja nie istnieje, to tworz jako nowa (zostanie zapisana na koncu pliku!)

    begin
      if MessageBox(Handle,'Group doesn`t exists!. It will be created at the end of file "worldmap.txt". Create?', 'Creating...', MB_YesNo + MB_IconQuestion) = IdYes then
      begin
        //ShowMessage('Group "'+sekcja +'" doesn`t exists!. This will create NEW one. It will be created at the end of file "worldmap.txt".');

        //Zapis z plikow tymczasowych
        INI:= TINIFile.Create(ExtractFilePath(Application.ExeName) + 'memo_crit.bak');
        try
          for i:=0 to 255 do
          begin
            if i<10 then string_i:='0'+IntToStr(i);
            if i>=10 then string_i:=IntToStr(i);
            if INI.ValueExists(Sekcja,'type_'+string_i) then plik_worldmap.WriteString(Sekcja, 'type_'+string_i,INI.ReadString(Sekcja,'type_'+string_i,'yyy'));
          end;

          if INI.ValueExists(Sekcja,'position') then plik_worldmap.WriteString(Sekcja, 'position',INI.ReadString(Sekcja,'position','yyy'));
          if INI.ValueExists(Sekcja,'team_num') then plik_worldmap.WriteString(Sekcja, 'team_num',INI.ReadString(Sekcja,'team_num','yyy'));

        finally
          INI.Free;
        end;
      end;
    end;

  finally
    plik_worldmap.Free;
  end;

end;



procedure TForm6.FormCreate(Sender: TObject);
var Lista: TStringList;
begin
//  WindowState:=wsMaximized;

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    sekcja:='';
    if plik_worldmap.SectionExists('Encounter: '+selected_encounter_group) then
    begin
      sekcja:='Encounter: '+selected_encounter_group;
      Label1.Caption:='['+Sekcja+']';

      Lista := TStringList.Create;
      plik_worldmap.ReadSectionValues(Sekcja, Lista);
      Memo1.Lines.Clear;
      Memo1.Lines.Add(Label1.Caption);
      Memo1.Lines.AddStrings(Lista);
      Lista.Free;

    end;
  finally
    plik_worldmap.Free;
  end;

end;

procedure TForm6.BitBtn3Click(Sender: TObject);
begin
  If not Assigned(Form12) then
  begin
//    Form3:=TForm3.Create(Application);
    Form12:=TForm12.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form12.Show;
  end
  else
  begin
    Form12.Close;
    Form12.Destroy;
    Form12:=TForm12.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form12.Show;
  end;
end;

procedure TForm6.BitBtn5Click(Sender: TObject);
begin
  If not Assigned(Form7) then
  begin
//    Form7:=TForm7.Create(Application);
    Form7:=TForm7.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form7.Show;
  end
  else
  begin
    Form7.Close;
    Form7.Destroy;
    Form7:=TForm7.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form7.Show;
  end;
end;

end.
