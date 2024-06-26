<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ForgetPassword.aspx.cs" Inherits="Web_Assignment.client.ForgetPassword" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <link rel="stylesheet" href="../css/forgetpassword.css" />
    <title></title>
    <style type="text/css">
        .auto-style1 {
            text-align: right;
            width: 306px;
        }

        .auto-style2 {
            text-align: left;
        }
        .auto-style3 {
            width: 306px;
        }
        .auto-style4 {
            text-align: center;
        }
    </style>
</head>

<body>
    <form id="form1" runat="server">
        <img src="../img/account/ufo-flying.png" alt="UFO" class="ufo" />
        <br /><br /><br /><br /><br />
        <img src="../img/account/galaxy.png" alt="GALAXY" class="topic" />
        <br /><br /><br />
        <table>
            <tr>
                <td class="auto-style1">
                    <asp:Label class="forglabel" ID="forgetusername" runat="server">Username :&nbsp; &nbsp; </asp:Label></td>
                <td class="auto-style2">
                    <asp:TextBox ID="forgusername" runat="server" class="box"></asp:TextBox></td>
            </tr>
            <tr>
                <td class="auto-style1">
                    &nbsp;</td>
                <td class="auto-style2">
                    &nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style1">
                    <asp:Label class="forglabel" ID="forgetemail" runat="server">Email :&nbsp; &nbsp; </asp:Label></td>
                <td class="auto-style2">
                    <asp:TextBox ID="forgemail" runat="server" class="box"></asp:TextBox></td>
            </tr>
            <tr>
                <td class="auto-style3">&nbsp;</td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style4" colspan="2">
                    <asp:Button class="submitbtn" ID="Button1" runat="server" Text="Check Password" OnClick="Button1_Click" />
                </td>
            </tr>
            <tr>
                <td class="auto-style3">&nbsp;</td>
                <td>
                    &nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style3">&nbsp;</td>
                <td> &nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style4" colspan="2">
                    <asp:Label ID="message" runat="server" Text="Please enter your username and email."></asp:Label>
                </td>
            </tr>
        </table>
        <br /><br /><br /><br /><br /><br /><br /><br /><br />
        <p class="account">
            Already found account? 
        <asp:HyperLink ID="signin" runat="server" class="hyper" NavigateUrl="~/client/Login.aspx">Sign In</asp:HyperLink>
        </p>
    </form>
</body>
</html>
