using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;



public partial class 野戦エディタ : 基本エディタ
{

    public 野戦エディタ() : base()
    {
        this.Text = nameof(野戦エディタ);
    }

    class BIND用の野戦情報型
    {
        野戦.ターン情報型 野戦ターン情報;
        public BIND用の野戦情報型()
        {
            野戦ターン情報 = new 野戦.ターン情報型();
        }

        public int 天気
        {
            get { return 野戦ターン情報.天気; }
            set { 野戦ターン情報.天気 = value; }
        }
        public int 残りターン
        {
            get { return 野戦ターン情報.残りターン; }
        }
    }

    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の野戦情報型> データ配列 = new();
            データ配列.Add(new BIND用の野戦情報型());
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }
    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用の野戦情報型.残りターン)].DefaultCellStyle.BackColor = Color.LightGray;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}