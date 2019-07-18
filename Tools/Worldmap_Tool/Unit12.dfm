object Form12: TForm12
  Left = 318
  Top = 280
  Width = 326
  Height = 489
  Caption = 'Critters List'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 8
    Top = 24
    Width = 113
    Height = 25
    Caption = 'Calculate PID:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object Label1: TLabel
    Left = 8
    Top = 0
    Width = 102
    Height = 20
    Caption = 'Critters List'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 56
    Width = 297
    Height = 393
    Style = csSimple
    ItemHeight = 13
    TabOrder = 0
    Text = 'ComboBox1'
    OnSelect = ComboBox1Select
  end
  object Edit1: TEdit
    Left = 128
    Top = 24
    Width = 177
    Height = 21
    TabOrder = 1
  end
end
