using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System;
using 将星録.最大数;

namespace 将星録;

public class ユニットエディタ : Form
{
    DataGridView dgv = new DataGridView();
    List<ユニット情報型> ユニット配列 = new();
    List<武将情報型> 武将配列 = new();

    public ユニットエディタ()
    {
        try
        {
            createユニット配列();

            setFormAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void createユニット配列()
    {
        for (int i = 0; i < 将星録.最大数.ユニット情報.配列数; i++)
        {
            ユニット配列.Add(new ユニット情報型(i));
        }

        for (int i = 0; i < 将星録.最大数.武将情報.総配列数; i++)
        {
            武将配列.Add(new 武将情報型(i));
        }
    }

    void setFormAttribute()
    {
        this.Text = "ユニットエディタ";
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
            DgvDataImport();
        }
    }

    enum タイトル { 配列IX = 0, 指揮武将姓名, 指揮武将配列IX, 所属城配列IX, 種別, 目的, 大砲, 鉄甲船, 第１部隊兵数, 第１部隊兵種, 第１部隊混乱, 第１部隊陣形位置, 第２部隊兵数, 第２部隊兵種, 第２部隊混乱, 第２部隊陣形位置, 第３部隊兵数, 第３部隊兵種, 第３部隊混乱, 第３部隊陣形位置, 第４部隊兵数, 第４部隊兵種, 第４部隊混乱, 第４部隊陣形位置, 第５部隊兵数, 第５部隊兵種, 第５部隊混乱, 第５部隊陣形位置, 輸送金銭, 輸送兵糧, 輸送軍馬, 輸送鉄砲, 輸送兵士, 輸送大砲, 現在Ｘ座標, 現在Ｙ座標, 後ユニット配列IX };
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

            // データグリッドビューをフォームに乗っける
            this.Controls.Add(dgv);
        }
        catch (Exception) { }
    }

    // 誤った型データを入れた場合は、元の値へと戻すようにする。
    void dvg_DataError(object sender, DataGridViewDataErrorEventArgs e)
    {
        e.Cancel = false;
    }

    void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        try
        {
            var IDCell = dgv[0, e.RowIndex];
            int ID = (int)IDCell.Value;

            var ユニット情報 = new 将星録.ユニット情報型(ID);
            // 対象のセル
            var cell = dgv[e.ColumnIndex, e.RowIndex];
            if (e.ColumnIndex == (int)タイトル.指揮武将配列IX)
            {
                try
                {
                    ユニット情報.指揮武将配列IX = (int)cell.Value;

                    updateユニット武将姓名(e, ユニット情報);

                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.指揮武将配列IX;

                    updateユニット武将姓名(e, ユニット情報);

                }
            }
            else if (e.ColumnIndex == (int)タイトル.所属城配列IX)
            {
                try
                {
                    ユニット情報.所属城配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.所属城配列IX;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.種別)
            {
                try
                {
                    ユニット情報.種別 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.種別;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.目的)
            {
                try
                {
                    ユニット情報.目的 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.目的;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.大砲)
            {
                try
                {
                    ユニット情報.大砲 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.大砲;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.鉄甲船)
            {
                try
                {
                    ユニット情報.鉄甲船 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.鉄甲船;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第１部隊兵種)
            {
                try
                {
                    ユニット情報.第１部隊兵種 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第１部隊兵種;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第１部隊兵数)
            {
                try
                {
                    ユニット情報.第１部隊兵数 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第１部隊兵数;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第１部隊混乱)
            {
                try
                {
                    ユニット情報.第１部隊混乱 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第１部隊混乱;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第１部隊陣形位置)
            {
                try
                {
                    ユニット情報.第１部隊陣形位置 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第１部隊陣形位置;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第２部隊兵種)
            {
                try
                {
                    ユニット情報.第２部隊兵種 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第２部隊兵種;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第２部隊兵数)
            {
                try
                {
                    ユニット情報.第２部隊兵数 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第２部隊兵数;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第２部隊混乱)
            {
                try
                {
                    ユニット情報.第２部隊混乱 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第２部隊混乱;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第２部隊陣形位置)
            {
                try
                {
                    ユニット情報.第２部隊陣形位置 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第２部隊陣形位置;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第３部隊兵種)
            {
                try
                {
                    ユニット情報.第３部隊兵種 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第３部隊兵種;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第３部隊兵数)
            {
                try
                {
                    ユニット情報.第３部隊兵数 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第３部隊兵数;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第３部隊混乱)
            {
                try
                {
                    ユニット情報.第３部隊混乱 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第３部隊混乱;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第３部隊陣形位置)
            {
                try
                {
                    ユニット情報.第３部隊陣形位置 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第３部隊陣形位置;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第４部隊兵種)
            {
                try
                {
                    ユニット情報.第４部隊兵種 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第４部隊兵種;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第４部隊兵数)
            {
                try
                {
                    ユニット情報.第４部隊兵数 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第４部隊兵数;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第４部隊混乱)
            {
                try
                {
                    ユニット情報.第４部隊混乱 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第４部隊混乱;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第４部隊陣形位置)
            {
                try
                {
                    ユニット情報.第４部隊陣形位置 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第４部隊陣形位置;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第５部隊兵種)
            {
                try
                {
                    ユニット情報.第５部隊兵種 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第５部隊兵種;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第５部隊兵数)
            {
                try
                {
                    ユニット情報.第５部隊兵数 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第５部隊兵数;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第５部隊混乱)
            {
                try
                {
                    ユニット情報.第５部隊混乱 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第５部隊混乱;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.第５部隊陣形位置)
            {
                try
                {
                    ユニット情報.第５部隊陣形位置 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.第５部隊陣形位置;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.輸送金銭)
            {
                try
                {
                    ユニット情報.輸送金銭 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.輸送金銭;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.輸送兵糧)
            {
                try
                {
                    ユニット情報.輸送兵糧 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.輸送兵糧;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.輸送軍馬)
            {
                try
                {
                    ユニット情報.輸送軍馬 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.輸送軍馬;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.輸送鉄砲)
            {
                try
                {
                    ユニット情報.輸送鉄砲 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.輸送鉄砲;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.輸送兵士)
            {
                try
                {
                    ユニット情報.輸送兵士 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.輸送兵士;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.輸送大砲)
            {
                try
                {
                    ユニット情報.輸送大砲 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.輸送大砲;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.後ユニット配列IX)
            {
                try
                {
                    ユニット情報.後ユニット配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = ユニット情報.後ユニット配列IX;
                }
            }

        }
        catch (Exception) { }

    }

    private void updateユニット武将姓名(DataGridViewCellEventArgs e, ユニット情報型 ユニット情報)
    {
        try
        {
            int iBushouID = ユニット情報.指揮武将配列IX;
            String strBushouName = "-";
            if (0 <= iBushouID && iBushouID < 武将配列.Count)
            {
                strBushouName = 武将配列[iBushouID].姓名;
            }
            var nameCell = dgv[(int)タイトル.指揮武将姓名, e.RowIndex];
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

            dgv.Columns[(int)タイトル.指揮武将姓名].ValueType = typeof(string);
            dgv.Columns[(int)タイトル.指揮武将姓名].ReadOnly = true;
            dgv.Columns[(int)タイトル.指揮武将姓名].DefaultCellStyle.BackColor = Color.Yellow;

            dgv.Columns[(int)タイトル.指揮武将配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns[(int)タイトル.所属城配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns[(int)タイトル.現在Ｘ座標].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.現在Ｘ座標].ReadOnly = true;
            dgv.Columns[(int)タイトル.現在Ｘ座標].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[(int)タイトル.現在Ｙ座標].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.現在Ｙ座標].ReadOnly = true;
            dgv.Columns[(int)タイトル.現在Ｙ座標].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[(int)タイトル.後ユニット配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;


            string[] names = Enum.GetNames(typeof(タイトル));
            for (int i = (int)タイトル.指揮武将配列IX; i < names.Length; i++)
            {
                dgv.Columns[i].ValueType = typeof(int);
            }

            // 横列単位で足してゆく、
            foreach (var ユニット in ユニット配列)
            {
                int iBushouID = ユニット.指揮武将配列IX;
                String strBushouName = "-";
                if (0 <= iBushouID && iBushouID < 武将配列.Count)
                {
                    strBushouName = 武将配列[iBushouID].姓名;
                }


                dgv.Rows.Add(
                    ユニット.配列IX,
                    strBushouName,
                    ユニット.指揮武将配列IX,
                    ユニット.所属城配列IX,
                    ユニット.種別,
                    ユニット.目的,
                    ユニット.大砲,
                    ユニット.鉄甲船,
                    ユニット.第１部隊兵数,
                    ユニット.第１部隊兵種,
                    ユニット.第１部隊混乱,
                    ユニット.第１部隊陣形位置,
                    ユニット.第２部隊兵数,
                    ユニット.第２部隊兵種,
                    ユニット.第２部隊混乱,
                    ユニット.第２部隊陣形位置,
                    ユニット.第３部隊兵数,
                    ユニット.第３部隊兵種,
                    ユニット.第３部隊混乱,
                    ユニット.第３部隊陣形位置,
                    ユニット.第４部隊兵数,
                    ユニット.第４部隊兵種,
                    ユニット.第４部隊混乱,
                    ユニット.第４部隊陣形位置,
                    ユニット.第５部隊兵数,
                    ユニット.第５部隊兵種,
                    ユニット.第５部隊混乱,
                    ユニット.第５部隊陣形位置,
                    ユニット.輸送金銭,
                    ユニット.輸送兵糧,
                    ユニット.輸送軍馬,
                    ユニット.輸送鉄砲,
                    ユニット.輸送兵士,
                    ユニット.輸送大砲,
                    ユニット.現在Ｘ座標,
                    ユニット.現在Ｙ座標,
                    ユニット.後ユニット配列IX
                    );
            }

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }
}