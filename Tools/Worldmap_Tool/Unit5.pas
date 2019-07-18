unit Unit5;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, IniFiles, StdCtrls, ComCtrls, ExtCtrls, Menus, Buttons, Grids,
  ValEdit;

type
  TForm5 = class(TForm)
    Panel2: TPanel;
    BitBtn_Save: TBitBtn;
    BitBtn_Cancel: TBitBtn;
    Panel1: TPanel;
    Label1: TLabel;
    BitBtn_View_worldmaptxt_: TBitBtn;
    BitBtn_Maps_List_: TBitBtn;
    BitBtn_Encounters_List_: TBitBtn;
    BitBtn_Actions_: TBitBtn;
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    Exit1: TMenuItem;
    View1: TMenuItem;
    Maps1: TMenuItem;
    EncGroup1: TMenuItem;
    N1: TMenuItem;
    worldmaptxt1: TMenuItem;
    Help1: TMenuItem;
    Helpme1: TMenuItem;
    About1: TMenuItem;
    Save1: TMenuItem;
    N2: TMenuItem;
    Exit2: TMenuItem;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Memo1: TMemo;
    BitBtn1: TBitBtn;

    procedure BitBtn_SaveClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure BitBtn_CancelClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure BitBtn_View_worldmaptxt_Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn_Maps_List_Click(Sender: TObject);
    procedure BitBtn_Encounters_List_Click(Sender: TObject);
    procedure BitBtn_Actions_Click(Sender: TObject);
    procedure Exit2Click(Sender: TObject);
//    procedure BitBtn_AddLineClick(Sender: TObject);
//    procedure BitBtn_DelLineClick(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
//    procedure ValueListEditor2DblClick(Sender: TObject);
  private
    { Private declarations }

  public
    { Public declarations }

  end;

var
  Form5: TForm5;
  Sekcja:String;
  selected_encounter_group:String; // nazwa zaznaczonego Encounter_Group w Memo1 albo w Combobox na formularzu Encounter Groups
  licznik_linii:Integer;



implementation
uses worldmap_tile_editor, Unit6, Unit7_show_worldmap_txt, Unit3_List_Maps,
  Unit3_List_Encounters, Unit8_Actions, Unit9_add_maps, Unit11;
{$R *.dfm}



// Save Encounter Table
procedure TForm5.BitBtn_SaveClick(Sender: TObject);
var i:Byte;
    string_i,linia_tmp:String;
    plikT:TextFile;
    plikT_tmp:TextFile;
//    memo1_INI: TINIFile;

//[Encounter Table 68]
//lookup_name=Wild6_M                                                                        ; Area between New Reno and NCR
//maps=Mountain Encounter 1, Mountain Encounter 2, Cavern Encounter 0
//enc_00=Chance:100%,Enc:(8-12) ARRO_Spore_Plants AMBUSH Player
begin
//zapisywanie
//  Label1.Caption - Encounter Table 68
//  Label2.Caption - Wild6_M

//  ValueListEditor2.Strings.SaveToFile('worldmap_tool.tmp');

  Memo1.Lines.SaveToFile('worldmap_tool.tmp');
  AssignFile(plikT_tmp,'temp1.tmp');
  Rewrite(plikT_tmp);
  Writeln(plikT_tmp,Label1.Caption);
  Writeln(plikT_tmp,'lookup_name='+Label2.Caption);
  Writeln(plikT_tmp,'maps='+Label3.Caption);
  CloseFile(plikT_tmp);

  AssignFile(plikT,'worldmap_tool.tmp');
  Reset(plikT);
  AssignFile(plikT_tmp,'temp1.tmp');
  Append(plikT_tmp);
  While not Eof(plikT) do
  begin
    Readln(plikT,linia_tmp);
    Writeln(plikT_tmp,linia_tmp);
  end;
  CloseFile(plikT);
  CloseFile(plikT_tmp);




//  Memo1.Lines.SaveToFile('memo1.bak');	{ save into backup file }

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    //najpierw wyczyszczenie ca³ej sekcji jesli istnieje
//    if plik_worldmap.SectionExists(Label1.Caption) then
    sekcja:=Label1.Caption; //memo1.Lines[0];
    delete(sekcja,pos('[',sekcja),1);
    delete(sekcja,pos(']',sekcja),1);
    
    if plik_worldmap.SectionExists(Sekcja) then
    begin
