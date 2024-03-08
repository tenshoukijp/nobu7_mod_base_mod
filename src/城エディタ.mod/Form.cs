using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;

public partial class 城エディタ : Form
{

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
}

public partial class 城エディタ : Form
{
    DataGridView dgv = new DataGridView();

    public 城エディタ()
    {
        try
        {
            setFormAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void setFormAttribute()
    {
        this.Text = "城エディタ";
        this.Width = 900;
        this.Height = 800;
        this.StartPosition = FormStartPosition.CenterScreen;
        this.ShowIcon = false;

        this.KeyPreview = true;
        this.KeyDown += Form_KeyDown;
    }

    void Form_KeyDown(object sender, KeyEventArgs e)
    {
        if (e.KeyCode == Keys.F5 && ActiveForm == this)
        {
            dgv.Rows.Clear();
            dvg_DataBinding();
        }
    }

    void setDataGridAttribute()
    {
        try
        {
            dgv.Dock = DockStyle.Fill;
            dgv.AllowUserToAddRows = false;
            dgv.AllowUserToDeleteRows = false;

            string fontName = 将星録.アプリケーション.フォント.フォント名;
            dgv.DefaultCellStyle.Font = new System.Drawing.Font(fontName, 16, FontStyle.Regular, GraphicsUnit.Pixel);

            // データグリッドのセルを編集した時のイベントハンドラを登録する。
            dgv.DataError += dvg_DataError;
            dgv.DataBindingComplete += dvg_DataBindingComplete;

            dvg_DataBinding();

            // データグリッドビューをフォームに乗っける
            this.Controls.Add(dgv);

        }
        catch (Exception) { }
    }

    private void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
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

    // 誤った型データを入れた場合は、元の値へと戻すようにする。
    void dvg_DataError(object sender, DataGridViewDataErrorEventArgs e)
    {
        try
        {
            e.Cancel = false;
        }
        catch (Exception) { }
    }

    void dvg_DataBinding()
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
}

