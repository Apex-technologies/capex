object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'CAPEX Test'
  ClientHeight = 639
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
    Height = 593
    ActivePage = ArraySheet
    TabOrder = 0
    object ArraySheet: TTabSheet
      Caption = 'Array Test'
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
    end
  end
  object Quit_Bt: TButton
    Left = 962
    Top = 607
    Width = 89
    Height = 25
    Caption = 'Quit'
    TabOrder = 1
    OnClick = Quit_BtClick
  end
end
