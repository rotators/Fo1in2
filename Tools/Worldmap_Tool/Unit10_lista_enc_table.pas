unit Unit10_lista_enc_table;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TForm10 = class(TForm)
    Label1: TLabel;
    SpeedButton1: TSpeedButton;
    Label2: TLabel;
    ComboBox1: TComboBox;
    procedure FormCreate(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure ComboBox1Change(Sender: TObject);
    procedure ComboBox1KeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form10: TForm10;

implementation

uses Worldmap_Tile_Editor, Unit5;

{$R *.dfm}

procedure TForm10.FormCreate(Sender: TObject);
begin
  ComboBox1.Items.Clear;
  ComboBox1.Items.AddStrings(Lista_Enc_Tables);
  ComboBox1.Text:=Combobox1.Items.Strings[0];
end;

procedure TForm10.SpeedButton1Click(Sender: TObject);
begin
  selected_encounter_table:=ComboBox1.Text;

  If not Assigned(Form5) then
  begin
//    Form6:=TForm6.Create(Application);
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

procedure TForm10.ComboBox1Change(Sender: TObject);
begin
  selected_encounter_table:=ComboBox1.Text;
  If not Assigned(Form5) then
  begin
//    Form6:=TForm6.Create(Application);
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

procedure TForm10.ComboBox1KeyPress(Sender: TObject; var Key: Char);
begin
  if Ord(key)=13 then
  begin
    selected_encounter_table:=ComboBox1.Text;
    If not Assigned(Form5) then
    begin
//    Form6:=TForm6.Create(Application);
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
end;

end.
