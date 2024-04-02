using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using 将星録.最大数;

namespace 将星録;



public partial class 野戦攻撃部隊エディタ : 基本エディタ
{

    public 野戦攻撃部隊エディタ() : base()
    {
        this.Text = nameof(野戦攻撃部隊エディタ);
    }

    class BIND用の野戦攻撃部隊情報型
    {
        野戦.攻撃部隊情報型 野戦攻撃部隊情報;
        public BIND用の野戦攻撃部隊情報型(int 部隊配列IX)
        {
            野戦攻撃部隊情報 = new 野戦.攻撃部隊情報型(部隊配列IX);
        }

        public int 配列IX
        {
            get { return 野戦攻撃部隊情報.配列IX; }
        }

        public int 部隊番号
        {
            get { return 野戦攻撃部隊情報.部隊番号; }
        }

        public int 兵数
        {
            get { return 野戦攻撃部隊情報.兵数; }
            set { 野戦攻撃部隊情報.兵数 = value; }
        }

        public int 種別
        {
            get { return 野戦攻撃部隊情報.種別; }
        }

        public int 行動済
        {
            get { return 野戦攻撃部隊情報.行動済; }
        }

        public int 旗部隊
        {
            get { return 野戦攻撃部隊情報.旗部隊; }
        }
    }

    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の野戦攻撃部隊情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.ユニット情報.軍勢部隊数; i++)
            {
                データ配列.Add(new BIND用の野戦攻撃部隊情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }
    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用の野戦攻撃部隊情報型.配列IX)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の野戦攻撃部隊情報型.部隊番号)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の野戦攻撃部隊情報型.種別)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の野戦攻撃部隊情報型.行動済)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の野戦攻撃部隊情報型.旗部隊)].DefaultCellStyle.BackColor = Color.LightGray;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}