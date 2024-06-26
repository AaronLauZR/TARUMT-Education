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
    public partial class PaymentTailwind : System.Web.UI.Page
    {
        string strCon = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                showProduct();
                displayTotal();
            }
        }

        protected void showProduct()
        {
            SqlConnection con = new SqlConnection(strCon);
            //select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '" + Request.QueryString["id"] + "')
            //select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '7df4f68c-1f12-456e-b745-e3afc70184a9')
            string strSelect = "select * from Product p where p.productId IN(select c.productId from Cart c where c.userId= '" + Session["UserId"] + "')";
            SqlDataAdapter sda = new SqlDataAdapter(strSelect, con);
            DataTable dt = new DataTable();
            sda.Fill(dt);
            Repeater1.DataSource = dt;
            Repeater1.DataBind();
        }

        protected void displayTotal()
        {
            lblFullPrice.Text = "RM " + (string)Session["buyTotal"];
        }

        protected void btnPayNow_Click(object sender, EventArgs e)
        {
            //paymentMessage.Style.Add("display", "block");
            disabledAll();
        }

        private void disabledAll()
        {
            ddlBankType.Enabled = false;
            txtAccountNumber.Enabled = false;
            txtAccountPassword.Enabled = false;
            btnPay.Enabled = false;
        }

        private void resetTextField()
        {
            txtAccountNumber.Text = string.Empty;
            txtAccountPassword.Text = string.Empty;
        }


        protected void LinkButtonViewReceipt_Click(object sender, EventArgs e)
        {
            //receiptModal.Style.Add("display", "block");
            //paymentMessage.Style.Add("display", "none");
        }

        protected void btnConfirmInvoice_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/client/GameLibrary.aspx");
        }

        protected void LinkButtonClose_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/client/GameLibrary.aspx");
        }

        protected void btnPay_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/client/PaymentGateway.aspx");
        }
    }
}