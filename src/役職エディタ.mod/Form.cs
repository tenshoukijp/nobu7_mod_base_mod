using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;



public partial class 役職エディタ : 基本エディタ
{

    public 役職エディタ() : base()
    {
        this.Text = nameof(役職エディタ);
    }

    class BIND用の役職情報型
    {
        役職情報型 役職情報;
        public BIND用の役職情報型(int 役職配列IX)
        {
            役職情報 = new 役職情報型(役職配列IX);
        }

        public int 配列IX
        {
            get { return 役職情報.配列IX; }
        }
        public string 役職名
        {
            get { return 役職情報.役職名; }
            set { 役職情報.役職名 = value; }
        }
        public int 役位
        {
            get { return 役職情報.役位; }
        }
        public int 所有大名配列IX
        {
            get { return 役職情報.所有大名配列IX; }
            set { 役職情報.所有大名配列IX = value; }
        }
    }

    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の役職情報型> データ配列 = new();
            for(int i=0; i< 将星録.最大数.役職情報.配列数; i++)
            {
                データ配列.Add(new BIND用の役職情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }
    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用の役職情報型.配列IX)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用の役職情報型.役位)].DefaultCellStyle.BackColor = Color.LightGray;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}