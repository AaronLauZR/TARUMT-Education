using System;
using System.Collections;
using System.Collections.Generic;
using System.Configuration;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Web_Assignment.admin
{
    public partial class Dashboard : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;

        protected void Page_Load(object sender, EventArgs e)
        {

            if (!IsPostBack)
            {
                retrieveTotalOrder();
                retrieveTotalProduct();
                retrieveTotalUser();
                retrieveTotalRole();
                retrieveOrderRecord();
            }

        }


        private void retrieveTotalOrder()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement

                con.Open();

                string strRetrieveOrder = "SELECT COUNT(*) AS TotalCount FROM [dbo].[Order]";
                SqlCommand cmd = new SqlCommand(strRetrieveOrder, con);

                int totalCount = (int)cmd.ExecuteScalar();

                con.Close();

                totalOrder.Text = totalCount.ToString();

            }

        }

        private void retrieveTotalProduct()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement

                con.Open();

                string strRetrieveProduct = "SELECT COUNT(*) AS TotalCount FROM [dbo].[Product]";
                SqlCommand cmd = new SqlCommand(strRetrieveProduct, con);

                int totalCount = (int)cmd.ExecuteScalar();

                con.Close();

                totalProduct.Text = totalCount.ToString();

            }

        }

        private void retrieveTotalUser()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement

                con.Open();

                string strRetrieveUser = "SELECT COUNT(*) AS TotalCount FROM [dbo].[User]";
                SqlCommand cmd = new SqlCommand(strRetrieveUser, con);

                int totalCount = (int)cmd.ExecuteScalar();

                con.Close();

                totalUser.Text = totalCount.ToString();

            }

        }


        private void retrieveTotalRole()
        {

            using (SqlConnection con = new SqlConnection(strCon))
            {
                //SQL Statement

                con.Open();

                string strRetrieveRole = "SELECT COUNT(*) AS TotalCount FROM [dbo].[Role]";
                SqlCommand cmd = new SqlCommand(strRetrieveRole, con);

                int totalCount = (int)cmd.ExecuteScalar();

                con.Close();

                totalRole.Text = totalCount.ToString();

            }

        }

        protected void retrieveOrderRecord()
        {
            using (SqlConnection con = new SqlConnection(strCon))
            {
                con.Open();
                SqlCommand cmd = new SqlCommand("select * from [dbo].[Order] o, [dbo].[User] u where o.userId = u.userId", con);
                SqlDataReader dr = cmd.ExecuteReader();
                if (dr.HasRows == true)
                {
                    GridViewOrder.DataSource = dr;
                    GridViewOrder.DataBind();
                    LabelNoData.Style.Add("display", "none");
                }
                else
                {
                    GridViewOrder.DataSource = dr;
                    GridViewOrder.DataBind();
                    LabelNoData.Style.Add("display", "block");
                }
            }

        }




    }
}