using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;



public partial class 城エディタ : 基本エディタ
{
    public 城エディタ() : base()
    {
        this.Text = nameof(城エディタ);
    }

    class BIND用の城情報型
    {
        城情報型 城情報;
        public BIND用の城情報型(int 城配列IX)
        {
            城情報 = new 城情報型(城配列IX);
        }

        public int 配列IX
        {
            get { return 城情報.配列IX; }
        }

        public string 城名
        {
            get { return 城情報.城名; }
            set { 城情報.城名 = value; }
        }

        public string 城称
        {
            get { return 城情報.城称; }
        }

        public int 籠城番号
        {
            get { return 城情報.籠城番号; }
            set { 城情報.籠城番号 = value; }
        }

        public int 所属大名配列IX
        {
            get { return 城情報.所属大名配列IX; }
            set { 城情報.所属大名配列IX = value; }
        }

        public int 城主武将配列IX
        {
            get { return 城情報.城主武将配列IX; }
            set { 城情報.城主武将配列IX = value; }
        }

        public int 規模
        {
            get { return 城情報.規模; }
            set { 城情報.規模 = value; }
        }

        public int 防御
        {
            get { return 城情報.防御; }
            set { 城情報.防御 = value; }
        }

        public int 防御MAX
        {
            get { return 城情報.防御MAX; }
        }

        public int 兵数
        {
            get { return 城情報.兵数; }
            set { 城情報.兵数 = value; }
        }

        public int 負傷兵数
        {
            get { return 城情報.負傷兵数; }
            set { 城情報.負傷兵数 = value; }
        }

        public int 金銭
        {
            get { return 城情報.金銭; }
            set { 城情報.金銭 = value; }
        }

        public int 兵糧
        {
            get { return 城情報.兵糧; }
            set { 城情報.兵糧 = value; }
        }

        public int 軍馬
        {
            get { return 城情報.軍馬; }
            set { 城情報.軍馬 = value; }
        }

        public int 鉄砲
        {
            get { return 城情報.鉄砲; }
            set { 城情報.鉄砲 = value; }
        }

        public int 大砲
        {
            get { return 城情報.大砲; }
            set { 城情報.大砲 = value; }
        }

        public int 商人
        {
            get { return 城情報.商人; }
            set { 城情報.商人 = value; }
        }

        public int 委任状態
        {
            get { return 城情報.委任状態; }
            set { 城情報.委任状態 = value; }
        }

        public int 委任攻撃
        {
            get { return 城情報.委任攻撃; }
            set { 城情報.委任攻撃 = value; }
        }

        public int 委任攻撃目標城配列IX
        {
            get { return 城情報.委任攻撃目標城配列IX; }
            set { 城情報.委任攻撃目標城配列IX = value; }
        }

        public int 開始ユニット配列IX
        {
            get { return 城情報.開始ユニット配列IX; }
            set { 城情報.開始ユニット配列IX = value; }
        }

        public int 後城配列IX
        {
            get { return 城情報.後城配列IX; }
            set { 城情報.後城配列IX = value; }
        }
    }

    // 誤った型データを入れた場合は、元の値へと戻すようにする。
    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の城情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.城情報.配列数; i++)
            {
                データ配列.Add(new BIND用の城情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }
    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns["配列IX"].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns["城称"].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns["防御MAX"].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns["所属大名配列IX"].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns["城主武将配列IX"].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns["開始ユニット配列IX"].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns["後城配列IX"].DefaultCellStyle.BackColor = Color.DarkOrange;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}

