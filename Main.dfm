object Form1: TForm1
  Left = 0
  Top = 0
  ActiveControl = VirtualStringTree1
  Caption = 'Main'
  ClientHeight = 486
  ClientWidth = 820
  Color = clBtnFace
  Constraints.MaxHeight = 525
  Constraints.MaxWidth = 836
  Constraints.MinHeight = 525
  Constraints.MinWidth = 836
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 146
    Height = 20
    AutoSize = False
    Caption = #1057#1050#1040#1053#1048#1056#1054#1042#1040#1058#1068
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 90
    Width = 146
    Height = 20
    AutoSize = False
    Caption = #1053#1077' '#1087#1091#1089#1090#1099#1077' '#1082#1083#1072#1089#1090#1077#1088#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 64
    Width = 202
    Height = 20
    Alignment = taCenter
    AutoSize = False
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Transparent = True
  end
  object Label4: TLabel
    Left = 8
    Top = 424
    Width = 146
    Height = 20
    AutoSize = False
    Caption = #1056#1072#1079#1084#1077#1088' '#1060#1057' ('#1052#1041')'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label5: TLabel
    Left = 8
    Top = 440
    Width = 146
    Height = 20
    AutoSize = False
    Caption = #1050#1086#1083'-'#1074#1086' '#1082#1083#1072#1089#1090#1077#1088#1086#1074' '#1074' '#1060#1057
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label6: TLabel
    Left = 8
    Top = 458
    Width = 146
    Height = 20
    AutoSize = False
    Caption = #1056#1072#1079#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072' ('#1041#1072#1081#1090')'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object FSSizeLabel: TLabel
    Left = 160
    Top = 422
    Width = 50
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object ClusterCountLabel: TLabel
    Left = 160
    Top = 440
    Width = 50
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object ClusterSizeLabel: TLabel
    Left = 160
    Top = 458
    Width = 50
    Height = 20
    Alignment = taRightJustify
    AutoSize = False
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object DBPath: TLabel
    Left = 292
    Top = 8
    Width = 396
    Height = 18
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object VolumeName: TLabel
    Left = 770
    Top = 12
    Width = 42
    Height = 20
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label12: TLabel
    Left = 8
    Top = 116
    Width = 146
    Height = 20
    AutoSize = False
    Caption = #1055#1086#1080#1089#1082' '#1089#1080#1075#1085#1072#1090#1091#1088
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object FSLabel: TLabel
    Left = 8
    Top = 398
    Width = 202
    Height = 20
    Alignment = taCenter
    AutoSize = False
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object ProgressLabel: TLabel
    Left = 8
    Top = 38
    Width = 202
    Height = 20
    Alignment = taCenter
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 214
    Top = 32
    Width = 598
    Height = 440
    Colors.BorderColor = clWhite
    Header.AutoSizeIndex = 0
    Header.Height = 20
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    TreeOptions.AutoOptions = [toAutoDropExpand, toAutoScroll, toAutoScrollOnExpand, toAutoSort, toAutoTristateTracking, toAutoDeleteMovedNodes, toAutoChangeScale]
    TreeOptions.PaintOptions = [toShowButtons, toShowDropmark, toShowHorzGridLines, toShowRoot, toShowTreeLines, toShowVertGridLines, toThemeAware, toUseBlendedImages]
    TreeOptions.SelectionOptions = [toFullRowSelect]
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'ID'
        Width = 71
      end
      item
        Position = 1
        Text = #1053#1086#1084#1077#1088' '#1050#1083#1072#1089#1090#1077#1088#1072
        Width = 94
      end
      item
        CaptionAlignment = taRightJustify
        Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coParentColor, coResizable, coShowDropMark, coVisible, coAllowFocus, coUseCaptionAlignment, coEditable, coStyleColor]
        Position = 2
        Text = #1057#1086#1076#1077#1088#1078#1080#1084#1086#1077' '#1050#1083#1072#1089#1090#1077#1088#1072
        Width = 325
      end
      item
        Position = 3
        Text = #1057#1080#1075#1085#1072#1090#1091#1088#1072
        Width = 95
      end>
  end
  object ScanToggleSwitch: TToggleSwitch
    Left = 160
    Top = 6
    Width = 50
    Height = 20
    DisabledColor = clSilver
    Enabled = False
    FrameColor = clMoneyGreen
    ShowStateCaption = False
    TabOrder = 1
    ThumbColor = clMoneyGreen
    OnClick = ScanToggleSwitchClick
  end
  object EmptyClusterToggleSwitch: TToggleSwitch
    Left = 160
    Top = 90
    Width = 50
    Height = 20
    DisabledColor = clSilver
    FrameColor = clMoneyGreen
    ShowStateCaption = False
    TabOrder = 2
    ThumbColor = clSkyBlue
    OnClick = EmptyClusterToggleSwitchClick
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 32
    Width = 202
    Height = 7
    Smooth = True
    SmoothReverse = True
    TabOrder = 3
  end
  object SearchSignToggleSwitch: TToggleSwitch
    Left = 160
    Top = 117
    Width = 50
    Height = 20
    DisabledColor = clSilver
    FrameColor = clMoneyGreen
    ShowStateCaption = False
    TabOrder = 4
    ThumbColor = clSkyBlue
    OnClick = SearchSignToggleSwitchClick
  end
  object DeleteButton: TButton
    Left = 112
    Top = 367
    Width = 98
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMenuText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = DeleteButtonClick
  end
  object DeleteAllButton: TButton
    Left = 8
    Top = 367
    Width = 98
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1105
    Enabled = False
    TabOrder = 6
    OnClick = DeleteAllButtonClick
  end
  object SelectVolumeButton: TButton
    Left = 694
    Top = 1
    Width = 70
    Height = 25
    Caption = #1052#1077#1090#1082#1072' '#1090#1086#1084#1072
    TabOrder = 7
    OnClick = SelectVolumeButtonClick
  end
  object SigCheckListBox: TCheckListBox
    Left = 8
    Top = 142
    Width = 202
    Height = 91
    OnClickCheck = SigCheckListBoxClickCheck
    Color = clMoneyGreen
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 16
    Font.Name = 'Tahoma'
    Font.Style = []
    HeaderBackgroundColor = clSkyBlue
    Items.Strings = (
      'PNG'
      'JPEG'
      'GIF'
      'PDF'
      'FILE')
    ParentFont = False
    TabOrder = 8
  end
  object Button3: TButton
    Left = 216
    Top = 1
    Width = 70
    Height = 25
    Caption = #1055#1091#1090#1100' '#1082' '#1041#1044
    TabOrder = 9
    OnClick = Button3Click
  end
  object ToggleSwitch1: TToggleSwitch
    Left = 128
    Top = 40
    Width = 72
    Height = 20
    TabOrder = 10
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    Filter = 
      #1060#1072#1081#1083#1099' SQLite '#1073#1072#1079' '#1076#1072#1085#1085#1099#1093' (*.db *.sqlite *.sqlite3 *.db3)|*.db;*.s' +
      'qlite;*.sqlite3;*.db3'
    Options = [ofHideReadOnly, ofNoChangeDir, ofPathMustExist, ofFileMustExist, ofNoReadOnlyReturn, ofEnableSizing]
    Title = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1089' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093
    Left = 264
    Top = 104
  end
end
