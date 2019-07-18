object Form3: TForm3
  Left = 619
  Top = 135
  Width = 370
  Height = 284
  Caption = 'Tile Data'
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
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 8
    Top = 40
    Width = 35
    Height = 13
    Caption = 'terrain: '
  end
  object Label3: TLabel
    Left = 8
    Top = 64
    Width = 15
    Height = 13
    Caption = 'fill: '
  end
  object Label4: TLabel
    Left = 8
    Top = 88
    Width = 82
    Height = 13
    Caption = 'morning chance: '
  end
  object Label5: TLabel
    Left = 8
    Top = 112
    Width = 90
    Height = 13
    Caption = 'afternoon chance: '
  end
  object Label6: TLabel
    Left = 8
    Top = 136
    Width = 68
    Height = 13
    Caption = 'night chance: '
  end
  object Label7: TLabel
    Left = 8
    Top = 160
    Width = 80
    Height = 13
    Caption = 'encounter table: '
  end
  object BitBtn1: TBitBtn
    Left = 240
    Top = 200
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 64
    Top = 200
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 1
    OnClick = BitBtn2Click
  end
  object BitBtn3: TBitBtn
    Left = 280
    Top = 152
    Width = 81
    Height = 21
    Caption = 'Edit this Table'
    TabOrder = 2
    OnClick = BitBtn3Click
  end
  object ComboBox1: TComboBox
    Left = 104
    Top = 32
    Width = 169
    Height = 21
    ItemHeight = 13
    TabOrder = 3
    Text = 'ComboBox1'
  end
  object ComboBox2: TComboBox
    Left = 104
    Top = 56
    Width = 169
    Height = 21
    ItemHeight = 13
    TabOrder = 4
    Text = 'ComboBox2'
  end
  object ComboBox3: TComboBox
    Left = 104
    Top = 80
    Width = 169
    Height = 21
    ItemHeight = 13
    TabOrder = 5
    Text = 'ComboBox3'
  end
  object ComboBox4: TComboBox
    Left = 104
    Top = 104
    Width = 169
    Height = 21
    ItemHeight = 13
    TabOrder = 6
    Text = 'ComboBox4'
  end
  object ComboBox5: TComboBox
    Left = 104
    Top = 128
    Width = 169
    Height = 21
    ItemHeight = 13
    TabOrder = 7
    Text = 'ComboBox5'
  end
  object ComboBox6: TComboBox
    Left = 104
    Top = 152
    Width = 169
    Height = 21
    ItemHeight = 13
    TabOrder = 8
    Text = 'ComboBox6'
  end
end
