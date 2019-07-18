unit Unit4_Enc_Percentage;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, IniFiles, Buttons, ExtCtrls;
type
  TForm4 = class(TForm)
    Label1: TLabel;
    BitBtn1: TBitBtn;
    Label8: TLabel;
    BitBtn2: TBitBtn;
    Panel1: TPanel;
    Label2: TLabel;
    Edit1: TEdit;
    Label3: TLabel;
    Edit2: TEdit;
    Label4: TLabel;
    Edit3: TEdit;
    Label5: TLabel;
    Edit4: TEdit;
    Label6: TLabel;
    Edit5: TEdit;
    Label7: TLabel;
    Edit6: TEdit;
    Panel2: TPanel;
    Label9: TLabel;
    Edit7: TEdit;
    procedure FormCreate(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure BitBtn2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form4: TForm4;
  linia:String; //zmienna typu string tymczasowa

implementation
uses worldmap_tile_editor;
{$R *.dfm}

procedure TForm4.FormCreate(Sender: TObject);
begin
  Top:=50;// ustawienie Form4 na pocz¹tku programu
  Left:=50;// ustawienie Form4 na pocz¹tku programu

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    linia:=plik_worldmap.ReadString('Data', Label2.Caption, 'dupa forced');
    Delete(linia,pos('%',linia),length(linia)-pos('%',linia)+1);
    Edit1.Text:=linia+'%';

    linia:=plik_worldmap.ReadString('Data', Label3.Caption, 'dupa forced');
    Delete(linia,pos('%',linia),length(linia)-pos('%',linia)+1);
    Edit2.Text:=linia+'%';

    linia:=plik_worldmap.ReadString('Data', Label4.Caption, 'dupa forced');
    Delete(linia,pos('%',linia),length(linia)-pos('%',linia)+1);
    Edit3.Text:=linia+'%';

    linia:=plik_worldmap.ReadString('Data', Label5.Caption, 'dupa forced');
    Delete(linia,pos('%',linia),length(linia)-pos('%',linia)+1);
    Edit4.Text:=linia+'%';

    linia:=plik_worldmap.ReadString('Data', Label6.Caption, 'dupa forced');
    Delete(linia,pos('%',linia),length(linia)-pos('%',linia)+1);
    Edit5.Text:=linia+'%';

    linia:=plik_worldmap.ReadString('Data', Label7.Caption, 'dupa forced');
    Delete(linia,pos('%',linia),length(linia)-pos('%',linia)+1);
    Edit6.Text:=linia+'%';

    linia:=plik_worldmap.ReadString('Data', 'terrain_types', 'dupa forced');
    Edit7.Text:=linia;

  finally
    plik_worldmap.Free;
  end;

end;

procedure TForm4.BitBtn1Click(Sender: TObject);
begin
  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    if Edit1.Text[length(Edit1.Text)]<>'%' then Edit1.Text:=Edit1.Text+'%';
    plik_worldmap.WriteString('Data',Label2.Caption,Edit1.Text);

    if Edit2.Text[length(Edit2.Text)]<>'%' then Edit2.Text:=Edit2.Text+'%';
    plik_worldmap.WriteString('Data',Label3.Caption,Edit2.Text);

    if Edit3.Text[length(Edit3.Text)]<>'%' then Edit3.Text:=Edit3.Text+'%';
    plik_worldmap.WriteString('Data',Label4.Caption,Edit3.Text);

    if Edit4.Text[length(Edit4.Text)]<>'%' then Edit4.Text:=Edit4.Text+'%';
    plik_worldmap.WriteString('Data',Label5.Caption,Edit4.Text);

    if Edit5.Text[length(Edit5.Text)]<>'%' then Edit5.Text:=Edit5.Text+'%';
    plik_worldmap.WriteString('Data',Label6.Caption,Edit5.Text);

    if Edit6.Text[length(Edit6.Text)]<>'%' then Edit6.Text:=Edit6.Text+'%';
    plik_worldmap.WriteString('Data',Label7.Caption,Edit6.Text);

    plik_worldmap.WriteString('Data','terrain_types',Edit7.Text);

  finally
    plik_worldmap.Free;
  end;

  Form4.Close;
end;

procedure TForm4.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action:=caFree;
  Form4:=nil;
end;

procedure TForm4.BitBtn2Click(Sender: TObject);
begin
  Form4.Close;
end;

end.
