using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using 将星録.最大数;

namespace 将星録;



public partial class 籠城戦防御部隊エディタ : 基本エディタ
{

    public 籠城戦防御部隊エディタ() : base()
    {
        this.Text = nameof(籠城戦防御部隊エディタ);
    }

    class BIND用の籠城戦防御部隊情報型
    {
        籠城戦.防御部隊情報型 籠城戦防御部隊情報;
        public BIND用の籠城戦防御部隊情報型(int 部隊配列IX)
        {
            籠城戦防御部隊情報 = new 籠城戦.防御部隊情報型(部隊配列IX);
        }

        public int 配列IX
        {
            get { return 籠城戦防御部隊情報.配列IX; }
        }

        public string 指揮武将姓名
        {
            get
            {
                int iBushouID = 籠城戦防御部隊情報.指揮武将配列IX;
                String strBushouName = "-";
                if (0 <= iBushouID && iBushouID < 最大数.武将情報.総配列数)
                {
                    var 武将情報 = new 武将情報型(iBushouID);
                    strBushouName = 武将情報.姓名;
                }
                return strBushouName;
            }
        }
        public int 指揮武将配列IX
        {
            get { return 籠城戦防御部隊情報.指揮武将配列IX; }
        }
        public int 部隊番号
        {
            get { return 籠城戦防御部隊情報.部隊番号; }
        }

        public int 兵数
        {
            get { return 籠城戦防御部隊情報.兵数; }
            set { 籠城戦防御部隊情報.兵数 = value; }
        }

        public int 行動残数
        {
            get { return 籠城戦防御部隊情報.行動残数; }
            set { 籠城戦防御部隊情報.行動残数 = value; }
        }

        public int 混乱
        {
            get { return 籠城戦防御部隊情報.混乱; }
            set { 籠城戦防御部隊情報.混乱 = value; }
        }

    }

    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の籠城戦防御部隊情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.籠城戦.防御部隊情報.配列数; i++)
            {
                データ配列.Add(new BIND用の籠城戦防御部隊情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }
    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用の籠城戦防御部隊情報型.配列IX)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の籠城戦防御部隊情報型.指揮武将配列IX)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の籠城戦防御部隊情報型.部隊番号)].DefaultCellStyle.BackColor = Color.LightGray;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}