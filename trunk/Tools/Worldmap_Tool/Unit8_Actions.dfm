object Form8: TForm8
  Left = 192
  Top = 107
  Width = 343
  Height = 530
  Caption = 'Possible Actions for Encounter Groups'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 228
    Height = 19
    Alignment = taCenter
    Caption = 'Actions for Encounter Groups'
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Arial'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ComboBox1: TComboBox
    Left = 0
    Top = 40
    Width = 321
    Height = 450
    Style = csSimple
    ItemHeight = 13
    TabOrder = 0
    Items.Strings = (
      'AMBUSH'
      'FIGHTING')
  end
end
