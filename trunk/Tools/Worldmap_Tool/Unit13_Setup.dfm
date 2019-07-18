object Form13: TForm13
  Left = 790
  Top = 315
  Width = 254
  Height = 372
  Caption = 'Form13'
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
  object RadioGroup1: TRadioGroup
    Left = 16
    Top = 21
    Width = 209
    Height = 105
    Caption = 'Choose Background map'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 1
    Items.Strings = (
      'Fallout 1 worldmap (\FO1\ directory)'
      'Fallout 2 worldmap (\FO2\ directory)')
    ParentFont = False
    TabOrder = 0
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 144
    Width = 209
    Height = 113
    Caption = 'Window size'
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 32
      Width = 82
      Height = 13
      Caption = 'Width (600-1920)'
    end
    object Label2: TLabel
      Left = 16
      Top = 64
      Width = 82
      Height = 13
      Caption = 'Height(700-1080)'
    end
    object SpinEdit1: TSpinEdit
      Left = 104
      Top = 32
      Width = 81
      Height = 22
      MaxValue = 1920
      MinValue = 600
      TabOrder = 0
      Value = 600
      OnClick = SpinEdit1Click
    end
    object SpinEdit2: TSpinEdit
      Left = 104
      Top = 64
      Width = 81
      Height = 22
      MaxValue = 1080
      MinValue = 700
      TabOrder = 1
      Value = 700
      OnClick = SpinEdit2Click
    end
  end
  object BitBtn1: TBitBtn
    Left = 16
    Top = 280
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 144
    Top = 280
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = BitBtn2Click
  end
end
