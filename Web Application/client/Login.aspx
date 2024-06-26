<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Login.aspx.cs" Inherits="Web_Assignment.client.Login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <link rel="stylesheet" href="../css/account.css" />
    <title></title>
    <style type="text/css">
        .auto-style1 {
            width: 32%;
            margin-left: 50%;
        }

        .auto-style2 {
            text-align: right;
            width: 306px;
        }

        .auto-style3 {
            text-align: left;
        }

        .auto-style4 {
            width: 306px;
        }

        .auto-style5 {
            text-align: right;
        }
    </style>
</head>

<body>
    <form id="form1" runat="server">

        <img src="../img/logo.png" alt="LOGO" class="logo2" />

        <img src="../img/account/ufo-flying.png" alt="UFO" class="ufo2" />

        <br />
        <br />
        <br />
        <br />
        <br />
        <img src="../img/account/galaxy.png" alt="GALAXY" class="topic2" />

        <br />
        <br />
        <br />
        <br />
        <table class="auto-style1">
            <tr>
                <td id="label" class="auto-style2">Username :&nbsp;&nbsp; </td>
                <td class="auto-style3">
                    <asp:TextBox ID="enterusername" runat="server" class="box"></asp:TextBox></td>
            </tr>
            <tr>
                <td class="auto-style4"></td>
                <td>
                    <asp:Label class="errormessage" ID="incorrect" runat="server"></asp:Label>
                </td>
            </tr>
            <tr>
                <td id="label" class="auto-style2">Password :&nbsp;&nbsp; </td>
                <td class="auto-style3">
                    <asp:TextBox ID="enterpassword" runat="server" class="box" TextMode="Password"></asp:TextBox></td>
            </tr>
            <tr>
                <td class="auto-style4"></td>
                <td class="auto-style5">
                    <asp:HyperLink ID="forgetpass" runat="server" class="forget" NavigateUrl="~/client/ForgetPassword.aspx">Forget Password?</asp:HyperLink></td>
            </tr>
            <tr>
                <td class="auto-style4">&nbsp;</td>
                <td class="auto-style5">&nbsp;</td>
            </tr>
            <tr>
                <td class="auto-style4"></td>
                <td class="auto-style3">
                    <asp:Button ID="login" runat="server" Text="Login" class="submitbtn" OnClick="login_Click" /></td>
            </tr>
        </table>
        <br />
        <br />
        <br />
        <br />
        <br />
        <br />
        <br />
        <br />
        <br />
        <br />
        <br />
        <br />
        <p class="account2">
            Do not have account? 
        <asp:HyperLink ID="signin" runat="server" class="hyper" NavigateUrl="~/client/Register.aspx">Sign In</asp:HyperLink>
        </p>

    </form>
</body>
</html>
