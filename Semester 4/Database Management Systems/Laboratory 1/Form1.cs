using System.Data;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using Microsoft.Data.SqlClient;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        private SqlConnection databaseConnection;

        private SqlDataAdapter weaponTableAdapter;
        private SqlDataAdapter statusEffectTableAdapter;

        private DataSet databaseSet;

        private BindingSource weaponDataBinding;
        private BindingSource statusEffectDataBinding;

        string queryWeaponTable;
        string queryStatusEffectTable;

        string weaponTableName;
        string statusEffectTableName;

        string weaponId;
        string statusEffectRefferencedId;

        string statusId;

        public Form1()
        {
            InitializeComponent();

            databaseConnection = new SqlConnection(GetConnectionString());

            weaponTableName = "WEAPON";
            statusEffectTableName = "STATUS_EFFECT";

            weaponId = "id";
            statusEffectRefferencedId = "weapon_id";
            statusId = "id";

            queryWeaponTable = "SELECT * FROM " + weaponTableName;
            queryStatusEffectTable = "SELECT * FROM " + statusEffectTableName;

            databaseConnection.Open();

            weaponTableAdapter = new SqlDataAdapter(queryWeaponTable, databaseConnection);
            statusEffectTableAdapter = new SqlDataAdapter(queryStatusEffectTable, databaseConnection);

            weaponDataBinding = new BindingSource();

            databaseSet = new DataSet();

            SetUpGrids();

            databaseConnection.Close();
        }

        private void UpdateDataSet()
        {
            databaseSet.Clear();
            weaponTableAdapter.Fill(databaseSet, weaponTableName);
            statusEffectTableAdapter.Fill(databaseSet, statusEffectTableName);
        }

        private void SetUpGrids()
        {
            UpdateDataSet();

            databaseSet.Relations.Add("WEAPONSTATUS_EFFECT",
               databaseSet.Tables[weaponTableName].Columns[weaponId],
                   databaseSet.Tables[statusEffectTableName].Columns[statusEffectRefferencedId]);

            weaponDataBinding.DataSource = databaseSet.Tables[weaponTableName];
            statusEffectDataBinding = new BindingSource(weaponDataBinding, "WEAPONSTATUS_EFFECT");
            this.dataGridView1.DataSource = weaponDataBinding;
            this.dataGridView2.DataSource = statusEffectDataBinding;
        }

        private string GetConnectionString()
        {
            return "Data Source=CORA\\MSSQLSERVER01;" +
                "Initial Catalog=Video Game Inventory;Integrated Security=true;TrustServerCertificate=True";
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                statusEffectTableAdapter.InsertCommand = new SqlCommand("INSERT INTO " + statusEffectTableName + " (id, name, extra_damage, weapon_id) VALUES (@id, @name, @extra_damage, @weapon_id)", databaseConnection);

                int new_id = databaseSet.Tables[statusEffectTableName].AsEnumerable().Max(row => row.Field<int>(statusId)) + 1;

                statusEffectTableAdapter.InsertCommand.Parameters.Add("@id", SqlDbType.Int).Value = new_id;
                statusEffectTableAdapter.InsertCommand.Parameters.Add("@name", SqlDbType.VarChar).Value = textBox1.Text;
                statusEffectTableAdapter.InsertCommand.Parameters.Add("@extra_damage", SqlDbType.Int).Value = Int32.Parse(textBox2.Text);
                statusEffectTableAdapter.InsertCommand.Parameters.Add("@weapon_id", SqlDbType.Int).Value = ((DataRowView)weaponDataBinding.Current)[0];

                databaseConnection.Open();
                statusEffectTableAdapter.InsertCommand.ExecuteNonQuery();

                MessageBox.Show("Inserted successfully");
                UpdateDataSet();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                databaseConnection.Close();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                statusEffectTableAdapter.UpdateCommand = new SqlCommand("UPDATE " + statusEffectTableName + " SET name=@name, extra_damage=@extra_damage, weapon_id=@weapon_id WHERE id=@id", databaseConnection);

                statusEffectTableAdapter.UpdateCommand.Parameters.Add("@id", SqlDbType.Int).Value = ((DataRowView)statusEffectDataBinding.Current)[0];
                statusEffectTableAdapter.UpdateCommand.Parameters.Add("@name", SqlDbType.VarChar).Value = textBox1.Text;
                statusEffectTableAdapter.UpdateCommand.Parameters.Add("@extra_damage", SqlDbType.Int).Value = Int32.Parse(textBox2.Text);
                statusEffectTableAdapter.UpdateCommand.Parameters.Add("@weapon_id", SqlDbType.Int).Value = ((DataRowView)weaponDataBinding.Current)[0];

                databaseConnection.Open();
                statusEffectTableAdapter.UpdateCommand.ExecuteNonQuery();

                MessageBox.Show("Updated successfully");
                UpdateDataSet();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            finally
            {
                databaseConnection.Close();
            }
        }

        private void StatusEffectDataGridUpdate()
        {
            dataGridView2.ClearSelection();
            dataGridView2.Rows[statusEffectDataBinding.Position].Selected = true;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            statusEffectDataBinding.MoveNext();
            StatusEffectDataGridUpdate();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            statusEffectDataBinding.MovePrevious();
            StatusEffectDataGridUpdate();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult dialogueResult = MessageBox.Show("Are you sure?\n No undo after delete", "Confirm Deletion", MessageBoxButtons.YesNo);
            if (dialogueResult == DialogResult.Yes){
                statusEffectTableAdapter.DeleteCommand = new SqlCommand("DELETE FROM " + statusEffectTableName + " WHERE id=@id", databaseConnection);

                statusEffectTableAdapter.DeleteCommand.Parameters.Add("@id", SqlDbType.Int).Value = ((DataRowView)statusEffectDataBinding.Current)[0];

                try
                {
                    databaseConnection.Open();
                    statusEffectTableAdapter.DeleteCommand.ExecuteNonQuery();

                    MessageBox.Show("Deleted successfully");
                    UpdateDataSet();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                finally
                {
                    databaseConnection.Close();
                }
            }
            else
            {
                MessageBox.Show("Deletion Aborded");
            }
        }
    }
}
