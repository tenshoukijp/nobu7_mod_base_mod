using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System;

namespace 将星録;



public partial class 大名エディタ : 基本エディタ
{

    public 大名エディタ() : base()
    {
        this.Text = nameof(大名エディタ);
        dgv.CellClick += dgv_CellClick;
    }

    class BIND用の大名情報型
    {
        大名情報型 大名情報;
        public BIND用の大名情報型(int 大名配列IX)
        {
            大名情報 = new 大名情報型(大名配列IX);
        }
        public int 配列IX
        {
            get { return 大名情報.配列IX; }
        }

        public string 大名姓名
        {
            get
            {
                int iBushouID = 大名情報.大名武将配列IX;
                String strBushouName = "-";
                if (0 <= iBushouID && iBushouID < 最大数.武将情報.総配列数)
                {
                    var 武将情報 = new 武将情報型(iBushouID);
                    strBushouName = 武将情報.姓名;
                }
                return strBushouName;
            }
        }

        public int 大名武将配列IX
        {
            get { return 大名情報.大名武将配列IX; }
            set { 大名情報.大名武将配列IX = value; }
        }

        public int 居城配列IX
        {
            get { return 大名情報.居城配列IX; }
            set { 大名情報.居城配列IX = value; }
        }

        public int プレイヤ担当
        {
            get { return 大名情報.プレイヤ担当; }
            set { 大名情報.プレイヤ担当 = value; }
        }

        public int 家紋番号
        {
            get { return 大名情報.家紋番号; }
            set { 大名情報.家紋番号 = value; }
        }

        public int 旗番号
        {
            get { return 大名情報.旗番号; }
            set { 大名情報.旗番号 = value; }
        }

        public int 朝廷
        {
            get { return 大名情報.朝廷; }
            set { 大名情報.朝廷 = value; }
        }

        public int 朝敵
        {
            get { return 大名情報.朝敵; }
            set { 大名情報.朝敵 = value; }
        }

        public int 鍛冶
        {
            get { return 大名情報.鍛冶; }
            set { 大名情報.鍛冶 = value; }
        }

        public int 布教
        {
            get { return 大名情報.布教; }
            set { 大名情報.布教 = value; }
        }

        public int 援軍申込大名配列IX
        {
            get { return 大名情報.援軍申込大名配列IX; }
            set { 大名情報.援軍申込大名配列IX = value; }
        }

        public int 援軍申受大名配列IX
        {
            get { return 大名情報.援軍申受大名配列IX; }
            set { 大名情報.援軍申受大名配列IX = value; }
        }

        public int 鉄甲船
        {
            get { return 大名情報.鉄甲船; }
            set { 大名情報.鉄甲船 = value; }
        }
    }

    protected override void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        try
        {
            var 指揮武将IXcolumns = dgv.Columns["大名武将配列IX"];
            // 対象のセル
            if (e.ColumnIndex == 指揮武将IXcolumns.Index)
            {
                bindingSource.ResetBindings(false);
            }
        }
        catch (Exception) { }
    }

    BindingSource bindingSource = new();
    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の大名情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.大名情報.配列数; i++)
            {
                データ配列.Add(new BIND用の大名情報型(i));
            }

            bindingSource.DataSource = データ配列;
            dgv.DataSource = bindingSource;
        }
        catch (Exception) { }
    }

    DataGridViewButtonColumn buttonColumn;

    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns["配列IX"].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns["大名姓名"].DefaultCellStyle.BackColor = Color.Yellow;
            dgv.Columns["大名武将配列IX"].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns["居城配列IX"].DefaultCellStyle.BackColor = Color.DarkOrange;

            if (buttonColumn != null)
            {
                dgv.Columns.Remove(buttonColumn);
            }
            buttonColumn = new DataGridViewButtonColumn();
            buttonColumn.HeaderText = "外交関係";
            buttonColumn.Text = "編集";
            buttonColumn.UseColumnTextForButtonValue = true; // 列内の全てのセルに同じテキストを表示
            dgv.Columns.Add(buttonColumn);

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }

    private void dgv_CellClick(object sender, DataGridViewCellEventArgs e)
    {
        try
        {
            if (e.RowIndex >= 0 && e.ColumnIndex >= 0)
            {
                if (dgv.Columns[e.ColumnIndex] is DataGridViewButtonColumn && e.RowIndex < dgv.Rows.Count)
                {
                    // ボタンがクリックされたセルの処理
                    var IDCell = dgv[0, e.RowIndex];
                    int ID = (int)IDCell.Value;
                    // e.RowIndex に押されたボタンが属する行のインデックスが入っている
                    将星録.大名関係エディタ editor = new 将星録.大名関係エディタ(ID);
                    editor.ShowDialog();
                }
            }
        }
        catch (Exception) { }
    }

}
