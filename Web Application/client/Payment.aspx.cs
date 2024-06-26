using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Web_Assignment.client
{
    public partial class Payment : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void btnPayNow_Click(object sender, EventArgs e)
        {
            paymentMessage.Style.Add("display", "block");
            disabledAll();
        }

        protected void ddlPaymentMethod_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (ddlPaymentMethod.SelectedIndex)
            {
                case 0:
                    displayOnlineBankingDetails();
                    break;
                case 1:
                    displayTouchNGoDetails();
                    break;
                default:
                    displayNonePaymentDetails();
                    break;

            }

        }

        private void displayOnlineBankingDetails()
        {

            olineBanking.Style.Add("display", "block");
            touchNGo.Style.Add("display", "none");
            //touchNGo.Visible = false;
            resetTextField();

        }

        private void displayTouchNGoDetails()
        {
            olineBanking.Style.Add("display", "none");
            touchNGo.Style.Add("display", "block");
            //olineBanking.Visible = false;
            //touchNGo.Visible = true;
            resetTextField();

        }

        private void displayNonePaymentDetails()
        {

            olineBanking.Style.Add("display", "none");
            touchNGo.Style.Add("display", "none");
            resetTextField();
        }

        private void disabledAll()
        {
            ddlPaymentMethod.Enabled = false;
            ddlBankType.Enabled = false;
            txtAccountNumber.Enabled = false;
            txtAccountPassword.Enabled = false;
            txtContactNumber.Enabled = false;
            txtPin.Enabled = false;
            btnPayNow.Enabled = false;

        }

        private void resetTextField()
        {
            txtAccountNumber.Text = string.Empty;
            txtAccountPassword.Text = string.Empty;
            txtContactNumber.Text = string.Empty;
            txtPin.Text = string.Empty;
        }


        protected void LinkButtonViewReceipt_Click(object sender, EventArgs e)
        {
            receiptModal.Style.Add("display", "block");
            paymentMessage.Style.Add("display", "none");
        }

        protected void btnConfirmInvoice_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/client/GameLibrary.aspx");
        }

        protected void LinkButtonClose_Click(object sender, EventArgs e)
        {
            Response.Redirect("~/client/GameLibrary.aspx");
        }
    }
}