object Form5: TForm5
  Left = 394
  Top = 256
  Width = 921
  Height = 552
  Caption = 'Editing Encounter Table'
  Color = clBtnFace
  Font.Charset = EASTEUROPE_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Courier New'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poMainFormCenter
  WindowState = wsMaximized
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object Panel2: TPanel
    Left = 0
    Top = 453
    Width = 905
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object BitBtn_Save: TBitBtn
      Left = 232
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Save'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = BitBtn_SaveClick
    end
    object BitBtn_Cancel: TBitBtn
      Left = 544
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Cancel'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = BitBtn_CancelClick
    end
    object BitBtn1: TBitBtn
      Left = 24
      Top = 8
      Width = 105
      Height = 25
      Caption = 'Delete Enc. Table'
      Enabled = False
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = BitBtn1Click
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 905
    Height = 65
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 4
      Top = 15
      Width = 120
      Height = 16
      Caption = 'Encounter Table'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 100
      Top = 31
      Width = 48
      Height = 16
      Caption = 'Label2'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 52
      Top = 47
      Width = 48
      Height = 16
      Caption = 'Label3'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 4
      Top = 31
      Width = 96
      Height = 16
      Caption = 'lookup_name='
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 4
      Top = 47
      Width = 40
      Height = 16
      Caption = 'maps='
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
    end
    object BitBtn_View_worldmaptxt_: TBitBtn
      Left = 440
      Top = 8
      Width = 121
      Height = 25
      Caption = 'View "worldmap.txt"'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = BitBtn_View_worldmaptxt_Click
    end
    object BitBtn_Maps_List_: TBitBtn
      Left = 568
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Maps names'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Visible = False
      OnClick = BitBtn_Maps_List_Click
    end
    object BitBtn_Encounters_List_: TBitBtn
      Left = 648
      Top = 8
      Width = 105
      Height = 25
      Caption = 'Encounter Groups'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = BitBtn_Encounters_List_Click
    end
    object BitBtn_Actions_: TBitBtn
      Left = 760
      Top = 8
      Width = 57
      Height = 25
      Caption = 'Actions'
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = BitBtn_Actions_Click
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 65
    Width = 905
    Height = 388
    Align = alClient
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    Left = 824
    Top = 8
    object File1: TMenuItem
      Caption = 'File'
      object Exit1: TMenuItem
        Caption = 'New'
        Enabled = False
      end
      object Save1: TMenuItem
        Caption = 'Save'
        Enabled = False
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit2: TMenuItem
        Caption = 'Close'
        OnClick = Exit2Click
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object Maps1: TMenuItem
        Caption = 'Maps Names'
        OnClick = BitBtn_Maps_List_Click
      end
      object EncGroup1: TMenuItem
        Caption = 'Encounter Group'
        OnClick = BitBtn_Encounters_List_Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object worldmaptxt1: TMenuItem
        Caption = 'View "worldmap.txt"'
        OnClick = BitBtn_View_worldmaptxt_Click
      end
    end
    object Help1: TMenuItem
      Caption = 'Help'
      object Helpme1: TMenuItem
        Caption = 'Help me'
      end
      object About1: TMenuItem
        Caption = 'About'
      end
    end
  end
end
