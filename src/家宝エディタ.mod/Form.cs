using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;

public partial class 家宝エディタ : 基本エディタ
{

    public 家宝エディタ() : base()
    {
        this.Text = nameof(家宝エディタ);
    }

    class BIND用の家宝情報型
    {
        家宝情報型 家宝情報;
        public BIND用の家宝情報型(int 家宝配列IX)
        {
            家宝情報 = new 家宝情報型(家宝配列IX);
        }

        public int 配列IX
        {
            get { return 家宝情報.配列IX; }
        }
        public string 家宝名
        {
            get { return 家宝情報.家宝名; }
            set { 家宝情報.家宝名 = value; }
        }

        public int 種類
        {
            get { return 家宝情報.種類; }
            set { 家宝情報.種類 = value; }
        }

        public int 画像
        {
            get { return 家宝情報.画像; }
            set { 家宝情報.画像 = value; }
        }

        public int 等級
        {
            get { return 家宝情報.等級; }
            set { 家宝情報.等級 = value; }
        }

        public int 能力上昇
        {
            get { return 家宝情報.能力上昇; }
            set { 家宝情報.能力上昇 = value; }
        }

        public int 政治
        {
            get { return 家宝情報.政治; }
            set { 家宝情報.政治 = value; }
        }

        public int 戦闘
        {
            get { return 家宝情報.戦闘; }
            set { 家宝情報.戦闘 = value; }
        }

        public int 智謀
        {
            get { return 家宝情報.智謀; }
            set { 家宝情報.智謀 = value; }
        }

        public int 南蛮
        {
            get { return 家宝情報.南蛮; }
            set { 家宝情報.南蛮 = value; }
        }

        public int 抑制
        {
            get { return 家宝情報.抑制; }
            set { 家宝情報.抑制 = value; }
        }

        public int 兵科効果
        {
            get { return 家宝情報.兵科効果; }
            set { 家宝情報.兵科効果 = value; }
        }

        public int 所有武将配列IX
        {
            get { return 家宝情報.所有武将配列IX; }
            set { 家宝情報.所有武将配列IX = value; }
        }
    }


    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の家宝情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.家宝情報.配列数; i++)
            {
                データ配列.Add(new BIND用の家宝情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }

    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用の家宝情報型.配列IX)].DefaultCellStyle.BackColor = Color.LightGray;
        }
        catch (Exception) { }
    }


}


