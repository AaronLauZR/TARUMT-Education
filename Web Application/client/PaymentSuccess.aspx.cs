using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

namespace Web_Assignment.client
{
    public partial class PaymentSuccess : System.Web.UI.Page
    {
        string connectionString = @"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=|DataDirectory|\Galaxy.mdf;Integrated Security=True;";
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                InsertData();
                ClearCart();
                Response.Redirect("~/client/GameLibraryTailWind.aspx");
            }
            //string email = Session["user"].ToString();
            // Get user data from the database
            using (SqlConnection con = new SqlConnection(connectionString))
            {
                //DataTable userData = GetUserData(con, email);
                //if (userData.Rows.Count > 0)
                //{
                    //DataRow userRow = userData.Rows[0];
                    // Insert the order into the database
                    //InsertOrder(con, userRow);
                    // Get the order ID from the database
                    //string orderId = GetOrderId(con, userRow["id"].ToString());
                    // Insert the order details into the database
                    //if (!string.IsNullOrEmpty(orderId))
                   // {
                     //   InsertOrderDetails(con, orderId);
                   // }
                //}
            }
        }


        private DataTable GetUserData(SqlConnection con, string email)
        {
            con.Open();
            SqlCommand cmd = con.CreateCommand();
            cmd.CommandType = CommandType.Text;
            cmd.CommandText = "SELECT * FROM [User] WHERE email = @email";
            cmd.Parameters.AddWithValue("@email", email);
            DataTable userData = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);
            da.Fill(userData);
            con.Close();
            return userData;
        }


        /*private void InsertOrder(SqlConnection con, DataRow userRow)
        {
            Guid newGuid = Guid.NewGuid();
            con.Open();
            string insertQuery = "INSERT INTO [Order] (orderDate, userID, orderId, amount) VALUES (@orderDate, @userId, @orderId, @amount)";
            using (SqlCommand com = new SqlCommand(insertQuery, con))
            {
                com.Parameters.Add(new SqlParameter("@orderDate", SqlDbType.DateTime)).Value = DateTime.Now;
                com.Parameters.Add(new SqlParameter("@userId", SqlDbType.NVarChar)).Value = newGuid;
                com.Parameters.Add(new SqlParameter("@orderId", SqlDbType.Int)).Value = newGuid;
                com.Parameters.Add(new SqlParameter("@amount", SqlDbType.Decimal)).Value = GetOrderTotal();
                com.ExecuteNonQuery();
            }
            con.Close();
        }*/

        private void InsertData()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                Guid newGuid = Guid.NewGuid();
                //SQL Statement
                string strAddOrder = "insert into [dbo].[Order] (orderDate, userID, amount) values (@orderDate, @userId, @amount)";
                decimal temp;
                Decimal.TryParse(Session["finaltotal"].ToString(), out temp);

                //Need sqlcommand to execute sql query
                SqlCommand cmd = new SqlCommand(strAddOrder, con);
                cmd.Parameters.AddWithValue("@orderDate", DateTime.Now);
                cmd.Parameters.AddWithValue("@userId", Session["UserId"].ToString());
                cmd.Parameters.AddWithValue("@amount", temp);
                int rowAffected = cmd.ExecuteNonQuery();
                con.Close();
                Response.Write("<script>alert('Success')</script>");
            }

        }

        private decimal GetOrderTotal()
        {
            if (Request.Cookies["aa"] != null)
            {
                string cookieValue = Request.Cookies["aa"].Value;
                string[] orders = cookieValue.Split('|');
                decimal total = 0;
                foreach (string order in orders)
                {
                    string[] orderDetails = order.Split(',');
                    if (orderDetails.Length < 5)
                    {
                        continue;
                    }
                    decimal price = decimal.Parse(orderDetails[2]);
                    int quantity = int.Parse(orderDetails[3]);
                    total += price * quantity;
                    total = 106;
                }
                return total;
            }
            return 0;
        }


        private string GetOrderId(SqlConnection con, string userId)
        {
            con.Open();
            SqlCommand cmd = con.CreateCommand();
            cmd.CommandType = CommandType.Text;
            cmd.CommandText = "SELECT TOP 1 * FROM [Order] WHERE userID = @userId ORDER BY id DESC";
            cmd.Parameters.AddWithValue("@userId", userId);
            DataTable orderIdData = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);
            da.Fill(orderIdData);
            if (orderIdData.Rows.Count == 0)
            {
                return null;
            }
            con.Close();
            return orderIdData.Rows[0]["id"].ToString();
        }

        private void InsertOrderDetails(SqlConnection con, string orderId)
        {
            if (Request.Cookies["aa"] == null)
            {
                return;
            }

            string cookieValue = Request.Cookies["aa"].Value;
            string[] orders = cookieValue.Split('|');
            foreach (string order in orders)
            {
                string[] orderDetails = order.Split(',');
                if (orderDetails.Length < 5)
                {
                    continue;
                }
                con.Open();
                SqlCommand cmd = con.CreateCommand();
                cmd.CommandType = CommandType.Text;
                cmd.CommandText = "INSERT INTO [OrderItem] VALUES (@orderId, @productId)";
                cmd.Parameters.AddWithValue("@orderId", orderId);
                cmd.Parameters.AddWithValue("@productId", orderDetails[0]);
                cmd.ExecuteNonQuery();
                con.Close();

                SqlCommand cmd2 = con.CreateCommand();
                cmd2.CommandType = CommandType.Text;
                cmd2.CommandText = "select top 1 * from [Order] where email='" + Session["user"].ToString() + "' order by id desc ";
                cmd2.ExecuteNonQuery();
                DataTable dt2 = new DataTable();
                SqlDataAdapter da2 = new SqlDataAdapter(cmd2);
                da2.Fill(dt2);
                foreach (DataRow dr2 in dt2.Rows)
                {
                    orderId = dr2["id"].ToString();
                }
            }
        }

        protected void ClearCart()
        {
            SqlConnection con = new SqlConnection(strCon);

            string strSelect = "DELETE FROM Cart WHERE userId = '" + Session["UserId"] + "'";

            SqlCommand cmd = new SqlCommand(strSelect, con);
            con.Open();

            cmd.ExecuteNonQuery();

            con.Close();
        }

        

    }
}




