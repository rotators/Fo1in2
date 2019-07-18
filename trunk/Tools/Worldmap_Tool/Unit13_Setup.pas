unit Unit13_Setup;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Spin, ExtCtrls, Buttons, IniFiles;

type
  TForm13 = class(TForm)
    RadioGroup1: TRadioGroup;
    GroupBox1: TGroupBox;
    SpinEdit1: TSpinEdit;
    SpinEdit2: TSpinEdit;
    Label1: TLabel;
    Label2: TLabel;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure SpinEdit1Click(Sender: TObject);
    procedure SpinEdit2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form13: TForm13;

implementation

uses Worldmap_Tile_Editor;

{$R *.dfm}

procedure TForm13.BitBtn2Click(Sender: TObject);
begin
  Form13.Close;
end;

procedure TForm13.BitBtn1Click(Sender: TObject); // Save - zachowaj ustawienia i zastosuj
begin
  INI := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'tile_editor.ini');
  try
    INI.WriteInteger('Panel', 'width', SpinEdit1.Value);
    INI.WriteInteger('Panel', 'height', SpinEdit2.Value);

    case RadioGroup1.ItemIndex of
    0: INI.WriteString('Background picture', 'path_bmp', '\FO1_BMP\');
    1: INI.WriteString('Background picture', 'path_bmp', '\FO2_BMP\');
    end;

  finally
    INI.Free;
  end;

  ShowMessage('To apply the changes, restart the program.');

  Form13.Close;
end;

procedure TForm13.FormCreate(Sender: TObject);
begin
  INI := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'tile_editor.ini');
  try
    SpinEdit1.Value:=INI.ReadInteger('Panel', 'width', 652);
    SpinEdit2.Value:=INI.ReadInteger('Panel', 'height', 696);

    if INI.ReadString('Background picture', 'path_bmp', '\FO2_BMP\') = '\FO1_BMP\' then
      RadioGroup1.ItemIndex:=0
    else // FO2_BMP
      RadioGroup1.ItemIndex:=1;

  finally
    INI.Free;
  end;
end;

procedure TForm13.SpinEdit1Click(Sender: TObject);
begin
//  SpinEdit2.Value:=Round(0.93333333* SpinEdit1.Value);
end;

procedure TForm13.SpinEdit2Click(Sender: TObject);
begin
//  SpinEdit1.Value:=Round(1.0714285* SpinEdit2.Value);
end;

end.

[Panel]
width=852
height=896
