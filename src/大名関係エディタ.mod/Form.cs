using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System;

namespace 将星録;

public partial class 大名関係エディタ : 基本エディタ
{
    int 主格大名配列IX;

    public 大名関係エディタ(int 主格大名配列IX) : base()
    {
        this.Text = nameof(大名関係エディタ);
        this.主格大名配列IX = 主格大名配列IX;
    }

    class BIND用の大名関係情報型
    {
        大名関係情報型 大名関係情報;

        int 主格大名配列IX;
        int 大名配列IX;
        public BIND用の大名関係情報型(int 主格大名配列IX, int 大名配列IX)
        {
            this.主格大名配列IX = 主格大名配列IX;
            this.大名配列IX = 大名配列IX;

            大名関係情報 = new 大名関係情報型();
        }

        public int 配列IX
        {
            get { return 大名配列IX; }
        }

        public string 大名姓名
        {
            get
            {
                大名情報型 大名情報 = new 大名情報型(大名配列IX);
                int iBushouID = 大名情報.大名武将配列IX;
                if (0 <= iBushouID && iBushouID < 最大数.武将情報.配列数)
                {
                    武将情報型 武将情報 = new 武将情報型(iBushouID);
                    return 武将情報.姓名;
                }
                else
                {
                    return "－";
                }
            }
        }

        public int 友好
        {
            get { return 大名関係情報.友好[主格大名配列IX, 大名配列IX]; }
            set { 大名関係情報.友好[主格大名配列IX, 大名配列IX] = value; }
        }

        public int 同盟残
        {
            get { return 大名関係情報.同盟残[主格大名配列IX, 大名配列IX]; }
            set { 大名関係情報.同盟残[主格大名配列IX, 大名配列IX] = value; }
        }

        public int 婚姻
        {
            get { return 大名関係情報.婚姻[主格大名配列IX, 大名配列IX]; }
            set { 大名関係情報.婚姻[主格大名配列IX, 大名配列IX] = value; }
        }
    }


    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の大名関係情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.大名情報.配列数; i++)
            {
                データ配列.Add(new BIND用の大名関係情報型(主格大名配列IX, i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }

    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用の大名関係情報型.配列IX)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の大名関係情報型.大名姓名)].DefaultCellStyle.BackColor = Color.Yellow;
            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}