//      ShowMessage('Section '+sekcja +' exists! This will OVERWRITE old section!');

      if MessageBox(Handle,'Section exists! Overwrite?','Saving...',MB_YesNo + MB_IconQuestion) = IdYes then
      begin
        //wyczyszczenie zawartosci sekcji (kluczy, bo sama sekcja musi pozostac, aby nowe dane zostaly zapisane do niej w tym samym miejscu w pliku, a nie na koncu jak to bylo do 25-06-2013!!!
        //plik_worldmap.EraseSection(Sekcja);
        if plik_worldmap.ValueExists(Sekcja, 'lookup_name') then plik_worldmap.DeleteKey(sekcja, 'lookup_name');
        if plik_worldmap.ValueExists(Sekcja, 'maps') then plik_worldmap.DeleteKey(sekcja, 'maps');

        for i:=0 to 255 do
        begin
          if i<10 then string_i:='0'+IntToStr(i);
          if i>=10 then string_i:=IntToStr(i);

          if plik_worldmap.ValueExists(Sekcja,'enc_'+string_i) then
          begin
            plik_worldmap.DeleteKey(sekcja, 'enc_'+string_i);
          end;
        end;




        INI:= TINIFile.Create(ExtractFilePath(Application.ExeName) + 'temp1.tmp');
        try
          if INI.ValueExists(Sekcja,'lookup_name') then
          begin
            plik_worldmap.WriteString(Sekcja, 'lookup_name',INI.ReadString(Sekcja,'lookup_name','yyy'));
          end;
          if INI.ValueExists(Sekcja,'maps') then
          begin
            plik_worldmap.WriteString(Sekcja, 'maps',INI.ReadString(Sekcja,'maps','yyy'));
          end;

          for i:=0 to 255 do
          begin
            if i<10 then string_i:='0'+IntToStr(i);
            if i>=10 then string_i:=IntToStr(i);
            if INI.ValueExists(Sekcja,'enc_'+string_i) then
            begin
              plik_worldmap.WriteString(Sekcja, 'enc_'+string_i,INI.ReadString(Sekcja,'enc_'+string_i,'yyy'));
            end;
          end;

        finally
          INI.Free;
        end;
      end;

    end

    else
    begin
      ShowMessage('Section '+sekcja +' not exists!. This will create NEW');

      INI:= TINIFile.Create(ExtractFilePath(Application.ExeName) + 'temp1.tmp');
      try
        if INI.ValueExists(Sekcja,'lookup_name') then
        begin
          plik_worldmap.WriteString(Sekcja, 'lookup_name',INI.ReadString(Sekcja,'lookup_name','yyy'));

          // dodaje NOW¥ sekcjê do Combobox6!!!!
          Lista_Enc_Tables.Add(INI.ReadString(Sekcja,'lookup_name','yyy'));
          Form1.ComboBox6.Items.AddStrings(Lista_Enc_Tables);
        end;
        if INI.ValueExists(Sekcja,'maps') then
        begin
          plik_worldmap.WriteString(Sekcja, 'maps',INI.ReadString(Sekcja,'maps','yyy'));
        end;

        for i:=0 to 255 do
        begin
          if i<10 then string_i:='0'+IntToStr(i);
          if i>=10 then string_i:=IntToStr(i);
          if INI.ValueExists(Sekcja,'enc_'+string_i) then
          begin
            plik_worldmap.WriteString(Sekcja, 'enc_'+string_i,INI.ReadString(Sekcja,'enc_'+string_i,'yyy'));
          end;
        end;
      finally
        INI.Free;
      end;
    end;

  finally
    plik_worldmap.Free;
  end;
end;




procedure TForm5.FormCreate(Sender: TObject);
var i:Byte;
    lookup_name:String;
    Lista: TStringList;   // tymczasowa pomocnicza zmienna

begin
//  Left:=0;
//  Top:=0;
//  WindowState:=wsNormal;
//  if ValueListEditor2.Keys[0]<>'enc_00' then
//  ValueListEditor2.InsertRow('enc_01','Chance:',true);

  licznik_linii:=0;

  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    sekcja:='';
    for i:=0 to 255 do
    begin
      if plik_worldmap.SectionExists('Encounter Table '+IntToStr(i)) then
      begin
        sekcja:='Encounter Table '+IntToStr(i);
        lookup_name:=plik_worldmap.ReadString(Sekcja, 'lookup_name', 'lookup_name');
