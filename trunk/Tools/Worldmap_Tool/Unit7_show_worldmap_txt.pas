unit Unit7_show_worldmap_txt;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm7 = class(TForm)
    Memo1: TMemo;
    procedure FormActivate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form7: TForm7;

implementation

{$R *.dfm}

procedure TForm7.FormActivate(Sender: TObject);
begin
//za³adowuje ca³y plik worldmap.txt do memo1
  Memo1.Clear;
  Memo1.Lines.LoadFromFile(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
end;

end.
