object Form2: TForm2
  Left = 212
  Top = 184
  Width = 386
  Height = 518
  Caption = 'Edit Tile'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label_Nazwa_Tile: TLabel
    Left = 152
    Top = 8
    Width = 69
    Height = 20
    Caption = '[Tile 41]'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 355
    Width = 47
    Height = 16
    Caption = 'art_idx'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 16
    Top = 387
    Width = 134
    Height = 16
    Caption = 'encounter_difficulty'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 224
    Top = 344
    Width = 76
    Height = 13
    Caption = 'numer przycisku'
    Enabled = False
    Visible = False
  end
  object Label_walk_mask_name: TLabel
    Left = 16
    Top = 416
    Width = 123
    Height = 16
    Caption = 'walk_mask_name'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object BitBtn_Zamknij: TBitBtn
    Left = 200
    Top = 456
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 0
    OnClick = BitBtn_ZamknijClick
  end
  object Panel1: TPanel
    Left = 12
    Top = 32
    Width = 352
    Height = 302
    BevelInner = bvRaised
    BevelOuter = bvLowered
    Caption = 'Panel1'
    TabOrder = 1
  end
  object BitBtn1: TBitBtn
    Left = 80
    Top = 456
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object Edit_art_idx: TEdit
    Left = 80
    Top = 352
    Width = 41
    Height = 24
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    Text = '490'
  end
  object Edit_encounter_difficulty: TEdit
    Left = 160
    Top = 384
    Width = 49
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    Text = '-15'
  end
  object Edit3: TEdit
    Left = 224
    Top = 360
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 5
    Text = 'Edit3'
    Visible = False
  end
  object Edit_walk_mask_name: TEdit
    Left = 160
    Top = 416
    Width = 97
    Height = 24
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    Text = 'Edit_walk_mask_name'
  end
end
