using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;



public partial class 官位エディタ : 基本エディタ
{

    public 官位エディタ() : base()
    {
        this.Text = nameof(官位エディタ);
    }

    class BIND用の官位情報型
    {
        官位情報型 官位情報;
        public BIND用の官位情報型(int 官位配列IX)
        {
            官位情報 = new 官位情報型(官位配列IX);
        }

        public int 配列IX
        {
            get { return 官位情報.配列IX; }
        }
        public string 官位名
        {
            get { return 官位情報.官位名; }
            set { 官位情報.官位名 = value; }
        }

        public int 階位
        {
            get { return 官位情報.階位; }
            set { 官位情報.階位 = value; }
        }
        public int 所有大名配列IX
        {
            get { return 官位情報.所有武将配列IX; }
            set { 官位情報.所有武将配列IX = value; }
        }
    }


    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の官位情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.官位情報.配列数; i++)
            {
                データ配列.Add(new BIND用の官位情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }

    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用の官位情報型.配列IX)].DefaultCellStyle.BackColor = Color.LightGray;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }

}

