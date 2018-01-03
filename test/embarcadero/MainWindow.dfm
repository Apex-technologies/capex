object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'CAPEX Test'
  ClientHeight = 730
  ClientWidth = 1059
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 1043
    Height = 665
    ActivePage = INI_Sheet
    TabOrder = 0
    object ArraySheet: TTabSheet
      Caption = 'Array Test'
      object FreqLabel: TLabel
        Left = 6
        Top = 538
        Width = 68
        Height = 13
        Caption = 'Freqency (Hz)'
      end
      object Label1: TLabel
        Left = 318
        Top = 538
        Width = 80
        Height = 13
        Caption = 'Threshold (A.U.)'
      end
      object Label2: TLabel
        Left = 507
        Top = 538
        Width = 97
        Height = 13
        Caption = 'Smoothing Winddow'
      end
      object Chart1: TChart
        Left = -4
        Top = 3
        Width = 1029
        Height = 518
        Legend.Visible = False
        MarginBottom = 1
        MarginRight = 1
        MarginTop = 1
        Title.Text.Strings = (
          'TChart')
        Title.Visible = False
        BottomAxis.Title.Caption = 'X Axis'
        DepthAxis.Automatic = False
        DepthAxis.AutomaticMaximum = False
        DepthAxis.AutomaticMinimum = False
        DepthAxis.Maximum = 0.500000000000000000
        DepthAxis.Minimum = -0.500000000000000000
        DepthTopAxis.Automatic = False
        DepthTopAxis.AutomaticMaximum = False
        DepthTopAxis.AutomaticMinimum = False
        DepthTopAxis.Maximum = 0.500000000000000000
        DepthTopAxis.Minimum = -0.500000000000000000
        LeftAxis.Title.Caption = 'Y Axis'
        RightAxis.Automatic = False
        RightAxis.AutomaticMaximum = False
        RightAxis.AutomaticMinimum = False
        RightAxis.Visible = False
        TopAxis.Automatic = False
        TopAxis.AutomaticMaximum = False
        TopAxis.AutomaticMinimum = False
        TopAxis.Visible = False
        View3D = False
        View3DOptions.Orthogonal = False
        BevelOuter = bvNone
        Color = clWhite
        TabOrder = 0
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series1: TFastLineSeries
          LinePen.Color = 10708548
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object Frequency_Bar: TTrackBar
        Left = 80
        Top = 533
        Width = 225
        Height = 25
        LineSize = 10
        Max = 100
        Min = 1
        PageSize = 1
        Frequency = 10
        Position = 1
        PositionToolTip = ptBottom
        TabOrder = 1
        ThumbLength = 15
        OnChange = Frequency_BarChange
      end
      object Noise_Bt: TButton
        Left = 972
        Top = 533
        Width = 60
        Height = 25
        Caption = 'Noise'
        TabOrder = 2
        OnClick = Noise_BtClick
      end
      object SetSmooth_Bt: TButton
        Left = 822
        Top = 533
        Width = 64
        Height = 25
        Caption = 'Set Smooth'
        TabOrder = 3
        OnClick = SetSmooth_BtClick
      end
      object Sinus_Bt: TButton
        Left = 906
        Top = 533
        Width = 60
        Height = 25
        Caption = 'Sinus'
        TabOrder = 4
        OnClick = Sinus_BtClick
      end
      object Smooth_Bar: TTrackBar
        Left = 614
        Top = 533
        Width = 201
        Height = 25
        LineSize = 10
        Max = 100
        Min = 1
        PageSize = 1
        Frequency = 10
        Position = 1
        PositionToolTip = ptBottom
        TabOrder = 5
        ThumbLength = 15
      end
      object Threshold_Edit: TEdit
        Left = 414
        Top = 535
        Width = 81
        Height = 21
        Alignment = taCenter
        TabOrder = 6
        Text = '-1.0'
        OnChange = Threshold_EditChange
      end
      object RadioGroup2: TRadioGroup
        Left = 518
        Top = 564
        Width = 291
        Height = 61
        Caption = 'Smoothing Functions'
        TabOrder = 7
      end
      object SmoothSquare_Radio: TRadioButton
        Left = 525
        Top = 584
        Width = 64
        Height = 17
        Caption = 'Square'
        Checked = True
        TabOrder = 8
        TabStop = True
      end
      object SmoothSinus_Radio: TRadioButton
        Left = 526
        Top = 604
        Width = 64
        Height = 17
        Caption = 'Sinus'
        TabOrder = 9
      end
      object SmoothSinc_Radio: TRadioButton
        Left = 618
        Top = 584
        Width = 99
        Height = 17
        Caption = 'Cardinal Sinus'
        TabOrder = 10
      end
      object SmoothGaussian_Radio: TRadioButton
        Left = 618
        Top = 604
        Width = 99
        Height = 17
        Caption = 'Gaussian'
        TabOrder = 11
      end
      object Derivative1_Bt: TButton
        Left = 318
        Top = 564
        Width = 177
        Height = 25
        Caption = 'Derivative Order 1'
        TabOrder = 12
        OnClick = Derivative1_BtClick
      end
      object Derivative2_Bt: TButton
        Left = 318
        Top = 590
        Width = 177
        Height = 25
        Caption = 'Derivative Order 2'
        TabOrder = 13
        OnClick = Derivative2_BtClick
      end
      object DerivativeDeltaX_Check: TCheckBox
        Left = 320
        Top = 616
        Width = 177
        Height = 17
        Caption = 'Divide by Delta X'
        TabOrder = 14
      end
      object SinusNoise_Bt: TButton
        Left = 906
        Top = 564
        Width = 126
        Height = 25
        Caption = 'Sinus + Noise'
        TabOrder = 15
        OnClick = SinusNoise_BtClick
      end
    end
    object INI_Sheet: TTabSheet
      Caption = 'INI File Test'
      ImageIndex = 2
      object OpenINI_Bt: TButton
        Left = 16
        Top = 24
        Width = 129
        Height = 33
        Caption = 'Open INI File'
        TabOrder = 0
        OnClick = OpenINI_BtClick
      end
      object IniGrid: TStringGrid
        Left = 16
        Top = 80
        Width = 1001
        Height = 528
        ColCount = 3
        DefaultColWidth = 320
        FixedCols = 0
        RowCount = 1000
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        TabOrder = 1
        ColWidths = (
          320
          320
          338)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          23
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
      object SaveINI_Bt: TButton
        Left = 151
        Top = 24
        Width = 129
        Height = 33
        Caption = 'Save INI File'
        TabOrder = 2
        OnClick = SaveINI_BtClick
      end
    end
  end
  object Quit_Bt: TButton
    Left = 1000
    Top = 679
    Width = 51
    Height = 25
    Caption = 'Quit'
    TabOrder = 1
    OnClick = Quit_BtClick
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 711
    Width = 1059
    Height = 19
    Panels = <
      item
        Width = 50
      end>
  end
  object OpenIniDialog: TOpenDialog
    Filter = 'INI FILE (*.INI)|*.ini'
    Left = 868
    Top = 56
  end
  object SaveIniDialog: TSaveDialog
    Filter = 'INI FILE (*.INI)|*.ini'
    Left = 972
    Top = 56
  end
end
