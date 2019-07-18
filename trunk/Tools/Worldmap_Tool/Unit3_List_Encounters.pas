unit Unit3_List_Encounters;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, IniFiles;

type
  TForm2 = class(TForm)
    Label1: TLabel;
    ComboBox1: TComboBox;
    SpeedButton1: TSpeedButton;
    Label2: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure ComboBox1DblClick(Sender: TObject);
    procedure ComboBox1KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation
  uses Worldmap_Tile_Editor, Unit6, Unit5;
{$R *.dfm}

procedure TForm2.FormCreate(Sender: TObject);
var iter:Byte;
    linia_cala: String;
begin
  //Lista_Encounters

  try
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
          if plik_worldmap.SectionExists(Lista.Strings[iter]) then
          begin
            linia_cala:=Lista.Strings[iter];
            Delete(linia_cala,1,11);

            Lista_Encounters.Add(linia_cala);
          end;
        end;

        ComboBox1.Items.Clear;
        ComboBox1.Items.AddStrings(Lista_Encounters);

      finally
        plik_worldmap.Free;
      end;
    finally
      Lista.Free;
    end;
  finally
    Lista_Encounters.Free;
  end;



  ComboBox1.Text:=Combobox1.Items.Strings[0];
end;

procedure TForm2.SpeedButton1Click(Sender: TObject);
begin
  selected_encounter_group:=ComboBox1.Text;

  If not Assigned(Form6) then
  begin
//    Form6:=TForm6.Create(Application);
    Form6:=TForm6.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form6.Show;
  end
  else
  begin
    Form6.Close;
    Form6.Destroy;
    Form6:=TForm6.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form6.Show;
  end;
end;

procedure TForm2.ComboBox1DblClick(Sender: TObject);
begin
  selected_encounter_group:=ComboBox1.Text;
  If not Assigned(Form6) then
  begin
//    Form6:=TForm6.Create(Application);
    Form6:=TForm6.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form6.Show;
  end
  else
  begin
    Form6.Close;
    Form6.Destroy;
    Form6:=TForm6.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form6.Show;
  end;

end;

procedure TForm2.ComboBox1KeyPress(Sender: TObject; var Key: Char);
begin
  if Ord(key)=13 then
  begin
    selected_encounter_group:=ComboBox1.Text;
    If not Assigned(Form6) then
    begin
//    Form6:=TForm6.Create(Application);
      Form6:=TForm6.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
      Form6.Show;
    end
    else
    begin
      Form6.Close;
      Form6.Destroy;
      Form6:=TForm6.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
      Form6.Show;
    end;
  end;
end;

end.