//        showMessage('lookup_name= '+lookup_name);//debug
        delete(lookup_name,pos(' ',lookup_name),length(lookup_name)-pos(' ',lookup_name)+1);
//        showMessage('delete(lookup_name)= '+lookup_name);//debug
        if lookup_name=selected_encounter_table then
        begin
          Label1.Caption:='['+Sekcja+']';     // wyswietla sie tutaj cala nazwa Encounter Table z numerkiem 24-08-2008
          Label2.Caption:=lookup_name;
          Label3.Caption:=plik_worldmap.ReadString(Sekcja, 'maps', 'mapki');
//          Edit2.Text:=IntToStr(i); Edit2 - > nie istnieje na Formie, wyci¹³em 24-08-2008
//          Label1.Caption:=Sekcja;
//          Label2.Caption:='Encounter table: '+lookup_name;
//          Label2.Caption:=lookup_name;

          Lista := TStringList.Create;
          try
            Lista.Clear;
            plik_worldmap.ReadSectionValues(Sekcja, Lista);
//            Memo1.Lines.Clear;

//            Memo1.Lines.Add(Label1.Caption);
//            Memo1.Lines.Add('['+sekcja+']');

            Memo1.Lines.AddStrings(Lista);
            Memo1.Lines.Delete(0); // wycina linie z nazwa lookup_name
            Memo1.Lines.Delete(0); // wycina linie z nazwami maps
 // zamiast tego to jest ValueListEditor  //aded 24-08-2008

//            Lista.Delete(0);
//            Lista.Delete(0);
//            ValueListEditor2.Strings.AddStrings(Lista);

          finally
            Lista.Free;
          end;

          Break; // koñczy pêtlê gdy sukces!
        end;
      end;
    end;
  finally
    plik_worldmap.Free;
  end;
end;



procedure TForm5.BitBtn_CancelClick(Sender: TObject);
begin
  licznik_linii:=0;
  Close();
end;


procedure TForm5.FormActivate(Sender: TObject);
begin
//  Left:=0;
//  Top:=0;
//  WindowState:=wsNormal;
  licznik_linii:=0;
end;


procedure TForm5.Button1Click(Sender: TObject);
begin
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

procedure TForm5.BitBtn_View_worldmaptxt_Click(Sender: TObject);
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


procedure TForm5.BitBtn_Maps_List_Click(Sender: TObject);
begin
  If not Assigned(Form3) then
  begin
//    Form3:=TForm3.Create(Application);
    Form3:=TForm3.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form3.Show;
  end
  else
  begin
    Form3.Close;
    Form3.Destroy;
    Form3:=TForm3.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form3.Show;
  end;
end;

procedure TForm5.BitBtn_Encounters_List_Click(Sender: TObject);
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

procedure TForm5.BitBtn_Actions_Click(Sender: TObject);
begin
  If not Assigned(Form8) then
  begin
//    Form3:=TForm3.Create(Application);
    Form8:=TForm8.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form8.Show;
  end
  else
  begin
    Form8.Close;
    Form8.Destroy;
    Form8:=TForm8.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form8.Show;
  end;
end;

procedure TForm5.Exit2Click(Sender: TObject);
begin
  Close();
end;


procedure TForm5.BitBtn1Click(Sender: TObject);
var linia:String;
begin
  plik_worldmap := TINIFile.Create(ExtractFilePath(Application.ExeName) + 'worldmap.txt');
  try
    linia:=Trim(Label1.Caption);
    Delete(linia,1,1);
    Delete(linia,length(linia),1);

    sekcja:=Trim(linia); //memo1.Lines[0];

    if plik_worldmap.SectionExists(sekcja) then
//    if plik_worldmap.SectionExists('Encounter: '+selected_encounter_group) then
    begin
      ShowMessage('sekcja '+ sekcja + ' istnieje, zostanie skasowana');
      //sekcja:='Encounter: '+selected_encounter_group;
      plik_worldmap.EraseSection(Sekcja);
    end;
  finally
    plik_worldmap.Free;
  end;
end;


end.

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
procedure TForm5.BitBtn_AddLineClick(Sender: TObject);
var ile_linii:Byte;
    iter:Integer;
    plik1,plik2:TextFile;
    linia1:string;

