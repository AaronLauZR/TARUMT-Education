using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Configuration;
using System.Data;

namespace Web_Assignment.client
{
    public partial class OrderCartTailWind : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                if(Session["userId"] == null)
                {
                    Response.Redirect("~/client/Login.aspx");
                }
                else
                {
                    if (checkHasRows())
                    {
                        displayProductInCart();
                        displayTotal();
                    }
                    else
                    {
                        Response.Write("<script>alert('Cart is empty!') </script>");

                        // Redirect to the current page
                        //Response.Redirect("~/client/Home.aspx");
                        Server.Transfer("~/client/Home.aspx");
                    }
                }
                
            }
        }

        protected void displayProductInCart()
        {
            SqlConnection con = new SqlConnection(strCon);
            //select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '" + Request.QueryString["id"] + "')
            //select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '7df4f68c-1f12-456e-b745-e3afc70184a9')
            string strSelect = "select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '"+ Session["UserId"]+ "')";

            SqlCommand cmd = new SqlCommand(strSelect, con);
            con.Open();
            SqlDataReader reader = cmd.ExecuteReader();

            if (reader.HasRows)
            {
                reader.Close();
                SqlDataAdapter sda = new SqlDataAdapter(strSelect, con);
                DataTable dt = new DataTable();
                sda.Fill(dt);
                Repeater1.DataSource = dt;
                Repeater1.DataBind();
            }
            con.Close();
        }

        protected Boolean checkHasRows()
        {
            Boolean gotRows = true;
            SqlConnection con = new SqlConnection(strCon);
            //select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '" + Request.QueryString["id"] + "')
            //select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '7df4f68c-1f12-456e-b745-e3afc70184a9')
            string strSelect = "select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '" + Session["UserId"] + "')";

            SqlCommand cmd = new SqlCommand(strSelect, con);
            con.Open();
            SqlDataReader reader = cmd.ExecuteReader();
            if (!reader.HasRows)
            {
                gotRows = false;
            }
            con.Close();
            return gotRows;
        }

        protected void btnRemove_Click(object sender, EventArgs e)
        {
            SqlConnection con = new SqlConnection(strCon);

            RepeaterItem item = (sender as LinkButton).Parent as RepeaterItem;
            Label ids = ((Label)item.FindControl("lblName")) as Label;

            string getId = "SELECT productId FROM Product WHERE name = @name";
            SqlCommand idcmd = new SqlCommand(getId, con);
            idcmd.Parameters.AddWithValue("@name", ids.Text);
            con.Open();
            object result = idcmd.ExecuteScalar();
            if (result != null)
            {
                string id = result.ToString();
                string delete = "DELETE FROM Cart WHERE productId = @id";
                SqlCommand cmd = new SqlCommand(delete, con);
                int productId = int.Parse(id);
                cmd.Parameters.AddWithValue("@id", id);
                cmd.ExecuteNonQuery();
            }
            con.Close();
            displayProductInCart();
            displayTotal();
        }

        protected decimal displayTotal()
        {
            SqlConnection con = new SqlConnection(strCon);
            //select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '7df4f68c-1f12-456e-b745-e3afc70184a9')
            string strSelect = "select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '" + Session["UserId"] +"')";
            SqlDataAdapter sda = new SqlDataAdapter(strSelect, con);
            DataTable dt = new DataTable();
            sda.Fill(dt);
            int nrow = dt.Rows.Count;
            int i = 0;
            decimal subtotal = 0;

            while (i < nrow)
            {
                subtotal += Convert.ToDecimal(dt.Rows[i]["price"].ToString());
                i += 1;
            }

            lblSubtotal.Text = "RM " + subtotal.ToString();
            lblTotal.Text = "RM " + subtotal.ToString();

            txtPromo.Text = "";
            lblDiscount.Text = "-RM 0.00";
            return subtotal;
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            string promocode = txtPromo.Text;
            decimal afterDiscount = 0;
            decimal beforeDiscount = displayTotal();
            decimal discount = 0;

            if (promocode == "ILUVWEB30")
            {
                // apply 30% discount
                discount = beforeDiscount * 0.3m;
                afterDiscount = beforeDiscount - discount;
                Response.Write("<script>alert('Promo code applied successfully!') </script>");

                txtPromo.Text = promocode;
                lblDiscount.Text = "-RM " + Math.Round(discount, 2);
                lblTotal.Text = "RM " + Math.Round(afterDiscount, 2);
            }
            else
            {
                Response.Write("<script>alert('Invalid promo code') </script>");
            }

        }

        protected void btnCheckout_Click(object sender, EventArgs e)
        {
            string originalPriceText = lblTotal.Text;
            string toRemove = "RM ";

            string priceValue = originalPriceText.Replace(toRemove, "");
            Session["buyTotal"] = priceValue;
            Response.Redirect("~/client/PaymentTailwind.aspx");
        }
    }
}