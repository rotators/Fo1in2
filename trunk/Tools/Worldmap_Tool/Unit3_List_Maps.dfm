object Form3: TForm3
  Left = 501
  Top = 162
  Width = 340
  Height = 531
  Caption = 'Maps List'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 102
    Height = 19
    Alignment = taCenter
    Caption = 'Maps names:'
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
  end
end