begin
  ile_linii:=ValueListEditor2.RowCount-2;

//  ShowMessage('Jest '+IntToStr(ile_linii)+' linijek');
  if (ile_linii=0) and (licznik_linii=0) then
  begin
    ValueListEditor2.InsertRow('enc_0'+IntToStr(ile_linii),'Chance:',true);
    inc(licznik_linii);
  end;

  if (ile_linii>=0) and (ile_linii<9) and (licznik_linii=0) then
  begin
    ValueListEditor2.InsertRow('enc_0'+IntToStr(ile_linii+1),'Chance:',true);
    inc(licznik_linii);
  end;

  if (ile_linii>=0) and (ile_linii<9) and (licznik_linii>0) then
  begin
    ValueListEditor2.InsertRow('enc_0'+IntToStr(ile_linii+1),'Chance:',true);
    inc(licznik_linii);
  end;

  if (ile_linii>=9) then
  begin
    ValueListEditor2.InsertRow('enc_'+IntToStr(ile_linii+1),'Chance:',true);
    inc(licznik_linii);
  end;

  ValueListEditor2.Refresh;

    iter:=0;
  ValueListEditor2.Strings.SaveToFile('temp1');
  AssignFile(plik1,'temp1');
  Reset(plik1);
//  AssignFile(plik2,'temp2');
//  Rewrite(plik2);
  While not eof(plik1) do
  begin
    Readln(plik1, linia1);
//    delete(linia1,1,6);
    // enc_11=
    if iter<10 then
    begin
      ValueListEditor2.Keys[iter+1]:='enc_0'+IntToStr(iter);
//      linia1:='enc_0'+IntToStr(iter)+linia1;
    end;
    if iter>=10 then
    begin
      ValueListEditor2.Keys[iter+1]:='enc_'+IntToStr(iter);
//      linia1:='enc_'+IntToStr(iter)+linia1;
    end;
    inc(iter);
//    Writeln(plik2,linia1);
  end;
  CloseFile(plik1);
//  CloseFile(plik2);
//  ValueListEditor2.CleanupInstance;


end;

procedure TForm5.BitBtn_DelLineClick(Sender: TObject);
var iter:Integer;
    plik1,plik2:TextFile;
    linia1:string;
begin
//  ile_linii:=ValueListEditor2.RowCount-1;
//  ShowMessage(IntToStr(ile_linii));
//  ValueListEditor2.InsertRow('enc_'+IntToStr(ile_linii+1),'new line',true);
  ValueListEditor2.DeleteRow(ValueListEditor2.Selection.Top);
  ValueListEditor2.Refresh;

  iter:=0;
  ValueListEditor2.Strings.SaveToFile('temp1');
  AssignFile(plik1,'temp1');
  Reset(plik1);
//  AssignFile(plik2,'temp2');
//  Rewrite(plik2);
  While not eof(plik1) do
  begin
    Readln(plik1, linia1);
//    delete(linia1,1,6);
    // enc_11=
    if iter<10 then
    begin
      ValueListEditor2.Keys[iter+1]:='enc_0'+IntToStr(iter);
//      linia1:='enc_0'+IntToStr(iter)+linia1;
    end;
    if iter>=10 then
    begin
      ValueListEditor2.Keys[iter+1]:='enc_'+IntToStr(iter);
//      linia1:='enc_'+IntToStr(iter)+linia1;
    end;
    inc(iter);
//    Writeln(plik2,linia1);
  end;
  CloseFile(plik1);
//  CloseFile(plik2);
//  ValueListEditor2.CleanupInstance;
end;


procedure TForm5.ValueListEditor2DblClick(Sender: TObject);
begin
  If not Assigned(Form11) then
  begin
//    Form3:=TForm3.Create(Application);
    Form11:=TForm11.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form11.Show;
  end
  else
  begin
    Form11.Close;
    Form11.Destroy;
    Form11:=TForm11.Create(nil);         // dlaczego 'nil' a nie 'Application' ?? Nie wiem ;) ale na razie dzia³a 08/12/2006
    Form11.Show;
  end;

// Chance:100%,Enc:(10-20) EPA_Alien AND (1-1) High_Radiation AMBUSH Player, If (Player(Level) > 40)
// Chance:100%,Special,Enc: Low_Radiation
// Chance:100%,Special,Enc: Rad_Vomiting, If (Global(702) > 70)
end;

