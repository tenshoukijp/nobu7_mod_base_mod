using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using 将星録;
using 将星録.列挙.家宝;

namespace 将星録
{
    public class 家宝エディタ : Form
    {
        DataGridView dgv = new DataGridView();

        public 家宝エディタ()
        {
            setFormAttribute();
            setDataGridAttribute();
        }

        private void setFormAttribute()
        {
            this.Text = "家宝エディタ";
            this.Width = 900;
            this.Height = 800;
            this.StartPosition = FormStartPosition.CenterScreen;
            this.ShowIcon = false;
        }

        enum タイトル { 配列IX=0, 家宝名, 種類, 画像, 等級, 能力上昇, 政治, 戦闘, 智謀, 南蛮, 抑制, 兵科効果, 所有武将配列IX };
        private void setDataGridAttribute()
        {
            dgv.Dock = DockStyle.Fill;
            dgv.AllowUserToAddRows = false;
            dgv.AllowUserToDeleteRows = false;

            string fontName = 将星録.アプリケーション.フォント.フォント名;
            dgv.DefaultCellStyle.Font = new System.Drawing.Font(fontName, 16, FontStyle.Regular, GraphicsUnit.Pixel);


            string[] colTitleArray =
            {
                nameof(タイトル.配列IX),
                nameof(タイトル.家宝名),
                nameof(タイトル.種類),
                nameof(タイトル.画像),
                nameof(タイトル.等級),
                nameof(タイトル.能力上昇),
                nameof(タイトル.政治),
                nameof(タイトル.戦闘),
                nameof(タイトル.智謀),
                nameof(タイトル.南蛮),
                nameof(タイトル.抑制),
                nameof(タイトル.兵科効果),
                nameof(タイトル.所有武将配列IX)
            };

            for (int i = 0; i <colTitleArray.Length; i++)
            {
                // 縦列のオブジェクトを作り
                DataGridViewTextBoxColumn dgvtbc = new DataGridViewTextBoxColumn();
                // タイトル文字列を設定
                dgvtbc.HeaderText = colTitleArray[i];
                // グリッドビューに縦列として追加。
                dgv.Columns.Add(dgvtbc);
            }

            // 各カラムに天翔記のデータ(532人の武将の、名字、名前、政才、戦才、智才)を足してゆく
            DgvDataImport();

            // データグリッドのセルを編集した時のイベントハンドラを登録する。
            dgv.CellValueChanged += dgv_CellValueChanged;

            // データグリッドビューをフォームに乗っける
            this.Controls.Add(dgv);
        }

        private void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            // throw new NotImplementedException();
        }

        void DgvDataImport()
        {

            // 横列単位で足してゆく、index:0, 姓:1, 名:2, 政治:3 戦闘:4 智謀:5 の順番通り
            for (int i = 0; i < 将星録.最大数.家宝情報.配列数; i++)
            {
                var 家宝 = new 将星録.家宝情報型(i);
                dgv.Rows.Add(
                  家宝.配列IX,
                  家宝.家宝名,
                  家宝.種類,
                  家宝.画像,
                  家宝.等級,
                  家宝.能力上昇,
                  家宝.政治,
                  家宝.戦闘,
                  家宝.智謀,
                  家宝.南蛮,
                  家宝.抑制,
                  家宝.兵科効果,
                  家宝.所有武将配列IX
                  );
                dgv.Columns[(int)タイトル.配列IX].ReadOnly = true;
            }

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
    }
}