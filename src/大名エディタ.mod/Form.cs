using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System;

namespace 将星録;

public class 大名エディタ : Form
{
    DataGridView dgv = new DataGridView();
    DataGridViewButtonColumn buttonColumn;
    List<大名情報型> 大名配列 = new();
    List<武将情報型> 武将配列 = new();

    public 大名エディタ()
    {
        try
        {
            create大名配列();

            setFormAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void create大名配列()
    {
        for (int i = 0; i < 将星録.最大数.大名情報.配列数; i++)
        {
            大名配列.Add(new 大名情報型(i));
        }

        for (int i = 0; i < 将星録.最大数.武将情報.総配列数; i++)
        {
            武将配列.Add(new 武将情報型(i));
        }
    }

    void setFormAttribute()
    {
        this.Text = "大名エディタ";
        this.Width = 900;
        this.Height = 800;
        this.StartPosition = FormStartPosition.CenterScreen;
        this.ShowIcon = false;

        this.KeyPreview = true;
        this.KeyDown += Form_KeyDown;
    }

    void Form_KeyDown(object sender, KeyEventArgs e)
    {
        if (e.KeyCode == Keys.F5)
        {
            dgv.Rows.Clear();
            dgv.Columns.Remove(buttonColumn);
            DgvDataImport();
        }
    }

    enum タイトル { 配列IX = 0, 大名姓名, 大名武将配列IX, 居城配列IX, プレイヤ担当, 家紋番号, 旗番号, 朝廷, 朝敵, 鍛冶, 布教, 援軍申込大名配列IX, 援軍申受大名配列IX, 鉄甲船 };
    void setDataGridAttribute()
    {
        try
        {
            dgv.Dock = DockStyle.Fill;
            dgv.AllowUserToAddRows = false;
            dgv.AllowUserToDeleteRows = false;

            string fontName = 将星録.アプリケーション.フォント.フォント名;
            dgv.DefaultCellStyle.Font = new System.Drawing.Font(fontName, 16, FontStyle.Regular, GraphicsUnit.Pixel);

            string[] names = Enum.GetNames(typeof(タイトル));
            for (int i = 0; i < names.Length; i++)
            {
                // 縦列のオブジェクトを作り
                DataGridViewTextBoxColumn dgvtbc = new DataGridViewTextBoxColumn();
                // タイトル文字列を設定
                dgvtbc.HeaderText = names[i];
                // グリッドビューに縦列として追加。
                dgv.Columns.Add(dgvtbc);
            }

            DgvDataImport();

            // データグリッドのセルを編集した時のイベントハンドラを登録する。
            dgv.DataError += dvg_DataError;
            dgv.CellValueChanged += dgv_CellValueChanged;
            dgv.CellClick += dgv_CellClick;

            // データグリッドビューをフォームに乗っける
            this.Controls.Add(dgv);
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
                    editor.Show();
                }
            }
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

    void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        try
        {
            var IDCell = dgv[0, e.RowIndex];
            int ID = (int)IDCell.Value;

            var 大名情報 = new 将星録.大名情報型(ID);
            // 対象のセル
            var cell = dgv[e.ColumnIndex, e.RowIndex];
            if (e.ColumnIndex == (int)タイトル.大名武将配列IX)
            {
                try
                {
                    大名情報.大名武将配列IX = (int)cell.Value;

                    update大名武将姓名(e, 大名情報);

                }
                catch (Exception)
                {
                    cell.Value = 大名情報.大名武将配列IX;

                    update大名武将姓名(e, 大名情報);

                }
            }
            else if (e.ColumnIndex == (int)タイトル.居城配列IX)
            {
                try
                {
                    大名情報.居城配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.居城配列IX;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.プレイヤ担当)
            {
                try
                {
                    大名情報.プレイヤ担当 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.プレイヤ担当;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.家紋番号)
            {
                try
                {
                    大名情報.家紋番号 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.家紋番号;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.旗番号)
            {
                try
                {
                    大名情報.旗番号 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.旗番号;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.朝廷)
            {
                try
                {
                    大名情報.朝廷 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.朝廷;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.朝敵)
            {
                try
                {
                    大名情報.朝敵 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.朝敵;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.鍛冶)
            {
                try
                {
                    大名情報.鍛冶 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.鍛冶;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.布教)
            {
                try
                {
                    大名情報.布教 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.布教;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.援軍申込大名配列IX)
            {
                try
                {
                    大名情報.援軍申込大名配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.援軍申込大名配列IX;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.援軍申受大名配列IX)
            {
                try
                {
                    大名情報.援軍申受大名配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.援軍申受大名配列IX;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.鉄甲船)
            {
                try
                {
                    大名情報.鉄甲船 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名情報.鉄甲船;
                }
            }
        }
        catch (Exception) { }
    }

    private void update大名武将姓名(DataGridViewCellEventArgs e, 大名情報型 大名情報)
    {
        try
        {
            int iBushouID = 大名情報.大名武将配列IX;
            String strBushouName = "-";
            if (0 <= iBushouID && iBushouID < 武将配列.Count)
            {
                strBushouName = 武将配列[iBushouID].姓名;
            }
            var nameCell = dgv[(int)タイトル.大名姓名, e.RowIndex];
            nameCell.Value = strBushouName;
        }
        catch (Exception) { }
    }

    void DgvDataImport()
    {
        try
        {
            dgv.Columns[(int)タイトル.配列IX].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.配列IX].ReadOnly = true;
            dgv.Columns[(int)タイトル.配列IX].DefaultCellStyle.BackColor = Color.LightGray;

            dgv.Columns[(int)タイトル.大名姓名].ValueType = typeof(string);
            dgv.Columns[(int)タイトル.大名姓名].ReadOnly = true;
            dgv.Columns[(int)タイトル.大名姓名].DefaultCellStyle.BackColor = Color.Yellow;

            dgv.Columns[(int)タイトル.大名武将配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns[(int)タイトル.居城配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;

            string[] names = Enum.GetNames(typeof(タイトル));
            for (int i = (int)タイトル.大名武将配列IX; i < names.Length; i++)
            {
                dgv.Columns[i].ValueType = typeof(int);
            }

            // 横列単位で足してゆく、
            foreach (var 大名 in 大名配列)
            {
                int iBushouID = 大名.大名武将配列IX;
                String strBushouName = "-";
                if (0 <= iBushouID && iBushouID < 武将配列.Count)
                {
                    strBushouName = 武将配列[iBushouID].姓名;
                }
                dgv.Rows.Add(
                  大名.配列IX,
                  strBushouName,
                  大名.大名武将配列IX,
                  大名.居城配列IX,
                  大名.プレイヤ担当,
                  大名.家紋番号,
                  大名.旗番号,
                  大名.朝廷,
                  大名.朝敵,
                  大名.鍛冶,
                  大名.布教,
                  大名.援軍申込大名配列IX,
                  大名.援軍申受大名配列IX,
                  大名.鉄甲船
                  );
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
}