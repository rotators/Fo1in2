object Form9: TForm9
  Left = 559
  Top = 133
  Width = 296
  Height = 557
  Caption = 'Select Maps for Random Encounter'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object BitBtn1: TBitBtn
    Left = 152
    Top = 16
    Width = 107
    Height = 25
    Caption = 'Add selected Map'
    TabOrder = 0
    OnClick = BitBtn1Click
  end
  object ListBox1: TListBox
    Left = 0
    Top = 48
    Width = 273
    Height = 465
    ItemHeight = 13
    MultiSelect = True
    Sorted = True
    TabOrder = 1
  end
end
