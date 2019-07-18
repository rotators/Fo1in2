unit Unit9_add_maps;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ComCtrls;

type
  TForm9 = class(TForm)
    BitBtn1: TBitBtn;
    ListBox1: TListBox;
    procedure FormCreate(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form9: TForm9;

implementation

uses Worldmap_Tile_Editor;

{$R *.dfm}

procedure TForm9.FormCreate(Sender: TObject);
begin
  ListBox1.Items.Clear;
  ListBox1.Items.AddStrings(Lista_Maps);
end;

procedure TForm9.BitBtn1Click(Sender: TObject);
begin
  ListBox1.CopySelection(Form1.ListBox1);

end;

end.
