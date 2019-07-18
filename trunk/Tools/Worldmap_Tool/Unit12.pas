unit Unit12;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TForm12 = class(TForm)
    SpeedButton1: TSpeedButton;
    ComboBox1: TComboBox;
    Label1: TLabel;
    Edit1: TEdit;
    procedure FormCreate(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure ComboBox1Select(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form12: TForm12;

implementation
uses Worldmap_Tile_Editor;
{$R *.dfm}

procedure TForm12.FormCreate(Sender: TObject);
begin
  ComboBox1.Items.Clear;
  ComboBox1.Items.AddStrings(Lista_Critters);
  ComboBox1.Text:=Combobox1.Items.Strings[0];
end;

procedure TForm12.SpeedButton1Click(Sender: TObject);
begin
  Edit1.Text:=IntToStr(16777216+ComboBox1.ItemIndex+1);
end;

procedure TForm12.ComboBox1Select(Sender: TObject);
begin
  Edit1.Text:=IntToStr(16777216+ComboBox1.ItemIndex+1);
end;

end.
