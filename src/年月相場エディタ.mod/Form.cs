using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;



public partial class 年月相場エディタ : 基本エディタ
{

    public 年月相場エディタ() : base()
    {
        this.Text = nameof(年月相場エディタ);
    }

    class BIND用の年月相場情報型
    {
        年月情報型 年月情報 = new();
        相場情報型 相場情報 = new();


        public BIND用の年月相場情報型()
        {
        }

        public int 年
        {
            get { return 年月情報.年; }
            set { 年月情報.年 = value; }
        }

        public int 月
        {
            get { return 年月情報.月; }
            set { 年月情報.月 = value; }
        }

        public int 兵糧
        {
            get { return 相場情報.兵糧; }
            set { 相場情報.兵糧 = value; }
        }

        public int 軍馬
        {
            get { return 相場情報.軍馬; }
            set { 相場情報.軍馬 = value; }
        }

        public int 鉄砲
        {
            get { return 相場情報.鉄砲; }
            set { 相場情報.鉄砲 = value; }
        }
    }

    // 誤った型データを入れた場合は、元の値へと戻すようにする。
    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の年月相場情報型> データ配列 = new();
            データ配列.Add(new BIND用の年月相場情報型());

            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }

    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}

