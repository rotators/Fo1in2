object Form2: TForm2
  Left = 944
  Top = 245
  Width = 344
  Height = 530
  Caption = 'Encounters List'
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
    Width = 152
    Height = 20
    Caption = 'Encounter Groups'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object SpeedButton1: TSpeedButton
    Left = 264
    Top = 32
    Width = 57
    Height = 22
    Caption = 'Edit'
    OnClick = SpeedButton1Click
  end
  object Label2: TLabel
    Left = 0
    Top = 40
    Width = 41
    Height = 13
    Caption = 'search...'
  end
  object ComboBox1: TComboBox
    Left = 0
    Top = 56
    Width = 321
    Height = 433
    Style = csSimple
    ItemHeight = 13
    TabOrder = 0
    Text = 'ComboBox1'
    OnDblClick = ComboBox1DblClick
    OnKeyPress = ComboBox1KeyPress
  end
end
