program WorldmapTileEditor;

uses
  Forms,
  Worldmap_tile_editor in 'Worldmap_tile_editor.pas' {Form1},
  Unit4_Enc_Percentage in 'Unit4_Enc_Percentage.pas' {Form4},
  Unit5 in 'Unit5.pas' {Form5},
  Unit6 in 'Unit6.pas' {Form6},
  Unit7_show_worldmap_txt in 'Unit7_show_worldmap_txt.pas' {Form7},
  Unit3_List_Maps in 'Unit3_List_Maps.pas' {Form3},
  Unit3_List_Encounters in 'Unit3_List_Encounters.pas' {Form2},
  Unit8_Actions in 'Unit8_Actions.pas' {Form8},
  Unit9_add_maps in 'Unit9_add_maps.pas' {Form9},
  Unit10_lista_enc_table in 'Unit10_lista_enc_table.pas' {Form10},
  Unit12 in 'Unit12.pas' {Form12},
  Unit13_Setup in 'Unit13_Setup.pas' {Form13};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm13, Form13);
  Application.Run;
end.
